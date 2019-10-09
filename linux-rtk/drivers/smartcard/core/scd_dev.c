#include <linux/kernel.h>
#include <linux/ioport.h>
#include <linux/delay.h>
#include <linux/slab.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/wait.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <asm-generic/uaccess.h>
#include "scd.h"
#include "scd_dev.h"



#define MAX_SCD_CNT     2
static scd_dev          node_list[MAX_SCD_CNT];
static dev_t            devno_base;
static struct class *   scd_dev_class = NULL;

void mars_scd_dumpdata(unsigned char* p_data, unsigned int len);

void mars_scd_dumpdata(unsigned char* p_data, unsigned int len)
{
	int i = 0;
	for(i=0;i<len;++i)
	{
		SC_INFO("data[%d] = 0x%x \n",i,p_data[i]);
	}
	SC_INFO("dump data end ~~   \n");
}


/*------------------------------------------------------------------
 * Func : create_scd_dev_node
 *
 * Desc : create a scd device node
 *
 * Parm : device : handle of scd device
 *         
 * Retn : 0 : success, others fail  
 *------------------------------------------------------------------*/
int create_scd_dev_node(scd_device* device)
{               
    int i;    
    
    for (i=0; i<MAX_SCD_CNT; i++)
    {
        if (node_list[i].device==NULL)
        {
            if (cdev_add(&node_list[i].cdev, devno_base + i, 1)<0)
            {
                SC_WARNING("scd warning : register character dev failed\n");    
                return -1;
            }
   
            node_list[i].device = device_create(
                            scd_dev_class,      // class 
                            NULL,               // parent
                            devno_base + i,     // dev number
                            device,             // driver data
                            "scd-%d",            // device name
                            i);                 // device id;                        
            
            return 0;
        }
    }
    
    return -1;
}



/*------------------------------------------------------------------
 * Func : remove_scd_dev_node
 *
 * Desc : remove a scd device node
 *
 * Parm : device : scd device to be unregistered
 *         
 * Retn : 0 : success, others fail  
 *------------------------------------------------------------------*/
void remove_scd_dev_node(scd_device* device)
{   
    int i = 0;
    
    for (i=0; i<MAX_SCD_CNT; i++)
    {
        if (node_list[i].device && dev_get_drvdata(node_list[i].device)==(void*)device)
        {
            device_destroy(scd_dev_class, devno_base + i);       // remove device     
            cdev_del(&node_list[i].cdev);
            node_list[i].device = NULL;
            return;
        }
    }
}



/*------------------------------------------------------------------
 * Func : scd_dev_open
 *
 * Desc : open function of scd dev
 *
 * Parm : inode : inode of dev
 *        file  : context of file
 *         
 * Retn : 0 : success, others fail  
 *------------------------------------------------------------------*/
static 
int scd_dev_open(struct inode *inode, struct file *file)
{
    unsigned int i = iminor(inode);    
    scd_device*  dev = NULL;
    
    if (!node_list[i].device)
        return -ENODEV;     
    
    dev = (scd_device*) dev_get_drvdata(node_list[i].device);
    
    if (dev)
    {
        scd_driver* drv = (scd_driver*) to_scd_driver(dev->dev.driver);                
        file->private_data = dev;
        drv->enable(dev, 1);
        return 0;
    }
    
    return -ENODEV;     
}



/*------------------------------------------------------------------
 * Func : scd_dev_release
 *
 * Desc : release function of scd dev
 *
 * Parm : inode : inode of dev
 *        file  : context of file
 *         
 * Retn : 0 : success, others fail  
 *------------------------------------------------------------------*/
static 
int scd_dev_release(
    struct inode*           inode, 
    struct file*            file
    )
{    
    scd_device* dev = (scd_device*) file->private_data;
    
    if (dev) {
        scd_driver* drv = (scd_driver*) to_scd_driver(dev->dev.driver);                
        drv->enable(dev, 0);
    }
                
    return 0;
}



/*------------------------------------------------------------------
 * Func : scd_dev_read
 *
 * Desc : read function of scd dev
 *
 * Parm : file  : context of file
 *        buff  : rx buffer addr
 *        size  : rx buffer size
 *        ofst  : read offset 
 *         
 * Retn : 0 : success, others fail  
 *------------------------------------------------------------------*/
static 
ssize_t scd_dev_read(
    struct file*            file,
    char __user*            buff, 
    size_t                  size,
    loff_t*                 ofst           
    )    
{
    scd_device* dev = (scd_device*) file->private_data;    
    scd_driver* drv = (scd_driver*) to_scd_driver(dev->dev.driver);    
    unsigned char tmp[512];
    int ret;     
    
    if (size > sizeof(tmp))
        size = sizeof(tmp); 
        
    ret = drv->read(dev, tmp, size); 
	//SC_WARNING("read data~~  size=%d ret=%d \n",size,ret);
    
    if (ret > 0)
    {
		mars_scd_dumpdata(tmp, ret);
        if (copy_to_user((unsigned char __user *) buff, tmp, ret)<0) 
        {
            SC_WARNING("read message failed, copy to user failed\n");
            return -EFAULT;
        }
    }
    
    return ret;              
}



/*------------------------------------------------------------------
 * Func : scd_dev_write
 *
 * Desc : write function of scd dev
 *
 * Parm : file  : context of file
 *        buff  : tx buffer addr
 *        size  : tx buffer size
 *        ofst  : write offset 
 *         
 * Retn : 0 : success, others fail  
 *------------------------------------------------------------------*/
static 
ssize_t scd_dev_write(
    struct file*            file,
    const char __user*      buff, 
    size_t                  size,
    loff_t*                 ofst           
    )    
{
    scd_device* dev = (scd_device*) file->private_data;    
    scd_driver* drv = (scd_driver*) to_scd_driver(dev->dev.driver);        
    unsigned char tmp[512]; 

    if (copy_from_user(tmp, (unsigned char __user *)buff, size)) {
        SC_WARNING("write message failed, copy data from user space failed\n");        
        return -EFAULT;
    }    
	SC_INFO("write data start~~  \n");
	mars_scd_dumpdata(tmp,size);
    return drv->xmit(dev, tmp, size);     
}



/*------------------------------------------------------------------
 * Func : scd_dev_ioctl
 *
 * Desc : ioctl function of scd dev
 *
 * Parm : 
 *        file  : context of file
 *        cmd   : control command
 *        arg   : arguments
 *         
 * Retn : 0 : success, others fail  
 *------------------------------------------------------------------*/
static 
long scd_dev_ioctl(
    struct file*            file,
    unsigned int            cmd, 
    unsigned long           arg
    )
{    
    scd_device* dev = (scd_device*) file->private_data; 
    scd_driver* drv;    
    scd_atr     atr;
    scd_atr*    p_atr;
    sc_msg_buff buff;    
    int         i;
    scd_param   param;
    scd_ifd_param ifd_param;
    int         ret;
    
    if (!dev)
        return -ENODEV;     
        
    drv = (scd_driver*) to_scd_driver(dev->dev.driver);            
        
    switch (cmd)
    {
    case SCD_SETPARAM:                
        
        if (copy_from_user(&ifd_param, (scd_ifd_param __user *)arg, sizeof(ifd_param)))
            return -EFAULT;
            
        ret  = drv->set_param(dev, SC_PARAM_CLOCK, ifd_param.clk);
        ret |= drv->set_param(dev, SC_PARAM_ETU,   ifd_param.etu);         
        return ret;
    
    case SCD_GETPARAM:                
                
        if (drv->get_param(dev, SC_PARAM_CLOCK, &ifd_param.clk)<0)
            return -EFAULT;
            
        if (drv->get_param(dev, SC_PARAM_ETU, &ifd_param.etu)<0)
            return -EFAULT;           

        return copy_to_user((scd_ifd_param __user *)arg, &ifd_param, sizeof(ifd_param));            
                                
    case SCD_SETPARAM_EX:                
        
        if (copy_from_user(&param, (scd_param __user *)arg, sizeof(param)))
            return -EFAULT;
                                               
        return drv->set_param(dev, param.id, param.val);            
        
    case SCD_GETPARAM_EX:                   
        if (copy_from_user(&param, (scd_param __user *)arg, sizeof(param)))
            return -EFAULT;                 
        if (drv->get_param(dev, param.id, (unsigned long *)&param.val)<0)
            return -EFAULT;
        return copy_to_user((scd_param __user *)arg, &param, sizeof(param));
                
	case SCD_ACTIVE:                    return drv->activate(dev);
	case SCD_DEACTIVE:                return drv->deactivate(dev);	        
	case SCD_RESET:                     return drv->reset(dev);     	          
	case SCD_GET_CARD_STATUS:           return drv->get_card_status(dev);
    case SCD_POLL_CARD_STATUS_CHANGE:   return drv->poll_card_status(dev);
    case SCD_GET_ATR:
        
        if (drv->get_atr(dev, &atr))    
            return -1;        
                
        p_atr = (scd_atr *)arg;                                                           
            
        put_user(atr.length, &p_atr->length);
                
        for(i=0; i < atr.length; i++)        
            put_user(atr.data[i], &p_atr->data[i]);        
            
        return 0;

    case SCD_READ:          
        
        if (copy_from_user(&buff, (sc_msg_buff __user *)arg, sizeof(sc_msg_buff)))
            return -EFAULT;
	//SC_WARNING("Read data length = %d  \n",buff.length);
        return scd_dev_read(file, buff.p_data, buff.length, 0);
    
    case SCD_WRITE:                             
        
        if (copy_from_user(&buff, (sc_msg_buff __user *)arg, sizeof(sc_msg_buff)))
            return -EFAULT;
                    
        return scd_dev_write(file, buff.p_data, buff.length, 0);

            
    default:        
        return -EFAULT;          
    }
    
    return 0;          
}

static long scd_dev_compat_ioctl(struct file* file,unsigned int cmd, unsigned long arg)
{
	 if (!file->f_op->unlocked_ioctl)
                return -ENOTTY;
#if defined(CONFIG_ARCH_MULTI_V7)
	return file->f_op->unlocked_ioctl(file, cmd, arg);
#else
	return file->f_op->unlocked_ioctl(file, cmd,(unsigned long)compat_ptr(arg));
#endif /* CONFIG_ARCH_MULTI_V7 */

}

static struct file_operations scd_dev_fops = 
{
    .owner      = THIS_MODULE,  
    .unlocked_ioctl	= scd_dev_ioctl,
    .compat_ioctl	= scd_dev_compat_ioctl,
    .open       = scd_dev_open,
    .read       = scd_dev_read,
    .write      = scd_dev_write,
    .release    = scd_dev_release,
};



/*------------------------------------------------------------------
 * Func : scd_dev_module_init
 *
 * Desc : scd dev init function
 *
 * Parm : N/A
 *         
 * Retn : 0 : success, others fail  
 *------------------------------------------------------------------*/
int __init scd_dev_module_init(void)
{        
    int i;
    if (alloc_chrdev_region(&devno_base, 0, MAX_SCD_CNT, "smartcard")!=0)    
        return -EFAULT;

    scd_dev_class = class_create(THIS_MODULE, "scd-dev");
           
    for (i=0; i<MAX_SCD_CNT; i++) 
    {   
        cdev_init(&node_list[i].cdev, &scd_dev_fops);        
        node_list[i].device = NULL;        
    }
        
    return 0;
}



/*------------------------------------------------------------------
 * Func : scd_dev_module_exit
 *
 * Desc : scd dev module exit function
 *
 * Parm : N/A
 *         
 * Retn : 0 : success, others fail  
 *------------------------------------------------------------------*/
void __exit scd_dev_module_exit(void)
{   
    int i = 0;            
    
    for (i=0; i<MAX_SCD_CNT; i++)    
    {
        if (node_list[i].device)
            remove_scd_dev_node((scd_device*)dev_get_drvdata(node_list[i].device));
    }
    
    unregister_chrdev_region(devno_base, MAX_SCD_CNT);
    
    class_destroy(scd_dev_class);
}
