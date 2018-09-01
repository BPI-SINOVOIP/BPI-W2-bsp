#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include "flash_nand_list.h"
#include "flash_nand_profile.h"

#define NF_PROFILE_FILE		  "nf_profile.bin"
//#define NULL	0
#define RBA_PERCENTAGE             5               // percentage of blocks reserved for bad block remapping

static unsigned int accumulate_byte_value(const void *buf, unsigned int length)
{
        unsigned int i, res;
        unsigned char *ptr = (unsigned char *)buf;

        if ((buf == NULL) || (length == 0))
                return 0;

        for (i = res = 0; i < length; i++)
                res += ptr[i];

        return res;
}

static void SaveBinary(const char* f_name, unsigned char* data_addr, int len)
{
        char sbuf[256]={0};
        int ptr_OUT=0;
        int w_ret=0,i=0;

        ptr_OUT = open(f_name, O_RDWR|O_CREAT, 0755);
        if (ptr_OUT == -1)
        {
                printf("nf_profiler: file open error\n");
                goto error_out;
        }

        while (len--)
        {
                w_ret = write(ptr_OUT, data_addr+i, 1);
                i++;
        }

        memset(sbuf, 0x00, 255);
        sprintf(sbuf, "sync;sync;");
        system(sbuf);
error_out:
        if (ptr_OUT)
                close(ptr_OUT);
        return;
}

void main(int argc, char * const argv[])
{
	unsigned long long die_size=0;
        unsigned int pages_per_chip=0, blocks_per_flash=0, pages_per_block=0;	
	int i;
        unsigned int tmp, checksum;
        n_device_type *device; 
	t_nand_profile *profile, profile_val;

	if (argc != 2)
	{
		printf("usage : \n");
		printf("\tnf_profiler nf_id\n");
		return;
	}

	printf("nf_profiler v1.0 : input nf_id=%s\n",argv[1]);

	memset((t_nand_profile*)&profile_val,0x00,sizeof(t_nand_profile));

	device = (n_device_type*)&n_device;
	profile = (t_nand_profile*)&profile_val;

	//identify the nf type
        for(i=0;i<DEV_SIZE_N;i++)
	{
		if (strcmp((device+i)->string, argv[1]) == 0)
		{
			printf("nf_profiler - find the match nf : %s\n",(device+i)->string);
			break;
		}
	}
	if (i>=DEV_SIZE_N)
		printf("nf_profiler - can'tfind the match nf, use K9F8G08U0M as default\n");
	else
		device = device+i;
	printf("nf_profiler : nf_id=%s\n", device->string);

        // build NAND profile
        memcpy(profile->identifier, NAND_PROFILE_IDENTIFIER, sizeof(NAND_PROFILE_IDENTIFIER));
        profile->revision = 0x2;

        for (tmp = 0; tmp < 4; tmp++)
                profile->manufacturer_id[tmp] = (device->id >> (tmp * 8)) & 0xff;

        if (device->read_id_len > 4) {
                profile->manufacturer_id[tmp] = device->id5;
                tmp++;

                if (device->read_id_len > 5)
                        profile->manufacturer_id[tmp] = device->id6;
        }

        if (strlen(device->string) < (sizeof(profile->flash_name) - 1))
                tmp = strlen(device->string);
        else
                tmp = sizeof(profile->flash_name) - 1;

        memcpy(profile->flash_name, device->string, tmp);

	pages_per_block  = (unsigned int) device->BlockSize / (unsigned int)device->PageSize;
        die_size = device->size / device->num_chips;
        pages_per_chip = die_size / device->PageSize;
        blocks_per_flash += die_size / device->BlockSize;

        profile->number_of_bbt = 2;
        profile->bbt_start_block = 0x1;
        profile->bbt_end_block = 0x2;
        profile->number_of_rsv_block = blocks_per_flash * RBA_PERCENTAGE / 100;
        profile->rsv_start_block = blocks_per_flash - profile->number_of_rsv_block;
        profile->rsv_end_block = blocks_per_flash - 1;
        profile->data_per_page = device->PageSize;

        switch (device->ecc_bit) {
                case ECC_6BIT:
                        tmp = 16 * (device->PageSize / 512);
                        break;
                case ECC_12BIT:
                        tmp = 32 * (device->PageSize / 512);
                       break;
                case ECC_16BIT:
                case ECC_24BIT:
                case ECC_40BIT:
                case ECC_43BIT:
                case ECC_65BIT:
                case ECC_72BIT:
                        tmp = 128 * (device->PageSize / 1024);
                        break;
                default:        // unknown type
                        return;
        }

        profile->oob_per_page = tmp;
        profile->page_per_block = pages_per_block;
        profile->block_per_die = blocks_per_flash;
        profile->ecc_bit = device->ecc_bit;
        profile->param_t1 = device->t1;
        profile->param_t2 = device->t2;
        profile->param_t3 = device->t3;
        profile->address_mode = device->addr_mode_rw;

        checksum = accumulate_byte_value(profile, 128);
        //modify by angus, rtd299x doesn't endian invert
        //for (tmp = 0; tmp < 4; tmp++)
                //profile->checksum[tmp] = (checksum >> (tmp * 8)) & 0xff;
        *(unsigned int *)profile->checksum = checksum;

	//save it
	SaveBinary(NF_PROFILE_FILE, (unsigned char*)&profile_val, sizeof(t_nand_profile));

        return;
}
