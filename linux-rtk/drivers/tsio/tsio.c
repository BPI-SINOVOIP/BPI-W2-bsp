#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/delay.h>
#include <linux/major.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <linux/io.h>
#include <linux/slab.h>
#include <linux/dma-mapping.h>
#include "tsio.h"
#include "tsio_dev.h"
#include "tsio_dbg.h"

#define rtd_inl(offset)             readl(offset)
#define rtd_outl(offset,val)        writel(val, offset)

struct class * tsio_dev_class = NULL;
static char * p_high_fifo = NULL;
static char * p_middle_fifo = NULL;
static char * p_low_fifo = NULL;
static unsigned long hfifo_phy_addr = 0, mfifo_phy_addr = 0;
static dma_addr_t phy_high_fifo;
static dma_addr_t phy_middle_fifo;
static struct device *tsio_dev;

static unsigned long bytes_to_long(unsigned char* p_data)
{
    unsigned long l = 0;
    
    l = ((p_data[3]<<24) | (p_data[2]<<16) | (p_data[1]<<8) | p_data[0]);
    return l;
}

static int tsio_send_cc(char * cc_arr, unsigned int data_len) 
{
    unsigned int data = 0, round = 0, i;
    unsigned char * cc_ptr = (unsigned char *)cc_arr;
    int rx_timeout = 0, rx_err = 0, ret = 0;
    unsigned long cc_data;
    void __iomem *tsio_reg_base = ioremap(TSIO_REG_BASE, 0x400);

    rtd_outl(tsio_reg_base + TSIO_CCTX_IDX, 0x0);
    
    round = data_len/4;
    if((data_len%4) != 0) {
        round++;
    }

    for( i = 0; i < round; i++) {
        data = bytes_to_long(cc_ptr);
        rtd_outl(tsio_reg_base + TSIO_CCTX, data);
	cc_ptr += 4;
    }

    data_len |= TSIO_START_TX;
    rtd_outl(tsio_reg_base + TSIO_CCTX_CRTL, data_len);

    i = 0;
    while(!(rtd_inl(tsio_reg_base + TSIO_CCTX_CRTL)&TSIO_TX_DONE)) {
        if(i > 20) {
            break;
        }

        udelay(50);
	i++;
    }
    rtd_outl(tsio_reg_base + TSIO_CCTX_CRTL, 0x0);

    i = 0;
    while(!(rtd_inl(tsio_reg_base + TSIO_CCRX_CRTL)&TSIO_RX_DONE)) {
        if(rtd_inl(tsio_reg_base + TSIO_CCRX_CRTL) & TSIO_RX_ERR) {
            rx_err = 1;
            break;
        }

        if(i > 20) {
            rx_timeout = 1;
            break;
        }
        udelay(50);
	i++;
    }

    rtd_outl(tsio_reg_base + TSIO_CCRX_IDX, 0x0);
    rtd_outl(tsio_reg_base + TSIO_CCRX_CRTL, 0x0);
    
    if(rx_err == 1 || rx_timeout == 1) {
        ret = 1;
    } else {
        ret = 0;

        for( i = 0; i < round; i++) {
            cc_data = rtd_inl(tsio_reg_base + TSIO_CCRX);
            TSIO_TRACE("TSIO_CCRX(0x%x): 0x%x\n", tsio_reg_base + TSIO_CCRX, cc_data);
        }
    }

    iounmap(tsio_reg_base);

    return ret;
}

static int tsio_start_descriptor(unsigned char file_mode){
    int i, ret = 1;
    unsigned int wptr_fifo, wptr_reg = 0, rptr_reg = 0;
    void __iomem *tsio_reg_base = ioremap(TSIO_REG_BASE, 0x400);

    if(file_mode == TSIO_CCP_TS) {
        wptr_reg = tsio_reg_base + TSIO_FIFO_M_WPTR;
        rptr_reg = tsio_reg_base + TSIO_FIFO_M_RPTR;
    } else {
        wptr_reg = tsio_reg_base + TSIO_FIFO_H_WPTR;
        rptr_reg = tsio_reg_base + TSIO_FIFO_H_RPTR;
    }

    //wptr_fifo = rtd_inl(wptr_reg);
    //wptr_fifo += 0x10;
    //rtd_outl(wptr_reg, wptr_fifo);

    TSIO_TRACE("tsio start des!\n");
    wptr_fifo = rtd_inl(tsio_reg_base + TSIO_FIFO_H_WPTR);
    wptr_fifo += 0x10;
    rtd_outl(tsio_reg_base + TSIO_FIFO_H_WPTR, wptr_fifo);

    i = 0;
    while(rtd_inl(tsio_reg_base + TSIO_FIFO_H_WPTR) != rtd_inl(tsio_reg_base + TSIO_FIFO_H_RPTR)) {
        if(rtd_inl(tsio_reg_base + TSIO_EXE_INFO) & (1<<7)) {
            ret = 0;
            TSIO_TRACE("tsio lost sync! \n");
            break;
        }

        if(i >= 4000) { //2000
            ret = 0;
            TSIO_TRACE("tsio time out! \n");
            break;
        }
        
        udelay(500);
        i++;
    }

    if(1) {
        TSIO_TRACE("TSIO_LINK_STATE: 0x%x\n", rtd_inl(tsio_reg_base + TSIO_LINK_STATE));
        TSIO_TRACE("TSIO_FIFO_H_RPTR: 0x%x\n", rtd_inl(tsio_reg_base + TSIO_FIFO_H_RPTR));
        TSIO_TRACE("TSIO_FIFO_H_WPTR: 0x%x\n", rtd_inl(tsio_reg_base + TSIO_FIFO_H_WPTR));
        TSIO_TRACE("TSIO_FIFO_M_RPTR: 0x%x\n", rtd_inl(tsio_reg_base + TSIO_FIFO_M_RPTR));
        TSIO_TRACE("TSIO_FIFO_M_WPTR: 0x%x\n", rtd_inl(tsio_reg_base + TSIO_FIFO_M_WPTR));
        TSIO_TRACE("TSIO_EXE_INFO: 0x%x\n", rtd_inl(tsio_reg_base + TSIO_EXE_INFO));
        TSIO_TRACE("DESP_EXE_INT: 0x%x\n", rtd_inl(tsio_reg_base + DESP_EXE_INT));
    }

    iounmap(tsio_reg_base);
    return ret;
}

static void tsio_set_descriptor(unsigned char file_mode, unsigned char srv_id, unsigned long phy_src_addr, unsigned long phy_dst_addr, unsigned long data_len){
    char * des_addr = NULL;
    unsigned long wptr_fifo, rptr_fifo, des_data_len;
    unsigned char setting[4];
    void __iomem *tsio_reg_base = ioremap(TSIO_REG_BASE, 0x400);

    memset(setting, 0, sizeof(setting));

    if(file_mode == TSIO_CCP_TS) {
        des_addr = p_middle_fifo;
    } else {
        des_addr = p_high_fifo;
    }

    if(des_addr == NULL) return;

    wptr_fifo = rtd_inl(tsio_reg_base + TSIO_FIFO_H_WPTR);
    rptr_fifo = rtd_inl(tsio_reg_base + TSIO_FIFO_H_RPTR);

    if(wptr_fifo == rptr_fifo) {
	if(file_mode == TSIO_TS || file_mode == TSIO_CCP_TS) {
            des_data_len = data_len & 0x01FFFFFF;
            setting[0] = (des_data_len & 0x000000FF);
            setting[1] = ((des_data_len & 0x0000FF00)>>8);
            setting[2] = ((des_data_len & 0x00FF0000)>>16);
            setting[3] = ((srv_id & 0x3f)<<2) | (des_data_len>>24);
            setting[3] |= 0x02;

            memset(((char *)des_addr), 0, 4);
            memcpy(((char *)des_addr)+4, &phy_src_addr, 4);
            memcpy(((char *)des_addr)+8, setting, 4);
            memset(((char *)des_addr)+12, 0, 4);
	} else if(file_mode == TSIO_BLK){
            des_data_len = data_len & 0x01FFFFFF;
            setting[0] = (des_data_len & 0x000000FF);
            setting[1] = ((des_data_len & 0x0000FF00)>>8);
            setting[2] = ((des_data_len & 0x00FF0000)>>16);
            setting[3] = ((srv_id & 0x3f)<<2) | (des_data_len>>24);

            memcpy(((char *)des_addr), &phy_dst_addr, 4);
            memcpy(((char *)des_addr)+4, &phy_src_addr, 4);
            memcpy(((char *)des_addr)+8, setting, 4);
            memset(((char *)des_addr)+12, 0, 4);
	    TSIO_TRACE("tsio_set_descriptor TSIO_BLK\n");
        }
    }

    TSIO_TRACE("Dump des_addr: 0x%08x\n", des_addr);
    TSIO_TRACE("%02x %02x %02x %02x \n", des_addr[0], des_addr[1], des_addr[2], des_addr[3]);
    TSIO_TRACE("%02x %02x %02x %02x \n", des_addr[4], des_addr[5], des_addr[6], des_addr[7]);
    TSIO_TRACE("%02x %02x %02x %02x \n", des_addr[8], des_addr[9], des_addr[10], des_addr[11]);
    TSIO_TRACE("%02x %02x %02x %02x \n", des_addr[12], des_addr[13], des_addr[14], des_addr[15]);
    iounmap(tsio_reg_base);
}

static void tsio_set_ring_buff(unsigned long phy_addr, unsigned long buff_size, int level){
    void __iomem *tsio_reg_base = ioremap(TSIO_REG_BASE, 0x400);
    if(level == TSIO_H_QUEUE) {
        rtd_outl(tsio_reg_base + TSIO_FIFO_H_BASE, phy_addr);
        rtd_outl(tsio_reg_base + TSIO_FIFO_H_LIMIT, phy_addr+buff_size);
        rtd_outl(tsio_reg_base + TSIO_FIFO_H_WPTR, phy_addr);
    } else if(level == TSIO_M_QUEUE) {
        rtd_outl(tsio_reg_base + TSIO_FIFO_M_BASE, phy_addr);
        rtd_outl(tsio_reg_base + TSIO_FIFO_M_LIMIT, phy_addr+buff_size);
        rtd_outl(tsio_reg_base + TSIO_FIFO_M_WPTR, phy_addr);
    } else if(level == TSIO_L_QUEUE) {
        rtd_outl(tsio_reg_base + TSIO_FIFO_L_BASE, phy_addr);
        rtd_outl(tsio_reg_base + TSIO_FIFO_L_LIMIT, phy_addr+buff_size);
        rtd_outl(tsio_reg_base + TSIO_FIFO_L_WPTR, phy_addr);
    }
    iounmap(tsio_reg_base);
}

static int tsio_link_up(void){
    int delay_cnt = 0, ret = 0;
    void __iomem *tsio_reg_base = ioremap(TSIO_REG_BASE, 0x400);

    if((rtd_inl(tsio_reg_base + TSIO_LINK_STATE)&TSIO_LINK_UP) == 0) {
        rtd_outl(tsio_reg_base + TSIO_CRTL, 0x11070008);
        while((rtd_inl(tsio_reg_base + TSIO_LINK_STATE)&TSIO_LINK_UP) == 0){
           udelay(50);
           if(delay_cnt > 20) {
               ret = -1;
               break;
           }
           delay_cnt++;
        }
    }

    TSIO_TRACE("TSIO_CRTL(0x%x): 0x%x\n", TSIO_CRTL, rtd_inl(tsio_reg_base + TSIO_CRTL));
    TSIO_TRACE("TSIO_LINK_STATE(0x%x): 0x%x\n", TSIO_LINK_STATE, rtd_inl(tsio_reg_base + TSIO_LINK_STATE));
    iounmap(tsio_reg_base);
    return ret;
}

static void tsio_link_down(void)
{
    if(rtd_inl(TSIO_LINK_STATE)&TSIO_LINK_UP) {
        rtd_outl(TSIO_CRTL, 0x10070008);
    }
}

static void tsio_clk_init(int tsio_clk){
    unsigned int clk_setting = 0;

    void __iomem *tsio_reg_base = ioremap(TSIO_REG_BASE, 0x400);
    void __iomem *clk_reg_base = ioremap(0x98000000, 0x800);
    void __iomem *clk_reg_base2 = ioremap(0x9803DA00, 0x100);

#ifdef TSIO_BGA
    rtd_outl(0x98007100, 0x40000000);
    rtd_outl(0x98007104, 0x00000000);
#endif

    rtd_outl(clk_reg_base + 0x270, 0x00000157);
    rtd_outl(clk_reg_base + 0x608, 0x081e1f80);
    rtd_outl(clk_reg_base + 0x248, 0x1a333007);
    rtd_outl(clk_reg_base + 0x254, 0x00001e01);
    rtd_outl(clk_reg_base + 0x05c, 0x30000000);
    rtd_outl(clk_reg_base + 0x068, 0x00000c00);
    rtd_outl(clk_reg_base2 + 0x80, 0x00000000);
    rtd_outl(clk_reg_base + 0x05c, 0x20000000);
    rtd_outl(clk_reg_base + 0x068, 0x00000800);
    rtd_outl(clk_reg_base + 0x250, 0x93464980);

    if(tsio_clk == TSIO_100MBPS) {
        rtd_outl(clk_reg_base + 0x250, 0x93064180);
    } else {
        rtd_outl(clk_reg_base + 0x250, 0x93464180);
    }

    if(tsio_clk == TSIO_50MBPS) {
        rtd_outl(clk_reg_base + 0x250, 0x97064780); //#25MHz, Icp=2u, Rs=32K, pll BW must lowerer than 3MHz
    }
    rtd_outl(clk_reg_base + 0x600, 0x0000000c);

    if(tsio_clk == TSIO_100MBPS) {
        rtd_outl(clk_reg_base + 0x604, 0x00004800); // 108 Mpbs
    } else {
        rtd_outl(clk_reg_base + 0x604, 0x00015000); // 50/200/400 Mbps
    }

    rtd_outl(clk_reg_base + 0x600, 0x0000000d);
    rtd_outl(clk_reg_base + 0x05c, 0xC3000000);
    rtd_outl(clk_reg_base + 0x75c, 0x41000050);
    rtd_outl(clk_reg_base + 0x068, 0x000000c0);
    rtd_outl(clk_reg_base + 0x768, 0x00000040);
    rtd_outl(clk_reg_base + 0x274, 0x0005DE10);
    rtd_outl(clk_reg_base + 0x278, 0x000741C0);

    rtd_outl(tsio_reg_base + TSIO_PHY_CLK, 0xffff);

    if(tsio_clk == TSIO_100MBPS) {
        rtd_outl(tsio_reg_base + TSIO_TX_PKT, 0x2503018); //100 Mbps
	rtd_outl(tsio_reg_base + TSIO_CRTL, 0x110700f8); //100 Mbps
    } else {
        rtd_outl(tsio_reg_base + TSIO_TX_PKT, 0x2583018); //50/200/400 Mbps
    }

    rtd_outl(tsio_reg_base + TSIO_PKT, 0x3f);

    clk_setting = rtd_inl(clk_reg_base + 0x084);
    if(tsio_clk == TSIO_400MBPS) {
        clk_setting |= ((1<<27)|(1<<26) | (1<<25)|(1<<24)); //400Mbps
    } else if(tsio_clk == TSIO_200MBPS) {
        clk_setting |= ((1<<27)|(1<<26) | (1<<25)|(0<<24)); //200Mbps   
    } else if(tsio_clk == TSIO_100MBPS) {
        clk_setting |= ((1<<27)|(0<<26) | (1<<25)|(1<<24)); //100Mbps  
    } else if(tsio_clk == TSIO_50MBPS) {
        clk_setting |= ((1<<27)|(0<<26) | (1<<25)|(0<<24)); //50Mbps
    }
    rtd_outl(clk_reg_base + 0x084, clk_setting);

    iounmap(tsio_reg_base);
    iounmap(clk_reg_base);
    iounmap(clk_reg_base2);
}

static int tsio_open(struct inode *inode, struct file *filp)
{
    int ret;
    TSIO_TRACE("tsio device open\n");
    tsio_clk_init(TSIO_200MBPS);

    tsio_set_ring_buff(phy_high_fifo, 512, TSIO_H_QUEUE);
    tsio_set_ring_buff(phy_middle_fifo, 512, TSIO_M_QUEUE);
    ret = tsio_link_up();

    return ret;
}

static ssize_t tsio_write(struct file *f, const char __user *buf, size_t count, loff_t *offp)
{
    char * p_dump = NULL;
    unsigned char write_buf[512];
    unsigned long data_len = 0, p_src_addr = 0, p_dst_addr = 0;
    int ret = 0, i;
    memset(write_buf, 0, sizeof(write_buf));

    TSIO_TRACE("tsio device write\n");
    TSIO_TRACE("count = %d\n", count);
 
    if(count > 512)
        return -EFAULT;
 
    if (copy_from_user(write_buf, buf, count))
        return -EFAULT;

    TSIO_TRACE("Dump write buff:\n");
    TSIO_TRACE("%02x %02x %02x %02x \n", write_buf[0], write_buf[1], write_buf[2], write_buf[3]);
    TSIO_TRACE("%02x %02x %02x %02x \n", write_buf[4], write_buf[5], write_buf[6], write_buf[7]);
    TSIO_TRACE("%02x %02x %02x %02x \n", write_buf[8], write_buf[9], write_buf[10], write_buf[11]);
    TSIO_TRACE("%02x %02x %02x %02x \n", write_buf[12], write_buf[13], write_buf[14], write_buf[15]);

    if(write_buf[0] == TSIO_TS || write_buf[0] == TSIO_CCP_TS) {
        data_len = bytes_to_long(&write_buf[4]);
        p_src_addr = bytes_to_long(&write_buf[8]);
        p_dst_addr = 0;
        tsio_set_descriptor(write_buf[0], write_buf[2], p_src_addr, p_dst_addr, data_len);
        ret = tsio_start_descriptor(write_buf[0]);
    } else if(write_buf[0] == TSIO_BLK) {
        data_len = bytes_to_long(&write_buf[4]);
        p_src_addr = bytes_to_long(&write_buf[8]);
        p_dst_addr = bytes_to_long(&write_buf[12]);
        TSIO_TRACE("data_len: %x\n", data_len);
        TSIO_TRACE("p_src_addr: %x\n", p_src_addr);
        TSIO_TRACE("p_dst_addr: %x\n", p_dst_addr);
        p_dump = phys_to_virt(p_src_addr);

        TSIO_TRACE("Dump p_dump buff:\n");
        TSIO_TRACE("%02x %02x %02x %02x \n", p_dump[0], p_dump[1], p_dump[2], p_dump[3]);
        TSIO_TRACE("%02x %02x %02x %02x \n", p_dump[4], p_dump[5], p_dump[6], p_dump[7]);
        tsio_set_descriptor(write_buf[0], write_buf[2], p_src_addr, p_dst_addr, data_len);
        ret = tsio_start_descriptor(write_buf[0]);
	TSIO_TRACE("ret = %d\n", ret);
    } else if(write_buf[0] == TSIO_CC) {
	data_len = bytes_to_long(&write_buf[4]);
	tsio_send_cc(&write_buf[8], data_len);
    }

    return count;
}

static long tsio_ioctl(struct file* file, unsigned int cmd, unsigned long arg)
{
    long ret = 0;
    unsigned int tsio_value;
    void __iomem *tsio_reg_base = ioremap(TSIO_REG_BASE, 0x400);
    void __iomem *clk_reg_base = ioremap(0x98000000, 0x800);

    TSIO_TRACE("tsio device compat ioctl\n");

    switch (cmd) {
        case TSIO_GET_LINK_STATUS:
            if((rtd_inl(tsio_reg_base + TSIO_LINK_STATE)&TSIO_LINK_UP) == 0) {
                tsio_value = 0;
            } else {
                tsio_value = 1;
            }
            ret = copy_to_user((unsigned int __user *)arg, &tsio_value, sizeof(tsio_value)); 
        break;

        case TSIO_GET_BW:
            tsio_value = 0;
            if(rtd_inl(clk_reg_base + 0x084)&(1<<26)){
                tsio_value |= (1<<1);
            }

            if(rtd_inl(clk_reg_base + 0x084)&(1<<24)){
                tsio_value |= (1<<0);
            }
            ret = copy_to_user((unsigned int __user *)arg, &tsio_value, sizeof(tsio_value)); 
        break;

        case TSIO_SET_BW:
             if (copy_from_user(&tsio_value, (unsigned int __user *)arg, sizeof(unsigned int)))
                return -EFAULT;

             if(tsio_value >= TSIO_50MBPS && tsio_value <= TSIO_400MBPS) {
                tsio_link_down();
                tsio_clk_init(tsio_value);
                tsio_link_up();
             }
        break;

        case TSIO_GET_STFF_SID:
            tsio_value = rtd_inl(tsio_reg_base + TSIO_PKT);
            ret = copy_to_user((unsigned int __user *)arg, &tsio_value, sizeof(tsio_value)); 
        break;

        case TSIO_SET_STFF_SID:
            if (copy_from_user(&tsio_value, (unsigned int __user *)arg, sizeof(unsigned int)))
                return -EFAULT;

            rtd_outl(tsio_reg_base + TSIO_PKT, tsio_value);
        break;

        case TSIO_GET_SYNC_THRES:
        break;

        case TSIO_SET_SYNC_THRES:
        break;

        case TSIO_SET_KEY_IDX:
        break;

        default:
            ret = -EFAULT;
    }

    iounmap(tsio_reg_base);
    iounmap(clk_reg_base);
    return ret;
}

#ifdef CONFIG_COMPAT
static long tsio_compat_ioctl(struct file* file,unsigned int cmd, unsigned long arg)
{
    TSIO_TRACE("tsio device compat ioctl\n");
    return tsio_ioctl(file, cmd,(unsigned long)compat_ptr(arg));
}
#endif

static int tsio_release(struct inode *inode, struct file *filp)
{
    TSIO_TRACE("tsio device close\n");
    return 0;
}

static const struct file_operations tsio_dev_fops = 
{
    .owner          = THIS_MODULE,
    .write          = tsio_write,
    .unlocked_ioctl = tsio_ioctl,
#ifdef CONFIG_COMPAT
    .compat_ioctl   = tsio_compat_ioctl,
#endif
    .open           = tsio_open,
//    .release        = tsio_release,
};

static int __init tsio_init(void)
{
    TSIO_TRACE("<1> TSIO initial !\n");
    if (register_chrdev(TSIO_MAJOR, "tsio", &tsio_dev_fops) < 0) {
        TSIO_WARNING("<1>%s: can't get major %d\n", "tsio", TSIO_MAJOR);
        return (-EBUSY);
    }

    tsio_dev_class = class_create(THIS_MODULE, "tsiodev"); // create a new class for tsio
    tsio_dev = device_create(tsio_dev_class, NULL, MKDEV(TSIO_MAJOR,0), NULL, "tsio_sc");

    TSIO_TRACE("Before dma_alloc_coherent tsio_dev\n");
    p_high_fifo  = dma_alloc_coherent(tsio_dev, 512, &phy_high_fifo, GFP_KERNEL);
    p_middle_fifo = dma_alloc_coherent(tsio_dev, 512, &phy_middle_fifo, GFP_KERNEL);
    
    TSIO_TRACE("p_high_fifo: 0x%08x\n", p_high_fifo);
    TSIO_TRACE("phy_high_fifo: 0x%08x\n", phy_high_fifo);
    TSIO_TRACE("p_middle_fifo: 0x%08x\n", p_middle_fifo);
    TSIO_TRACE("phy_middle_fifo: 0x%08x\n", phy_middle_fifo);

    TSIO_TRACE("<1>%s: started\n", "tsio");
    return 0;
}

static __exit void tsio_exit(void)
{
    if(p_high_fifo) {
        dma_free_coherent(tsio_dev, 512, p_high_fifo, phy_high_fifo);
    }

    if(p_middle_fifo) {
        dma_free_coherent(tsio_dev, 512, p_middle_fifo, phy_middle_fifo);
    }
    device_destroy(tsio_dev_class, MKDEV(TSIO_MAJOR,0));
    unregister_chrdev(TSIO_MAJOR, "tsio");
    TSIO_TRACE("<1> remove tsio!\n");
}

module_init(tsio_init);
module_exit(tsio_exit);

MODULE_LICENSE("GPL");
