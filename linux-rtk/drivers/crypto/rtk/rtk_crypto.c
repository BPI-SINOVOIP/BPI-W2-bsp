/*
 * rtk_crypto.c - MCP driver
 *
 * Copyright (c) 2017 Realtek Semiconductor Corp.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 */
#include <linux/cpufeature.h>
#include <linux/crypto.h>
#include <linux/module.h>

#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/dma-mapping.h>
#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/ioport.h>
#include <linux/delay.h>
#include <linux/slab.h>
#include <linux/mm.h>
#include <linux/interrupt.h>
#include <linux/wait.h>
#include <linux/of_address.h>
#include <linux/of_platform.h>
#include <linux/uaccess.h>
#include <linux/compat.h>
#include <linux/io.h>
#include <asm/mutex.h>

#include "asm/cacheflush.h"

#include <crypto/ablk_helper.h>
#include <crypto/algapi.h>

#include <crypto/sha.h>
#include <crypto/sha256_base.h>

#include "rtk_crypto.h"

static void __iomem *RTK_MCP_BASE;
static void __iomem *RTK_CRT_BASE;

static DEFINE_SPINLOCK(mcp_buffer_lock);
static DEFINE_MUTEX(mcp_mutex);

static struct platform_device* local_pdev;

MODULE_DESCRIPTION("rtk rtd1xxx Crypto Extensions");
MODULE_AUTHOR("Aaron Lin<aaron.lin@realtek.com>");
MODULE_LICENSE("GPL v2");

#define DEVNAME "rtk_crypto_mcp"

#define DYN_ALLOC 1

extern void aes_cipher_encrypt(struct crypto_tfm *tfm, u8 dst[], u8 const src[]);
extern void aes_cipher_decrypt(struct crypto_tfm *tfm, u8 dst[], u8 const src[]);

static unsigned long sha256_data_dma_vaddr;
static dma_addr_t sha256_data_dma_phyaddr;

static dma_addr_t sha256_padding_dma_phyaddr;

static unsigned int update_count=0;
static unsigned long last_len;

/*------------------------------------------------------------------
 * Func : _mcp_phy_init
 * Desc : init mcp engine
 * Parm : N/A
 * Retn : N/A
 *------------------------------------------------------------------*/
static int crypto__mcp_phy_init(void)
{
#ifdef CONFIG_ARCH_RTD139x
	unsigned int cur_value;
#endif


	//_mcp_load_otp();
	SET_MCP_CTRL(MCP_GO, RTK_MCP_BASE); // dessert go bit
	SET_MCP_EN(0xFE, RTK_MCP_BASE); // disable all interrupts
	SET_MCP_STATUS(0xFE, RTK_MCP_BASE); // clear interrupts status
	SET_MCP_BASE (0, RTK_MCP_BASE);
	SET_MCP_LIMIT(0, RTK_MCP_BASE);
	SET_MCP_RDPTR(0, RTK_MCP_BASE);
	SET_MCP_WRPTR(0, RTK_MCP_BASE);

#ifdef CONFIG_ARCH_RTD139x
	/* auto power management */
	cur_value = GET_PWM_CTRL(RTK_MCP_BASE);
	cur_value |= (1 << 22) | (1 << 23) | (1 << 24) | (1 << 25) | (1 << 27) | (1 << 28);
	SET_PWM_CTRL(cur_value, RTK_MCP_BASE);
#endif

	return 0;
}

/*------------------------------------------------------------------
 * Func : mcp_init
 * Desc : init mcp engine
 * Parm : N/A
 * Retn : N/A
 *------------------------------------------------------------------*/
static int crypto_mcp_init(void)
{
	if (crypto__mcp_phy_init()<0)
		return -1;

#if 0//def MCP_INTERRUPT_ENABLE
	if (request_irq(MCP_IRQ, mcp_isr, SA_INTERRUPT | SA_SHIRQ, "MCP", &mcp_wait_queue) < 0){
		mcp_warning("Request irq %d failed\n", MCP_IRQ);
		return -ENODEV;
	}
#endif

	return 0;
}

/*------------------------------------------------------------------
 * Func : mcp_uninit
 * Desc : uninit mcp engine
 * Parm : N/A
 * Retn : N/A
 *------------------------------------------------------------------*/
static void crypto_mcp_uninit(void)
{
	SET_MCP_CTRL(MCP_GO, RTK_MCP_BASE); // dessert go bit
	SET_MCP_EN(0xFE, RTK_MCP_BASE); // disable all interrupts
	msleep_interruptible(10); // wait for hw stop
	SET_MCP_BASE (0, RTK_MCP_BASE);
	SET_MCP_LIMIT(0, RTK_MCP_BASE);
	SET_MCP_RDPTR(0, RTK_MCP_BASE);
	SET_MCP_WRPTR(0, RTK_MCP_BASE);
#if 0 //def MCP_INTERRUPT_ENABLE
	free_irq(MCP_IRQ, &mcp_wait_queue);
#endif
}

/*---------------------------------------------------------------------- 
 * Func : mcp_dump_mem 
 * Desc : dump data in memory
 * Parm : data : start address of data
 * len : length of data
 * Retn : N/A
 *----------------------------------------------------------------------*/ 
void crypto_mcp_dump_mem(unsigned char* data, unsigned int len)
{
	int i;
	for (i = 0 ; i < len ; i++){
		if ((i & 0xF)==0)
			mcp_info("\n %04x | ", i);
		mcp_info("%02x ", data[i]);
	}
	mcp_info("\n");
}

/*---------------------------------------------------------------------- 
 * Func : mcp_dump_all_registers 
 * Desc : dump mcp registers
 * Parm : N/A
 * Retn : N/A
 *----------------------------------------------------------------------*/ 
void crypto_mcp_dump_all_registers(void)
{
	mcp_info("****** MCP Registers ******\n");
	mcp_info("MCP_CTRL addr:0x%x, value:0x%x\n", MCP_CTRL, GET_MCP_CTRL(RTK_MCP_BASE));
	mcp_info("MCP_STATUS addr:0x%x, value:0x%x\n", MCP_STATUS, GET_MCP_STATUS(RTK_MCP_BASE));
	mcp_info("MCP_EN addr:0x%x, value:0x%x\n", MCP_EN, GET_MCP_EN(RTK_MCP_BASE));
	mcp_info("MCP_BASE addr:0x%p, value:0x%x\n", RTK_MCP_BASE, GET_MCP_BASE(RTK_MCP_BASE));
	mcp_info("MCP_LIMIT addr:0x%x, value:0x%x\n", MCP_LIMIT, GET_MCP_LIMIT(RTK_MCP_BASE));
	mcp_info("MCP_RDPTR addr:0x%x, value:0x%x\n", MCP_RDPTR, GET_MCP_RDPTR(RTK_MCP_BASE));
	mcp_info("MCP_WRPTR addr:0x%x, value:0x%x\n", MCP_WRPTR, GET_MCP_WRPTR(RTK_MCP_BASE));
	mcp_info("MCP_DES_COUNT addr:0x%x, value:0x%x\n", MCP_DES_COUNT, GET_MCP_DES_COUNT(RTK_MCP_BASE));
	mcp_info("MCP_DES_COMPARE addr:0x%x, value:0x%x\n", MCP_DES_COMPARE, GET_MCP_DES_COMPARE(RTK_MCP_BASE));
}

/*---------------------------------------------------------------------- 
 * Func : mcp_dump_descriptor 
 * Desc : dump mcp descriptor
 * Parm : p_desc: pointer  to descriptor
 * Retn : N/A
 *----------------------------------------------------------------------*/ 
void crypto_mcp_dump_descriptor(mcp_desc *p_desc)
{
	int i = 0;

	mcp_info("****** MCP Descriptor ******\n");
	mcp_info("p_desc->flags:0x%0x\n", p_desc->flags);

	for(i = 0 ; i < sizeof(p_desc->key)/sizeof(p_desc->key[0]) ; i++){
		mcp_info("p_desc->key[%d]:0x%0x\n", i, p_desc->key[i]);
	}

	for(i = 0 ; i < sizeof(p_desc->iv)/sizeof(p_desc->iv[0]) ; i++){
		mcp_info("p_desc->iv[%d]:0x%0x\n", i, p_desc->iv[i]);
	}

	mcp_info("p_desc->data_in:0x%0x\n", p_desc->data_in);
	mcp_info("p_desc->data_out:0x%0x\n", p_desc->data_out);
	mcp_info("p_desc->length:0x%0x\n", p_desc->length);
}

/*------------------------------------------------------------------ 
 * Func : _mcp_set_desc_buffer
 * Desc : set descriptors buffer
 * Parm : base  : base address of descriptor buffer
 * limit : limit address of descriptor buffer
 * rp : read pointer of descriptor buffer
 * wp : write pointer of descriptor buffer
 * Retn : 0
 *------------------------------------------------------------------*/
int crypto__mcp_set_desc_buffer(unsigned long	 base, unsigned long limit, unsigned long rp, unsigned long wp)
{
	unsigned long event;

	spin_lock_irqsave(&mcp_buffer_lock, event);
	SET_MCP_BASE (base, RTK_MCP_BASE);
	SET_MCP_LIMIT(limit, RTK_MCP_BASE);
	SET_MCP_RDPTR(rp, RTK_MCP_BASE);
	SET_MCP_WRPTR(wp, RTK_MCP_BASE);
	spin_unlock_irqrestore(&mcp_buffer_lock, event);

	return 0;
}

/*------------------------------------------------------------------ 
 * Func : _mcp_start_xfer
 * Desc : Start Xfer
 * Parm : N/A
 * Retn : S_OK /  S_FALSE 
 *------------------------------------------------------------------*/
int crypto__mcp_start_xfer(void)
{
	int ret = -1;
	int WaitTime = 0x3FF << 2;
	int wiat_clear_timeout = 0;

	SET_MCP_DES_COUNT(0x0, RTK_MCP_BASE);   // descriptor in ddr
	SET_MCP_CTRL(MCP_CLEAR | MCP_WRITE_DATA, RTK_MCP_BASE);	// issue clear

	while ((GET_MCP_CTRL(RTK_MCP_BASE) & MCP_CLEAR) && wiat_clear_timeout++ < 30);

	if (GET_MCP_CTRL(RTK_MCP_BASE) & MCP_CLEAR){
		mcp_warning("wait clear bit deassert timeout,  force unset clear bit, (CTRL=%08x, STATUS=%08x)\n", GET_MCP_CTRL(RTK_MCP_BASE), GET_MCP_STATUS(RTK_MCP_BASE));
		SET_MCP_CTRL(MCP_CLEAR, RTK_MCP_BASE);	// issue clear
		mcp_warning("CTRL=%08x, STATUS=%08x)\n",GET_MCP_CTRL(RTK_MCP_BASE), GET_MCP_STATUS(RTK_MCP_BASE));
	}

	SET_MCP_EN(0xFE, RTK_MCP_BASE);
	SET_MCP_STATUS(0xFE, RTK_MCP_BASE);	// clear status

	mcp_info("before go:\n");
	crypto_mcp_dump_all_registers();

	SET_MCP_CTRL(MCP_GO | MCP_WRITE_DATA, RTK_MCP_BASE);

	while (WaitTime--){
		mcp_debug("STATUS=%08x, CTRL=%08x\n",GET_MCP_STATUS(RTK_MCP_BASE), GET_MCP_CTRL(RTK_MCP_BASE));
		if (!(GET_MCP_CTRL(RTK_MCP_BASE) & MCP_GO)) {
			mcp_info("ctrl break\n");
			break;
		}

		if (GET_MCP_STATUS(RTK_MCP_BASE)&0x6) {
			mcp_info("status break\n");
			break;
		}

		//msleep_interruptible(1);
		//msleep(1);
	}
#ifdef CONFIG_ARCH_RTD16xx
	ret = ((GET_MCP_STATUS(RTK_MCP_BASE) & ~(MCP_RING_EMPTY | MCP_COMPARE|MCP_KL_DONE|MCP_K_KL_DONE))) ? -1 : 0;
#else
	ret = ((GET_MCP_STATUS(RTK_MCP_BASE) & ~(MCP_RING_EMPTY | MCP_COMPARE))) ? -1 : 0;
#endif
	mcp_info("after go:\n");
	crypto_mcp_dump_all_registers();

	if (ret <0)
		mcp_warning("do mcp command failed, (MCP_Status %08x)\n", GET_MCP_STATUS(RTK_MCP_BASE));

	SET_MCP_CTRL(MCP_GO, RTK_MCP_BASE); // clear go bit
	SET_MCP_STATUS(0xFE, RTK_MCP_BASE); // clear ring empty

	return ret;
}

/*------------------------------------------------------------------ 
 * Func : mcp_do_command 
 * Desc : Do Command
 * Parm : p_desc : number of Descriptor to be Execute
 * n_desc : number of Descriptor to be Execute
 * Retn : 0 : success, others fail  
 *------------------------------------------------------------------*/
int crypto_mcp_do_command(mcp_desc* p_desc, int n_desc)
{
	int	 ret = 0;
	int	 len = sizeof(mcp_desc) * n_desc;

	int	 i, j;
	unsigned long desc_dma_vaddr;
          unsigned long data_out_vaddr;
	dma_addr_t desc_dma;
	mcp_desc *p_desc_vaddr;

	if(n_desc){
		mutex_lock(&mcp_mutex);

		desc_dma_vaddr = (unsigned long)dma_alloc_coherent(&local_pdev->dev, n_desc * sizeof(mcp_desc) + sizeof(mcp_desc), &desc_dma, GFP_ATOMIC|GFP_DMA);
		//desc_dma_vaddr = kmalloc(n_desc * sizeof(mcp_desc) + sizeof(mcp_desc), GFP_KERNEL);
		if (desc_dma_vaddr){

			p_desc_vaddr = (mcp_desc *)desc_dma_vaddr;

			for (i = 0; i < n_desc ; i++){
				p_desc_vaddr->flags = p_desc->flags;

				for (j = 0 ; j < sizeof(p_desc->key) / sizeof(p_desc->key[0]) ; j++) {
					p_desc_vaddr->key[j] = p_desc->key[j];
				}

				for (j = 0 ; j < sizeof(p_desc->iv) / sizeof(p_desc->iv[0]) ; j++) {
					p_desc_vaddr->iv[j] = p_desc->iv[j];
				}

				//p_desc_vaddr->data_in = virt_to_phys(p_desc->data_in);
				//p_desc_vaddr->data_out = virt_to_phys(p_desc->data_out);
				p_desc_vaddr->data_in = p_desc->data_in;
				p_desc_vaddr->data_out = p_desc->data_out;
				p_desc_vaddr->length = p_desc->length;
#if 1//def MCP_DEBUG_EN
				__flush_dcache_area(p_desc_vaddr, sizeof(mcp_desc)*2);
				crypto_mcp_dump_descriptor(p_desc_vaddr);
#else
				mcp_info("Do command, flags:0x%0x\n", p_desc->flags);
#endif
				p_desc_vaddr++;
				p_desc++;
			}

			p_desc_vaddr = p_desc_vaddr - n_desc;
			p_desc = p_desc - n_desc;

			crypto__mcp_set_desc_buffer(desc_dma, desc_dma + len + sizeof(mcp_desc), desc_dma, desc_dma + len);
			ret = crypto__mcp_start_xfer();
		}else{
			mcp_warning("no dma buffer for descriptor!\n");
			ret = -1;   // error, no dma buffer for descriptor
		}
                    //crypto_mcp_dump_mem((unsigned char *)p_desc->data_out, 16);
                    //__flush_dcache_area(p_desc_vaddr->data_out, p_desc_vaddr->length);
		dma_free_coherent(&local_pdev->dev, n_desc * sizeof(mcp_desc), (void *)desc_dma_vaddr, desc_dma);

		mutex_unlock(&mcp_mutex);
	}

	return ret;
}

/********************************************************************************
 AES
 ********************************************************************************/
/*------------------------------------------------------------------
 * Func : MCP_AES_DESC_INIT
 * Desc : Init AES Descriptor
 * Parm : pDesc : Descriptor to be Load
 * EnDe : Encryption/Descryption
 * 0 for Decryption / 1 for Encryption
 * Mode : Operation Mode
 * Key : Key Value
 * IV : Initial Vector
 * Retn : S_OK /  S_FALSE 
 *------------------------------------------------------------------*/
int crypto_MCP_AES_DESC_INIT(mcp_desc*	 pDesc, unsigned char EnDe, unsigned char Mode, unsigned char Key[32], unsigned char IV[16], unsigned int key_len)
{
	memset(pDesc, 0, sizeof(mcp_desc));

	switch (Mode){
	case MCP_BCM_ECB:
	case MCP_BCM_CBC:
	case MCP_BCM_CTR:
		pDesc->flags = MARS_MCP_MODE(MCP_ALGO_AES) | MARS_MCP_BCM(Mode) | MARS_MCP_ENC(EnDe);

		if(Key){

                              if(key_len<32){
			pDesc->key[0]  = (Key[ 0]<<24) + (Key[ 1]<<16) + (Key[ 2]<<8) + Key[ 3];
			pDesc->key[1]  = (Key[ 4]<<24) + (Key[ 5]<<16) + (Key[ 6]<<8) + Key[ 7];
			pDesc->key[2]  = (Key[ 8]<<24) + (Key[ 9]<<16) + (Key[10]<<8) + Key[11];
			pDesc->key[3]  = (Key[12]<<24) + (Key[13]<<16) + (Key[14]<<8) + Key[15];
                                }

                              if(key_len == 24){
                                        //printk(KERN_ERR "*************alg: crypto_MCP_AES_DESC_INIT, len: %d\n", key_len);
                                        pDesc->flags |= 0x18;
            			pDesc->key[4]  = (Key[ 16]<<24) + (Key[ 17]<<16) + (Key[ 18]<<8) + Key[ 19];
            			pDesc->key[5]  = (Key[ 20]<<24) + (Key[ 21]<<16) + (Key[ 22]<<8) + Key[ 23];
                              }else if(key_len == 32){

                                        //printk(KERN_ERR "*************alg: crypto_MCP_AES_DESC_INIT, len: %d\n", key_len);
                                        pDesc->flags |= 0x3010;
                                        pDesc->key[0]  = (unsigned int)Key;
                              }
		}else
			pDesc->flags |= MARS_MCP_KEY_SEL(MCP_KEY_SEL_OTP);

		if(IV){
			pDesc->iv[0]   = (IV[ 0]<<24) + (IV[ 1]<<16) + (IV[ 2]<<8) + IV[ 3];
			pDesc->iv[1]   = (IV[ 4]<<24) + (IV[ 5]<<16) + (IV[ 6]<<8) + IV[ 7];
			pDesc->iv[2]   = (IV[ 8]<<24) + (IV[ 9]<<16) + (IV[10]<<8) + IV[11];
			pDesc->iv[3]   = (IV[12]<<24) + (IV[13]<<16) + (IV[14]<<8) + IV[15];
		}
		return 0;
	default:
		mcp_warning("Init AES descriptor failed - invalid mode (%d)\n", Mode);
		return -1;
	}
}

/*------------------------------------------------------------------
 * Func : MCP_AES_Decryption
 * Desc : Do AES Decryption
 * Parm : mode : Operation Mode
 * key : Key Value
 * iv : Initial Vector
 * p_in : Data In
 * p_out : Data Out
 * len : Data Length
 * Retn : 0 for success, others failed
 *------------------------------------------------------------------*/
int crypto_MCP_AES_Decryption(unsigned char mode, unsigned char key[16], unsigned char iv[16], unsigned char* p_in, unsigned char* p_out, unsigned long len, unsigned int key_len)
{
	mcp_desc desc;
	int ret;

	unsigned long data_dma_vaddr=NULL;
	dma_addr_t data_dma_phyaddr;
	unsigned char *pData = NULL;
	int i = 0;

	unsigned long key_dma_vaddr=NULL;
	dma_addr_t key_dma_phyaddr;
	unsigned char *pKey = NULL;
          unsigned char tmp_iv[16];
	//int i = 0;

	data_dma_vaddr = (unsigned long)dma_alloc_coherent(&local_pdev->dev, len, &data_dma_phyaddr, GFP_ATOMIC|GFP_DMA);

	if (data_dma_vaddr) {
		pData = (unsigned char *)data_dma_vaddr;

		for (i = 0; i < len; i++) {
			pData[i] = p_in[i];
		}

                if(iv && mode==MCP_BCM_CBC){ //update for next iv
		for (i = 0; i < 16; i++) {
			 tmp_iv[i]=pData[len-16+i];
		}
                }
		//mcp_dump_data_with_text(pData, 16, "decrypted value : ");
	}else{
		mcp_warning("test dma alloc fail");
	}


         if(key_len==32){
            	key_dma_vaddr = (unsigned long)dma_alloc_coherent(&local_pdev->dev, key_len, &key_dma_phyaddr, GFP_ATOMIC|GFP_DMA);

            	if (key_dma_vaddr) {
            		pKey = (unsigned char *)key_dma_vaddr;

            		for (i = 0; i < key_len; i++) {
            			pKey[i] = key[i];
            		}
            		//mcp_dump_data_with_text(pKey, key_len, "decrypted key : ");
            	}else{
            		mcp_warning("test key dma alloc fail");
            	}

                    crypto_MCP_AES_DESC_INIT(&desc, 0, mode, (unsigned char *)key_dma_phyaddr, iv, key_len);
         }else{
	            crypto_MCP_AES_DESC_INIT(&desc, 0, mode, key, iv, key_len);
         }

	desc.data_in = data_dma_phyaddr;
	desc.data_out = data_dma_phyaddr;
	//desc.length = len & ~0xF;
	desc.length = len;

	ret = crypto_mcp_do_command(&desc, 1);
	//printk(KERN_ERR "*************alg: crypto_MCP_AES_Decryption, ret: %d\n",ret);
		for (i = 0; i < len; i++) {
			 p_out[i]=pData[i];
		}

                if(iv && mode==MCP_BCM_CBC){ //update for next iv
		for (i = 0; i < 16; i++) {
			 iv[i]=tmp_iv[i];
		}
                }

            dma_free_coherent(&local_pdev->dev, len, (void *)data_dma_vaddr, data_dma_phyaddr);

            if(key_dma_vaddr){
                        mcp_warning("free key dma alloc");
                        dma_free_coherent(&local_pdev->dev, key_len, (void *)key_dma_vaddr, key_dma_phyaddr);
            }
	return ret;
}

/*------------------------------------------------------------------
 * Func : MCP_AES_Encryption
 * Desc : Do AES Encryption
 * Parm : mode : Operation Mode
 * key : Key Value
 * iv : Initial Vector
 * p_in : Data In
 * p_out : Data Out
 * len : Data Length
 * Retn : 0 for success, others failed
 *------------------------------------------------------------------*/
int crypto_MCP_AES_Encryption(unsigned char mode, unsigned char key[16], unsigned char iv[16], unsigned char* p_in, unsigned char* p_out, unsigned long len, unsigned int key_len)
{
	mcp_desc desc;
	int ret;

	unsigned long data_dma_vaddr=NULL;
	dma_addr_t data_dma_phyaddr;
	unsigned char *pData = NULL;
	int i = 0;

	unsigned long key_dma_vaddr=NULL;
	dma_addr_t key_dma_phyaddr;
	unsigned char *pKey = NULL;
	//int i = 0;

	data_dma_vaddr = (unsigned long)dma_alloc_coherent(&local_pdev->dev, len, &data_dma_phyaddr, GFP_ATOMIC|GFP_DMA);

	if (data_dma_vaddr) {
		pData = (unsigned char *)data_dma_vaddr;

		for (i = 0; i < len; i++) {
			pData[i] = p_in[i];
		}
		//mcp_dump_data_with_text(pData, 16, "decrypted value : ");
	}else{
		mcp_warning("test dma alloc fail");
	}


         if(key_len==32){ //for aes 256
            	key_dma_vaddr = (unsigned long)dma_alloc_coherent(&local_pdev->dev, key_len, &key_dma_phyaddr, GFP_ATOMIC|GFP_DMA);

            	if (key_dma_vaddr) {
            		pKey = (unsigned char *)key_dma_vaddr;

            		for (i = 0; i < key_len; i++) {
            			pKey[i] = key[i];
            		}
            		//mcp_dump_data_with_text(pKey, key_len, "decrypted key : ");
            	}else{
            		mcp_warning("test key dma alloc fail");
            	}

                    crypto_MCP_AES_DESC_INIT(&desc, 1, mode, (unsigned char *)key_dma_phyaddr, iv, key_len);
         }else{
                    crypto_MCP_AES_DESC_INIT(&desc, 1, mode, key, iv, key_len);
         }

	desc.data_in = data_dma_phyaddr;
	desc.data_out = data_dma_phyaddr;
	//desc.length = len & ~0xF;
	desc.length = len;

	ret = crypto_mcp_do_command(&desc, 1);
	//printk(KERN_ERR "*************alg: crypto_MCP_AES_Encryption, ret: %d\n",ret);
		for (i = 0; i < len; i++) {
			 p_out[i]=pData[i];
		}

        if(iv && mode==MCP_BCM_CBC){ //update for next iv
		for (i = 0; i < 16; i++) {
			 iv[i]=pData[len-16+i];
		}
        }

            dma_free_coherent(&local_pdev->dev, len, (void *)data_dma_vaddr, data_dma_phyaddr);

            if(key_dma_vaddr){
                        mcp_warning("free key dma alloc");
                        dma_free_coherent(&local_pdev->dev, key_len, (void *)key_dma_vaddr, key_dma_phyaddr);
            }
	return ret;
}

/*------------------------------------------------------------------ 
 * Func : MCP_AES_128_ECB_DataEncryptTest
 * Desc : Test AES 128 ECB
 * Parm : N/A
 * Retn : N/A
 *------------------------------------------------------------------*/
void crypto_MCP_AES_128_ECB_DataEncryptTest(void)
{
	unsigned char Data[16]={0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88,
										 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff, 0x00};
	unsigned char Key[16];

	unsigned long data_dma_vaddr;
	dma_addr_t data_dma_phyaddr;
	unsigned char *pData = NULL;
	int i = 0;

	data_dma_vaddr = (unsigned long)dma_alloc_coherent(&local_pdev->dev, sizeof(Data), &data_dma_phyaddr, GFP_ATOMIC|GFP_DMA);

	if (data_dma_vaddr) {
		memset(Key, 'b', sizeof(Key));

		pData = (unsigned char *)data_dma_vaddr;

		for (i = 0; i < sizeof(Data); i++) {
			pData[i] = Data[i];
		}

		crypto_MCP_AES_Encryption(MCP_BCM_ECB, Key,NULL, (unsigned char *)data_dma_phyaddr, (unsigned char *)data_dma_phyaddr, 16, 16);

		mcp_dump_data_with_text(pData, 16, "encrypted value : ");

		crypto_MCP_AES_Decryption(MCP_BCM_ECB, Key,NULL, (unsigned char *)data_dma_phyaddr, (unsigned char *)data_dma_phyaddr, 16, 16);

		mcp_dump_data_with_text(pData, 16, "decrypted value : ");
	}else{
		mcp_warning("test dma alloc fail");
	}

	dma_free_coherent(&local_pdev->dev, sizeof(Data), (void *)data_dma_vaddr, data_dma_phyaddr);
}

static int rtk_mcp_aes_ecb_cipher_encrypt(struct blkcipher_desc *desc, struct scatterlist *dst,
		       struct scatterlist *src, unsigned int nbytes)
{
	struct crypto_aes_ctx *ctx = crypto_blkcipher_ctx(desc->tfm);
	int err, first, rounds = 6 + ctx->key_length / 4;
	struct blkcipher_walk walk;
	unsigned int blocks;
	//printk(KERN_ERR "*************alg: ecb_encrypt, nbytes:%d\n", nbytes);
	desc->flags &= ~CRYPTO_TFM_REQ_MAY_SLEEP;
	blkcipher_walk_init(&walk, dst, src, nbytes);
	err = blkcipher_walk_virt(desc, &walk);

	for (first = 1; (blocks = (walk.nbytes / AES_BLOCK_SIZE)); first = 0) {
		crypto_MCP_AES_Encryption(MCP_BCM_ECB, (unsigned char*)ctx->key_enc, NULL, walk.src.virt.addr, walk.dst.virt.addr, AES_BLOCK_SIZE*blocks, ctx->key_length);
		err = blkcipher_walk_done(desc, &walk, walk.nbytes % AES_BLOCK_SIZE);
	}
	return err;
}

static int rtk_mcp_aes_ecb_cipher_decrypt(struct blkcipher_desc *desc, struct scatterlist *dst,
		       struct scatterlist *src, unsigned int nbytes)
{
	struct crypto_aes_ctx *ctx = crypto_blkcipher_ctx(desc->tfm);
	int err, first, rounds = 6 + ctx->key_length / 4;
	struct blkcipher_walk walk;
	unsigned int blocks;
	//printk(KERN_ERR "*************alg: ecb_decrypt\n");
	desc->flags &= ~CRYPTO_TFM_REQ_MAY_SLEEP;
	blkcipher_walk_init(&walk, dst, src, nbytes);
	err = blkcipher_walk_virt(desc, &walk);

	for (first = 1; (blocks = (walk.nbytes / AES_BLOCK_SIZE)); first = 0) {
		crypto_MCP_AES_Decryption(MCP_BCM_ECB, (unsigned char*)ctx->key_enc, NULL, walk.src.virt.addr, walk.dst.virt.addr, AES_BLOCK_SIZE*blocks, ctx->key_length);
		err = blkcipher_walk_done(desc, &walk, walk.nbytes % AES_BLOCK_SIZE);
	}
	return err;
}

static int rtk_mcp_aes_cbc_cipher_encrypt(struct blkcipher_desc *desc, struct scatterlist *dst,
		       struct scatterlist *src, unsigned int nbytes)
{
	struct crypto_aes_ctx *ctx = crypto_blkcipher_ctx(desc->tfm);
	int err, first, rounds = 6 + ctx->key_length / 4;
	struct blkcipher_walk walk;
	unsigned int blocks;
	//printk(KERN_ERR "*************alg: cbc_encrypt, nbytes:%d\n", nbytes);
	desc->flags &= ~CRYPTO_TFM_REQ_MAY_SLEEP;
	blkcipher_walk_init(&walk, dst, src, nbytes);
	err = blkcipher_walk_virt(desc, &walk);
	unsigned char IV[16];
memcpy(IV, walk.iv, 16);
	for (first = 1; (blocks = (walk.nbytes / AES_BLOCK_SIZE)); first = 0) {
		crypto_MCP_AES_Encryption(MCP_BCM_CBC, (unsigned char*)ctx->key_enc, IV, walk.src.virt.addr, walk.dst.virt.addr, AES_BLOCK_SIZE*blocks, ctx->key_length);
		err = blkcipher_walk_done(desc, &walk, walk.nbytes % AES_BLOCK_SIZE);
	}
	return err;
}

static int rtk_mcp_aes_cbc_cipher_decrypt(struct blkcipher_desc *desc, struct scatterlist *dst,
		       struct scatterlist *src, unsigned int nbytes)
{
	struct crypto_aes_ctx *ctx = crypto_blkcipher_ctx(desc->tfm);
	int err, first, rounds = 6 + ctx->key_length / 4;
	struct blkcipher_walk walk;
	unsigned int blocks;
	//printk(KERN_ERR "*************alg: cbc_decrypt\n");
	desc->flags &= ~CRYPTO_TFM_REQ_MAY_SLEEP;
	blkcipher_walk_init(&walk, dst, src, nbytes);
	err = blkcipher_walk_virt(desc, &walk);
	unsigned char IV[16];
memcpy(IV, walk.iv, 16);

	for (first = 1; (blocks = (walk.nbytes / AES_BLOCK_SIZE)); first = 0) {
		crypto_MCP_AES_Decryption(MCP_BCM_CBC, (unsigned char*)ctx->key_enc, IV, walk.src.virt.addr, walk.dst.virt.addr, AES_BLOCK_SIZE*blocks, ctx->key_length);
		err = blkcipher_walk_done(desc, &walk, walk.nbytes % AES_BLOCK_SIZE);
	}

	return err;
}

static int rtk_mcp_aes_ctr_cipher_encrypt(struct blkcipher_desc *desc, struct scatterlist *dst,
		       struct scatterlist *src, unsigned int nbytes)
{
	struct crypto_aes_ctx *ctx = crypto_blkcipher_ctx(desc->tfm);
	int err, first, rounds = 6 + ctx->key_length / 4;
	struct blkcipher_walk walk;
	unsigned int blocks;

	unsigned long q_cnt = 0;
	unsigned long r_cnt = 0;
	unsigned char IV[16];
	unsigned char ecnt[16];
	int i;
	unsigned int n=0;
	unsigned int total_bytes=0;
	unsigned long DataLen_count=0;

	desc->flags &= ~CRYPTO_TFM_REQ_MAY_SLEEP;
	blkcipher_walk_init(&walk, dst, src, nbytes);
	err = blkcipher_walk_virt_block(desc, &walk, AES_BLOCK_SIZE);

            memcpy(IV, walk.iv, 16);
            total_bytes=nbytes;

	while ((blocks = (walk.nbytes / AES_BLOCK_SIZE))) {
		crypto_MCP_AES_Encryption(MCP_BCM_CTR, (unsigned char*)ctx->key_enc, walk.iv, walk.src.virt.addr, walk.dst.virt.addr, blocks*AES_BLOCK_SIZE, ctx->key_length);
		first = 0;
		nbytes -= blocks * AES_BLOCK_SIZE;
		/* Add count value to IV */
		q_cnt = walk.nbytes/ 16; // block num

		while(q_cnt--) {
			i = 15;
			do {
				IV[i]++;
			} while (!IV[i] && i-- >= 0);
		}
                    memcpy(walk.iv, IV, 16); //for next iv
		if (nbytes && nbytes == walk.nbytes% AES_BLOCK_SIZE)
			break;
		err = blkcipher_walk_done(desc, &walk,
					  walk.nbytes % AES_BLOCK_SIZE);
	}

	if (walk.nbytes % AES_BLOCK_SIZE) {
		u8 *tdst = walk.dst.virt.addr + blocks * AES_BLOCK_SIZE;
		u8 *tsrc = walk.src.virt.addr + blocks * AES_BLOCK_SIZE;

		DataLen_count=total_bytes % AES_BLOCK_SIZE;
		while (DataLen_count--) {
		if (n == 0){
                            crypto_MCP_AES_Encryption(MCP_BCM_ECB, (unsigned char*)ctx->key_enc, NULL, IV, ecnt, AES_BLOCK_SIZE, ctx->key_length);
		}

		*(tdst++) = *(tsrc++) ^ ecnt[n];
		n = (n+1) % 16;

		if (n == 0) {
			i = 15;
			do {
				IV[i]++;
			} while (!IV[i] && i-- >= 0);
		}
	}

		err = blkcipher_walk_done(desc, &walk, 0);
	}

	return err;
}

static int rtk_mcp_aes_ctr_cipher_decrypt(struct blkcipher_desc *desc, struct scatterlist *dst,
		       struct scatterlist *src, unsigned int nbytes)
{
	struct crypto_aes_ctx *ctx = crypto_blkcipher_ctx(desc->tfm);
	int err, first, rounds = 6 + ctx->key_length / 4;
	struct blkcipher_walk walk;
	unsigned int blocks;

	unsigned long q_cnt = 0;
	unsigned long r_cnt = 0;
	unsigned char IV[16];
	unsigned char ecnt[16];
	int i;
	unsigned int n=0;
	unsigned int total_bytes=0;
	unsigned long DataLen_count=0;

	desc->flags &= ~CRYPTO_TFM_REQ_MAY_SLEEP;
	blkcipher_walk_init(&walk, dst, src, nbytes);
	err = blkcipher_walk_virt_block(desc, &walk, AES_BLOCK_SIZE);

            memcpy(IV, walk.iv, 16);
            total_bytes=nbytes;

	while ((blocks = (walk.nbytes / AES_BLOCK_SIZE))) {
		crypto_MCP_AES_Decryption(MCP_BCM_CTR, (unsigned char*)ctx->key_enc, walk.iv, walk.src.virt.addr, walk.dst.virt.addr, blocks*AES_BLOCK_SIZE, ctx->key_length);
		first = 0;
		nbytes -= blocks * AES_BLOCK_SIZE;
		/* Add count value to IV */
		q_cnt = walk.nbytes/ 16; // block num

		while(q_cnt--) {
			i = 15;
			do {
				IV[i]++;
			} while (!IV[i] && i-- >= 0);
		}
                    memcpy(walk.iv, IV, 16); //for next iv
		if (nbytes && nbytes == walk.nbytes% AES_BLOCK_SIZE)
			break;
		err = blkcipher_walk_done(desc, &walk,
					  walk.nbytes % AES_BLOCK_SIZE);
	}

	if (walk.nbytes % AES_BLOCK_SIZE) {
		u8 *tdst = walk.dst.virt.addr + blocks * AES_BLOCK_SIZE;
		u8 *tsrc = walk.src.virt.addr + blocks * AES_BLOCK_SIZE;

		DataLen_count=total_bytes % AES_BLOCK_SIZE;
		while (DataLen_count--) {
		if (n == 0){
                            crypto_MCP_AES_Encryption(MCP_BCM_ECB, (unsigned char*)ctx->key_enc, NULL, IV, ecnt, AES_BLOCK_SIZE, ctx->key_length);
		}

		*(tdst++) = *(tsrc++) ^ ecnt[n];
		n = (n+1) % 16;

		if (n == 0) {
			i = 15;
			do {
				IV[i]++;
			} while (!IV[i] && i-- >= 0);
		}
	}

		err = blkcipher_walk_done(desc, &walk, 0);
	}

	return err;
}

int crypto_rtk_aes_key(struct crypto_aes_ctx *ctx, const u8 *in_key,
		unsigned int key_len)
{
#if 1
	const __le32 *key = (const __le32 *)in_key;

	if (key_len != AES_KEYSIZE_128 && key_len != AES_KEYSIZE_192 &&
			key_len != AES_KEYSIZE_256)
		return -EINVAL;

	ctx->key_length = key_len;

	ctx->key_enc[0] = le32_to_cpu(key[0]);
	ctx->key_enc[1] = le32_to_cpu(key[1]);
	ctx->key_enc[2] = le32_to_cpu(key[2]);
	ctx->key_enc[3] = le32_to_cpu(key[3]);

	switch (key_len) {
	case AES_KEYSIZE_128:
		break;

	case AES_KEYSIZE_192:
		ctx->key_enc[4] = le32_to_cpu(key[4]);
		ctx->key_enc[5] = le32_to_cpu(key[5]);
		break;

	case AES_KEYSIZE_256:
		ctx->key_enc[4] = le32_to_cpu(key[4]);
		ctx->key_enc[5] = le32_to_cpu(key[5]);
		ctx->key_enc[6] = le32_to_cpu(key[6]);
		ctx->key_enc[7] = le32_to_cpu(key[7]);
		break;
	}
    #endif
	return 0;
}

int rtk_mcp_aes_setkey(struct crypto_tfm *tfm, const u8 *in_key,
		  unsigned int key_len)
{
	struct crypto_aes_ctx *ctx = crypto_tfm_ctx(tfm);
	int ret;
	//mcp_dump_data_with_text(in_key, key_len, "in_key : ");
	//ret = crypto_rtk_aes_expand_key(ctx, in_key, key_len);
	ret = crypto_rtk_aes_key(ctx, in_key, key_len);
    
	//mcp_dump_data_with_text((unsigned char *)ctx->key_enc, key_len, "extend ctx->key_enc : ");
	//mcp_dump_data_with_text((unsigned char *)ctx->key_dec, key_len, "extend ctx->key_dec : ");
	if (!ret)
		return 0;

	tfm->crt_flags |= CRYPTO_TFM_RES_BAD_KEY_LEN;
	return -EINVAL;
}
EXPORT_SYMBOL(rtk_mcp_aes_setkey);

static int append_padding(unsigned int length, unsigned char *dst)
{
    unsigned int num_of_bits;
    int i, j, tmp;
    int pad_len;

    if ((length == 0) || (dst == NULL)) {
        return -1;
    }

    // calculate padding length
    pad_len = 1;
    while ((length + pad_len) % 64 != 56)
        pad_len++;
    pad_len += 8;

    // fill padding pattern
    memset(dst, 0, pad_len);
    dst[0] = 1 << 7;

    num_of_bits = length * 8;
    for (i = pad_len - 8, j = 32; j >= 0; j -= 32) {
        tmp = (int) ((long long)num_of_bits >> j);
        dst[i++] = (tmp >> 24) & 0xff;
        dst[i++] = (tmp >> 16) & 0xff;
        dst[i++] = (tmp >> 8) & 0xff;
        dst[i++] =  tmp & 0xff;
        //printf("%ld >> %d = %d\n", num_of_bits, j, tmp);
    }

    return pad_len;
}

int crypto_MCP_SHA256_update(unsigned char* p_in, unsigned long len)
{
	mcp_desc desc;
	int ret;

	unsigned char *pData = NULL;
	int i = 0;

	sha256_data_dma_vaddr = (unsigned long)dma_alloc_coherent(&local_pdev->dev, len, &sha256_data_dma_phyaddr, GFP_ATOMIC|GFP_DMA);

	if (sha256_data_dma_vaddr) {
		pData = (unsigned char *)sha256_data_dma_vaddr;

		for (i = 0; i < len; i++) {
			pData[i] = p_in[i];
		}
		//mcp_dump_data_with_text(pData, 16, "decrypted value : ");
		ret = 0;
	}else{
		mcp_warning("crypto_MCP_SHA256_update dma alloc fail");
                    ret = -1;
	}

	return ret;
}

int crypto_MCP_SHA256_final(unsigned char* p_out, unsigned long len, unsigned int iv[8], unsigned int is_final)
{
	mcp_desc desc;
	int ret;

	unsigned char *pData = NULL;
    	unsigned char *pPaddingData = NULL;
	int i = 0;
	pData = (unsigned char *)sha256_data_dma_vaddr;
          unsigned long padding_tmp_vaddr;
          unsigned int padding_len;

          pPaddingData = (unsigned char *)padding_tmp_vaddr;
          if(update_count>1 && is_final){
                padding_len=((last_len/64)+2)*64;
                //printk(KERN_ERR "*************alg: software padding, padding len: %d\n", padding_len);    
                padding_tmp_vaddr = (unsigned long)dma_alloc_coherent(&local_pdev->dev, padding_len, &sha256_padding_dma_phyaddr, GFP_ATOMIC|GFP_DMA);
                memset(padding_tmp_vaddr, 0x0, sizeof(padding_tmp_vaddr));
                memcpy(padding_tmp_vaddr, pData, last_len);
                append_padding(len,padding_tmp_vaddr + last_len);
          }

	desc.flags= 0xb;

	desc.key[0] = iv[0];
	desc.key[1] = iv[1];
	desc.key[2] = iv[2];
	desc.key[3] = iv[3];
	desc.key[4] = iv[4];
	desc.key[5] = iv[5];
	desc.iv[0] = iv[6];
	desc.iv[1] = iv[7];

//for (i = 0; i < 8; i++) {
//printk(KERN_ERR "*************alg: crypto_MCP_SHA256_final, p_out: %x\n",iv[i]);
//}

          if(update_count>1 && is_final){
            	desc.data_in = sha256_padding_dma_phyaddr;
            	desc.data_out = sha256_padding_dma_phyaddr;

                      //if(len%16)
                      //len+=0x10;
                
            	//desc.length = len & ~0xF;
            	//desc.length = len;
                      if((last_len%64)<56)
                        desc.length = padding_len-64;
                     else{
                        desc.length = padding_len;
                     }

                      SET_MCP_CTRL1(GET_MCP_CTRL1(RTK_MCP_BASE) | 0x800, RTK_MCP_BASE); //disable auto padding
          }else{

                      desc.data_in = sha256_data_dma_phyaddr;
                      desc.data_out = sha256_data_dma_phyaddr;

                      //desc.length = len & ~0xF;
                      desc.length = len;

                      if(is_final){
                              //printk(KERN_ERR "*************alg: hw padding.\n");
                              SET_MCP_CTRL1(GET_MCP_CTRL1(RTK_MCP_BASE) & ~0x800, RTK_MCP_BASE); //auto padding
                      }else{
                              //printk(KERN_ERR "*************alg: hw padding off.\n");
                              SET_MCP_CTRL1(GET_MCP_CTRL1(RTK_MCP_BASE) | 0x800, RTK_MCP_BASE); //disable auto padding
                      }

          }

	ret = crypto_mcp_do_command(&desc, 1);
	//printk(KERN_ERR "*************alg: crypto_MCP_SHA256_final, ret: %d\n",ret);

	if(update_count>1 && is_final){

            	if(sha256_data_dma_vaddr && padding_tmp_vaddr){
            		for (i = 0; i < 32; i++) {
            			 p_out[i]=pPaddingData[i];
            			 //printk(KERN_ERR "*************alg: crypto_MCP_SHA256_final, p_out: %x\n",p_out[i]);
            		}

            		dma_free_coherent(&local_pdev->dev, len, (void *)sha256_data_dma_vaddr, sha256_data_dma_phyaddr);
            		dma_free_coherent(&local_pdev->dev, padding_len, (void *)padding_tmp_vaddr, sha256_padding_dma_phyaddr);
            	}

	}else{

                    	if(sha256_data_dma_vaddr){
                    		for (i = 0; i < 32; i++) {
                    			 p_out[i]=pData[i];
                    			 //printk(KERN_ERR "*************alg: crypto_MCP_SHA256_final, p_out: %x\n",p_out[i]);
                    		}

                    		dma_free_coherent(&local_pdev->dev, len, (void *)sha256_data_dma_vaddr, sha256_data_dma_phyaddr);
                    	}
	}
    
	return ret;
}
#if 0
static inline int rtk_sha256_base_init(struct shash_desc *desc)
{
	struct sha256_state *sctx = shash_desc_ctx(desc);
	sctx->state[0] = SHA256_H0;
	sctx->state[1] = SHA256_H1;
	sctx->state[2] = SHA256_H2;
	sctx->state[3] = SHA256_H3;
	sctx->state[4] = SHA256_H4;
	sctx->state[5] = SHA256_H5;
	sctx->state[6] = SHA256_H6;
	sctx->state[7] = SHA256_H7;
	sctx->count = 0;

	update_count=0;
	return 0;
}
#endif
int swap_endian(unsigned int input)
{
        unsigned int output;

        output = (input & 0xff000000)>>24|
                         (input & 0x00ff0000)>>8|
                         (input & 0x0000ff00)<<8|
                         (input & 0x000000ff)<<24;
        return output;
}
#if 0
int rtk_crypto_sha256_update(struct shash_desc *desc, const u8 *data,
			  unsigned int len)
{
        	struct sha256_state *sctx = shash_desc_ctx(desc);
            unsigned int iv[8];
            unsigned int i=0;
	//unsigned int partial = sctx->count % SHA256_BLOCK_SIZE;
	//printk(KERN_ERR "*************alg: sha256_base_do_update, len:%d\n", len);
	//sctx->count += len;

	if(update_count){
              crypto_MCP_SHA256_final((unsigned char*)iv, sctx->count, sctx->state, 0);
              for(i = 0 ; i < 8 ; i++) {
                    iv[i] = swap_endian(iv[i]);
                }
              sctx->state[0] = iv[0];
              sctx->state[1] = iv[1];
              sctx->state[2] = iv[2];
              sctx->state[3] = iv[3];
              sctx->state[4] = iv[4];
              sctx->state[5] = iv[5];
              sctx->state[6] = iv[6];
              sctx->state[7] = iv[7];

              //print_hex_dump(KERN_ERR, "", DUMP_PREFIX_OFFSET,
			//16, 1,
			//(unsigned char *)sctx->state, 32, false);
             
            crypto_MCP_SHA256_update(data, len);
              last_len = len;
        }else
            crypto_MCP_SHA256_update(data, len);

        sctx->count += len;
	//return sha256_base_do_update(desc, data, len, sha256_generic_block_fn);
	update_count++;
	return 0;
}
EXPORT_SYMBOL(rtk_crypto_sha256_update);

static int rtk_sha256_final(struct shash_desc *desc, u8 *out)
{
        	struct sha256_state *sctx = shash_desc_ctx(desc);
          //printk(KERN_ERR "*************alg: rtk_sha256_final, sctx->count:%d\n", sctx->count);
          return crypto_MCP_SHA256_final(out, sctx->count, sctx->state, 1);
}

int rtk_crypto_sha256_finup(struct shash_desc *desc, const u8 *data,
			unsigned int len, u8 *hash)
{
	//printk(KERN_ERR "*************alg: rtk_crypto_sha256_finup\n");
	rtk_crypto_sha256_update(desc, data, len);
	return rtk_sha256_final(desc, hash);
}
EXPORT_SYMBOL(rtk_crypto_sha256_finup);
#endif
//==================================================================================

static inline int rtk_sha256_base_init(struct shash_desc *desc)
{
	struct sha256_state *sctx = shash_desc_ctx(desc);

	sctx->state[0] = CRYPTO_SHA256_H0;
	sctx->state[1] = CRYPTO_SHA256_H1;
	sctx->state[2] = CRYPTO_SHA256_H2;
	sctx->state[3] = CRYPTO_SHA256_H3;
	sctx->state[4] = CRYPTO_SHA256_H4;
	sctx->state[5] = CRYPTO_SHA256_H5;
	sctx->state[6] = CRYPTO_SHA256_H6;
	sctx->state[7] = CRYPTO_SHA256_H7;
	sctx->count = 0;

	return 0;
}

static inline int rtk_sha256_base_do_update(struct shash_desc *desc,
					const u8 *data,
					unsigned int len,
					sha256_block_fn *block_fn)
{
	struct sha256_state *sctx = shash_desc_ctx(desc);
	unsigned int partial = sctx->count % SHA256_BLOCK_SIZE;

	sctx->count += len;
//printk(KERN_ERR "*************alg: sha256_base_do_update, len:%d, sctx->count:%d\n", len, sctx->count);
	if (unlikely((partial + len) >= SHA256_BLOCK_SIZE)) {
		int blocks;

		if (partial) {
			int p = SHA256_BLOCK_SIZE - partial;

			memcpy(sctx->buf + partial, data, p);
			data += p;
			len -= p;
			//printk(KERN_ERR "*************alg: sha256_base_do_update partial, len:%d, sctx->count:%d\n", len, sctx->count);
			block_fn(sctx, sctx->buf, 1*SHA256_BLOCK_SIZE);
		}

		blocks = len / SHA256_BLOCK_SIZE;
		len %= SHA256_BLOCK_SIZE;

		if (blocks) {
                                //printk(KERN_ERR "*************alg: sha256_base_do_update blocks, len:%d, sctx->count:%d, blocks:%d\n", len, sctx->count, blocks);
			block_fn(sctx, data, blocks*SHA256_BLOCK_SIZE);
			data += blocks * SHA256_BLOCK_SIZE;
		}
		partial = 0;
	}
	if (len)
		memcpy(sctx->buf + partial, data, len);

	return 0;
}

static inline int rtk_sha256_base_do_finalize(struct shash_desc *desc,
					  sha256_block_fn *block_fn)
{
	const int bit_offset = SHA256_BLOCK_SIZE - sizeof(__be64);
	struct sha256_state *sctx = shash_desc_ctx(desc);
	__be64 *bits = (__be64 *)(sctx->buf + bit_offset);
	unsigned int partial = sctx->count % SHA256_BLOCK_SIZE;

	sctx->buf[partial++] = 0x80;
	if (partial > bit_offset) {
		memset(sctx->buf + partial, 0x0, SHA256_BLOCK_SIZE - partial);
		partial = 0;
		//printk(KERN_ERR "*************alg: sha256_base_do_finalize blocks, sctx->count:%d, partial:%d\n", sctx->count, partial);
		block_fn(sctx, sctx->buf, 1*SHA256_BLOCK_SIZE);
	}

	memset(sctx->buf + partial, 0x0, bit_offset - partial);
	*bits = cpu_to_be64(sctx->count << 3);
	block_fn(sctx, sctx->buf, 1*SHA256_BLOCK_SIZE);

	return 0;
}

static inline int rtk_sha256_base_finish(struct shash_desc *desc, u8 *out)
{
	unsigned int digest_size = crypto_shash_digestsize(desc->tfm);
	struct sha256_state *sctx = shash_desc_ctx(desc);
	__be32 *digest = (__be32 *)out;
	int i;
//printk(KERN_ERR "*************alg: sha256_base_finish,  sctx->count:%d\n", sctx->count);
	for (i = 0; digest_size > 0; i++, digest_size -= sizeof(__be32))
		put_unaligned_be32(sctx->state[i], digest++);

	*sctx = (struct sha256_state){};
	return 0;
}


static void rtk_sha256_generic_block_fn(struct sha256_state *sctx, u8 const *data,
				    int len)
{
            unsigned int iv[8];
            unsigned int i=0;
	//unsigned int partial = sctx->count % SHA256_BLOCK_SIZE;
	//printk(KERN_ERR "*************alg: sha256_base_do_update, len:%d\n", len);
	//sctx->count += len;

            crypto_MCP_SHA256_update(data, len);
            crypto_MCP_SHA256_final((unsigned char*)iv, len, sctx->state, 0);

              for(i = 0 ; i < 8 ; i++) {
                    iv[i] = swap_endian(iv[i]);
                }
              sctx->state[0] = iv[0];
              sctx->state[1] = iv[1];
              sctx->state[2] = iv[2];
              sctx->state[3] = iv[3];
              sctx->state[4] = iv[4];
              sctx->state[5] = iv[5];
              sctx->state[6] = iv[6];
              sctx->state[7] = iv[7];

	return 0;
}

int rtk_crypto_sha256_update(struct shash_desc *desc, const u8 *data,
			  unsigned int len)
{
//printk(KERN_ERR "*************alg: crypto_sha256_update, len:%d\n", len);
	return rtk_sha256_base_do_update(desc, data, len, rtk_sha256_generic_block_fn);
}
EXPORT_SYMBOL(rtk_crypto_sha256_update);

static int rtk_sha256_final(struct shash_desc *desc, u8 *out)
{
//printk(KERN_ERR "*************alg: sha256_final\n");
	rtk_sha256_base_do_finalize(desc, rtk_sha256_generic_block_fn);
	return rtk_sha256_base_finish(desc, out);
}

int rtk_crypto_sha256_finup(struct shash_desc *desc, const u8 *data,
			unsigned int len, u8 *hash)
{
	rtk_sha256_base_do_update(desc, data, len, rtk_sha256_generic_block_fn);
	return rtk_sha256_final(desc, hash);
}
EXPORT_SYMBOL(rtk_crypto_sha256_finup);

static struct crypto_alg rtk_aes_ecb_alg = {

	.cra_name		= "ecb(aes)",
	.cra_driver_name	= "__driver-ecb-aes-rtk",
	.cra_priority		= 0,
	.cra_flags		= CRYPTO_ALG_TYPE_BLKCIPHER |
				  CRYPTO_ALG_INTERNAL,
	.cra_blocksize		= AES_BLOCK_SIZE,
	.cra_ctxsize		= sizeof(struct crypto_aes_ctx),
	.cra_alignmask		= 0xf,
	.cra_type		= &crypto_blkcipher_type,
	.cra_module		= THIS_MODULE,
	.cra_blkcipher = {
		.min_keysize	= AES_MIN_KEY_SIZE,
		.max_keysize	= AES_MAX_KEY_SIZE,
		.ivsize		= AES_BLOCK_SIZE,
		.setkey		= rtk_mcp_aes_setkey,
		.encrypt	= rtk_mcp_aes_ecb_cipher_encrypt,
		.decrypt	= rtk_mcp_aes_ecb_cipher_decrypt,
	}
};

static struct crypto_alg rtk_aes_cbc_alg = {

	.cra_name		= "cbc(aes)",
	.cra_driver_name	= "__driver-cbc-aes-rtk",
	.cra_priority		= 0,
	.cra_flags		= CRYPTO_ALG_TYPE_BLKCIPHER |
				  CRYPTO_ALG_INTERNAL,
	.cra_blocksize		= AES_BLOCK_SIZE,
	.cra_ctxsize		= sizeof(struct crypto_aes_ctx),
	.cra_alignmask		= 0xf,
	.cra_type		= &crypto_blkcipher_type,
	.cra_module		= THIS_MODULE,
	.cra_blkcipher = {
		.min_keysize	= AES_MIN_KEY_SIZE,
		.max_keysize	= AES_MAX_KEY_SIZE,
		.ivsize		= AES_BLOCK_SIZE,
		.setkey		= rtk_mcp_aes_setkey,
		.encrypt	= rtk_mcp_aes_cbc_cipher_encrypt,
		.decrypt	= rtk_mcp_aes_cbc_cipher_decrypt,
	}
};

static struct crypto_alg rtk_aes_ctr_alg = {

	.cra_name		= "ctr(aes)",
	.cra_driver_name	= "__driver-ctr-aes-rtk",
	.cra_priority		= 0,
	.cra_flags		= CRYPTO_ALG_TYPE_BLKCIPHER |
				  CRYPTO_ALG_INTERNAL,
	.cra_blocksize		= 1,//for chunk
	.cra_ctxsize		= sizeof(struct crypto_aes_ctx),
	.cra_alignmask		= 0xf,
	.cra_type		= &crypto_blkcipher_type,
	.cra_module		= THIS_MODULE,
	.cra_blkcipher = {
		.min_keysize	= AES_MIN_KEY_SIZE,
		.max_keysize	= AES_MAX_KEY_SIZE,
		.ivsize		= AES_BLOCK_SIZE,
		.setkey		= rtk_mcp_aes_setkey,
		.encrypt	= rtk_mcp_aes_ctr_cipher_encrypt,
		.decrypt	= rtk_mcp_aes_ctr_cipher_decrypt,
	}
};

static struct shash_alg rtk_sha256_alg = { 
	.digestsize	=	SHA256_DIGEST_SIZE,
	.init		=	rtk_sha256_base_init,
	.update		=	rtk_crypto_sha256_update,
	.final		=	rtk_sha256_final,
	.finup		=	rtk_crypto_sha256_finup,
	.descsize	=	sizeof(struct sha256_state),
	.base		=	{
		.cra_name	=	"sha256",
		.cra_driver_name=	"sha256-rtk",
		.cra_flags	=	CRYPTO_ALG_TYPE_SHASH,
		.cra_blocksize	=	SHA256_BLOCK_SIZE,
		.cra_module	=	THIS_MODULE,
	}
};

#if 0
static int __init rtk_mcp_aes_mod_init(void)
{
printk(KERN_ERR "*************alg: rtk_mcp_aes_mod_init\n");
	return crypto_register_alg(&rtk_aes_alg);
}

static void __exit rtk_mcp_aes_mod_exit(void)
{
	crypto_unregister_alg(&rtk_aes_alg);
}

//module_cpu_feature_match(AES, rtk_mcp_aes_mod_init);
//module_exit(rtk_mcp_aes_mod_exit);

module_init(rtk_mcp_aes_mod_init);
module_exit(rtk_mcp_aes_mod_exit);
#endif
#if 0
static int rtk_crypto_mcp_probe(struct platform_device *pdev)
{
	//local_pdev = pdev;

	//printk(KERN_ERR "[RTK MCP] MCP driver initial begin.\n");
printk(KERN_ERR "*************alg: rtk_crypto_mcp_probe\n");

    	//RTK_MCP_BASE = ioremap(0x98015000, 0x1000);
	//RTK_CRT_BASE = ioremap(0x98000000, 0x100);

#if 0
	RTK_MCP_BASE = of_iomap(pdev->dev.of_node, 0);
	if (!MCP_BASE) {
		dev_err(&pdev->dev, "no mcp address\n");
		return -EINVAL;
	}

	RTK_TP_BASE = of_iomap(pdev->dev.of_node, 1);
	if (!RTK_TP_BASE) {
		dev_err(&pdev->dev, "no tp address\n");
		return -EINVAL;
	}

	printk(KERN_INFO "[RTK MCP] MCP Base: 0x%p\n", RTK_MCP_BASE);
	printk(KERN_INFO "[RTK MCP] TP Base: 0x%p\n", RTK_TP_BASE);

	 if (mcp_init()<0)
		 return -ENODEV;

	 cdev_init(&mcp_dev, &mcp_ops);

	if (alloc_chrdev_region(&devno, 0, 1, MCP_DEVICE_NAME) != 0){
		cdev_del(&mcp_dev);
		printk("%s %s %d",__FILE__, __func__,__LINE__);
		return -EFAULT;
	}

	if (cdev_add(&mcp_dev, devno, 1) < 0)
		return -EFAULT;

	mcp_dev_class = class_create(THIS_MODULE, MCP_DEVICE_NAME); // create a new class for mcp

	mcp_device = device_create(mcp_dev_class, NULL, devno, NULL, "mcp_core");
#endif
	printk(KERN_ERR "[RTK MCP] MCP driver initial done.\n");

	return crypto_register_alg(&rtk_aes_alg);
}

static int rtk_crypto_mcp_remove(struct platform_device *dev)
{
	printk(KERN_ERR "[RTK MCP] MCP driver remove begin.\n");
#if 0
	device_destroy(mcp_dev_class, mcp_device->devt);

	cdev_del(&mcp_dev);

	unregister_chrdev_region(devno, 1);

	mcp_uninit();
#endif
	printk(KERN_ERR "[RTK MCP] MCP driver remove done.\n");

	return 0;
}

static struct of_device_id rtk_crypto_mcp_ids[] = {
	{ .compatible = "Realtek,rtk-mcp" },
	{ /* Sentinel */ },
};

static struct platform_driver rtk_crypto_mcp_driver = {
	.probe = rtk_crypto_mcp_probe,
	.remove = rtk_crypto_mcp_remove,
	.driver = {
		.name = "RTK_CRYPTO_MCP",
		.of_match_table = of_match_ptr(rtk_crypto_mcp_ids),
	},
};

module_platform_driver(rtk_crypto_mcp_driver);
#endif

static struct platform_device *rtk_crypto_mcp_device;

static int rtk_crypto_mcp_probe(struct platform_device *pdev)
{
	int ret=0;
	//printk(KERN_ERR "[RTK_CRYPTO]rtk_crypto_mcp_probe\n");
	local_pdev = pdev;
    
	RTK_MCP_BASE = ioremap(0x98015000, 0x1000);
	RTK_CRT_BASE = ioremap(0x98000000, 0x100);
	//SET_CRT_MCP_RESET((GET_CRT_MCP_RESET(RTK_CRT_BASE)|0x30000), RTK_CRT_BASE);
	//SET_CRT_MCP_CLK((GET_CRT_MCP_CLK(RTK_CRT_BASE)|0xc), RTK_CRT_BASE);

	mcp_debug("STATUS=%08x, CTRL=%08x\n",GET_MCP_STATUS(RTK_MCP_BASE), GET_MCP_CTRL(RTK_MCP_BASE));
	//mcp_debug("GET_CRT_MCP_RESET=%08x\n",GET_CRT_MCP_RESET(RTK_CRT_BASE));
	//mcp_debug("GET_CRT_MCP_CLK=%08x\n",GET_CRT_MCP_CLK(RTK_CRT_BASE));
	crypto_mcp_init();


   //crypto_register_alg(&rtk_aes_alg);
   ret = crypto_register_alg(&rtk_aes_ecb_alg);
   if(ret){
	printk(KERN_ERR "[RTK_CRYPTO]rtk_aes_ecb_alg register fail\n");
   }
   ret = crypto_register_alg(&rtk_aes_cbc_alg);
   if(ret){
	printk(KERN_ERR "[RTK_CRYPTO]rtk_aes_cbc_alg register fail\n");
   }
   ret = crypto_register_alg(&rtk_aes_ctr_alg);
    if(ret){
	printk(KERN_ERR "[RTK_CRYPTO]rtk_aes_ctr_alg register fail\n");
   }
   ret = crypto_register_shash(&rtk_sha256_alg);
    if(ret){
	printk(KERN_ERR "[RTK_CRYPTO]rtk_sha256_alg register fail\n");
   }
   return ret;
}

static int rtk_crypto_mcp_remove(struct platform_device *pdev)
{
    int ret;
    pr_err("%s(#%d)\n", __func__, __LINE__);
   ret = crypto_unregister_alg(&rtk_aes_ecb_alg);
   if(ret){
	printk(KERN_ERR "[RTK_CRYPTO]rtk_aes_ecb_alg unregister fail\n");
   }
   ret = crypto_unregister_alg(&rtk_aes_cbc_alg);
   if(ret){
	printk(KERN_ERR "[RTK_CRYPTO]rtk_aes_cbc_alg unregister fail\n");
   }
   ret = crypto_unregister_alg(&rtk_aes_ctr_alg);
    if(ret){
	printk(KERN_ERR "[RTK_CRYPTO]rtk_aes_ctr_alg unregister fail\n");
   }
   ret = crypto_unregister_shash(&rtk_sha256_alg);
    if(ret){
	printk(KERN_ERR "[RTK_CRYPTO]rtk_sha256_alg unregister fail\n");
   }
    return ret;
}

static struct platform_driver rtk_crypto_mcp_driver = {
    .driver = {
        .name  = DEVNAME,
        .owner = THIS_MODULE,
    },
    .probe  = rtk_crypto_mcp_probe,
    .remove = rtk_crypto_mcp_remove,
};

static int __init rtk_crypto_mcp_init(void)
{
    int err;
    //printk(KERN_ERR "*************alg: rtk_crypto_mcp_init\n");
    pr_err("%s(#%d)\n", __func__, __LINE__);

    /* using platform_device_alloc() + platform_device_add() 
     * instead of platform_device_register() to avoid the OOPS, 
     *     "Device 'brook.0' does not have a release() function,
     *      it is broken and must be fixed."
     */
    rtk_crypto_mcp_device = platform_device_alloc(DEVNAME, 0);
    if (!rtk_crypto_mcp_device) {
        pr_err("%s(#%d): platform_device_alloc fail\n",
               __func__, __LINE__);
        return -ENOMEM;
    }

    err = platform_device_add(rtk_crypto_mcp_device);
    if (err) {
        pr_err("%s(#%d): platform_device_add failed\n",
               __func__, __LINE__);
        goto dev_add_failed;
    }

    err = platform_driver_register(&rtk_crypto_mcp_driver);
    if (err) {
        dev_err(&(rtk_crypto_mcp_device->dev), "%s(#%d): platform_driver_register fail(%d)\n",
                __func__, __LINE__, err);
        goto dev_reg_failed;
    }
    return err;

dev_add_failed:
    platform_device_put(rtk_crypto_mcp_device);
dev_reg_failed:
    platform_device_unregister(rtk_crypto_mcp_device);

    return err;
}
module_init(rtk_crypto_mcp_init);

static void __exit rtk_crypto_mcp_exit(void)
{
    dev_info(&(rtk_crypto_mcp_device->dev), "%s(#%d)\n", __func__, __LINE__);
    platform_device_unregister(rtk_crypto_mcp_device);
    platform_driver_unregister(&rtk_crypto_mcp_driver);
}
module_exit(rtk_crypto_mcp_exit);

