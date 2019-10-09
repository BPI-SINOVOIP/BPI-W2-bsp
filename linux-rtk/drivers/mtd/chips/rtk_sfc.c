/*
 * MTD chip driver for SPI Serial Flash 
 * w/ Serial Flash Controller Interface
 *
 * Copyright 2005 Chih-pin Wu <wucp@realtek.com.tw>
 * Copyright 2014 Louis Yang  <louis_yang@realtek.com>
 *
 */

//#define CONFIG_MTD_RTK_MD_READ_COMPARE
//#define CONFIG_MTD_RTK_MD_WRITE_COMPARE
//#define DEV_DEBUG
#define EMMC_ISSUE_LOCK

#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/types.h>
#include <linux/errno.h>
#include <linux/mtd/physmap.h>

#include <linux/module.h>
#include <linux/mtd/mtd.h>
#include <linux/mtd/map.h>
#include <linux/mtd/cfi.h>
#include <linux/mtd/partitions.h>
#include <linux/slab.h>
#include <linux/sysctl.h>
#include <linux/sched.h>
#include <linux/list.h>
#include <linux/pm.h>
#include <asm/io.h>
#include <linux/bitops.h>
#include <mtd/mtd-abi.h>
#include <linux/jiffies.h>
#include <linux/delay.h>
#include <linux/time.h>
#include <linux/proc_fs.h>
#include <linux/string.h>
#include <linux/platform_device.h>
#include <linux/interrupt.h>
#include <linux/dma-mapping.h>
#include "../mtdcore.h"
#if defined(CONFIG_MTD_RTK_SFC_DEBUG)
#include <linux/slab.h>
#endif
#include "rtk_sfc.h"
#ifdef EMMC_ISSUE_LOCK
#include <soc/realtek/rtd129x_lockapi.h>
#endif


/*
 * Mapping drivers for chip access
 */
#undef CONFIG_MTD_COMPLEX_MAPPINGS


/*
 * Definitions
 */
//#define dma_cache_sync(a,b,c,d) dma_map_single(NULL,b,c,d)

#if  defined(CONFIG_REALTEK_USE_HWSEM_AS_SENTINEL)
#define SFC_USE_DELAY   (0)
#else
#define SFC_USE_DELAY   (1)
#endif

#ifdef CONFIG_NOR_SUPPORT_MAX_ERASE_SIZE
#define NOR_SUPPORT_MAX_ERASE_SIZE  (1)
#else
#define NOR_SUPPORT_MAX_ERASE_SIZE  (0)
#endif

#ifdef CONFIG_NOR_ENTER_4BYTES_MODE
#define ENTER_4BYTES_MODE   (1)
#else
#define ENTER_4BYTES_MODE   (0)
#endif

#ifdef CONFIG_NOR_AUTO_HW_POLLING
#define SFC_HW_POLL         (1)
#else
#define SFC_HW_POLL         (0)
#endif

#ifdef CONFIG_MTD_RTK_SFC_MULTI_READ
#define SFC_MULTI_READ      (1)
#else
#define SFC_MULTI_READ      (0)
#endif

#if defined(CONFIG_MTD_RTK_SFC_DEBUG)
typedef enum {
    INVALID             = 0,
    READ_ACCESS         = 0x10000000,
    READ_COMPLETED      = 0x01000000,
    WRITE_ACCESS        = 0x20000000,
    WRITE_COMPLETED     = 0x02000000,
    ERASE_ACCESS        = 0x40000000,
    ERASE_COMPLETED     = 0x04000000,

    READ_READY          = 0x00000001,
    READ_STAGE_1        = 0x00000002,
    READ_STAGE_2        = 0x00000004,
    READ_STAGE_3        = 0x00000008,
    WRITE_READY         = 0x00000100,
    WRITE_STAGE_1       = 0x00000200,
    WRITE_STAGE_2       = 0x00000400,
    WRITE_STAGE_3       = 0x00000800,
    WRITE_STAGE_4       = 0x00001000,
    WRITE_STAGE_5       = 0x00002000,
} PROGRESS_STATUS;

typedef struct _tagDescriptorTable {
    int from;
    int to;
    int length;
    PROGRESS_STATUS status;
} DESCRIPTOR_TABLE;

#define DBG_ENTRY_NUM 256

static int *dbg_counter = NULL;
static DESCRIPTOR_TABLE *dbg_table = NULL;
#endif


/*
 * Global Variables
 */
static void __iomem *rbus_base_virt = 0;
static void __iomem *nor_base_virt = 0;

static resource_size_t nor_size;

struct SFC_REG_INFO {
    unsigned int sfc_sck;
    unsigned int sfc_ce;
    unsigned int sfc_wp;
    unsigned int sfc_pos_latch;
};
static struct SFC_REG_INFO g_sfc_reg;

static volatile unsigned char *FLASH_POLL_ADDR;
static volatile unsigned char *FLASH_BASE;

static struct mtd_info descriptor;
static rtk_sfc_info_t rtk_sfc_info;

static struct rw_semaphore rw_sem;

unsigned int g_isSegErase = 0;

#ifdef CONFIG_MTD_RTK_SFC_READ_MD
static void *read_dma_buf = NULL;
static dma_addr_t read_dma_handle;
#endif

#ifdef CONFIG_MTD_RTK_SFC_WRITE_MD
static void *write_dma_buf = NULL;
static dma_addr_t write_dma_handle;
#endif


/*
 * Function Prototype
 */
static int rtk_sfc_attach(struct mtd_info *mtd_info);
#if SFC_USE_DELAY
static inline void sfc_delay(void);
#define delaymicro 50
#endif


#if defined(CONFIG_MTD_RTK_SFC_DEBUG)
static inline void add_debug_entry(int from, int to, int length, PROGRESS_STATUS status) {
    if(dbg_counter && dbg_table) {
        if((*dbg_counter) < (DBG_ENTRY_NUM - 1))
            (*dbg_counter)++;
        else
            (*dbg_counter) = 0;

        dbg_table[*dbg_counter].from = from;
        dbg_table[*dbg_counter].to = to;
        dbg_table[*dbg_counter].length = length;
        dbg_table[*dbg_counter].status = status;
    }
}

static inline void change_status(PROGRESS_STATUS status) {
    if(dbg_counter && dbg_table)
        dbg_table[*dbg_counter].status |= status;
}
#endif


void inline setSSTWrteStutReg(void)//Only for MXIC 256/128 MB . Add by alexchang 1217-2010
{
    unsigned char tmp;  
    /* EWSR: enable write status register */
    SFC_SYNC;
    printk("[%s]\n",__FUNCTION__);

    SYS_REG_TRY_LOCK(0);//add by alexchang 0722-2010
    REG_WRITE_U32(0x0000050, SFC_OPCODE);

#if SFC_USE_DELAY
    sfc_delay();
#endif

    REG_WRITE_U32(0x00000000, SFC_CTL);
    SYS_REG_TRY_UNLOCK;//add by alexchang 0722-2010
    SFC_SYNC;

    tmp = (unsigned char)*((volatile unsigned char*)FLASH_POLL_ADDR);

}

static unsigned int endian_swap(unsigned int x)
{
    x = (x>>24) |((x<<8) & 0x00FF0000) |((x>>8) & 0x0000FF00) |(x<<24);
    return x;
}

#if SFC_USE_DELAY
static inline void sfc_delay(void) {
    udelay(delaymicro);
}
#endif

static inline void _switch_to_read_mode(rtk_sfc_info_t *sfc_info, rtk_sfc_read_mode_t mode) {

    unsigned int sfc_opcode;
    unsigned int sfc_ctl;
    unsigned int tmp;

    /* restore opcode to read */
    sfc_opcode = 0x00000003;
    sfc_ctl = 0x00000018;

    SFC_SYNC;
    SYS_REG_TRY_LOCK(0);
    REG_WRITE_U32(sfc_opcode, SFC_OPCODE);
#if SFC_USE_DELAY
    sfc_delay();
#endif
    REG_WRITE_U32(sfc_ctl, SFC_CTL);
    tmp = *(volatile unsigned int*)(FLASH_BASE);
    SYS_REG_TRY_UNLOCK;
    SFC_SYNC;

    return;
}
//---------------------------------------------------------------------------------------------

static int read_rems(rtk_sfc_info_t *sfc_info, unsigned char *byte1, unsigned char*byte2) 
{
    SFC_SYNC;
    SYS_REG_TRY_LOCK(0);//add by alexchang 0722-2010
    REG_WRITE_U32(0x00000090, SFC_OPCODE);  /* Read Electronic Manufacturer & Device ID */
#if SFC_USE_DELAY
    sfc_delay();
#endif

    REG_WRITE_U32(0x0000001a, SFC_CTL); /* dataen = 1, adren = 0, dmycnt = 3 */
    SYS_REG_TRY_UNLOCK;
    SFC_SYNC;

    *byte1 = *((volatile unsigned char*)(FLASH_POLL_ADDR + 0));

    printk("*byte1=0x%x \n",*byte1);
    SFC_SYNC;
    SYS_REG_TRY_LOCK(0);//add by alexchang 0722-2010
    REG_WRITE_U32(0x00000090, SFC_OPCODE);  /* Read Electronic Manufacturer & Device ID */
#if SFC_USE_DELAY
    sfc_delay();
#endif

    REG_WRITE_U32(0x0000001a, SFC_CTL); /* dataen = 1, adren = 0, dmycnt = 3 */
    SYS_REG_TRY_UNLOCK;//add by alexchang 0722-2010
    SFC_SYNC;

    *byte2 = *((volatile unsigned char*)(FLASH_POLL_ADDR + 1));
    printk("*byte2=0x%x \n",*byte2);

    return 0;
}

#if ENTER_4BYTES_MODE
static int en_4bytes_addr_mode(void) {
    volatile unsigned char tmp2;

    SFC_SYNC;
    SYS_REG_TRY_LOCK(0);//add by alexchang 0722-2010
    REG_WRITE_U32(0x000000b7, SFC_OPCODE);  /* enter 4-bytes address mode */
#if SFC_USE_DELAY
    sfc_delay();
#endif

    REG_WRITE_U32(0x00000000, SFC_CTL);
    SYS_REG_TRY_UNLOCK;//add by alexchang 0722-2010
    SFC_SYNC;   
    tmp2 = *(volatile unsigned char *)FLASH_POLL_ADDR;

    return 0;

}

static int exit_4bytes_addr_mode(void) {
    volatile unsigned char tmp2;

    SFC_SYNC;
    SYS_REG_TRY_LOCK(0);//add by alexchang 0722-2010
    REG_WRITE_U32(0x000000e9, SFC_OPCODE);  /* exit 4-bytes address mode */
#if SFC_USE_DELAY
    sfc_delay();
#endif

    REG_WRITE_U32(0x00000000, SFC_CTL);
    SYS_REG_TRY_UNLOCK;//add by alexchang 0722-2010
    SFC_SYNC;   
    tmp2 = *(volatile unsigned char *)FLASH_POLL_ADDR;

    return 0;

}
#endif

/*--------------------------------------------------------------------------------
  GD serial flash information list
  [GD 25Q16B] 16Mbit
  erase size: 32KB / 64KB

  [GD 25Q64B] 64Mbit
  erase size: 32KB / 64KB 

  [GD 25Q128B] 128Mbit
  erase size: 32KB / 64KB
  --------------------------------------------------------------------------------*/
static int gd_init(rtk_sfc_info_t *sfc_info) {
    switch(sfc_info->device_id1) {
        case 0x40:
            switch(sfc_info->device_id2) {
                case 0x14:
                    printk(KERN_NOTICE "RtkSFC MTD: GD 25Q08B detected.\n");
                    SFC_4KB_ERASE;
                    sfc_info->sec_64k_en = sfc_info->sec_32k_en = sfc_info->sec_4k_en = SUPPORTED;
                    sfc_info->sec_256k_en = NOT_SUPPORTED;
                    sfc_info->mtd_info->size = 0x00100000;
                    break;
                case 0x15:
                    printk(KERN_NOTICE "RtkSFC MTD: GD 25Q16B detected.\n");
                    SFC_4KB_ERASE;
                    sfc_info->sec_64k_en = sfc_info->sec_32k_en = sfc_info->sec_4k_en = SUPPORTED;
                    sfc_info->sec_256k_en = NOT_SUPPORTED;
                    sfc_info->mtd_info->size = 0x200000;
                    break;
                case 0x16:
                    printk(KERN_NOTICE "RtkSFC MTD: GD 25Q32B detected.\n");
                    SFC_4KB_ERASE;
                    sfc_info->sec_64k_en = sfc_info->sec_32k_en = sfc_info->sec_4k_en = SUPPORTED;
                    sfc_info->sec_256k_en = NOT_SUPPORTED;
                    sfc_info->mtd_info->size = 0x400000;
                    break;  
                case 0x17:
                    printk(KERN_NOTICE "RtkSFC MTD: GD 25Q64B detected.\n");
                    SFC_4KB_ERASE;
                    sfc_info->sec_64k_en = sfc_info->sec_32k_en = sfc_info->sec_4k_en = SUPPORTED;
                    sfc_info->sec_256k_en = NOT_SUPPORTED;
                    sfc_info->mtd_info->size = 0x800000;
                    break;
                case 0x18:
                    printk(KERN_NOTICE "RtkSFC MTD: GD 25Q128B detected.\n");
                    SFC_4KB_ERASE;
                    sfc_info->sec_64k_en = sfc_info->sec_32k_en = sfc_info->sec_4k_en = SUPPORTED;
                    sfc_info->sec_256k_en = NOT_SUPPORTED;
                    sfc_info->mtd_info->size = 0x1000000;
                    break;
                default:
                    printk(KERN_NOTICE "RtkSFC MTD: GD unknown id2=0x%x detected.\n",
                            sfc_info->device_id2);
                    break;
            }
            break;
        default:
            printk(KERN_NOTICE "RtkSFC MTD: GD unknown id1=0x%x detected.\n",
                    sfc_info->device_id1);
            break;
    }
    if(sfc_info->erase_opcode==0xFFFFFFFF)//Set to default.
    {
        SFC_4KB_ERASE;
    }
    return 0;
}

/*--------------------------------------------------------------------------------
  SST serial flash information list
  [SST 25VF016B] 16Mbit
  erase size: 4KB / 32KB / 64KB

  [SST 25VF040B] 4Mbit
  erase size: 4KB / 32KB / 64KB
  --------------------------------------------------------------------------------*/
static int sst_init(rtk_sfc_info_t *sfc_info) {
    switch(sfc_info->device_id1) {
        case 0x25:
            switch(sfc_info->device_id2) {
                case 0x41:
                    printk(KERN_NOTICE "RtkSFC MTD: SST 25VF016B detected.\n");
                    sfc_info->sec_64k_en = sfc_info->sec_32k_en = sfc_info->sec_4k_en = SUPPORTED;
                    sfc_info->sec_256k_en = NOT_SUPPORTED;
                    sfc_info->mtd_info->size = 0x200000;
                    break;
                case 0x8d:
                    printk(KERN_NOTICE "RtkSFC MTD: SST 25VF040B detected.\n");
                    sfc_info->sec_64k_en = sfc_info->sec_32k_en = sfc_info->sec_4k_en = SUPPORTED;
                    sfc_info->sec_256k_en = NOT_SUPPORTED;
                    sfc_info->mtd_info->size = 0x80000;
                    break;
                default:
                    printk(KERN_NOTICE "RtkSFC MTD: SST unknown id2=0x%x detected.\n",
                            sfc_info->device_id2);
                    break;
            }
            break;
        default:
            printk(KERN_NOTICE "RtkSFC MTD: SST unknown id1=0x%x detected.\n",
                    sfc_info->device_id1);
            break;
    }
    if(sfc_info->erase_opcode==0xFFFFFFFF)//Set to default.
    {
        SFC_4KB_ERASE;
    }
    return 0;
}

/*--------------------------------------------------------------------------------
  SPANSION serial flash information list
  [SPANSION S25FL004A ]
  erase size: 64KB

  [SPANSION S25FL008A ]
  erase size: 64KB

  [SPANSION S25FL016A ]
  erase size: 64KB

  [SPANSION S25FL032A ]
  erase size: 64KB

  [SPANSION S25FL064A ]
  erase size: 64KB

  [SPANSION S25FL128P](256K sector)
  erase size: 64KB / 256KB

  [SPANSION S25FL129P](256K sector)
  erase size: 64KB / 256KB
  --------------------------------------------------------------------------------*/
static int spansion_init(rtk_sfc_info_t *sfc_info) {
    switch(sfc_info->device_id1) {
        case 0x02:
            switch(sfc_info->device_id2) {
                case 0x12:
                    printk(KERN_NOTICE "RtkSFC MTD: SPANSION S25FL004A detected.\n");
                    sfc_info->sec_64k_en = SUPPORTED;
                    sfc_info->sec_256k_en = sfc_info->sec_32k_en = sfc_info->sec_4k_en = NOT_SUPPORTED;
                    sfc_info->mtd_info->size = 0x80000;
                    break;
                case 0x13:
                    printk(KERN_NOTICE "RtkSFC MTD: SPANSION S25FL008A detected.\n");
                    sfc_info->sec_64k_en = SUPPORTED;
                    sfc_info->sec_256k_en = sfc_info->sec_32k_en = sfc_info->sec_4k_en = NOT_SUPPORTED;
                    sfc_info->mtd_info->size = 0x100000;
                    break;
                case 0x14:
                    printk(KERN_NOTICE "RtkSFC MTD: SPANSION S25FL016A detected.\n");
                    sfc_info->sec_64k_en = SUPPORTED;
                    sfc_info->sec_256k_en = sfc_info->sec_32k_en = sfc_info->sec_4k_en = NOT_SUPPORTED;
                    sfc_info->mtd_info->size = 0x200000;
                    break;
                case 0x15:
                    printk(KERN_NOTICE "RtkSFC MTD: SPANSION S25FL032A detected.\n");
                    sfc_info->sec_64k_en = SUPPORTED;
                    sfc_info->sec_256k_en = sfc_info->sec_32k_en = sfc_info->sec_4k_en = NOT_SUPPORTED;
                    sfc_info->mtd_info->size = 0x400000;
                    break;
                case 0x16:
                    printk(KERN_NOTICE "RtkSFC MTD: SPANSION S25FL064A detected.\n");
                    sfc_info->sec_64k_en = SUPPORTED;
                    sfc_info->sec_256k_en = sfc_info->sec_32k_en = sfc_info->sec_4k_en = NOT_SUPPORTED;
                    sfc_info->mtd_info->size = 0x800000;
                    break;
                default:
                    printk(KERN_NOTICE "RtkSFC MTD: SPANSION unknown id2=0x%x detected.\n",
                            sfc_info->device_id2);
                    break;
            }
            break;
        case 0x20:
            switch(sfc_info->device_id2) {
                case 0x18: // S25FL128P/129P has two types of erase size, must identify via extended device id
                    {
                        unsigned int tmp2 = 0;
                        u8 ext_id1;
                        u8 ext_id2;
                        SFC_SYNC;
                        SYS_REG_TRY_LOCK(0);//add by alexchang 0722-2010
                        REG_WRITE_U32(0x0000009f, SFC_OPCODE);  /* JEDEC Read ID */

#if SFC_USE_DELAY
                        sfc_delay();
#endif

                        REG_WRITE_U32(0x00000013, SFC_CTL); /* dataen = 1, adren = 0, dmycnt = 3 */
                        SYS_REG_TRY_UNLOCK;//add by alexchang 0722-2010
                        SFC_SYNC;
                        tmp2 = *(volatile unsigned int *)FLASH_POLL_ADDR;
                        printk("Extension ID : 0x%x\n",tmp2);

                        ext_id1 = RDID_DEVICE_EID_1(tmp2);
                        ext_id2 = RDID_DEVICE_EID_2(tmp2);

                        if(ext_id1 == 0x03 && ext_id2 == 0x00) {
                            printk(KERN_NOTICE "RtkSFC MTD: SPANSION S25FL128P(256K sector) detected.\n");
                            SFC_256KB_ERASE;    
                            sfc_info->sec_256k_en = sfc_info->sec_64k_en = SUPPORTED;
                            sfc_info->sec_32k_en = sfc_info->sec_4k_en = NOT_SUPPORTED;
                            sfc_info->mtd_info->size = 0x1000000;
                        }
                        else if(ext_id1 == 0x4d && ext_id2 == 0x00) {
                            printk(KERN_NOTICE "RtkSFC MTD: SPANSION S25FL129P(256K sector) detected.\n");
                            SFC_256KB_ERASE;
                            sfc_info->attr |= RTK_SFC_ATTR_SUPPORT_DUAL_IO;
                            sfc_info->sec_256k_en = SUPPORTED;
                            sfc_info->sec_64k_en = sfc_info->sec_32k_en = sfc_info->sec_4k_en = NOT_SUPPORTED;
                            sfc_info->mtd_info->size = 0x1000000;
                        }
                        else if(ext_id1 == 0x4d && ext_id2 == 0x01) {
                            printk(KERN_NOTICE "RtkSFC MTD: SPANSION S25FL129P(64K sector) detected.\n");
                            SFC_64KB_ERASE;
                            sfc_info->attr |= RTK_SFC_ATTR_SUPPORT_DUAL_IO;
                            sfc_info->sec_64k_en = SUPPORTED;
                            sfc_info->sec_256k_en = sfc_info->sec_32k_en = sfc_info->sec_4k_en = NOT_SUPPORTED;
                            sfc_info->mtd_info->size = 0x1000000;
                        }   

                        else {
                            printk(KERN_NOTICE "RtkSFC MTD: SPANSION S25FL128P or others (64K sector) detected.\n");
                            SFC_64KB_ERASE;
                            sfc_info->sec_64k_en = SUPPORTED;
                            sfc_info->sec_256k_en = sfc_info->sec_32k_en = sfc_info->sec_4k_en = NOT_SUPPORTED;
                            sfc_info->mtd_info->size = 0x1000000;
                        }
                    }
                    break;
                default:
                    printk(KERN_NOTICE "RtkSFC MTD: SPANSION unknown id2=0x%x detected.\n",
                            sfc_info->device_id2);
                    break;
            }
            break;
        default:
            printk(KERN_NOTICE "RtkSFC MTD: SPANSION unknown id1=0x%x detected.\n",
                    sfc_info->device_id1);
            break;
    }
    if(sfc_info->erase_opcode==0xFFFFFFFF)//Set to default.
    {
        SFC_64KB_ERASE;
    }

    return 0;
}

/*--------------------------------------------------------------------------------
  MXIC serial flash information list
  [MXIC MX25L4005]
  erase size: 4KB / 64KB

  [MXIC MX25L8005 / MX25L8006E]
  erase size: 4KB / 64KB

  [MXIC MX25L1605]
  erase size: 4KB / 64KB    

  [MXIC MX25L3205]
  erase size: 4KB / 64KB

  [MXIC MX25L6405D]
  erase size: 4KB / 64KB


  [MXIC MX25L6445E]
  erase size: 4KB / 32KB / 64KB

  [MXIC MX25L12845E]
  erase size: 4KB / 32KB / 64KB

  [MXIC MX25L12805E]
  erase size: 4KB / 64KB

  [MXIC MX25L25635E]
  erase size: 4KB / 32KB / 64KB

  [MXIC MX25L6455E]
  erase size:  4KB / 32KB / 64KB

  [MXIC MX25L12855E]
  erase size: 4KB / 32KB / 64KB

  --------------------------------------------------------------------------------*/

static int mxic_init(rtk_sfc_info_t *sfc_info) {
    unsigned char manufacturer_id, device_id;

    switch(sfc_info->device_id1) {
        case 0x20:
            switch(sfc_info->device_id2) {
                case 0x13:
                    printk(KERN_NOTICE "RtkSFC MTD: MXIC MX25L4005 detected.\n");
                    SFC_4KB_ERASE;
                    sfc_info->sec_64k_en = sfc_info->sec_4k_en = SUPPORTED;
                    sfc_info->sec_256k_en = sfc_info->sec_32k_en = NOT_SUPPORTED;
                    sfc_info->mtd_info->size = 0x80000;
                    break;
                case 0x14:
                    printk(KERN_NOTICE "RtkSFC MTD: MXIC MX25L8005/MX25L8006E detected.\n");
                    SFC_4KB_ERASE;
                    sfc_info->sec_64k_en = sfc_info->sec_4k_en = SUPPORTED;
                    sfc_info->sec_256k_en = sfc_info->sec_32k_en = NOT_SUPPORTED;
                    sfc_info->mtd_info->size = 0x100000;
                    break;
                case 0x15:
                    printk(KERN_NOTICE "RtkSFC MTD: MXIC MX25L1605 detected.\n");
                    SFC_4KB_ERASE;
                    sfc_info->sec_64k_en = sfc_info->sec_4k_en = SUPPORTED;
                    sfc_info->sec_256k_en = sfc_info->sec_32k_en = NOT_SUPPORTED;
                    sfc_info->mtd_info->size = 0x200000;
                    break;
                case 0x16:
                    printk(KERN_NOTICE "RtkSFC MTD: MXIC MX25L3205 detected.\n");
                    SFC_4KB_ERASE;
                    sfc_info->attr |= RTK_SFC_ATTR_SUPPORT_DUAL_O;
                    sfc_info->sec_64k_en = sfc_info->sec_4k_en = SUPPORTED;
                    sfc_info->sec_256k_en = sfc_info->sec_32k_en = NOT_SUPPORTED;
                    sfc_info->mtd_info->size = 0x400000;
                    break;
                case 0x17:
                    read_rems(sfc_info, &manufacturer_id, &device_id);
                    if(manufacturer_id == 0xc2 && device_id == 0x16) {
                        printk(KERN_NOTICE "RtkSFC MTD: MXIC MX25L6445E detected....\n");
                        SFC_4KB_ERASE;
                        //sfc_info->attr |= RTK_SFC_ATTR_SUPPORT_DUAL_IO;               
                        sfc_info->sec_64k_en = sfc_info->sec_32k_en = sfc_info->sec_4k_en = SUPPORTED;
                        sfc_info->sec_256k_en = NOT_SUPPORTED;
                    }
                    else {
                        printk(KERN_NOTICE "RtkSFC MTD: MXIC MX25L6405D detected.\n");
                        SFC_4KB_ERASE;
                        sfc_info->sec_64k_en = sfc_info->sec_4k_en = SUPPORTED;
                        sfc_info->sec_256k_en = sfc_info->sec_32k_en = NOT_SUPPORTED;
                    }
                    sfc_info->mtd_info->size = 0x800000;
                    break;
                case 0x18:
                    read_rems(sfc_info, &manufacturer_id, &device_id);
                    if(manufacturer_id == 0xc2 && device_id == 0x17) {
                        printk(KERN_NOTICE "RtkSFC MTD: MXIC MX25L12845E detected.\n");
                        SFC_4KB_ERASE;
                        sfc_info->attr |= RTK_SFC_ATTR_SUPPORT_DUAL_IO|RTK_SFC_ATTR_SUPPORT_DUAL_O;
                        sfc_info->sec_64k_en = sfc_info->sec_32k_en = sfc_info->sec_4k_en = SUPPORTED;
                        sfc_info->sec_256k_en = NOT_SUPPORTED;
                    }
                    else {
                        printk(KERN_NOTICE "RtkSFC MTD: MXIC MX25L12805 detected.\n");
                        SFC_4KB_ERASE;
                        sfc_info->sec_64k_en = sfc_info->sec_4k_en = SUPPORTED;
                        sfc_info->sec_256k_en = sfc_info->sec_32k_en = NOT_SUPPORTED;
                    }
                    sfc_info->mtd_info->size = 0x1000000;
                    break;
                case 0x19:
                    read_rems(sfc_info, &manufacturer_id, &device_id);
                    if(manufacturer_id == 0xc2 && device_id == 0x18) {
                        printk(KERN_NOTICE "RtkSFC MTD: MXIC MX25L25635E detected.\n");


                        SYS_REG_TRY_LOCK(0);//add by alexchang 0722-200

                        REG_WRITE_U32(0x0000002b, SFC_OPCODE);  

                        REG_WRITE_U32(0x00000010, SFC_CTL); /* dataen = 1, adren = 0, dmycnt = 0 */
                        SYS_REG_TRY_UNLOCK;//add by alexchang 0722-2010
                        SFC_SYNC;
                        if ((*(volatile unsigned char *)FLASH_POLL_ADDR) 
                                & 0x4) 
                        {
#if ENTER_4BYTES_MODE
                            exit_4bytes_addr_mode();
#else

#endif
                        }
                        SFC_4KB_ERASE;
                        sfc_info->attr |= RTK_SFC_ATTR_SUPPORT_DUAL_IO;
                        sfc_info->sec_64k_en = sfc_info->sec_32k_en = sfc_info->sec_4k_en = SUPPORTED;
                        sfc_info->sec_256k_en = NOT_SUPPORTED;
                        sfc_info->mtd_info->size = 0x2000000;

                        /* enter 4-byte address mode */
                        /* cuz watchdog reset issue , we dont 
                           support yet */
#if ENTER_4BYTES_MODE
                        en_4bytes_addr_mode();
                        sfc_info->attr |= RTK_SFC_ATTR_SUPPORT_4BYTE_ADDR_MODE;
#endif

                    }
                    else {
                        printk(KERN_NOTICE "RtkSFC MTD: MXIC unknown mnftr_id=0x%x, dev_id=0x%x .\n", manufacturer_id, device_id) ;
                        SFC_4KB_ERASE;
                        sfc_info->sec_4k_en = SUPPORTED;
                        sfc_info->sec_256k_en = sfc_info->sec_64k_en = sfc_info->sec_32k_en = NOT_SUPPORTED;
                    }
                    break;

                default:
                    printk(KERN_NOTICE "RtkSFC MTD: MXIC unknown id2=0x%x detected.\n",
                            sfc_info->device_id2);
                    SFC_4KB_ERASE;
                    sfc_info->sec_4k_en = SUPPORTED;
                    sfc_info->sec_256k_en = sfc_info->sec_64k_en = sfc_info->sec_32k_en = NOT_SUPPORTED;
                    break;
            }
            break;
        case 0x26:////add by alexchang 1206-2010
            switch(sfc_info->device_id2) {
                case 0x17:
                    printk(KERN_NOTICE "RtkSFC MTD: MXIC MX25L6455E detected.\n");
                    SFC_4KB_ERASE;
                    sfc_info->sec_64k_en = sfc_info->sec_32k_en = sfc_info->sec_4k_en = SUPPORTED;
                    sfc_info->sec_256k_en = NOT_SUPPORTED;
                    sfc_info->mtd_info->size = 0x800000;
                    break;

                case 0x18:
                    printk(KERN_NOTICE "RtkSFC MTD: MXIC MX25L12855E detected.\n");
                    SFC_4KB_ERASE;
                    sfc_info->sec_64k_en = sfc_info->sec_32k_en = sfc_info->sec_4k_en = SUPPORTED;
                    sfc_info->sec_256k_en = NOT_SUPPORTED;
                    sfc_info->mtd_info->size = 0x1000000;
                    break;

                default:
                    printk(KERN_NOTICE "RtkSFC MTD: MXIC unknown id2=0x%x detected.\n",
                            sfc_info->device_id2);
                    break;
            }
            break;
        default:
            printk(KERN_NOTICE "RtkSFC MTD: MXIC unknown id1=0x%x detected.\n",
                    sfc_info->device_id1);
            break;
    }

    if(sfc_info->erase_opcode==0xFFFFFFFF)//Set to default.
    {
        SFC_64KB_ERASE;
    }

    return 0;

}
/*--------------------------------------------------------------------------------
  PMC serial flash information list

  --------------------------------------------------------------------------------*/

static int pmc_init(rtk_sfc_info_t *sfc_info) {
    switch(sfc_info->device_id1) {
        case 0x9d:
            switch(sfc_info->device_id2) {
                case 0x7c:
                    printk(KERN_NOTICE "RtkSFC MTD: PMC Pm25LV010 detected.\n");
                    sfc_info->mtd_info->size = 0x20000;
                    break;
                case 0x7d:
                    printk(KERN_NOTICE "RtkSFC MTD: PMC Pm25LV020 detected.\n");
                    sfc_info->mtd_info->size = 0x40000;
                    break;
                case 0x7e:
                    printk(KERN_NOTICE "RtkSFC MTD: PMC Pm25LV040 detected.\n");
                    sfc_info->mtd_info->size = 0x80000;
                    break;
                case 0x46:
                    printk(KERN_NOTICE "RtkSFC MTD: PMC Pm25LQ032 detected.\n");
                    SFC_4KB_ERASE;
                    sfc_info->sec_64k_en = sfc_info->sec_4k_en = SUPPORTED;
                    sfc_info->sec_256k_en = sfc_info->sec_32k_en = NOT_SUPPORTED;
                    sfc_info->mtd_info->size = 0x400000;
                    break;      
                default:
                    printk(KERN_NOTICE "RtkSFC MTD: PMC unknown id2=0x%x detected.\n",
                            sfc_info->device_id2);
                    break;
            }
            break;
        default:
            printk(KERN_NOTICE "RtkSFC MTD: PMC unknown id1=0x%x detected.\n",
                    sfc_info->device_id1);
            break;
    }
    sfc_info->erase_size    = 0x1000;   //4KB
    sfc_info->erase_opcode  = 0x000000d7;   //for 4KB erase.
    return 0;
}

/*--------------------------------------------------------------------------------
  STM serial flash information list
  [ST M25P128]
  erase size: 2MB

  [ST M25Q128]

  [STM N25Q032]
  erase size: 4KB / 64KB

  [STM N25Q064]
  erase size: 4KB / 64KB
  --------------------------------------------------------------------------------*/

static int stm_init(rtk_sfc_info_t *sfc_info) {
    switch(sfc_info->device_id1) {
        case 0x20:
            switch(sfc_info->device_id2) {
                case 0x17:
                    printk(KERN_NOTICE "RtkSFC MTD: ST M25P64 detected.\n");
                    SFC_64KB_ERASE;
                    sfc_info->sec_64k_en = SUPPORTED;
                    sfc_info->sec_256k_en = sfc_info->sec_32k_en = sfc_info->sec_4k_en = NOT_SUPPORTED;
                    sfc_info->mtd_info->size = 0x1000000;
                    break;
                case 0x18:
                    printk(KERN_NOTICE "RtkSFC MTD: ST M25P128 detected.\n");
                    SFC_256KB_ERASE;
                    sfc_info->sec_256k_en = SUPPORTED;
                    sfc_info->sec_64k_en = sfc_info->sec_32k_en = sfc_info->sec_4k_en = NOT_SUPPORTED;
                    sfc_info->mtd_info->size = 0x1000000;
                    break;
                default:
                    printk(KERN_NOTICE "RtkSFC MTD: ST unknown id2=0x%x detected.\n",   sfc_info->device_id2);
                    SFC_64KB_ERASE;
                    sfc_info->sec_64k_en = SUPPORTED;
                    sfc_info->sec_256k_en = sfc_info->sec_32k_en = sfc_info->sec_4k_en = NOT_SUPPORTED;
                    break;
            }
            break;

        case 0xba:
            switch(sfc_info->device_id2) {
                case 0x16:
                    printk(KERN_NOTICE "RtkSFC MTD: ST N25Q032 detected.\n");
                    SFC_4KB_ERASE;
                    sfc_info->sec_4k_en = SUPPORTED;
                    sfc_info->sec_256k_en = sfc_info->sec_64k_en = sfc_info->sec_32k_en = NOT_SUPPORTED;
                    sfc_info->mtd_info->size = 0x400000;
                    break;
                case 0x17:
                    printk(KERN_NOTICE "RtkSFC MTD: ST N25Q064 detected.\n");
                    SFC_4KB_ERASE;
                    sfc_info->sec_4k_en = SUPPORTED;
                    sfc_info->sec_256k_en = sfc_info->sec_64k_en = sfc_info->sec_32k_en = NOT_SUPPORTED;
                    sfc_info->mtd_info->size = 0x800000;
                    break;
                case 0x18:
                    printk(KERN_NOTICE "RtkSFC MTD: ST N25Q128 detected.\n");
                    SFC_64KB_ERASE;
                    sfc_info->sec_64k_en = SUPPORTED;
                    sfc_info->sec_256k_en = sfc_info->sec_32k_en = sfc_info->sec_4k_en = NOT_SUPPORTED;
                    sfc_info->mtd_info->size = 0x1000000;
                    break;
                default:
                    printk(KERN_NOTICE "RtkSFC MTD: ST unknown id2=0x%x detected.\n",   sfc_info->device_id2);
                    SFC_64KB_ERASE;
                    sfc_info->sec_64k_en = SUPPORTED;
                    sfc_info->sec_256k_en = sfc_info->sec_32k_en = sfc_info->sec_4k_en = NOT_SUPPORTED;
                    break;
            }
            break;
        default:
            printk(KERN_NOTICE "RtkSFC MTD: ST unknown id1=0x%x detected.\n",   sfc_info->device_id1);
            SFC_64KB_ERASE;
            sfc_info->sec_64k_en = SUPPORTED;
            sfc_info->sec_256k_en = sfc_info->sec_32k_en = sfc_info->sec_4k_en = NOT_SUPPORTED;
            break;
    }
    if(sfc_info->erase_opcode==0xFFFFFFFF)//Set to default.
    {
        SFC_64KB_ERASE;
    }

    return 0;
}


/*--------------------------------------------------------------------------------
  EON serial flash information list
  [EON EN25B64-100FIP]64Mbits
  erase size: 64KB

  [EON EN25F16]
  erase size: 4KB / 64KB

  [EON EN25Q64]
  erase size: 4KB 


  [EON EN25Q128]
  erase size: 4KB / 64KB
  --------------------------------------------------------------------------------*/
static int eon_init(rtk_sfc_info_t *sfc_info) {
    switch(sfc_info->device_id1) {
        case 0x20:
            switch(sfc_info->device_id2) {
                case 0x17:
                    printk(KERN_NOTICE "RtkSFC MTD: EON EN25B64-100FIP detected.\n");
                    SFC_64KB_ERASE;
                    sfc_info->sec_64k_en = SUPPORTED;
                    sfc_info->sec_256k_en = sfc_info->sec_32k_en = sfc_info->sec_4k_en = NOT_SUPPORTED;
                    sfc_info->mtd_info->size = 0x800000;
                    g_isSegErase = 1;
                    break;
                default:
                    printk(KERN_NOTICE "RtkSFC MTD: EON unknown id2=0x%x detected.\n",
                            sfc_info->device_id2);
                    SFC_4KB_ERASE;
                    sfc_info->sec_4k_en = SUPPORTED;
                    sfc_info->sec_256k_en = sfc_info->sec_64k_en = sfc_info->sec_32k_en = NOT_SUPPORTED;
                    break;
            }
            return 0;

        case 0x31:
            switch(sfc_info->device_id2) {
                case 0x15:
                    printk(KERN_NOTICE "RtkSFC MTD: EON EN25F16 detected.\n");
                    SFC_4KB_ERASE;
                    sfc_info->sec_4k_en = SUPPORTED;
                    sfc_info->sec_256k_en = sfc_info->sec_64k_en = sfc_info->sec_32k_en = NOT_SUPPORTED;
                    sfc_info->mtd_info->size = 0x200000;
                    break;
                default:
                    printk(KERN_NOTICE "RtkSFC MTD: EON unknown id2=0x%x detected.\n",
                            sfc_info->device_id2);
                    break;
            }
            return 0;

        case 0x30:
            switch(sfc_info->device_id2) {
                case 0x16:
                    printk(KERN_NOTICE "RtkSFC MTD: EON EN25Q32 detected.\n");
                    SFC_4KB_ERASE;
                    sfc_info->sec_64k_en = sfc_info->sec_4k_en = SUPPORTED;
                    sfc_info->sec_256k_en = sfc_info->sec_32k_en = NOT_SUPPORTED;
                    sfc_info->mtd_info->size = 0x400000;
                    break;          
                case 0x17:
                    printk(KERN_NOTICE "RtkSFC MTD: EON EN25Q64 detected.\n");
                    SFC_4KB_ERASE;
                    sfc_info->sec_64k_en = sfc_info->sec_4k_en = SUPPORTED;
                    sfc_info->sec_256k_en = sfc_info->sec_32k_en = NOT_SUPPORTED;
                    sfc_info->mtd_info->size = 0x800000;
                    break;          
                case 0x18:
                    printk(KERN_NOTICE "RtkSFC MTD: EON EN25Q128 detected.\n");
                    SFC_4KB_ERASE;
                    sfc_info->sec_64k_en = sfc_info->sec_4k_en = SUPPORTED;
                    sfc_info->sec_256k_en = sfc_info->sec_32k_en = NOT_SUPPORTED;
                    sfc_info->mtd_info->size = 0x1000000;
                    break;
                default:
                    printk(KERN_NOTICE "RtkSFC MTD: EON unknown id2=0x%x detected.\n",
                            sfc_info->device_id2);
                    break;
            }
            return 0;

        case 0x70: 
            switch(sfc_info->device_id2) {
                case 0x15:
                    printk(KERN_NOTICE "RtkSFC MTD: EON EON_EN25QH16 detected.\n");
                    SFC_4KB_ERASE;
                    sfc_info->sec_64k_en = sfc_info->sec_32k_en = sfc_info->sec_4k_en = SUPPORTED;
                    sfc_info->sec_256k_en = NOT_SUPPORTED;
                    sfc_info->mtd_info->size = 0x1000000;
                    break;
                case 0x18:
                    printk(KERN_NOTICE "RtkSFC MTD: EON EON_EN25QH16128A detected.\n");
                    SFC_4KB_ERASE;
                    sfc_info->sec_64k_en = sfc_info->sec_32k_en = sfc_info->sec_4k_en = SUPPORTED;
                    sfc_info->sec_256k_en = NOT_SUPPORTED;
                    sfc_info->mtd_info->size = 0x1000000;
                    break;
                default:
                    printk(KERN_NOTICE "RtkSFC MTD: EON unknown id2=0x%x detected.\n",
                            sfc_info->device_id2);
                    break;
            }
            return 0;
        default:
            printk(KERN_NOTICE "RtkSFC MTD: EON unknown id1=0x%x detected.\n",
                    sfc_info->device_id1);
            break;
    }

    // set to default.
    if(sfc_info->erase_opcode == 0xFFFFFFFF) {
        SFC_64KB_ERASE;
    }

    return 0;
}

/*--------------------------------------------------------------------------------
  ATMEL serial flash information list
  [ATMEL AT25DF641A]64Mbits
  erase size: 64KB

  [ATMEL AT25DF321A]
  erase size: 4KB / 64KB
  --------------------------------------------------------------------------------*/
static int atmel_init(rtk_sfc_info_t *sfc_info) {
    switch(sfc_info->device_id1) {
        case 0x48:
        case 0x86:
            switch(sfc_info->device_id2) {
                case 0x1:
                case 0x0:
                    printk(KERN_NOTICE "RtkSFC MTD: AT25DF641A detected.\n");
                    SFC_4KB_ERASE;
                    sfc_info->sec_4k_en = SUPPORTED;
                    sfc_info->sec_256k_en = sfc_info->sec_64k_en = sfc_info->sec_32k_en = NOT_SUPPORTED;
                    sfc_info->mtd_info->size = 0x800000;
                    break;
                default:
                    printk(KERN_NOTICE "RtkSFC MTD: AT25DF641A unknown id2=0x%x detected.\n",
                            sfc_info->device_id2);
                    SFC_4KB_ERASE;
                    sfc_info->sec_4k_en = SUPPORTED;
                    sfc_info->sec_256k_en = sfc_info->sec_64k_en = sfc_info->sec_32k_en = NOT_SUPPORTED;
                    break;
            }
            return 0;

        case 0x47:
            switch(sfc_info->device_id2) {
                case 0x1:
                case 0x0:           
                    printk(KERN_NOTICE "RtkSFC MTD: AT25DF321A detected.\n");
                    SFC_4KB_ERASE;
                    sfc_info->sec_4k_en = SUPPORTED;
                    sfc_info->sec_256k_en = sfc_info->sec_64k_en = sfc_info->sec_32k_en = NOT_SUPPORTED;
                    sfc_info->mtd_info->size = 0x400000;
                    break;
                default:
                    printk(KERN_NOTICE "RtkSFC MTD: AT25DF321A like unknown id2=0x%x detected.\n",
                            sfc_info->device_id2);
                    SFC_4KB_ERASE;
                    sfc_info->sec_4k_en = SUPPORTED;
                    sfc_info->sec_256k_en = sfc_info->sec_64k_en = sfc_info->sec_32k_en = NOT_SUPPORTED;
                    sfc_info->mtd_info->size = 0x400000;
                    break;
            }
            return 0;

        default:
            printk(KERN_NOTICE "RtkSFC MTD: EON unknown id1=0x%x detected.\n",
                    sfc_info->device_id1);
            break;
    }

    // set to default.
    if(sfc_info->erase_opcode == 0xFFFFFFFF) {
        SFC_4KB_ERASE;
    }

    return 0;
}

/*--------------------------------------------------------------------------------
  WINBOND serial flash information list
  [WINBOND 25Q128BVFG]
  erase size: 

  [WINBOND W25Q32BV]32 Mbits
  erase size:4KB /32KB /64KB

  [SPANSION S25FL064K ] 64Mbits //SPANSION brand, Winbond OEM
  erase size: 4KB / 32KB / 64KB

  --------------------------------------------------------------------------------*/
static int winbond_init(rtk_sfc_info_t *sfc_info) {
    switch(sfc_info->device_id1) {
        case 0x40:
            switch(sfc_info->device_id2) {
                case 0x14:
                    printk(KERN_NOTICE "RtkSFC MTD: WINBOND W25Q80BV detected.\n");
                    SFC_4KB_ERASE;
                    sfc_info->attr |= RTK_SFC_ATTR_SUPPORT_DUAL_IO|RTK_SFC_ATTR_SUPPORT_DUAL_O;
                    sfc_info->sec_64k_en = sfc_info->sec_32k_en = sfc_info->sec_4k_en = SUPPORTED;
                    sfc_info->sec_256k_en = NOT_SUPPORTED;
                    sfc_info->mtd_info->size = 0x100000;
                    break;
                case 0x19:
                    printk(KERN_NOTICE "RtkSFC MTD: WINBOND S25FL256K detected.\n");
                    SFC_4KB_ERASE;
                    sfc_info->sec_4k_en = sfc_info->sec_32k_en = sfc_info->sec_64k_en = SUPPORTED;
                    sfc_info->sec_256k_en = NOT_SUPPORTED;
                    sfc_info->mtd_info->size = 0x2000000;
                    //louis
#if 0
                    FLASH_BASE = (unsigned char*)0xbdc00000;    
                    FLASH_POLL_ADDR = (unsigned char*)0xbec00000;
#endif
                    break;
                case 0x16:
                    printk(KERN_NOTICE "RtkSFC MTD: WINBOND W25Q32BV(W25Q32FV) detected.\n");
                    SFC_4KB_ERASE;
                    sfc_info->attr |= RTK_SFC_ATTR_SUPPORT_DUAL_IO|RTK_SFC_ATTR_SUPPORT_DUAL_O;
                    sfc_info->sec_64k_en = sfc_info->sec_32k_en = sfc_info->sec_4k_en = SUPPORTED;
                    sfc_info->sec_256k_en = NOT_SUPPORTED;
                    sfc_info->mtd_info->size = 0x400000;
                    break;
                case 0x17:
                    printk(KERN_NOTICE "RtkSFC MTD: SPANSION S25FL064K detected.\n");
                    SFC_4KB_ERASE;
                    sfc_info->attr |= RTK_SFC_ATTR_SUPPORT_DUAL_IO|RTK_SFC_ATTR_SUPPORT_DUAL_O;         
                    sfc_info->sec_4k_en = sfc_info->sec_32k_en = sfc_info->sec_64k_en = SUPPORTED;
                    sfc_info->sec_256k_en = NOT_SUPPORTED;
                    sfc_info->mtd_info->size = 0x800000;
                    break;
                case 0x18:
                    printk(KERN_NOTICE "RtkSFC MTD: WINBOND 25Q128BVFG(W25Q128BVFIG) detected.\n");
                    SFC_4KB_ERASE;
                    sfc_info->attr |= RTK_SFC_ATTR_SUPPORT_DUAL_IO|RTK_SFC_ATTR_SUPPORT_DUAL_O;
                    sfc_info->sec_64k_en = sfc_info->sec_4k_en = SUPPORTED;
                    sfc_info->sec_256k_en = sfc_info->sec_32k_en = NOT_SUPPORTED;
                    sfc_info->mtd_info->size = 0x1000000;
                    break;
                default:
                    printk(KERN_NOTICE "RtkSFC MTD: WINBOND unknown id2=0x%x detected.\n",
                            sfc_info->device_id2);
                    SFC_4KB_ERASE;
                    sfc_info->sec_4k_en = SUPPORTED;
                    sfc_info->sec_256k_en = sfc_info->sec_64k_en = sfc_info->sec_32k_en = NOT_SUPPORTED;

                    break;
            }
            return 0;
        case 0x60:
            switch(sfc_info->device_id2) {
                case 0x16:
                    printk(KERN_NOTICE "RtkSFC MTD: WINBOND W25Q32FV(Quad Mode) detected.\n");
                    SFC_4KB_ERASE;
                    sfc_info->sec_64k_en = sfc_info->sec_32k_en = sfc_info->sec_4k_en = SUPPORTED;
                    sfc_info->sec_256k_en = NOT_SUPPORTED;
                    sfc_info->mtd_info->size = 0x400000;            
                    break;
                default:
                    printk(KERN_NOTICE "RtkSFC MTD: WINBOND unknown id2=0x%x detected.\n",
                            sfc_info->device_id2);
                    SFC_4KB_ERASE;
                    sfc_info->sec_4k_en = SUPPORTED;
                    sfc_info->sec_256k_en = sfc_info->sec_64k_en = sfc_info->sec_32k_en = NOT_SUPPORTED;

                    break;
            }
            return 0;
        default:
            printk(KERN_NOTICE "RtkSFC MTD: WINBOND unknown id1=0x%x detected.\n",
                    sfc_info->device_id1);
            break;
    }
    SFC_4KB_ERASE;
    return 0;
}

/*--------------------------------------------------------------------------------
  ESMT serial flash information list
  [ESMT F25L32PA]32 Mbits
  erase size:4KB / 64KB
  [ESMT F25L64QA]64 Mbits
  erase size:4KB / 32KB / 64KB
  --------------------------------------------------------------------------------*/
static int esmt_init(rtk_sfc_info_t *sfc_info) {
    switch(sfc_info->device_id1) {
        case 0x20:
            switch(sfc_info->device_id2) {
                case 0x16:
                    printk(KERN_NOTICE "RtkSFC MTD: ESMT F25L32PA detected.\n");
                    SFC_4KB_ERASE;
                    sfc_info->sec_64k_en = sfc_info->sec_4k_en = SUPPORTED;
                    sfc_info->sec_256k_en = sfc_info->sec_32k_en = NOT_SUPPORTED;
                    sfc_info->mtd_info->size = 0x400000;
                    break;

                default:
                    printk(KERN_NOTICE "RtkSFC MTD: ESMT unknown id2=0x%x detected.\n",
                            sfc_info->device_id2);
                    SFC_4KB_ERASE;
                    sfc_info->sec_4k_en = SUPPORTED;
                    sfc_info->sec_256k_en = sfc_info->sec_64k_en = sfc_info->sec_32k_en = NOT_SUPPORTED;

                    break;
            }
            break;
        case 0x40:
            switch(sfc_info->device_id2) {
                case 0x16:
                    printk(KERN_NOTICE "RtkSFC MTD: ESMT F25L32PA detected.\n");
                    SFC_4KB_ERASE;
                    sfc_info->sec_64k_en = sfc_info->sec_4k_en = SUPPORTED;
                    sfc_info->sec_256k_en = sfc_info->sec_32k_en = NOT_SUPPORTED;
                    sfc_info->mtd_info->size = 0x400000;
                    break;

                default:
                    printk(KERN_NOTICE "RtkSFC MTD: ESMT unknown id2=0x%x detected.\n",
                            sfc_info->device_id2);
                    SFC_4KB_ERASE;
                    sfc_info->sec_4k_en = SUPPORTED;
                    sfc_info->sec_256k_en = sfc_info->sec_64k_en = sfc_info->sec_32k_en = NOT_SUPPORTED;

                    break;
            }
            break;
        case 0x41:
            switch(sfc_info->device_id2) {
                case 0x16:
                    printk(KERN_NOTICE "RtkSFC MTD: ESMT F25L32QA detected.\n");
                    SFC_4KB_ERASE;
                    sfc_info->sec_64k_en = sfc_info->sec_4k_en = SUPPORTED;
                    sfc_info->sec_256k_en = sfc_info->sec_32k_en = NOT_SUPPORTED;
                    sfc_info->mtd_info->size = 0x400000;
                    break;

                case 0x17:
                    printk(KERN_NOTICE "RtkSFC MTD: ESMT F25L64QA detected.\n");
                    SFC_4KB_ERASE;
                    sfc_info->sec_64k_en = sfc_info->sec_32k_en = sfc_info->sec_4k_en = SUPPORTED;
                    sfc_info->sec_256k_en = NOT_SUPPORTED;
                    sfc_info->mtd_info->size = 0x800000;
                    break;

                default:
                    printk(KERN_NOTICE "RtkSFC MTD: ESMT unknown id2=0x%x detected.\n",
                            sfc_info->device_id2);
                    SFC_4KB_ERASE;
                    sfc_info->sec_4k_en = SUPPORTED;
                    sfc_info->sec_256k_en = sfc_info->sec_64k_en = sfc_info->sec_32k_en = NOT_SUPPORTED;

                    break;
            }
            break;
        default:
            printk(KERN_NOTICE "RtkSFC MTD: ESMT unknown id1=0x%x detected.\n",
                    sfc_info->device_id1);
            break;
    }

    if(sfc_info->erase_opcode == 0xFFFFFFFF)//Set to default.
    {
        SFC_64KB_ERASE;
    }

    return 0;
}

inline size_t sfc_memcpy(void *dst, void *src, size_t len) {    
    int i;  
    size_t len_align;   
    if ((((unsigned long) dst & 0x3) == 0) && (((unsigned long) src & 0x03) == 0) ) {
        len_align = len & ~((unsigned long) 0x03);      
        for(i = 0; i < len_align; i += 4) {         
            *((u32*) ((u64)dst+i) ) = *((u32*)((u64)src+i));        
        }       
        for(; i < len; i ++) {          
            *((u8*) ((u64)dst+i) ) = *((u8*)((u64)src+i));      
        }                       
        return len; 
    } else if ((((unsigned long) dst & 0x1) == 0) && (((unsigned long) src & 0x01) == 0)) {     
        len_align = len & ~((unsigned long) 0x01);      
        for(i = 0; i < len_align; i += 2) {         
            *((u16*) ((u64)dst+i) ) = *((u16*)((u64)src+i));        
        }
        for(; i < len; i ++) {          
            *((u8*) ((u64)dst+i) ) = *((u8*)((u64)src+i));      
        }                   
    } else {        
        for(i=0; i < len; i ++) {           
            *((u8*) ((u64)dst+i) ) = *((u8*)((u64)src+i));      
        }                   
    }   
    return len; 
}

static void  _sfc_enable_4B_addr_mode(void)
{
	unsigned char tmp;
	/*Just can read 1 byte*/

#ifdef DEV_DEBUG
	printk(KERN_WARNING "EN4B\n");
#endif
    SFC_SYNC;
    REG_WRITE_U32(0x000000b7, SFC_OPCODE);
    REG_WRITE_U32(0x00000000, SFC_CTL);
    SFC_SYNC;
	tmp = *(volatile unsigned char*)(FLASH_BASE);
}

static void  _sfc_disable_4B_addr_mode(void)
{
	unsigned char tmp;
	/*Just can read 1 byte*/

#ifdef DEV_DEBUG
	printk(KERN_WARNING "EX4B\n");
#endif
    SFC_SYNC;
    REG_WRITE_U32(0x000000e9, SFC_OPCODE);
    REG_WRITE_U32(0x00000000, SFC_CTL);
    SFC_SYNC;
    tmp = *(volatile unsigned char*)(FLASH_BASE);
}

static void  _sfc_enable_host_4B_addr(void)
{
#ifdef DEV_DEBUG
    printk(KERN_WARNING "enable host 4B addr\n");
#endif
    SFC_SYNC;
    REG_WRITE_U32(0x00000001, 0x9801a828);
    SFC_SYNC;
}

static void  _sfc_disable_host_4B_addr(void)
{
#ifdef DEV_DEBUG
    printk(KERN_WARNING "disable host 4B addr\n");
#endif
    SFC_SYNC;
    REG_WRITE_U32(0x00000000, 0x9801a828);
    SFC_SYNC;
}

static int _sfc_read_bytes(struct mtd_info *mtd, loff_t from, size_t len,
        size_t *retlen, const u_char *buf) {
			
	unsigned int curr_nor_addr = (unsigned long long)FLASH_BASE + from;
	unsigned int nor_boundary_addr = (unsigned long long)FLASH_BASE + (16 * 1024 * 1024);
	unsigned int byte_len_before_16MB, byte_len_after_16MB;
	
	if (curr_nor_addr < nor_boundary_addr) {
        if ((curr_nor_addr + len) > nor_boundary_addr) {
            byte_len_before_16MB = nor_boundary_addr - curr_nor_addr;
            byte_len_after_16MB = len - byte_len_before_16MB;
        }
        else {
            byte_len_before_16MB = len;
            byte_len_after_16MB = 0;
        }
    }
    else {
        byte_len_before_16MB = 0;
        byte_len_after_16MB = len;
    }

	/* read berfore 16MB */
    if (byte_len_before_16MB) {
        _switch_to_read_mode((rtk_sfc_info_t*)mtd->priv, eREAD_MODE_SINGLE_FAST_READ);

        *retlen = sfc_memcpy((void *)buf, (void *)(FLASH_BASE + from), byte_len_before_16MB); 
    }

    /* read after 16MB */
    if (byte_len_after_16MB) {
        _sfc_enable_4B_addr_mode();
        _sfc_enable_host_4B_addr();
        _switch_to_read_mode((rtk_sfc_info_t*)mtd->priv, eREAD_MODE_SINGLE_FAST_READ);

        *retlen = sfc_memcpy((void *)(buf + byte_len_before_16MB),
			(void *)(FLASH_BASE + from + byte_len_before_16MB), byte_len_after_16MB); 

        _sfc_disable_4B_addr_mode();
        _sfc_disable_host_4B_addr();
    }  

    return 0;
}

#ifdef CONFIG_MTD_RTK_SFC_READ_MD
static int _sfc_read_md(struct mtd_info *mtd, loff_t from, size_t len,
					size_t *retlen, u_char *buf) {

	volatile u8 *src = (volatile u8*)(NOR_BASE_PHYS + from);
	
	u32 val;
	int ret;

    u8 *dest = (u8*)buf;
    u32 read_count = 0;

    u8 *p_data_buf;
    int i;
	
	unsigned int curr_nor_addr = (unsigned long long)FLASH_BASE + from;
	unsigned int nor_boundary_addr = (unsigned long long)FLASH_BASE + (16 * 1024 * 1024);
	unsigned int byte_len_before_16MB, byte_len_after_16MB;
    
#ifdef CONFIG_MTD_RTK_MD_READ_COMPARE
	u8 *org_src = (u8*)buf;
	unsigned int org_from = from;
	size_t org_len = len;
retry_mdread:
#endif

#ifdef DEV_DEBUG
	printk(KERN_WARNING "Rtk SFC MTD: %s() $ [%08X => %08X (virt: %08X) : %08X]\n", __func__, (u32)(u64)src, (unsigned long)(virt_to_phys(buf)), (u32)(u64)buf, (int)len);
#endif

	if(unlikely((len <= RTK_SFC_SMALL_PAGE_WRITE_MASK) || (len & RTK_SFC_SMALL_PAGE_WRITE_MASK)))
		BUG();
	
	if (curr_nor_addr < nor_boundary_addr) {
		if ((curr_nor_addr + len) > nor_boundary_addr) {
			byte_len_before_16MB = nor_boundary_addr - curr_nor_addr;
			byte_len_after_16MB = len - byte_len_before_16MB;
		}
		else {
			byte_len_before_16MB = len;
			byte_len_after_16MB = 0;
        }
    }
	else {
		byte_len_before_16MB = 0;
		byte_len_after_16MB = len;
	}

	if (byte_len_before_16MB) {
		len = byte_len_before_16MB;
		while(len > 0) {
			size_t dma_length;
			
			if(len >= MD_PP_DATA_SIZE)
				dma_length = MD_PP_DATA_SIZE;
			else
				dma_length = len;

			p_data_buf = (u8 *)read_dma_buf;

			_switch_to_read_mode((rtk_sfc_info_t*)mtd->priv, eREAD_MODE_DUAL_FAST_READ);

			//setup MD DDR addr and flash addr
			//REG_WRITE_U32(((unsigned int)dest), MD_FDMA_DDR_SADDR);
			REG_WRITE_U32(((unsigned long)read_dma_handle), MD_FDMA_DDR_SADDR);
			REG_WRITE_U32(((unsigned long)src), MD_FDMA_FL_SADDR);

			//setup MD direction and move data length
			val = (0x2C000000 | dma_length);        //do swap
			REG_WRITE_U32(val, MD_FDMA_CTRL2);		//for dma_length bytes.

			mb();
			SFC_SYNC;

			//go 
			REG_WRITE_U32(0x03, MD_FDMA_CTRL1);

			/* wait for MD done its operation */
			while((ret = REG_READ_U32(MD_FDMA_CTRL1)) & 0x1);

			for (i = 0; i < dma_length; i++) {
				dest[i] = p_data_buf[i];
			}

			src += dma_length;
			dest += dma_length;
			read_count += dma_length;
			len -= dma_length;
		}
	}
	
	if (byte_len_after_16MB) {
		_sfc_enable_4B_addr_mode();
        _sfc_enable_host_4B_addr();	
	
		len = byte_len_after_16MB;
		while(len > 0) {
			size_t dma_length;
			
			if(len >= MD_PP_DATA_SIZE)
				dma_length = MD_PP_DATA_SIZE;
			else
				dma_length = len;

			p_data_buf = (u8 *)read_dma_buf;

			_switch_to_read_mode((rtk_sfc_info_t*)mtd->priv, eREAD_MODE_DUAL_FAST_READ);

			//setup MD DDR addr and flash addr
			//REG_WRITE_U32(((unsigned int)dest), MD_FDMA_DDR_SADDR);
			REG_WRITE_U32(((unsigned long)read_dma_handle), MD_FDMA_DDR_SADDR);
			REG_WRITE_U32(((unsigned long)src), MD_FDMA_FL_SADDR);

			//setup MD direction and move data length
			val = (0x2C000000 | dma_length);        //do swap
			REG_WRITE_U32(val, MD_FDMA_CTRL2);		//for dma_length bytes.

			mb();
			SFC_SYNC;

			//go 
			REG_WRITE_U32(0x03, MD_FDMA_CTRL1);

			/* wait for MD done its operation */
			while((ret = REG_READ_U32(MD_FDMA_CTRL1)) & 0x1);

			for (i = 0; i < dma_length; i++) {
				dest[i] = p_data_buf[i];
			}

			src += dma_length;
			dest += dma_length;
			read_count += dma_length;
			len -= dma_length;
		}
		_sfc_disable_4B_addr_mode();
        _sfc_disable_host_4B_addr();
	}

    *retlen = read_count;

	return 0;
}
//---------------------------------------------------------------------------------------------

static int rtk_sfc_read_pages(struct mtd_info *mtd, loff_t from, size_t len,
						size_t *retlen, u_char *buf) {
	rtk_sfc_info_t *sfc_info;
	size_t read_len = 0;
	size_t rlen = 0;
	size_t length_to_read;
	unsigned long buf_addr = 0;
#ifdef CONFIG_MTD_RTK_MD_READ_COMPARE
	u8 *org_src = (u8*)buf;
	unsigned int org_from = from;
	size_t org_len = len;
retry_read:
#endif

#ifdef DEV_DEBUG 
    printk(KERN_WARNING "Rtk SFC MTD: rtk_sfc_read_pages(), from = %08X, length = %08X\n", (int)from, (int)len);
#endif

#if defined(CONFIG_MTD_RTK_SFC_DEBUG)
	add_debug_entry(from, buf, len, READ_ACCESS);
#endif

	if((sfc_info = (rtk_sfc_info_t*)mtd->priv) == NULL)
		return -EINVAL;

	down_write(&rw_sem);

	buf_addr = (unsigned long)buf;
	SFC_FLUSH_CACHE(buf_addr,len);

	/* Set SB2 to in-order mode */
	//_before_serial_flash_access();

	*retlen = 0;

#if defined(CONFIG_MTD_RTK_SFC_DEBUG)
	change_status(READ_READY);
#endif

	// 1st pass: read data 0-3 bytes 
	if(len > 0 && (from & RTK_SFC_SMALL_PAGE_WRITE_MASK)) {
		if(len > RTK_SFC_SMALL_PAGE_WRITE_MASK)
			length_to_read = (RTK_SFC_SMALL_PAGE_WRITE_MASK + 1) - (from & RTK_SFC_SMALL_PAGE_WRITE_MASK);
		else
			length_to_read = len;

		_sfc_read_bytes(mtd, from, length_to_read, &rlen, buf);

#ifdef DEV_DEBUG 
		printk(KERN_WARNING "Rtk SFC MTD: rtk_sfc_read() $ PASS #1 $ [%08X:%08X]\n", (int)from, (int)len);
		printk(KERN_WARNING "Rtk SFC MTD: rtk_sfc_read() $ PASS #1 $ %d bytes read\n", (int)rlen);
#endif

		from += rlen;
		read_len += rlen;
		len -= rlen;
		buf += rlen;
	}

#if defined(CONFIG_MTD_RTK_SFC_DEBUG)
	change_status(READ_STAGE_1);
#endif

	// 2rd pass: using MD to read data which aligned in 4 bytes
	if(len > RTK_SFC_SMALL_PAGE_WRITE_MASK && ((((unsigned long)buf) & RTK_SFC_SMALL_PAGE_WRITE_MASK)==0)  && 
		((from &  RTK_SFC_SMALL_PAGE_WRITE_MASK)==0)) 
	{
		length_to_read = len & (~RTK_SFC_SMALL_PAGE_WRITE_MASK);

		_sfc_read_md(mtd, from, length_to_read, &rlen, buf);

#ifdef DEV_DEBUG 
		printk(KERN_WARNING "Rtk SFC MTD: rtk_sfc_read() $ PASS #2 $ [%08X:%08X]\n", (int)from, (int)len);
		printk(KERN_WARNING "Rtk SFC MTD: rtk_sfc_read() $ PASS #2 $ %d bytes read\n", (int)rlen);
#endif

		from += rlen;
		read_len += rlen;
		len -= rlen;
		buf += rlen;
	}

#if defined(CONFIG_MTD_RTK_SFC_DEBUG)
	change_status(READ_STAGE_2);
#endif

	// 3rd pass: read rest data (0-3 bytes)
	if(len > 0) {
		length_to_read = len;

    	//dma_cache_sync(NULL,buf, len, DMA_FROM_DEVICE);
		_sfc_read_bytes(mtd, from, length_to_read, &rlen, buf);

#ifdef DEV_DEBUG 
		printk(KERN_WARNING "Rtk SFC MTD: rtk_sfc_read() $ PASS #3 $ [%08X:%08X]\n", (int)from, (int)len);
		printk(KERN_WARNING "Rtk SFC MTD: rtk_sfc_read() $ PASS #3 $ %d bytes read\n", (int)rlen);
#endif

		from += rlen;
		read_len += rlen;
		len -= rlen;
		buf += rlen;
	}

	*retlen = read_len;

#if defined(CONFIG_MTD_RTK_SFC_DEBUG)
	change_status(READ_STAGE_3);
#endif
	/* Restore SB2 */
	//_after_serial_flash_access();
#if 0
//#ifdef CONFIG_MTD_RTK_MD_READ_COMPARE 
	if (memcmp((void *) (FLASH_BASE + org_from), (void *) org_src, org_len)) {
	    	printk("read error at buf=%x %x len=%x\n", org_src, (FLASH_BASE + org_from), org_len);	
		printk("\nsrc: ");
		int i;
		for (i=0; i < org_len; i++) {
			printk("%02x ", org_src[i]);
			if (i%8 == 7) printk("\n");
		}
		printk("\ndest: ");
		for (i=0; i < org_len; i++) {
			printk("%02x ",  ((unsigned char *)(FLASH_BASE + org_from))[i]);
			if (i%8 == 7) printk("\n");
		}			
		goto retry_read;
	}
#endif	

	up_write(&rw_sem);

#if defined(CONFIG_MTD_RTK_SFC_DEBUG)
	change_status(READ_COMPLETED);
#endif
	return 0;
}
#endif

static int rtk_sfc_read(struct mtd_info *mtd, loff_t from, size_t len,
        size_t *retlen, u_char *buf) {
    rtk_sfc_info_t *sfc_info;
#ifdef EMMC_ISSUE_LOCK
    unsigned long lock_flag;
#endif

#if defined(CONFIG_MTD_RTK_SFC_DEBUG)
    add_debug_entry(from, buf, len, READ_ACCESS);
#endif

    if((sfc_info = (rtk_sfc_info_t*)mtd->priv) == NULL)
        return -EINVAL;
    if(!buf)
        return -EINVAL;

    down_write(&rw_sem);

#ifdef EMMC_ISSUE_LOCK
    rtk_lockapi_lock(lock_flag, (char *)__FUNCTION__);
#endif

    SFC_FLUSH_CACHE((unsigned long) &buf,len);

#if defined(CONFIG_MTD_RTK_SFC_DEBUG)
    change_status(READ_READY);
#endif

#ifdef DEV_DEBUG 
    printk(KERN_WARNING "Rtk SFC MTD: rtk_sfc_read(), from = %08X, length = %08X\n", (int)from, (int)len);
#endif

    *retlen = 0;

    _sfc_read_bytes(mtd, from, len, retlen, buf);

#ifdef EMMC_ISSUE_LOCK
    rtk_lockapi_unlock(lock_flag, (char *)__FUNCTION__);
#endif

    up_write(&rw_sem);

#if defined(CONFIG_MTD_RTK_SFC_DEBUG)
    change_status(READ_COMPLETED);
#endif

    return 0;
}

static int _sfc_write_bytes(struct mtd_info *mtd, loff_t to, size_t len,
        size_t *retlen, const u_char *buf) {
    u8 *src = (u8*)buf;
    volatile u8 *dest = (volatile u8*)(FLASH_BASE + to);
    u32 written_count = 0;
	
	unsigned int curr_nor_addr = (unsigned long long)FLASH_BASE + to;
	unsigned int nor_boundary_addr = (unsigned long long)FLASH_BASE + (16 * 1024 * 1024);
	unsigned int byte_len_before_16MB, byte_len_after_16MB;
	
	if (curr_nor_addr < nor_boundary_addr) {
        if ((curr_nor_addr + len) > nor_boundary_addr) {
            byte_len_before_16MB = nor_boundary_addr - curr_nor_addr;
            byte_len_after_16MB = len - byte_len_before_16MB;
        }
        else {
            byte_len_before_16MB = len;
            byte_len_after_16MB = 0;
        }
    }
    else {
        byte_len_before_16MB = 0;
        byte_len_after_16MB = len;
    }

    //rtk_sfc_info_t *sfc_info = (rtk_sfc_info_t*)mtd->priv;    

    // write enable
    REG_WRITE_U32(0x00000006,SFC_OPCODE);
    REG_WRITE_U32(0x00000000,SFC_CTL);
    SFC_SYNC;

    // disable write protect
    REG_WRITE_U32(0x00000000,SFC_WP);

    // enable write status register
    REG_WRITE_U32(0x00000050,SFC_OPCODE);
    REG_WRITE_U32(0x00000000,SFC_CTL);
    SFC_SYNC;

    // write status register , no memory protection
    REG_WRITE_U32(0x00000001,SFC_OPCODE);
    REG_WRITE_U32(0x00000010,SFC_CTL);
    SFC_SYNC;

    REG_WRITE_U32(0x00000106,SFC_EN_WR);
    REG_WRITE_U32(0x00000105,SFC_WAIT_WR);
    REG_WRITE_U32(0x00ffffff,SFC_CE);
	
	if (byte_len_before_16MB) {
		SFC_SYNC;
		SYS_REG_TRY_LOCK(0);//add by alexchang 0722-2010
		REG_WRITE_U32(0x00000002, SFC_OPCODE);  /* Byte Programming */
#if SFC_USE_DELAY
		sfc_delay();
#endif

		REG_WRITE_U32(0x00000018, SFC_CTL); /* dataen = 1, adren = 1, dmycnt = 0 */
		SYS_REG_TRY_UNLOCK;//add by alexchang 0722-2010
		SFC_SYNC;

		len = byte_len_before_16MB;
		while(len--) {
			/* send write enable first */
			SFC_SYNC;
			SYS_REG_TRY_LOCK(0);//add by alexchang 0722-2010
			REG_WRITE_U32(0x00000006, SFC_OPCODE);  /* Write enable */
#if SFC_USE_DELAY
			sfc_delay();
#endif
			REG_WRITE_U32(0x00180000, SFC_CTL); /* dataen = 0, adren = 0, dmycnt = 0 */
			SYS_REG_TRY_UNLOCK;//add by alexchang 0722-2010
			SFC_SYNC;

			SFC_SYNC;
			SYS_REG_TRY_LOCK(0);//add by alexchang 0722-2010
			REG_WRITE_U32(0x00000002, SFC_OPCODE);  /* Byte Programming */
#if SFC_USE_DELAY
			sfc_delay();
#endif
			REG_WRITE_U32(0x00000018, SFC_CTL); /* dataen = 1, adren = 1, dmycnt = 0 */
			SYS_REG_TRY_UNLOCK;//add by alexchang 0722-2010
			SFC_SYNC;

			*dest++ = *src++;
			mb();
#if !SFC_HW_POLL
			/* using RDSR to make sure the operation is completed. */
			do {
				SFC_SYNC;
				SYS_REG_TRY_LOCK(0);//add by alexchang 0722-2010
				REG_WRITE_U32(0x00000005, SFC_OPCODE);  /* RDSR */
#if SFC_USE_DELAY 
				sfc_delay();
#endif
				REG_WRITE_U32(0x00000010, SFC_CTL); /* dataen = 1, adren = 0, dmycnt = 0 */
				SYS_REG_TRY_UNLOCK;//add by alexchang 0722-2010
				SFC_SYNC;
			} while((*(volatile unsigned char *)FLASH_POLL_ADDR) & 0x1);
#endif
			written_count++;
		}
	}
	
	if (byte_len_after_16MB) {
		_sfc_enable_4B_addr_mode();
        _sfc_enable_host_4B_addr();
		
		SFC_SYNC;
		SYS_REG_TRY_LOCK(0);//add by alexchang 0722-2010
		REG_WRITE_U32(0x00000002, SFC_OPCODE);  /* Byte Programming */
#if SFC_USE_DELAY
		sfc_delay();
#endif

		REG_WRITE_U32(0x00000018, SFC_CTL); /* dataen = 1, adren = 1, dmycnt = 0 */
		SYS_REG_TRY_UNLOCK;//add by alexchang 0722-2010
		SFC_SYNC;

		len = byte_len_after_16MB;
		while(len--) {
			/* send write enable first */
			SFC_SYNC;
			SYS_REG_TRY_LOCK(0);//add by alexchang 0722-2010
			REG_WRITE_U32(0x00000006, SFC_OPCODE);  /* Write enable */
#if SFC_USE_DELAY
			sfc_delay();
#endif
			REG_WRITE_U32(0x00180000, SFC_CTL); /* dataen = 0, adren = 0, dmycnt = 0 */
			SYS_REG_TRY_UNLOCK;//add by alexchang 0722-2010
			SFC_SYNC;

			SFC_SYNC;
			SYS_REG_TRY_LOCK(0);//add by alexchang 0722-2010
			REG_WRITE_U32(0x00000002, SFC_OPCODE);  /* Byte Programming */
#if SFC_USE_DELAY
			sfc_delay();
#endif
			REG_WRITE_U32(0x00000018, SFC_CTL); /* dataen = 1, adren = 1, dmycnt = 0 */
			SYS_REG_TRY_UNLOCK;//add by alexchang 0722-2010
			SFC_SYNC;

			*dest++ = *src++;
			mb();
#if !SFC_HW_POLL
			/* using RDSR to make sure the operation is completed. */
			do {
				SFC_SYNC;
				SYS_REG_TRY_LOCK(0);//add by alexchang 0722-2010
				REG_WRITE_U32(0x00000005, SFC_OPCODE);  /* RDSR */
#if SFC_USE_DELAY 
				sfc_delay();
#endif
				REG_WRITE_U32(0x00000010, SFC_CTL); /* dataen = 1, adren = 0, dmycnt = 0 */
				SYS_REG_TRY_UNLOCK;//add by alexchang 0722-2010
				SFC_SYNC;
			} while((*(volatile unsigned char *)FLASH_POLL_ADDR) & 0x1);
#endif
			written_count++;
		}
		
		_sfc_disable_4B_addr_mode();
        _sfc_disable_host_4B_addr();
	}

    /* send write disable then */
    SFC_SYNC;
    SYS_REG_TRY_LOCK(0);//add by alexchang 0722-2010
    REG_WRITE_U32(0x00000004, SFC_OPCODE);  /* Write disable */

    REG_WRITE_U32(0x00000000, SFC_CTL); /* dataen = 0, adren = 0, dmycnt = 0 */
    SYS_REG_TRY_UNLOCK;//add by alexchang 0722-2010
    SFC_SYNC;

    *retlen = written_count;

    return 0;
}

#ifdef CONFIG_MTD_RTK_SFC_WRITE_MD
/*
 * _sfc_write_small_pages()
 * using MD to write data from DDR to FLASH which size is within a single page
 *
 * pass-in address must be aligned on 4-bytes, and 
 * length must be multiples of 4-bytes
 */

static int _sfc_write_small_pages(struct mtd_info *mtd, loff_t to, size_t len,
					size_t *retlen, const u_char *buf) {

	u8 *src = (u8*)buf;
	volatile u8 *dest = (volatile u8*)(NOR_BASE_PHYS + to);
	u32 written_count = 0;
	//static u8 true_data_buf[MD_PP_DATA_SIZE*2];
	//u8 *data_buf;
	u32 val;
	int ret;
	int i;
#ifdef EMMC_ISSUE_LOCK
    unsigned long lock_flag;
#endif

    u8 *p_data_buf;
	
	unsigned int curr_nor_addr = (unsigned long long)FLASH_BASE + to;
	unsigned int nor_boundary_addr = (unsigned long long)FLASH_BASE + (16 * 1024 * 1024);
	unsigned int byte_len_before_16MB, byte_len_after_16MB;
    
	rtk_sfc_info_t *sfc_info = (rtk_sfc_info_t*)mtd->priv;
    (void)sfc_info;

	// support write fewer than 256 bytes and size must be multiples of 4-bytes
	if(unlikely((len >= MD_PP_DATA_SIZE) || (len & RTK_SFC_SMALL_PAGE_WRITE_MASK)))
		BUG();

	if((to & RTK_SFC_SMALL_PAGE_WRITE_MASK)) // only support write onto 4-bytes aligned area
		BUG();
		
	if (curr_nor_addr < nor_boundary_addr) {
        if ((curr_nor_addr + len) > nor_boundary_addr) {
            byte_len_before_16MB = nor_boundary_addr - curr_nor_addr;
            byte_len_after_16MB = len - byte_len_before_16MB;
        }
        else {
            byte_len_before_16MB = len;
            byte_len_after_16MB = 0;
        }
    }
    else {
        byte_len_before_16MB = 0;
        byte_len_after_16MB = len;
    }

#ifdef EMMC_ISSUE_LOCK
    rtk_lockapi_lock(lock_flag, (char *)__FUNCTION__);
#endif

    // write enable
	REG_WRITE_U32(0x00000006,SFC_OPCODE);
	REG_WRITE_U32(0x00000000,SFC_CTL);
	SFC_SYNC;

	// disable write protect
	REG_WRITE_U32(0x00000000,SFC_WP);
 
	// enable write status register
	REG_WRITE_U32(0x00000050,SFC_OPCODE);
	REG_WRITE_U32(0x00000000,SFC_CTL);
	SFC_SYNC;

	// write status register , no memory protection
	REG_WRITE_U32(0x00000001,SFC_OPCODE);
	REG_WRITE_U32(0x00000010,SFC_CTL);
	SFC_SYNC;

    REG_WRITE_U32(0x00000106,SFC_EN_WR);
    REG_WRITE_U32(0x00000105,SFC_WAIT_WR);
    REG_WRITE_U32(0x00ffffff,SFC_CE);

	if (byte_len_before_16MB) {
		SFC_SYNC;
		SYS_REG_TRY_LOCK(0);//add by alexchang 0722-2010
		REG_WRITE_U32(0x00000002, SFC_OPCODE);	/* Byte Programming */
#if SFC_USE_DELAY
		sfc_delay();
#endif

		REG_WRITE_U32(0x00000018, SFC_CTL);	/* dataen = 1, adren = 1, dmycnt = 0 */
		SYS_REG_TRY_UNLOCK;//add by alexchang 0722-2010
		SFC_SYNC;

#ifdef EMMC_ISSUE_LOCK
		rtk_lockapi_unlock(lock_flag, (char *)__FUNCTION__);
#endif
		len = byte_len_before_16MB;
		while(len > 0) {
			p_data_buf = (u8 *)write_dma_buf;
        
			for(i = 0; i < len ; i += 4) { /* endian convert */
#if 0
				val = *((u32*)(src + i));
				*((u32*)(data_buf + i)) = 
#if 0
							((val >> 24) |
							((val >> 8 ) & 0x0000ff00) |
							((val << 8 ) & 0x00ff0000) |
							(val << 24));
#else
							val;
#endif
#endif
				*((u32*)(p_data_buf + i)) = *((u32*)(src + i));
			}

#ifdef EMMC_ISSUE_LOCK
			rtk_lockapi_lock(lock_flag, (char *)__FUNCTION__);
#endif

			//issue write command
			SFC_SYNC;
			SYS_REG_TRY_LOCK(0);//add by alexchang 0722-2010
			REG_WRITE_U32(0x00000002, SFC_OPCODE);
		
#if SFC_USE_DELAY
			sfc_delay();
#endif

			REG_WRITE_U32(0x00000018, SFC_CTL);
			SYS_REG_TRY_UNLOCK;//add by alexchang 0722-2010
			SFC_SYNC;

#ifdef EMMC_ISSUE_LOCK
			rtk_lockapi_unlock(lock_flag, (char *)__FUNCTION__);
#endif

			//setup MD DDR addr and flash addr
			//REG_WRITE_U32(((unsigned long)virt_to_phys(data_buf)), MD_FDMA_DDR_SADDR);
			REG_WRITE_U32(((unsigned long)write_dma_handle), MD_FDMA_DDR_SADDR);
			REG_WRITE_U32(((unsigned long)dest), MD_FDMA_FL_SADDR);


			//setup MD direction and move data length
			val = (0x2E000000 | len);               // do swap
			REG_WRITE_U32(val, MD_FDMA_CTRL2);		//for dma_length bytes.

			//dma_cache_sync(NULL,data_buf, len, DMA_TO_DEVICE);

			mb();
			SFC_SYNC;

			//go 
			REG_WRITE_U32(0x03, MD_FDMA_CTRL1);

			/* wait for MD done its operation */
			while((ret = REG_READ_U32(MD_FDMA_CTRL1)) & 0x1);

#if !SFC_HW_POLL
			/* wait for flash controller done its operation */
			do {
#ifdef EMMC_ISSUE_LOCK
				rtk_lockapi_lock(lock_flag, (char *)__FUNCTION__);
#endif

				SFC_SYNC;

				SYS_REG_TRY_LOCK(0);//add by alexchang 0722-2010
				REG_WRITE_U32(0x00000005, SFC_OPCODE); 
#if SFC_USE_DELAY
				sfc_delay();
#endif
				REG_WRITE_U32(0x00000010, SFC_CTL);
				SYS_REG_TRY_UNLOCK;//add by alexchang 0722-2010
				SFC_SYNC;

#ifdef EMMC_ISSUE_LOCK
				rtk_lockapi_unlock(lock_flag, (char *)__FUNCTION__);
#endif
			} while((*(volatile unsigned char *)FLASH_POLL_ADDR) & 0x1);
#endif     	    
			/* shift to next page to writing */
			src += len;
			dest += len;
			written_count += len;
			len -= len;
		} //end of page program
	}
	
	if (byte_len_after_16MB) {
		_sfc_enable_4B_addr_mode();
        _sfc_enable_host_4B_addr();
		
		SFC_SYNC;
		SYS_REG_TRY_LOCK(0);//add by alexchang 0722-2010
		REG_WRITE_U32(0x00000002, SFC_OPCODE);	/* Byte Programming */
#if SFC_USE_DELAY
		sfc_delay();
#endif

		REG_WRITE_U32(0x00000018, SFC_CTL);	/* dataen = 1, adren = 1, dmycnt = 0 */
		SYS_REG_TRY_UNLOCK;//add by alexchang 0722-2010
		SFC_SYNC;

#ifdef EMMC_ISSUE_LOCK
		rtk_lockapi_unlock(lock_flag, (char *)__FUNCTION__);
#endif
		len = byte_len_after_16MB;
		while(len > 0) {
			p_data_buf = (u8 *)write_dma_buf;
        
			for(i = 0; i < len ; i += 4) { /* endian convert */
#if 0
				val = *((u32*)(src + i));
				*((u32*)(data_buf + i)) = 
#if 0
							((val >> 24) |
							((val >> 8 ) & 0x0000ff00) |
							((val << 8 ) & 0x00ff0000) |
							(val << 24));
#else
							val;
#endif
#endif
				*((u32*)(p_data_buf + i)) = *((u32*)(src + i));
			}

#ifdef EMMC_ISSUE_LOCK
			rtk_lockapi_lock(lock_flag, (char *)__FUNCTION__);
#endif

			//issue write command
			SFC_SYNC;
			SYS_REG_TRY_LOCK(0);//add by alexchang 0722-2010
			REG_WRITE_U32(0x00000002, SFC_OPCODE);
		
#if SFC_USE_DELAY
			sfc_delay();
#endif

			REG_WRITE_U32(0x00000018, SFC_CTL);
			SYS_REG_TRY_UNLOCK;//add by alexchang 0722-2010
			SFC_SYNC;

#ifdef EMMC_ISSUE_LOCK
			rtk_lockapi_unlock(lock_flag, (char *)__FUNCTION__);
#endif

			//setup MD DDR addr and flash addr
			//REG_WRITE_U32(((unsigned long)virt_to_phys(data_buf)), MD_FDMA_DDR_SADDR);
			REG_WRITE_U32(((unsigned long)write_dma_handle), MD_FDMA_DDR_SADDR);
			REG_WRITE_U32(((unsigned long)dest), MD_FDMA_FL_SADDR);


			//setup MD direction and move data length
			val = (0x2E000000 | len);               // do swap
			REG_WRITE_U32(val, MD_FDMA_CTRL2);		//for dma_length bytes.

			//dma_cache_sync(NULL,data_buf, len, DMA_TO_DEVICE);

			mb();
			SFC_SYNC;

			//go 
			REG_WRITE_U32(0x03, MD_FDMA_CTRL1);

			/* wait for MD done its operation */
			while((ret = REG_READ_U32(MD_FDMA_CTRL1)) & 0x1);

#if !SFC_HW_POLL
			/* wait for flash controller done its operation */
			do {
#ifdef EMMC_ISSUE_LOCK
				rtk_lockapi_lock(lock_flag, (char *)__FUNCTION__);
#endif

				SFC_SYNC;

				SYS_REG_TRY_LOCK(0);//add by alexchang 0722-2010
				REG_WRITE_U32(0x00000005, SFC_OPCODE); 
#if SFC_USE_DELAY
				sfc_delay();
#endif
				REG_WRITE_U32(0x00000010, SFC_CTL);
				SYS_REG_TRY_UNLOCK;//add by alexchang 0722-2010
				SFC_SYNC;

#ifdef EMMC_ISSUE_LOCK
				rtk_lockapi_unlock(lock_flag, (char *)__FUNCTION__);
#endif
			} while((*(volatile unsigned char *)FLASH_POLL_ADDR) & 0x1);
#endif     	    
			/* shift to next page to writing */
			src += len;
			dest += len;
			written_count += len;
			len -= len;
		} //end of page program
		
		_sfc_disable_4B_addr_mode();
        _sfc_disable_host_4B_addr();
	}

#ifdef EMMC_ISSUE_LOCK
    rtk_lockapi_lock(lock_flag, (char *)__FUNCTION__);
#endif

    /* send write disable then */
    SFC_SYNC;
 
	SYS_REG_TRY_LOCK(0);//add by alexchang 0722-2010
	REG_WRITE_U32(0x00000004, SFC_OPCODE);	/* Write disable */ 
#if SFC_USE_DELAY
	sfc_delay();
#endif

	REG_WRITE_U32(0x00000000, SFC_CTL);	/* dataen = 0, adren = 0, dmycnt = 0 */
	SYS_REG_TRY_UNLOCK;//add by alexchang 0722-2010
	SFC_SYNC;

#ifdef EMMC_ISSUE_LOCK
    rtk_lockapi_unlock(lock_flag, (char *)__FUNCTION__);
#endif

	*retlen = written_count;

	return 0;
}

static int _sfc_write_pages(struct mtd_info *mtd, loff_t to, size_t len,
					size_t *retlen, const u_char *buf) {

	u8 *src = (u8*)buf;
	volatile u8 *dest = (volatile u8*)(NOR_BASE_PHYS + to);
	u32 written_count = 0;
	//u8 data_buf[MD_PP_DATA_SIZE];
	u32 val;
	int ret;
	int i;
#ifdef EMMC_ISSUE_LOCK
    unsigned long lock_flag;
#endif

    u8 *p_data_buf;
	
	unsigned int curr_nor_addr = (unsigned long long)FLASH_BASE + to;
	unsigned int nor_boundary_addr = (unsigned long long)FLASH_BASE + (16 * 1024 * 1024);
	unsigned int byte_len_before_16MB, byte_len_after_16MB;

	rtk_sfc_info_t *sfc_info = (rtk_sfc_info_t*)mtd->priv;
    (void)sfc_info;

	if(unlikely((len < MD_PP_DATA_SIZE))) {
		*retlen = 0;
		return 0;
	}

	if(unlikely(((u64)dest&(MD_PP_DATA_SIZE-1)))) {
		BUG();
	}
	
	if (curr_nor_addr < nor_boundary_addr) {
        if ((curr_nor_addr + len) > nor_boundary_addr) {
            byte_len_before_16MB = nor_boundary_addr - curr_nor_addr;
            byte_len_after_16MB = len - byte_len_before_16MB;
        }
        else {
            byte_len_before_16MB = len;
            byte_len_after_16MB = 0;
        }
    }
    else {
        byte_len_before_16MB = 0;
        byte_len_after_16MB = len;
    }

#ifdef EMMC_ISSUE_LOCK
    rtk_lockapi_lock(lock_flag, (char *)__FUNCTION__);
#endif

    // write enable
	REG_WRITE_U32(0x00000006,SFC_OPCODE);
	REG_WRITE_U32(0x00000000,SFC_CTL);
	SFC_SYNC;

	// disable write protect
	REG_WRITE_U32(0x00000000,SFC_WP);
 
	// enable write status register
	REG_WRITE_U32(0x00000050,SFC_OPCODE);
	REG_WRITE_U32(0x00000000,SFC_CTL);
	SFC_SYNC;

	// write status register , no memory protection
	REG_WRITE_U32(0x00000001,SFC_OPCODE);
	REG_WRITE_U32(0x00000010,SFC_CTL);
	SFC_SYNC;
 
	REG_WRITE_U32(0x00000106,SFC_EN_WR);
    REG_WRITE_U32(0x00000105,SFC_WAIT_WR);
    REG_WRITE_U32(0x00ffffff,SFC_CE);

	if (byte_len_before_16MB) {
		SFC_SYNC;
		SYS_REG_TRY_LOCK(0);//add by alexchang 0722-2010
		REG_WRITE_U32(0x00000002, SFC_OPCODE);	/* Byte Programming */
#if SFC_USE_DELAY
		sfc_delay();
#endif

		REG_WRITE_U32(0x00000018, SFC_CTL);	/* dataen = 1, adren = 1, dmycnt = 0 */
		SYS_REG_TRY_UNLOCK;//add by alexchang 0722-2010
		SFC_SYNC;

#ifdef EMMC_ISSUE_LOCK
		rtk_lockapi_unlock(lock_flag, (char *)__FUNCTION__);
#endif 
		len = byte_len_before_16MB;
		while(len >= MD_PP_DATA_SIZE) {
			p_data_buf = (u8 *)write_dma_buf;
			
			/* data moved by MD module is endian inverted.
						revert it before moved to flash */
			for(i = 0; i < MD_PP_DATA_SIZE; i += 4) {
#if 0
				val = *((u32*)(src + i));
				*((u32*)(data_buf + i)) = 
#if 0
							((val >> 24) |
							((val >> 8 ) & 0x0000ff00) |
							((val << 8 ) & 0x00ff0000) |
							(val << 24));
#else
							val;
#endif
#endif
				*((u32*)(p_data_buf + i)) = *((u32*)(src + i));
			}

#ifdef EMMC_ISSUE_LOCK
			rtk_lockapi_lock(lock_flag, (char *)__FUNCTION__);
#endif

			SFC_SYNC; 
			SYS_REG_TRY_LOCK(0);//add by alexchang 0722-2010
			REG_WRITE_U32(0x00000002, SFC_OPCODE);
		
#if SFC_USE_DELAY
			sfc_delay();
#endif

			REG_WRITE_U32(0x00000018, SFC_CTL);
			SYS_REG_TRY_UNLOCK;//add by alexchang 0722-2010
			SFC_SYNC; 

#ifdef EMMC_ISSUE_LOCK
			rtk_lockapi_unlock(lock_flag, (char *)__FUNCTION__);
#endif 

			//setup MD DDR addr and flash addr
			//REG_WRITE_U32(((unsigned long)virt_to_phys(data_buf)), MD_FDMA_DDR_SADDR);
			REG_WRITE_U32(((unsigned long)write_dma_handle), MD_FDMA_DDR_SADDR);
			REG_WRITE_U32(((unsigned long)dest), MD_FDMA_FL_SADDR);

			//setup MD direction and move data length
			val = (0x26000000 | MD_PP_DATA_SIZE);   // do swap
			REG_WRITE_U32(val, MD_FDMA_CTRL2);		//for dma_length bytes.
			
			//dma_cache_sync(NULL, data_buf, MD_PP_DATA_SIZE, DMA_TO_DEVICE);

			mb();
			SFC_SYNC;

			//go 
			REG_WRITE_U32(0x03, MD_FDMA_CTRL1);

			/* wait for MD done its operation */
			while((ret = REG_READ_U32(MD_FDMA_CTRL1)) & 0x1);

#if !SFC_HW_POLL
			/* wait for flash controller done its operation */
			do {
#ifdef EMMC_ISSUE_LOCK
				rtk_lockapi_lock(lock_flag, (char *)__FUNCTION__);
#endif

				SFC_SYNC;
	 
				SYS_REG_TRY_LOCK(0);//add by alexchang 0722-2010
				REG_WRITE_U32(0x00000005, SFC_OPCODE);
			
#if SFC_USE_DELAY
				sfc_delay();
#endif

				REG_WRITE_U32(0x00000010, SFC_CTL);
				SYS_REG_TRY_UNLOCK;//add by alexchang 0722-2010
				SFC_SYNC;

#ifdef EMMC_ISSUE_LOCK
				rtk_lockapi_unlock(lock_flag, (char *)__FUNCTION__);
#endif 
			} while((*(volatile unsigned char *)FLASH_POLL_ADDR) & 0x1);
#endif

			/* shift to next page to writing */
			src += MD_PP_DATA_SIZE;
			dest += MD_PP_DATA_SIZE;
			written_count += MD_PP_DATA_SIZE;
			len -= MD_PP_DATA_SIZE;
		}//end of page program
	}
	
	if (byte_len_after_16MB) {
		_sfc_enable_4B_addr_mode();
        _sfc_enable_host_4B_addr();
		
		SFC_SYNC;
		SYS_REG_TRY_LOCK(0);//add by alexchang 0722-2010
		REG_WRITE_U32(0x00000002, SFC_OPCODE);	/* Byte Programming */
#if SFC_USE_DELAY
		sfc_delay();
#endif

		REG_WRITE_U32(0x00000018, SFC_CTL);	/* dataen = 1, adren = 1, dmycnt = 0 */
		SYS_REG_TRY_UNLOCK;//add by alexchang 0722-2010
		SFC_SYNC;

#ifdef EMMC_ISSUE_LOCK
		rtk_lockapi_unlock(lock_flag, (char *)__FUNCTION__);
#endif 
		len = byte_len_after_16MB;
		while(len >= MD_PP_DATA_SIZE) {
			p_data_buf = (u8 *)write_dma_buf;
			
			/* data moved by MD module is endian inverted.
						revert it before moved to flash */
			for(i = 0; i < MD_PP_DATA_SIZE; i += 4) {
#if 0
				val = *((u32*)(src + i));
				*((u32*)(data_buf + i)) = 
#if 0
							((val >> 24) |
							((val >> 8 ) & 0x0000ff00) |
							((val << 8 ) & 0x00ff0000) |
							(val << 24));
#else
							val;
#endif
#endif
				*((u32*)(p_data_buf + i)) = *((u32*)(src + i));
			}

#ifdef EMMC_ISSUE_LOCK
			rtk_lockapi_lock(lock_flag, (char *)__FUNCTION__);
#endif

			SFC_SYNC; 
			SYS_REG_TRY_LOCK(0);//add by alexchang 0722-2010
			REG_WRITE_U32(0x00000002, SFC_OPCODE);
		
#if SFC_USE_DELAY
			sfc_delay();
#endif

			REG_WRITE_U32(0x00000018, SFC_CTL);
			SYS_REG_TRY_UNLOCK;//add by alexchang 0722-2010
			SFC_SYNC; 

#ifdef EMMC_ISSUE_LOCK
			rtk_lockapi_unlock(lock_flag, (char *)__FUNCTION__);
#endif 

			//setup MD DDR addr and flash addr
			//REG_WRITE_U32(((unsigned long)virt_to_phys(data_buf)), MD_FDMA_DDR_SADDR);
			REG_WRITE_U32(((unsigned long)write_dma_handle), MD_FDMA_DDR_SADDR);
			REG_WRITE_U32(((unsigned long)dest), MD_FDMA_FL_SADDR);

			//setup MD direction and move data length
			val = (0x26000000 | MD_PP_DATA_SIZE);   // do swap
			REG_WRITE_U32(val, MD_FDMA_CTRL2);		//for dma_length bytes.
			
			//dma_cache_sync(NULL, data_buf, MD_PP_DATA_SIZE, DMA_TO_DEVICE);

			mb();
			SFC_SYNC;

			//go 
			REG_WRITE_U32(0x03, MD_FDMA_CTRL1);

			/* wait for MD done its operation */
			while((ret = REG_READ_U32(MD_FDMA_CTRL1)) & 0x1);

#if !SFC_HW_POLL
			/* wait for flash controller done its operation */
			do {
#ifdef EMMC_ISSUE_LOCK
				rtk_lockapi_lock(lock_flag, (char *)__FUNCTION__);
#endif

				SFC_SYNC;
	 
				SYS_REG_TRY_LOCK(0);//add by alexchang 0722-2010
				REG_WRITE_U32(0x00000005, SFC_OPCODE);
			
#if SFC_USE_DELAY
				sfc_delay();
#endif

				REG_WRITE_U32(0x00000010, SFC_CTL);
				SYS_REG_TRY_UNLOCK;//add by alexchang 0722-2010
				SFC_SYNC;

#ifdef EMMC_ISSUE_LOCK
				rtk_lockapi_unlock(lock_flag, (char *)__FUNCTION__);
#endif 
			} while((*(volatile unsigned char *)FLASH_POLL_ADDR) & 0x1);
#endif

			/* shift to next page to writing */
			src += MD_PP_DATA_SIZE;
			dest += MD_PP_DATA_SIZE;
			written_count += MD_PP_DATA_SIZE;
			len -= MD_PP_DATA_SIZE;
		}//end of page program
		
		_sfc_disable_4B_addr_mode();
        _sfc_disable_host_4B_addr();
	}

#ifdef EMMC_ISSUE_LOCK
    rtk_lockapi_lock(lock_flag, (char *)__FUNCTION__);
#endif

    /* send write disable then */
    SFC_SYNC; 
	SYS_REG_TRY_LOCK(0);//add by alexchang 0722-2010
	REG_WRITE_U32(0x00000004, SFC_OPCODE);	/* Write disable */
 
#if SFC_USE_DELAY
	sfc_delay();
#endif

	REG_WRITE_U32(0x00000000, SFC_CTL);	/* dataen = 0, adren = 0, dmycnt = 0 */
	SYS_REG_TRY_UNLOCK;//add by alexchang 0722-2010
	SFC_SYNC;

#ifdef EMMC_ISSUE_LOCK
    rtk_lockapi_unlock(lock_flag, (char *)__FUNCTION__);
#endif

	*retlen = written_count;

	return 0;
}

//---------------------------------------------------------------------------------------------

/* rtk_sfc_write_pages() supports MD(move data module) page programming(PP). */
static int rtk_sfc_write_pages(struct mtd_info *mtd, loff_t to, size_t len,
						size_t *retlen, const u_char *buf) {
	rtk_sfc_info_t *sfc_info;
	u8 *src = (u8*)buf;
#ifdef CONFIG_MTD_RTK_MD_WRITE_COMPARE
	u8 *org_src = (u8*)buf;
	unsigned int org_to = to;
	size_t org_len = len;
	u32 i;
	u32 cmp_cnt=0, cmp_mod=0;
	volatile u32 *ptr_flash=NULL, *ptr_src=NULL;
#endif
	size_t written_len = 0;
	size_t wlen = 0;
	size_t length_to_write;
	int ret;
	
#if defined(CONFIG_MTD_RTK_SFC_DEBUG)
	add_debug_entry(buf, to, len, WRITE_ACCESS);
#endif

#ifdef DEV_DEBUG 
	printk(KERN_WARNING "Rtk SFC MTD: rtk_sfc_write_pages(), addr = %08X, size = %08X\n", (unsigned int)(unsigned long)to, (unsigned int)(unsigned long)len);
#endif

	if((sfc_info = (rtk_sfc_info_t*)mtd->priv) == NULL) { 
		printk("sfc_info is NULL\n");
		return -EINVAL;
	}

	down_write(&rw_sem);

	//SFC_FLUSH_CACHE((unsigned long) buf,len);

	/* Set SB2 to in-order mode */
	//_before_serial_flash_access();
#ifdef CONFIG_MTD_RTK_MD_WRITE_COMPARE
retry_mdwrite:	
#endif
#if defined(CONFIG_MTD_RTK_SFC_DEBUG)
	change_status(WRITE_READY);
#endif

	// 1st pass: write data 0-3 bytes 
	// (to make destination address within 4-bytes alignment)
	if(len > 0 && (to & RTK_SFC_SMALL_PAGE_WRITE_MASK)) {
		if(len > RTK_SFC_SMALL_PAGE_WRITE_MASK)
			length_to_write = (RTK_SFC_SMALL_PAGE_WRITE_MASK + 1) - (to & RTK_SFC_SMALL_PAGE_WRITE_MASK);
		else
			length_to_write = len;

		ret = _sfc_write_bytes(mtd, to, length_to_write, &wlen, src);

		if(ret || unlikely(wlen != length_to_write)) {
			*retlen = wlen;

			/* Restore SB2 */
			//_after_serial_flash_access();

			up_write(&rw_sem);
			return ret;
		}

#ifdef DEV_DEBUG 
		printk(KERN_WARNING "Rtk SFC MTD: rtk_sfc_write() $ PASS #1 $ [%08X:%08X]\n", (int)to, (int)len);
		printk(KERN_WARNING "Rtk SFC MTD: rtk_sfc_write() $ PASS #1 $ %d bytes written\n", (int)wlen);
#endif

		src += wlen;
		written_len += wlen;
		len -= wlen;
		to += wlen;
	}

#if defined(CONFIG_MTD_RTK_SFC_DEBUG)
	change_status(WRITE_STAGE_1);
#endif

	// 2st pass: write data which aligned in 4 bytes but smaller than a single page (256 bytes)
	// (to make destination address within 256-bytes alignment)
	if(len > RTK_SFC_SMALL_PAGE_WRITE_MASK && 
					(((to + MD_PP_DATA_SIZE - 1) & (~(MD_PP_DATA_SIZE - 1))) - to) > RTK_SFC_SMALL_PAGE_WRITE_MASK) {
		length_to_write = ((to + MD_PP_DATA_SIZE - 1) & (~(MD_PP_DATA_SIZE - 1))) - to;

		if(length_to_write > len)
			length_to_write = len;

		if(length_to_write & RTK_SFC_SMALL_PAGE_WRITE_MASK)
			length_to_write = length_to_write & (~RTK_SFC_SMALL_PAGE_WRITE_MASK);

		ret = _sfc_write_small_pages(mtd, to, length_to_write, &wlen, src);

		if(ret || unlikely(wlen != length_to_write)) {
			*retlen = wlen;

			/* Restore SB2 */
			//_after_serial_flash_access();

			up_write(&rw_sem);

			return ret;
		}

#ifdef DEV_DEBUG 
		printk(KERN_WARNING "Rtk SFC MTD: rtk_sfc_write() $ PASS #2 $ [%08X:%08X]\n", (int)to, (int)len);
		printk(KERN_WARNING "Rtk SFC MTD: rtk_sfc_write() $ PASS #2 $ %d bytes written\n", (int)wlen);
#endif

		src += wlen;
		written_len += wlen;
		len -= wlen;
		to += wlen;
	}

#if defined(CONFIG_MTD_RTK_SFC_DEBUG)
	change_status(WRITE_STAGE_2);
#endif

	// 3rd pass: write data in page unit (256 bytes)
	if(len >= MD_PP_DATA_SIZE) {
		length_to_write = len / MD_PP_DATA_SIZE * MD_PP_DATA_SIZE;

		ret = _sfc_write_pages(mtd, to, length_to_write, &wlen, src);

		if(ret || unlikely(wlen != length_to_write)) {
			*retlen = wlen;

			/* Restore SB2 */
			//_after_serial_flash_access();

			up_write(&rw_sem);
			return ret;
		}

#ifdef DEV_DEBUG 
		printk(KERN_WARNING "Rtk SFC MTD: rtk_sfc_write() $ PASS #3 $ [%08X:%08X] (%d)\n", (int)to, (int)len, MD_PP_DATA_SIZE);
		printk(KERN_WARNING "Rtk SFC MTD: rtk_sfc_write() $ PASS #3 $ %d bytes written\n", (int)wlen);
#endif

		src += wlen;
		written_len += wlen;
		len -= wlen;
		to += wlen;
	}

#if defined(CONFIG_MTD_RTK_SFC_DEBUG)
	change_status(WRITE_STAGE_3);
#endif

	// 4th pass: write data which aligned in 4 bytes but smaller than a single page (256 bytes)
	if(len > 0 && (len & (~RTK_SFC_SMALL_PAGE_WRITE_MASK))) {
		length_to_write = len & (~RTK_SFC_SMALL_PAGE_WRITE_MASK);

		ret = _sfc_write_small_pages(mtd, to, length_to_write, &wlen, src);

		if(ret || unlikely(wlen != length_to_write)) {
			*retlen = wlen;

			/* Restore SB2 */
			//_after_serial_flash_access();

			up_write(&rw_sem);
			return ret;
		}

#ifdef DEV_DEBUG 
		printk(KERN_WARNING "Rtk SFC MTD: rtk_sfc_write() $ PASS #4 $ [%08X:%08X]\n", (int)to, (int)len);
		printk(KERN_WARNING "Rtk SFC MTD: rtk_sfc_write() $ PASS #4 $ %d bytes written\n", (int)wlen);
#endif

		src += wlen;
		written_len += wlen;
		len -= wlen;
		to += wlen;
	}

#if defined(CONFIG_MTD_RTK_SFC_DEBUG)
	change_status(WRITE_STAGE_4);
#endif

	// 5th pass: write data 0-3 bytes
	if(len > 0) {
		length_to_write = len;

		ret = _sfc_write_bytes(mtd, to, length_to_write, &wlen, src);

		if(ret || unlikely(wlen != length_to_write)) {
			*retlen = wlen;

			/* Restore SB2 */
			//_after_serial_flash_access();

			up_write(&rw_sem);
			return ret;
		}

#ifdef DEV_DEBUG 
		printk(KERN_WARNING "Rtk SFC MTD: rtk_sfc_write() $ PASS #5 $ [%08X:%08X]\n", (int)to, (int)len);
		printk(KERN_WARNING "Rtk SFC MTD: rtk_sfc_write() $ PASS #5 $ %d bytes written\n", (int)wlen);
#endif

		src += wlen;
		written_len += wlen;
		len -= wlen;
		to += wlen;
	}

#if defined(CONFIG_MTD_RTK_SFC_DEBUG)
	change_status(WRITE_STAGE_5);
#endif

	*retlen = written_len;

	/* restore opcode to read */
	_switch_to_read_mode((rtk_sfc_info_t*)mtd->priv, eREAD_MODE_SINGLE_FAST_READ);

	/* Restore SB2 */
	//_after_serial_flash_access();
#ifdef CONFIG_MTD_RTK_MD_WRITE_COMPARE 
        //TODO : louis, cache flush issues need to take care, not correct everytime
	ptr_flash = (volatile unsigned int*)(FLASH_BASE + org_to);
	ptr_src = (volatile unsigned int*)(org_src);

	cmp_cnt = org_len / 4;
	cmp_mod = org_len % 4;
	for(i=0;i<cmp_cnt;i++)
	{
		if (ptr_flash[i] != endian_swap(ptr_src[i]))
		{
	    		printk("1 write error at buf=%x %x len=%x\n", org_src, (FLASH_BASE + org_to), org_len);	
			for (i=0; i < org_len; i++) {
				printk("%02x ", org_src[i]);
				if (i%8 == 7) printk("\n");
			}
			printk("\ndest: ");
			for (i=0; i < org_len; i++) {
				printk("%02x ", ((unsigned char *)(FLASH_BASE + org_to))[i]);
				if (i%8 == 7) printk("\n");
			}
			while(1) {
				msleep(3000);
			}				
			goto retry_mdwrite;
		}
	}
	for(i=0;i<cmp_mod;i++)
	{
		if (org_src[cmp_cnt*4+i] != ((u8*)(FLASH_BASE + org_to))[cmp_cnt*4+i])
		{
	    		printk("2 write error at buf=%x %x len=%x\n", org_src, (FLASH_BASE + org_to), org_len);	
			for (i=0; i < org_len; i++) {
				printk("%02x ", org_src[i]);
				if (i%8 == 7) printk("\n");
			}
			printk("\ndest: ");
			for (i=0; i < org_len; i++) {
				printk("%02x ", ((unsigned char *)(FLASH_BASE + org_to))[i]);
				if (i%8 == 7) printk("\n");
			}
			while(1) {
				msleep(3000);
			}				
			goto retry_mdwrite;
		}
	}
#endif	
	up_write(&rw_sem);

#if defined(CONFIG_MTD_RTK_SFC_DEBUG)
	change_status(WRITE_COMPLETED);
#endif

	return 0;
}
#endif


static int rtk_sfc_write(struct mtd_info *mtd, loff_t to, size_t len,
        size_t *retlen, const u_char *buf) {
    int retval;
#ifdef EMMC_ISSUE_LOCK
    unsigned long lock_flag;
#endif

#if defined(CONFIG_MTD_RTK_SFC_DEBUG)
    add_debug_entry(buf, to, len, WRITE_ACCESS);
#endif

    down_write(&rw_sem);

#ifdef EMMC_ISSUE_LOCK
    rtk_lockapi_lock(lock_flag, (char *)__FUNCTION__);
#endif

    SFC_FLUSH_CACHE((unsigned long) buf,len);

#if defined(CONFIG_MTD_RTK_SFC_DEBUG)
    change_status(WRITE_READY);
#endif

#ifdef DEV_DEBUG 
    printk(KERN_WARNING "Rtk SFC MTD: rtk_sfc_write(), to = %08X, length = %08X\n", (int)to, (int)len);
#endif

    retval = _sfc_write_bytes(mtd, to, len, retlen, buf);

    /* restore opcode to read */
    _switch_to_read_mode((rtk_sfc_info_t*)mtd->priv, eREAD_MODE_SINGLE_FAST_READ);

#ifdef EMMC_ISSUE_LOCK
    rtk_lockapi_unlock(lock_flag, (char *)__FUNCTION__);
#endif

    up_write(&rw_sem);

#if defined(CONFIG_MTD_RTK_SFC_DEBUG)
    change_status(WRITE_COMPLETED);
#endif

    return retval;
}

#ifdef EON_SEGMENT_ERASE
static int rtk_EON_segm_erase(struct mtd_info *mtd, struct erase_info *instr) {
    rtk_sfc_info_t *sfc_info;
    unsigned int size;
    volatile unsigned char *addr;
    unsigned char tmp;

    unsigned int erase_addr;
    unsigned int erase_opcode;
    unsigned int erase_size;

#ifdef EMMC_ISSUE_LOCK
    unsigned long lock_flag;
#endif

#if defined(CONFIG_MTD_RTK_SFC_DEBUG)
    add_debug_entry(instr->addr, 0, instr->len, ERASE_ACCESS);
#endif

    if((sfc_info = (rtk_sfc_info_t*)mtd->priv) == NULL) {
        return -EINVAL;
    }

    if(instr->addr + instr->len > mtd->size)
        return -EINVAL;

    down_write(&rw_sem);

#ifdef DEV_DEBUG 
    printk(KERN_WARNING "Rtk SFC MTD: rtk_sfc_erase(), addr = %08X, size = %08X\n", instr->addr, instr->len);
#endif

#ifdef EMMC_ISSUE_LOCK
    rtk_lockapi_lock(lock_flag, (char *)__FUNCTION__);
#endif

    //disable auto-prog
    REG_WRITE_U32(0x00000005, SFC_WAIT_WR);
    REG_WRITE_U32(0x00000006, SFC_EN_WR);
    
#ifdef EMMC_ISSUE_LOCK
    rtk_lockapi_unlock(lock_flag, (char *)__FUNCTION__);
#endif

    addr = FLASH_BASE + (instr->addr);
    size = instr->len;

    erase_addr = (unsigned int)instr->addr;
    erase_opcode = sfc_info->erase_opcode;
    erase_size = mtd->erasesize;

    for(size = instr->len ; size > 0 ; size -= erase_size) {

        if((addr-FLASH_BASE)>=0 && (addr-FLASH_BASE)<0x10000)
        {
            erase_opcode = 0x000000d8;
            if((addr-FLASH_BASE)>=0 && (addr-FLASH_BASE)<0x1000)
            {
                erase_size = 0x1000;
            }
            else if((addr-FLASH_BASE)>=0x1000 && (addr-FLASH_BASE)<0x2000)
            {
                erase_size = 0x1000;
            }
            else if((addr-FLASH_BASE)>=0x2000 && (addr-FLASH_BASE)<0x4000)
            {
                erase_size = 0x2000;
            }
            else if((addr-FLASH_BASE)>=0x4000 && (addr-FLASH_BASE)<0x8000)
            {
                erase_size = 0x4000;
            }
            else if((addr-FLASH_BASE)>=0x8000 && (addr-FLASH_BASE)<0x10000)
            {
                erase_size = 0x8000;
            }

        }
        else
        {

            /* choose erase sector size */
            if (((erase_addr&(0x10000-1)) == 0) && (size >= 0x10000) && (sfc_info->sec_64k_en == SUPPORTED))
            {
                erase_opcode = 0x000000d8;
                erase_size = 0x10000;
            }
            else if (((erase_addr&(0x1000-1)) == 0) && (size >= 0x1000) && (sfc_info->sec_4k_en == SUPPORTED))
            {
                erase_opcode = 0x00000020;
                erase_size = 0x1000;
            }
            else
            {
                erase_opcode = sfc_info->erase_opcode;
                erase_size = mtd->erasesize;
            }
        }

#ifdef EMMC_ISSUE_LOCK
        rtk_lockapi_lock(lock_flag, (char *)__FUNCTION__);
#endif

        /* prior to any write instructions, send write enable first */
        //(write enable)
        SFC_SYNC;
        SYS_REG_TRY_LOCK(0);//add by alexchang 0722-2010
        REG_WRITE_U32(0x00000006, SFC_OPCODE);

#if SFC_USE_DELAY
        sfc_delay();
#endif

        REG_WRITE_U32(0x00000000, SFC_CTL); /* dataen = 0, adren = 0, dmycnt = 0 */
        SYS_REG_TRY_UNLOCK;//add by alexchang 0722-2010
        SFC_SYNC;
        tmp = *(volatile unsigned char *)FLASH_POLL_ADDR;
        SFC_SYNC;
        SYS_REG_TRY_LOCK(0);//add by alexchang 0722-2010
        REG_WRITE_U32(erase_opcode, SFC_OPCODE);    /* Sector-Erase */
#if SFC_USE_DELAY
        sfc_delay();
#endif

        REG_WRITE_U32(0x00000008, SFC_CTL); /* adren = 1 */
        SYS_REG_TRY_UNLOCK;//add by alexchang 0722-2010
        SFC_SYNC;
        tmp = *addr;

#ifdef EMMC_ISSUE_LOCK
        rtk_lockapi_unlock(lock_flag, (char *)__FUNCTION__);
#endif

        /* using RDSR to make sure the operation is completed. */
        while(1) {
#ifdef EMMC_ISSUE_LOCK
            rtk_lockapi_lock(lock_flag, (char *)__FUNCTION__);
#endif
            
            SFC_SYNC;
            SYS_REG_TRY_LOCK(0);//add by alexchang 0722-2010
            REG_WRITE_U32(0x00000005, SFC_OPCODE);  /* Read status register */

#if SFC_USE_DELAY
            sfc_delay();
#endif

            REG_WRITE_U32(0x00000010, SFC_CTL); /* dataen = 1, adren = 0, dmycnt = 0 */
            SYS_REG_TRY_UNLOCK;//add by alexchang 0722-2010
            SFC_SYNC;
            
#ifdef EMMC_ISSUE_LOCK
            rtk_lockapi_unlock(lock_flag, (char *)__FUNCTION__);
#endif

            if((*(volatile unsigned char *)FLASH_POLL_ADDR) & 0x1)
                msleep(100); // erasing 256KBytes might take up to 2 seconds!
            else
                break;
        }

        addr += erase_size;
        erase_addr += erase_size;

    }
    
#ifdef EMMC_ISSUE_LOCK
    rtk_lockapi_lock(lock_flag, (char *)__FUNCTION__);
#endif

    /* send write disable then */
    SFC_SYNC;
    SYS_REG_TRY_LOCK(0);//add by alexchang 0722-2010
    REG_WRITE_U32(0x00000004, SFC_OPCODE);  /* Write disable */

#if SFC_USE_DELAY
    sfc_delay();
#endif

    REG_WRITE_U32(0x00000000, SFC_CTL); /* dataen = 0, adren = 0, dmycnt = 0 */
    SYS_REG_TRY_UNLOCK;//add by alexchang 0722-2010
    SFC_SYNC;
    tmp = *(volatile unsigned char *)FLASH_POLL_ADDR;

    /* restore opcode to read */
    _switch_to_read_mode(sfc_info, eREAD_MODE_SINGLE_FAST_READ);

#ifdef EMMC_ISSUE_LOCK
    rtk_lockapi_unlock(lock_flag, __FUNCTION__);
#endif

    up_write(&rw_sem);

    instr->state = MTD_ERASE_DONE;
    mtd_erase_callback(instr);

#if defined(CONFIG_MTD_RTK_SFC_DEBUG) 
    change_status(ERASE_COMPLETED);
#endif

    return 0;   

}
#endif

static int rtk_sfc_erase(struct mtd_info *mtd, struct erase_info *instr) 
{
    rtk_sfc_info_t *sfc_info;
    unsigned int size;
    volatile unsigned char *addr;
    unsigned char tmp;

    unsigned int erase_addr;
    unsigned int erase_opcode;
    unsigned int erase_size;
	//unsigned int curr_address;
	unsigned char en4B_flag = 0;

#ifdef EMMC_ISSUE_LOCK
    unsigned long lock_flag;
#endif

#if defined(CONFIG_MTD_RTK_SFC_DEBUG)
    add_debug_entry(instr->addr, 0, instr->len, ERASE_ACCESS);
#endif

    if((sfc_info = (rtk_sfc_info_t*)mtd->priv) == NULL) {
        return -EINVAL;
    }

    if(instr->addr + instr->len > mtd->size)
        return -EINVAL;

    down_write(&rw_sem);

#ifdef DEV_DEBUG 
    printk("Rtk SFC MTD: rtk_sfc_erase(), addr = %08X, size = %08X\n", (unsigned int)instr->addr, (unsigned int) instr->len);
#endif

#ifdef EMMC_ISSUE_LOCK
    rtk_lockapi_lock(lock_flag, (char *)__FUNCTION__);
#endif

    //disable auto-prog
    REG_WRITE_U32(0x00000005, SFC_WAIT_WR);
    REG_WRITE_U32(0x00000006, SFC_EN_WR);

#ifdef EMMC_ISSUE_LOCK
    rtk_lockapi_unlock(lock_flag, (char *)__FUNCTION__);
#endif

    addr = FLASH_BASE + (instr->addr);
    size = instr->len;

    erase_addr = (unsigned int)instr->addr;
    erase_opcode = sfc_info->erase_opcode;
    erase_size = mtd->erasesize;

    for(size = instr->len ; size > 0 ; size -= erase_size) {
		
		if (en4B_flag == 0) {
            if (((unsigned long long)addr - (unsigned long long)FLASH_BASE) >= (16 * 1024 *1024)) {
                _sfc_enable_4B_addr_mode();
				_sfc_enable_host_4B_addr();
                en4B_flag = 1;
            }
        }

        /* choose erase sector size */
        if (((erase_addr&(0x10000-1)) == 0) && (size >= 0x10000) && (sfc_info->sec_64k_en == SUPPORTED))
        {
            erase_opcode = 0x000000d8;
            erase_size = 0x10000;
        }
/*
           else if (((erase_addr&(0x8000-1)) == 0) && (size >= 0x8000) && (sfc_info->sec_32k_en == SUPPORTED))
           {
                erase_opcode = 0x00000052;
                erase_size = 0x8000;
           }
*/
        else if (((erase_addr&(0x1000-1)) == 0) && (size >= 0x1000) && (sfc_info->sec_4k_en == SUPPORTED))
        {
            erase_opcode = 0x00000020;
            erase_size = 0x1000;
        }
        else
        {
            erase_opcode = sfc_info->erase_opcode;
            erase_size = mtd->erasesize;
        }

#ifdef EMMC_ISSUE_LOCK
        rtk_lockapi_lock(lock_flag, (char *)__FUNCTION__);
#endif 

        /* prior to any write instructions, send write enable first */
        //(write enable)  
        SFC_SYNC;

        SYS_REG_TRY_LOCK(0);//add by alexchang 0722-2010
        REG_WRITE_U32(0x00000006, SFC_OPCODE);

#if SFC_USE_DELAY
        sfc_delay();
#endif

        REG_WRITE_U32(0x00000000, SFC_CTL); /* dataen = 0, adren = 0, dmycnt = 0 */
        SYS_REG_TRY_UNLOCK;//add by alexchang 0722-2010
        SFC_SYNC;
        tmp = *(volatile unsigned char *)FLASH_POLL_ADDR;
        SFC_SYNC;
        SYS_REG_TRY_LOCK(0);//add by alexchang 0722-2010
        REG_WRITE_U32(erase_opcode, SFC_OPCODE);    /* Sector-Erase */
#if SFC_USE_DELAY
        sfc_delay();
#endif

        REG_WRITE_U32(0x00000008, SFC_CTL); /* adren = 1 */
        SYS_REG_TRY_UNLOCK;//add by alexchang 0722-2010
        SFC_SYNC;
        tmp = *addr;

#ifdef EMMC_ISSUE_LOCK
        rtk_lockapi_unlock(lock_flag, (char *)__FUNCTION__);
#endif


        /* using RDSR to make sure the operation is completed. */
        while(1) {
#ifdef EMMC_ISSUE_LOCK
            rtk_lockapi_lock(lock_flag, (char *)__FUNCTION__);
#endif

            SFC_SYNC;

            SYS_REG_TRY_LOCK(0);//add by alexchang 0722-2010
            REG_WRITE_U32(0x00000005, SFC_OPCODE);  /* Read status register */

#if SFC_USE_DELAY
            sfc_delay();
#endif

            REG_WRITE_U32(0x00000010, SFC_CTL); /* dataen = 1, adren = 0, dmycnt = 0 */
            SYS_REG_TRY_UNLOCK;//add by alexchang 0722-2010
            SFC_SYNC;

#ifdef EMMC_ISSUE_LOCK
            rtk_lockapi_unlock(lock_flag, (char *)__FUNCTION__);
#endif

            if((*(volatile unsigned char *)FLASH_POLL_ADDR) & 0x1)
                msleep(100); // erasing 256KBytes might take up to 2 seconds!
            else
                break;
        }

        addr += erase_size;
        erase_addr += erase_size;

		if (en4B_flag == 1) {
			_sfc_disable_4B_addr_mode();
			_sfc_disable_host_4B_addr();
        }
    }

#ifdef EMMC_ISSUE_LOCK
    rtk_lockapi_lock(lock_flag, (char *)__FUNCTION__);
#endif

    /* send write disable then */
    SFC_SYNC;

    SYS_REG_TRY_LOCK(0);//add by alexchang 0722-2010
    REG_WRITE_U32(0x00000004, SFC_OPCODE);  /* Write disable */

#if SFC_USE_DELAY
    sfc_delay();
#endif

    REG_WRITE_U32(0x00000000, SFC_CTL); /* dataen = 0, adren = 0, dmycnt = 0 */
    SYS_REG_TRY_UNLOCK;//add by alexchang 0722-2010
    SFC_SYNC;
    tmp = *(volatile unsigned char *)FLASH_POLL_ADDR;

    //enable auto-prog
    REG_WRITE_U32(0x00000105, SFC_WAIT_WR);
    REG_WRITE_U32(0x00000106, SFC_EN_WR);

    /* restore opcode to read */
    _switch_to_read_mode(sfc_info, eREAD_MODE_SINGLE_FAST_READ);

#ifdef EMMC_ISSUE_LOCK
    rtk_lockapi_unlock(lock_flag, (char *)__FUNCTION__);
#endif

    up_write(&rw_sem);

    instr->state = MTD_ERASE_DONE;
    mtd_erase_callback(instr);

#if defined(CONFIG_MTD_RTK_SFC_DEBUG) 
    change_status(ERASE_COMPLETED);
#endif

    return 0;
}

static int rtk_sfc_suspend(struct mtd_info *mtd)
{
#ifdef EMMC_ISSUE_LOCK
    unsigned long lock_flag;

    rtk_lockapi_lock(lock_flag, (char *)__FUNCTION__);
#endif

    // save register when suspend
    g_sfc_reg.sfc_ce = REG_READ_U32(SFC_CE);
    g_sfc_reg.sfc_wp = REG_READ_U32(SFC_WP);
    g_sfc_reg.sfc_sck = REG_READ_U32(SFC_SCK);
    g_sfc_reg.sfc_pos_latch = REG_READ_U32(SFC_POS_LATCH);

#ifdef EMMC_ISSUE_LOCK
    rtk_lockapi_unlock(lock_flag, (char *)__FUNCTION__);
#endif

    return 0;
}

static void rtk_sfc_resume(struct mtd_info *mtd)
{
#ifdef EMMC_ISSUE_LOCK
    unsigned long lock_flag;

    rtk_lockapi_lock(lock_flag, (char *)__FUNCTION__);
#endif

    SYS_REG_TRY_LOCK(0);//add by alexchang 0722-2010

    REG_WRITE_U32(0x00000000, SFC_WP);

    // // restore register when resume
    REG_WRITE_U32(g_sfc_reg.sfc_ce, SFC_CE);
    REG_WRITE_U32(g_sfc_reg.sfc_wp, SFC_WP);
    REG_WRITE_U32(g_sfc_reg.sfc_sck, SFC_SCK);
    REG_WRITE_U32(g_sfc_reg.sfc_pos_latch, SFC_POS_LATCH);
    SFC_SYNC;

    SYS_REG_TRY_UNLOCK;

#ifdef EMMC_ISSUE_LOCK
    rtk_lockapi_unlock(lock_flag, (char *)__FUNCTION__);
#endif
}

void rtk_sfc_shutdown(struct mtd_info *mtd)
{
#ifdef EMMC_ISSUE_LOCK
    unsigned long lock_flag;
#endif

    down_write(&rw_sem);

#ifdef EMMC_ISSUE_LOCK
    rtk_lockapi_lock(lock_flag, (char *)__FUNCTION__);
#endif

    while((REG_READ_U32(MD_FDMA_CTRL1)) & 0x1);
    SYS_REG_TRY_LOCK(0);//add by alexchang 0722-2010
    REG_WRITE_U32(0x00000805, SFC_OPCODE);  /* RDSR */
#if SFC_USE_DELAY 
    sfc_delay();
#endif

    REG_WRITE_U32(0x00000010, SFC_CTL); /* dataen = 1, adren = 0, dmycnt = 0 */
    SYS_REG_TRY_UNLOCK;//add by alexchang 0722-2010
    SFC_SYNC;

    while((*(volatile unsigned char *)FLASH_POLL_ADDR) & 0x1);

    _switch_to_read_mode(&rtk_sfc_info, eREAD_MODE_SINGLE_FAST_READ);

#ifdef EMMC_ISSUE_LOCK
    rtk_lockapi_unlock(lock_flag, (char *)__FUNCTION__);
#endif

    up_write(&rw_sem);

    return;
}

static int rtk_sfc_probe(struct platform_device *pdev) 
{
    struct mtd_info *mtd_info;
    rtk_sfc_info_t *sfc_info;
    unsigned int id = 0;
    unsigned int reg_muxpad5 = 0;
    int ret = 0;
#ifdef EMMC_ISSUE_LOCK
    unsigned long lock_flag;
#endif

    mtd_info = (struct mtd_info*)&descriptor;

    if((sfc_info = (rtk_sfc_info_t*)mtd_info->priv) == NULL) {
        return -ENODEV;
    }

#ifdef EMMC_ISSUE_LOCK
    rtk_lockapi_lock(lock_flag, (char *)__FUNCTION__);
#endif

    // set spi pin mux
    SFC_SYNC;
    SYS_REG_TRY_LOCK(0);
    reg_muxpad5 = REG_READ_U32(SYS_MUXPAD5) | 0x00000001; 
    REG_WRITE_U32(reg_muxpad5, SYS_MUXPAD5);
    SFC_SYNC;

    // configure spi flash controller register
#if 0
    REG_WRITE_U32(0x00000013, SFC_SCK);
    REG_WRITE_U32(0x00000000, SFC_POS_LATCH);
    REG_WRITE_U32(0x00071307, SFC_CE);    
#else // same as bootcode
	REG_WRITE_U32(0x00000013, SFC_SCK);
    REG_WRITE_U32(0x00000001, SFC_POS_LATCH);
    REG_WRITE_U32(0x00090101, SFC_CE);
#endif
    SFC_SYNC;

    // read Manufacture & device ID
    REG_WRITE_U32(0x0000009f, SFC_OPCODE);
#if SFC_USE_DELAY
    sfc_delay();
#endif
    REG_WRITE_U32(0x00000010, SFC_CTL);
    SFC_SYNC;

#ifdef EMMC_ISSUE_LOCK
    rtk_lockapi_unlock(lock_flag, (char *)__FUNCTION__);
#endif

#ifdef DEV_DEBUG
    printk(KERN_INFO "Read id orginal address : %p\n", FLASH_POLL_ADDR);
#endif
    id = endian_swap(*(volatile unsigned int *)FLASH_POLL_ADDR);
    id >>= 8;
#ifdef DEV_DEBUG
    printk(KERN_INFO "Read id orginal value : 0x%08x\n", id);
#endif
    sfc_info->manufacturer_id = (id & 0x00FF0000)>>16;
    sfc_info->device_id2 = RDID_DEVICE_EID_1(id);
    sfc_info->device_id1 = RDID_DEVICE_EID_2(id);
    printk(KERN_ERR "--RDID Seq: 0x%x | 0x%x | 0x%x\n",sfc_info->manufacturer_id,sfc_info->device_id1,sfc_info->device_id2);

    switch(sfc_info->manufacturer_id) {
        case MANUFACTURER_ID_SST:
            ret = sst_init(sfc_info);
            break;

        case MANUFACTURER_ID_SPANSION:
            ret = spansion_init(sfc_info);
            break;
        case MANUFACTURER_ID_MXIC:
            ret = mxic_init(sfc_info);
            break;
        case MANUFACTURER_ID_PMC:
            ret = pmc_init(sfc_info);
            break;
        case MANUFACTURER_ID_STM:
            ret = stm_init(sfc_info);
            break;
        case MANUFACTURER_ID_EON:
            ret = eon_init(sfc_info);
            break;
        case MANUFACTURER_ID_ATMEL:
            ret = atmel_init(sfc_info);
            break;

        case MANUFACTURER_ID_WINBOND:
            ret = winbond_init(sfc_info);
            break;
        case MANUFACTURER_ID_ESMT:
            ret = esmt_init(sfc_info);
            break;
        case MANUFACTURER_ID_GD:
            ret = gd_init(sfc_info);
            break;
        default:
            printk(KERN_ERR "RtkSFC MTD: Unknown flash type.\n");
            printk(KERN_ERR "Manufacturer's ID = %02X, Memory Type = %02X, Memory Capacity = %02X\n", id & 0xff, (id >> 8) & 0xff, (id >> 16) & 0xff);

            return -ENODEV;
            break;
    }

    mtd_info->erasesize = sfc_info->erase_size;
    mtd_info->writesize = 0x100;
#ifdef EON_SEGMENT_ERASE
    if(g_isSegErase)
    {
        printk("Set EON segment erase.\n");
        mtd_info->erase = rtk_EON_segm_erase;
    }
#endif

    printk("Supported Erase Size:%s%s%s%s.\n"
            , sfc_info->sec_256k_en ? " 256KB" : ""
            , sfc_info->sec_64k_en ? " 64KB" : ""
            , sfc_info->sec_32k_en ?" 32KB" : ""
            , sfc_info->sec_4k_en ? " 4KB" : ""
          );
#if SFC_MULTI_READ
    printk("Attr:%s%s%s.\n"
            ,(sfc_info->attr & RTK_SFC_ATTR_SUPPORT_DUAL_O) ? " dualread" : ""
            ,(sfc_info->attr & RTK_SFC_ATTR_SUPPORT_DUAL_IO) ? " dualIO" : ""
            ,(sfc_info->attr & RTK_SFC_ATTR_SUPPORT_4BYTE_ADDR_MODE) ? " 4bytemode" : ""
          );
#endif

#if defined(CONFIG_MTD_RTK_SFC_READ_MD) || defined(CONFIG_MTD_RTK_SFC_WRITE_MD)
        printk("RtkSFC MTD: Enable RtkSFC MD PP callback function.\n");
    
	#if defined(CONFIG_MTD_RTK_SFC_READ_MD)
        mtd_info->_read = rtk_sfc_read_pages;
        printk("MD_READ Enable..\n");
	#else
        printk("MD_READ Disable..\n");
	#endif
	#if defined(CONFIG_MTD_RTK_SFC_WRITE_MD)
        mtd_info->_write = rtk_sfc_write_pages;
        printk("MD_WRITE Enable..\n");
	#else
        printk("MD_WRITE Disable..\n");
	#endif
#endif

    if((ret = rtk_sfc_attach(&descriptor)) != 0) {
        printk("[%s]Realtek SFC attach fail\n",__FUNCTION__);
        
        return ret;
    }

    return 0;
}

static struct resource physmap_flash_resource[] = {
    [0] = {
        .start  = ((unsigned int)NOR_BASE_PHYS),
        .end    = ((unsigned int)NOR_BASE_PHYS + FLASH_SIZE - 1),
        .flags = IORESOURCE_MEM
    },
#if 0
    [1] = {
        .start  = IRQ_SB2,
        .end    = IRQ_SB2,
        .flags  = IORESOURCE_IRQ,
    },

    [2] = {
        .start  = ((unsigned int)SPI_RBUS_VIRT),
        .end    = ((unsigned int)SPI_RBUS_VIRT+FLASH_SIZE-1),
        .flags = IORESOURCE_MEM
    }
#endif
};

static u64 rtkSFC_dmamask = DMA_BIT_MASK(32); 
static struct platform_device *rtkSFC_device;
static struct platform_driver rtkSFC_driver = {
    .probe      = rtk_sfc_probe,
    .driver     =
    {
        .name   = "RtkSFC",
        .owner  = THIS_MODULE,
    },
};

static int rtk_sfc_init_1(void)
{
    int rc = 0;
    struct mtd_info *mtd_info;
    rtk_sfc_info_t *sfc_info;

    mtd_info = (struct mtd_info*)&descriptor;

    if((sfc_info = (rtk_sfc_info_t*)mtd_info->priv) == NULL) {
        return -ENODEV;
    }

    init_rwsem(&rw_sem);

    rc = platform_driver_register(&rtkSFC_driver);

    if (!rc) {
        rtkSFC_device = platform_device_alloc("RtkSFC", 0);
        rtkSFC_device->num_resources = ARRAY_SIZE(physmap_flash_resource);
        rtkSFC_device->dev.dma_mask = &rtkSFC_dmamask;
        rtkSFC_device->dev.coherent_dma_mask = DMA_BIT_MASK(32);
        rtkSFC_device->resource = physmap_flash_resource;

        if (rtkSFC_device) {
            rc = platform_device_add(rtkSFC_device);
            if ((sfc_info->manufacturer_id == 0xff)&&
                    (sfc_info->device_id2 == 0xff) &&
                    (sfc_info->device_id1 == 0xff))
            {
                rc = -1;
            }
        }
        else {
            rc = -ENOMEM;
        }

        if (rc < 0) {
            platform_device_put(rtkSFC_device);
            platform_driver_unregister(&rtkSFC_driver);
        }
    }

    if (rc < 0){
        printk(KERN_INFO "Realtek SFC Driver installation fails.\n\n");
        return -ENODEV;
    } else {
        printk(KERN_INFO "Realtek SFC Driver is successfully installing.\n\n");
    }

    return rc;
}

static int __init rtk_sfc_init(void) 
{

    printk("RtkSFC MTD init ...\n");
    printk("NOR flash support list ..\n");

#if  defined(CONFIG_REALTEK_USE_HWSEM_AS_SENTINEL )
    printk("(V) HWSEMA support.\n");
#else
    printk("(X) HWSEMA support.\n");
#endif

#if SFC_HW_POLL
    printk("(V) AUTO_HW_POLL support.\n");
#else
    printk("(X) AUTO_HW_POLL support.\n");
#endif

#if ENTER_4BYTES_MODE
    printk("(V) 4Bytes mode support.\n");
#else
    printk("(X) 4Bytes mode support.\n");
#endif

#if NOR_SUPPORT_MAX_ERASE_SIZE
    printk("(V) Max erase size support.\n");
#else
    printk("(X) Max erase size support.\n");
#endif

#if SFC_USE_DELAY
    printk("(V) Sfc_delay support.\n");
#else
    printk("(X) Sfc_delay support.\n");
#endif

#if SFC_MULTI_READ
    printk("(V) Multi-read support.\n");
#else
    printk("(X) Multi-read support.\n");
#endif

    // map rbus and nor virtual addr
    rbus_base_virt = ioremap(RBUS_BASE_PHYS, RBUS_SIZE);
    nor_base_virt = ioremap(NOR_BASE_PHYS, FLASH_SIZE);

    // set spi flash resource
    physmap_flash_resource[0].start = (unsigned long)nor_base_virt;
    physmap_flash_resource[0].end = physmap_flash_resource[0].start + FLASH_SIZE - 1;

    // prepare parameters
    nor_size = FLASH_SIZE;
    FLASH_POLL_ADDR = FLASH_BASE = (unsigned char*)(nor_base_virt);   

    /* prepare mtd_info */
    memset(&descriptor, 0, sizeof(struct mtd_info));
    memset(&rtk_sfc_info, 0, sizeof(rtk_sfc_info_t));

    rtk_sfc_info.mtd_info = &descriptor;

    descriptor.priv = &rtk_sfc_info;
    descriptor.name = "RtkSFC";
    descriptor.size = nor_size; 
    descriptor.flags = MTD_WRITEABLE;
    descriptor._erase = rtk_sfc_erase;
    descriptor._read = rtk_sfc_read;
    descriptor._suspend = rtk_sfc_suspend;
    descriptor._write = rtk_sfc_write;
    descriptor._resume = rtk_sfc_resume;
    //descriptor._shutdown = rtk_sfc_shutdown;
    descriptor.owner = THIS_MODULE;
    descriptor.type = MTD_DATAFLASH;//MTD_DATAFLASH for general serial flash
    descriptor.numeraseregions = 0; // uni-erasesize
    descriptor.oobsize = 0;

    /* Allocate DMA buffers */
#ifdef CONFIG_MTD_RTK_SFC_READ_MD
    read_dma_buf = dma_alloc_coherent(NULL, MD_PP_DATA_SIZE, &read_dma_handle, GFP_ATOMIC);
#endif
#ifdef CONFIG_MTD_RTK_SFC_WRITE_MD
    write_dma_buf= dma_alloc_coherent(NULL, MD_PP_DATA_SIZE, &write_dma_handle, GFP_ATOMIC);
#endif

    rtk_sfc_init_1();

    return 0;
}

static const char * const part_probes[] = { "cmdlinepart", "RedBoot", NULL };
static int rtk_sfc_attach(struct mtd_info *mtd_info) 
{
    int nr_parts = 0;
    struct mtd_partitions mtd_parts;
    int ret = 0;
#ifdef EMMC_ISSUE_LOCK
    unsigned long lock_flag;

    rtk_lockapi_lock(lock_flag, (char *)__FUNCTION__);
#endif

    memset(&mtd_parts, 0, sizeof(mtd_parts));
    /* WRSR: write status register, no memory protection */
    SFC_SYNC;
    SYS_REG_TRY_LOCK(0);//add by alexchang 0722-2010
    REG_WRITE_U32(0x00000001, SFC_OPCODE);
#if SFC_USE_DELAY
    sfc_delay();
#endif
    REG_WRITE_U32(0x00000010, SFC_CTL);
    SYS_REG_TRY_UNLOCK;//add by alexchang 0722-2010
    SFC_SYNC;
    *((volatile unsigned char*)FLASH_POLL_ADDR)= 0x00;

#ifdef EMMC_ISSUE_LOCK
    rtk_lockapi_unlock(lock_flag, (char *)__FUNCTION__);
#endif

    /*
     * Partition selection stuff.
     */
#ifdef CONFIG_MTD_CMDLINE_PARTS
    printk("[%s]descriptor size 0x%x\n",__FUNCTION__,(unsigned int)descriptor.size);    
    if(!parse_mtd_partitions(&descriptor, part_probes, &mtd_parts, NULL))
        nr_parts = mtd_parts.nr_parts;
#endif

    if(nr_parts <= 0) {
        printk(KERN_NOTICE "Rtk SFC: using single partition\n");
        if(add_mtd_device(&descriptor)) {
            printk(KERN_WARNING "Rtk SFC: (for SST/SPANSION/MXIC/WINBOND SPI-Flash) Failed to register new device\n");            
            ret = -EAGAIN;
            goto out;
        }
    }
    else {
        printk(KERN_NOTICE "Rtk SFC: using dynamic partition\n");
        ret = add_mtd_partitions(&descriptor, mtd_parts.parts, nr_parts);
        if(ret) goto out;
    }

    /* restore opcode to read */
    _switch_to_read_mode(&rtk_sfc_info, eREAD_MODE_SINGLE_FAST_READ);

#if defined(CONFIG_MTD_RTK_SFC_DEBUG)
    /* allocating debug information */
    if((dbg_counter = (int *) kmalloc(sizeof(int), GFP_KERNEL)))
        memset(dbg_counter, 0, sizeof(int));

    if((dbg_table = (DESCRIPTOR_TABLE *) kmalloc(sizeof(DESCRIPTOR_TABLE) * DBG_ENTRY_NUM, GFP_KERNEL)))
        memset(dbg_table, 0, sizeof(DESCRIPTOR_TABLE) * DBG_ENTRY_NUM);

    printk("DEBUG COUNTER = %08X  /  DEBUG TABLE = %08X\n", dbg_counter, dbg_table);
#endif

    printk("Rtk SFC: (for SST/SPANSION/MXIC SPI Flash)\n");
out:
    /* Cleanup any parsed partitions */
    mtd_part_parser_cleanup(&mtd_parts);

    return ret;
}


static void __exit rtk_sfc_exit(void)
{
#ifdef EMMC_ISSUE_LOCK
    unsigned long lock_flag;
#endif

#if defined(CONFIG_MTD_RTK_SFC_DEBUG)
    if(dbg_counter)
        kfree(dbg_counter);
    if(dbg_table)
        kfree(dbg_table);
#endif

#ifdef EMMC_ISSUE_LOCK
    rtk_lockapi_lock(lock_flag, (char *)__FUNCTION__);
#endif

    /* put read opcode into control register */
    SFC_SYNC;
    SYS_REG_TRY_LOCK(0);//add by alexchang 0722-2010
    REG_WRITE_U32(0x00000003, SFC_OPCODE);

#if SFC_USE_DELAY
    sfc_delay();
#endif

    REG_WRITE_U32(0x00000018, SFC_CTL);
    SYS_REG_TRY_UNLOCK;//add by alexchang 0722-2010
    SFC_SYNC;

#ifdef EMMC_ISSUE_LOCK
    rtk_lockapi_unlock(lock_flag, (char *)__FUNCTION__);
#endif

    del_mtd_device(&descriptor);

    /* Free DMA buffers */
#ifdef CONFIG_MTD_RTK_SFC_READ_MD
    if(read_dma_buf)
        dma_free_coherent(NULL, MD_PP_DATA_SIZE, (void *)read_dma_buf, read_dma_handle);
#endif
#ifdef CONFIG_MTD_RTK_SFC_WRITE_MD
    if(write_dma_buf)
        dma_free_coherent(NULL, MD_PP_DATA_SIZE, (void *)write_dma_buf, write_dma_handle);
#endif
}


module_init(rtk_sfc_init);
module_exit(rtk_sfc_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Chih-pin Wu <wucp@realtek.com.tw>");
MODULE_DESCRIPTION("MTD chip driver for Realtek Rtk Serial Flash Controller");
