/*
 * rtd16xx_ddr_calibration.c
 *
 * Copyright (c) 2017 Realtek Semiconductor Corp.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 */

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/printk.h>
#include <linux/delay.h>
#include <linux/smp.h>
#include <linux/types.h>
#include <linux/ioport.h>
#include <linux/io.h>
#include <linux/memblock.h>
#include <linux/slab.h>
#include <asm/cacheflush.h>

#define MEM_VERIFIED_CNT 20

void hexdump(char *note, unsigned char *buf, unsigned int len)
{
	pr_crit("%s\n", note);
	print_hex_dump(KERN_CONT, "", DUMP_PREFIX_OFFSET, 16, 1, buf, len,
		false);
}
EXPORT_SYMBOL(hexdump);

struct _memory_verified_handle {
	unsigned char *memAddress;
	size_t memByte;
};

struct _memory_verified_handle phys_wb_area[] = {
	{(unsigned char *)0x0a000000, 0x20},
	{(unsigned char *)0x0a001000, 0x20}
};

struct _memory_verified_handle *mem_vhandle[20];
struct _memory_verified_handle **mem_wbhandle;

static unsigned char memory_verified_datagen(int i)
{
	return (unsigned char) (i & 0xff);
}

static struct _memory_verified_handle *memory_verified_handle_create(size_t byte)
{
	int i = 0;

	struct _memory_verified_handle *handle =
		(struct _memory_verified_handle *)
		kmalloc(sizeof(struct _memory_verified_handle), GFP_KERNEL);

	if (!handle)
		return NULL;

	/*
	 * > 32KB : vmalloc
	 * < 32KB : kmalloc
	 */
	if (byte > 0x8000)
		handle->memAddress = vmalloc(byte);
	else
		handle->memAddress = kmalloc(byte, GFP_KERNEL);

	if (!handle->memAddress) {
		kfree(handle);
		return NULL;
	}

	for (i = 0; i < byte ; i++)
		handle->memAddress[i] = memory_verified_datagen(i);

	handle->memByte = byte;

	return handle;
}

static int memory_verified_release(struct _memory_verified_handle *handle)
{
	int ret = 0, i = 0;
	unsigned char data;

	if (!handle) {
		pr_err("%s: handle is NULL !\n", __func__);
		return -1;
	}

	if (!handle->memByte) {
		ret = -2;
		pr_info("%s: handle %p ", __func__, (void *) handle);
		pr_info("(memByte = %ld, memAddress = 0x%08lx)\n",
			(long int) handle->memByte,
			(unsigned long) handle->memAddress);

		if (handle->memAddress)
			goto free1;
		else
			goto free0;
	}

	for (i = 0 ; i < handle->memByte ; i++) {
		data = memory_verified_datagen(i);

		if (handle->memAddress[i] != data) {
			pr_info("%s: handle %p memAddress[0x%x]",
				__func__, (void *) handle, i);
			pr_info("=> 0x%x != 0x%x (%ld bytes at 0x%08lx)\n",
				handle->memAddress[i], data,
				(long int) handle->memByte,
				(unsigned long) handle->memAddress);
			ret = -4;
		}
	}

	if (ret == -4) {
		pr_err("%s: memory phyAddt 0x%08llx\n",
			__func__, __pa(handle->memAddress));
		hexdump("[%s] memory verified error\n",
			handle->memAddress, handle->memByte);
	}

free1:
	kfree(handle->memAddress);
free0:
	kfree(handle);

	return ret;
}

static struct _memory_verified_handle *memory_writeback_handle_create(
	struct _memory_verified_handle *phys_area)
{
	void *tmp_addr;

	struct _memory_verified_handle *handle =
		(struct _memory_verified_handle *)
		kmalloc(sizeof(struct _memory_verified_handle), GFP_KERNEL);

	if (!handle)
		goto out;

	handle->memAddress = kmalloc(phys_area->memByte, GFP_KERNEL);

	if (!handle->memAddress) {
		kfree(handle);
		handle = NULL;
		goto out;
	}

	handle->memByte = phys_area->memByte;
	tmp_addr = phys_to_virt((phys_addr_t) phys_area->memAddress);
	hexdump("[RTD16xx_PM] Before write back dump:",
		(unsigned char *) tmp_addr, phys_area->memByte);
	memcpy(handle->memAddress, tmp_addr, phys_area->memByte);
	__flush_dcache_area(handle->memAddress, phys_area->memByte);
out:
	return handle;
}

static int memory_writeback_release(struct _memory_verified_handle *handle,
	struct _memory_verified_handle *phys_area)
{
	int ret = 0;
	void *tmp_addr;

	if (!handle) {
		ret = -1;
		goto out;
	}

	if (!handle->memAddress) {
		ret = -1;
		goto free_out;
	}

	tmp_addr = phys_to_virt((phys_addr_t)phys_area->memAddress);
	hexdump("[RTD16xx_PM] Resume back dump:**********************",
		(unsigned char *) tmp_addr, phys_area->memByte);
	memcpy(tmp_addr, handle->memAddress, handle->memByte);
	__flush_dcache_area(tmp_addr, phys_area->memByte);
	hexdump("[RTD16xx_PM] After write back dump:",
		(unsigned char *) tmp_addr, phys_area->memByte);

	kfree(handle->memAddress);

free_out:
	kfree(handle);
out:
	return ret;
}

void memory_check_begin(void)
{
	int i = 0;

	for (i = 0 ; i < MEM_VERIFIED_CNT ; i++)
		mem_vhandle[i] = memory_verified_handle_create(0x4000);
}
EXPORT_SYMBOL(memory_check_begin);

void memory_check_end(void)
{
	int i = 0;

	pr_info("%s: Resume Memory Verifying ... State 0\n", __func__);
	for (i = 0 ; i < MEM_VERIFIED_CNT ; i++)
		memory_verified_release(mem_vhandle[i]);

	pr_info("%s: Resume Memory Verifying ... State 1\n", __func__);
	for (i = 0 ; i < MEM_VERIFIED_CNT; i++)
		mem_vhandle[i] = memory_verified_handle_create(0x4000);

	for (i = 0 ; i < MEM_VERIFIED_CNT ; i++)
		memory_verified_release(mem_vhandle[i]);

}
EXPORT_SYMBOL(memory_check_end);

void rtk_ddr_calibration_save(void)
{
	int i = 0;
	int size_tmp1 = 0;
	int size_tmp2 = 0;
	int size_tmp3 = 0;

	size_tmp1 = sizeof(phys_wb_area);
	size_tmp2 = sizeof(struct _memory_verified_handle);
	size_tmp3 = sizeof(struct _memory_verified_handle *);
	mem_wbhandle = kmalloc(size_tmp1 / size_tmp2 * size_tmp3, GFP_KERNEL);
	if (mem_wbhandle) {
		for (i = 0 ; i < (size_tmp1 / size_tmp2) ; i++)
			mem_wbhandle[i] = memory_writeback_handle_create(
					&phys_wb_area[i]);
	}
}
EXPORT_SYMBOL(rtk_ddr_calibration_save);

void rtk_ddr_calibration_restore(void)
{
	int i = 0;
	int size_tmp1 = 0;
	int size_tmp2 = 0;

	if (mem_wbhandle) {
		for (i = 0 ; i < (size_tmp1 / size_tmp2) ; i++)
			memory_writeback_release(
				mem_wbhandle[i], &phys_wb_area[i]);
		kfree(mem_wbhandle);
	}
}
EXPORT_SYMBOL(rtk_ddr_calibration_restore);
