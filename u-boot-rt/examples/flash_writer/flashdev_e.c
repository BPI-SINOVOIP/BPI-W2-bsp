#include <project_config_f.h>
#include <sysdefs.h>

#include "flashdev_e.h"
#include "dvrboot_inc/util.h"

extern unsigned char * dummy_512B;

/************************************************************************
 *
 *  Description :
 *  -------------
 *  Parameters :
 *  ------------
 *  Return values :
 ************************************************************************/
int do_erase_e( void * dev,
                unsigned int * dest,
                unsigned int byte_length)
{
    e_device_type *card = (e_device_type *)dev;

    UPRINTF("     emmc:%s(do nothing)\n", __FUNCTION__);
    
    // add your code here, we may write data with zero pattern
    
    return 0;
}

/************************************************************************
 *
 *  Description :
 *  -------------
 *  Parameters :    array_ptr   	address of pool of write data source.
 *                  dest      		target address that want to write to card
 *                  dest=0x%08x    	total size you want to write
 *                  signature       reserved
 *					boot_partition  whether write the data to boot partition X at the same t    ime
 *                                  0              :do not write to boot parition           
 *                                  MMC_PART_BOOT_1:write to boot partition 1
 *                                  MMC_PART_BOOT_2:write to boot partition 2
 *  ------------
 *  Return values :  0->success  -1-->fail
 ************************************************************************/
int do_write_e( void * dev,
				unsigned char * array_ptr,
                unsigned int * dest,
                unsigned int byte_length,
                unsigned int signature,
                const unsigned int boot_partition)
{
    unsigned int xfered_blk_cnt;
    UPRINTF("     emmc:%s *dest=0x%08x, array_ptr=0x%08x, byte_len=0x%08x\n", __FUNCTION__, *dest, array_ptr, byte_length);

   
   if( boot_partition !=0 && boot_partition !=1 && boot_partition !=2 ){
		prints("illegal parameter for partition choose\n");
	    return -1;
   }

   switch(boot_partition){
      case MMC_PART_UDA:
   	   prints("write data to UDA\n");
	   xfered_blk_cnt = rtk_eMMC_write( *dest, byte_length, (unsigned int *) array_ptr, 0 );
   	   break;
      case MMC_PART_BOOT_1:
   	   prints("write data to BOOT1\n");
   	   emmc_switch_partition(MMC_PART_BOOT_1);
	   xfered_blk_cnt = rtk_eMMC_write( *dest, byte_length, (unsigned int *) array_ptr, 0 );
   	   emmc_switch_partition(MMC_PART_UDA);
   	   break;
      case MMC_PART_BOOT_2:
   	   prints("write data to BOOT2\n");
   	   emmc_switch_partition(MMC_PART_BOOT_2);
	   xfered_blk_cnt = rtk_eMMC_write( *dest, byte_length, (unsigned int *) array_ptr, 0 );
   	   emmc_switch_partition(MMC_PART_UDA);
   	   break;
   }

   if( !xfered_blk_cnt ) 
   	  return -1;
   else
   	  return 0;
}

/************************************************************************
 *
 *  Description :
 *  -------------
 *  Parameters :    src      		target address that want to read from card.
 *                  dest     		pool of read data from card.
 *                  dest=0x%08x  	total size you want to get.                  
 *				    boot_partiton	whether read data from boot partition
 * 								    0				:read from UDA							 
 *									MMC_PART_BOOT_1 :read from boot partition 1
 * 									MMC_PART_BOOT_2 :read from boot partition 2
 *  ------------
 *  Return values :
 ************************************************************************/
int do_read_e( void * dev,
               unsigned int * src,
               unsigned char * dest,
               unsigned int byte_length,
               unsigned int boot_partition )
{
    unsigned int xfered_blk_cnt;
    UPRINTF("     emmc:%s *src=0x%08x, dest=0x%08x, byte_len=0x%08x\n", __FUNCTION__, *src, dest, byte_length);


   if( boot_partition !=0 && boot_partition !=1 && boot_partition !=2 ){
   	  prints("illegal parameter for partition choose\n");
   	  return -1;
   }

   switch(boot_partition){
      case MMC_PART_UDA:
   	   prints("read from UDA\n");
   	   xfered_blk_cnt = rtk_eMMC_read( *src, byte_length, (unsigned int *) dest, 0 );
   	   break;
      case MMC_PART_BOOT_1:
   	   prints("read from BOOT1\n");
   	   emmc_switch_partition(MMC_PART_BOOT_1);
   	   xfered_blk_cnt = rtk_eMMC_read( *src, byte_length, (unsigned int *) dest, 0 );
   	   emmc_switch_partition(MMC_PART_UDA);
   	   break;
      case MMC_PART_BOOT_2:
   	   prints("read from BOOT2\n");
   	   emmc_switch_partition(MMC_PART_BOOT_2);
   	   xfered_blk_cnt = rtk_eMMC_read( *src, byte_length, (unsigned int *) dest, 0 );
   	   emmc_switch_partition(MMC_PART_UDA);
   	   break;
   }	   

   
	if( !xfered_blk_cnt ) 
	   return -1;
	else 
	   return 0;

}

/************************************************************************
 *
 *  Description :
 *  -------------
 *  Parameters :
 *  ------------
 *  Return values :
 ************************************************************************/
int do_identify_e( void ** dev )
{
    *dev = &emmc_card; // used for dvrmain
    
    return rtk_eMMC_init();
}

/************************************************************************
 *
 *  Description :
 *  -------------
 *  Parameters :
 *  ------------
 *  Return values :
 ************************************************************************/
int do_init_e(void *dev)
{
    e_device_type *card = (e_device_type *)dev;

    //UPRINTF("     emmc:%s(do nothing)\n", __FUNCTION__);

    // add your code here

	//disable dcache for emmc case to avoid ip descriptor flush issue
	prints("-------->disable dcache \n");
	disable_dcache();

	return 0;
}

/************************************************************************
 *
 *  Description :
 *  -------------
 *  Parameters :
 *  ------------
 *  Return values :
 ************************************************************************/
void do_exit_e(void *dev)
{
    e_device_type *card = (e_device_type *)dev;

	UPRINTF("     emmc:%s(do nothing)\n", __FUNCTION__);

    // add your code here
}

/************************************************************************
 *
 *  Description :
 *  -------------
 *  Parameters :    array_ptr   	NILL
 *                  block_no 		target block address
 *                  byte_length   	total byte length // fix 512 bytes
 *                  signature       overwrite patten
 *                  page_offset 	reserved
 *  ------------
 *  Return values :
 ************************************************************************/
int do_hide_hwsetting_e( void * dev,
				unsigned char * array_ptr,
                unsigned int * block_no,
                unsigned int byte_length,
                unsigned int signature,
                const unsigned int page_offset)
{
    unsigned int i, j;
    unsigned int xfered_blk_cnt;
    unsigned int target_part_idx;
   
    UPRINTF("     emmc:%s blk#=0x%04x, len=0x%04x, buf=0x%08x\n", __FUNCTION__, *block_no, byte_length, dummy_512B);
    
	#define START_PART_IDX 2
	#define END_PART_IDX 0
	
	#if ( START_PART_IDX < END_PART_IDX )
		echo "SETTING ERROR"
	#endif

	target_part_idx = START_PART_IDX;
	
	while( 1 ) {
	
		
		dummy_512B[0] = 0x55;
		dummy_512B[1] = 0xAA;
		dummy_512B[2] = 0xA5;
		dummy_512B[3] = 0x5A;

		// read 1st hw-setting block
		// byte_length must be 512 bytes
		xfered_blk_cnt = rtk_eMMC_read( *block_no, byte_length, (unsigned int *) dummy_512B, 0 );
	    if( xfered_blk_cnt != 1 ) {
            #ifdef FOR_ICE_LOAD
	    	prints("\nemmc: do_hide_hwsetting_e() read blk 0x");
            print_hex(*block_no);
            prints(" fail\n");
            #else
	    	UPRINTF("\nemmc: %s read blk 0x$08x fail\n", __FUNCTION__, *block_no);
            #endif
	    	return -1;
	    }
#if 0 // show magic tag 0xFFFFFFFF or 0xFFFFFFFE
	    for( i = 0; i < 3; i++ ) {
	    	if( i == 0 ) {
	    		UPRINTF("old : %03xh :", (i<<4));
	    	}
	    	else {
	    		UPRINTF("      %03xh :", (i<<4));
	    	}
	    	for( j = 0; j < 16; j++ ) {
	    		UPRINTF(" %02x", dummy_512B[((i*16)+j)] );
	    	}
	    	UPRINTF("\n");
	    }
#endif
		// overwrite 1st word with 0xFFFFFFFFE
		dummy_512B[0] = (unsigned char)((signature & 0x000000FF));
		dummy_512B[1] = (unsigned char)((signature & 0x0000FF00)>>8);
		dummy_512B[2] = (unsigned char)((signature & 0x00FF0000)>>16);
		dummy_512B[3] = (unsigned char)((signature & 0xFF000000)>>24);
#if 0 // show magic tag 0xFFFFFFFF or 0xFFFFFFFE
	    for( i = 0; i < 3; i++ ) {
	    	if( i == 0 ) {
	    		UPRINTF("new : %03xh :", (i<<4));
	    	}
	    	else {
	    		UPRINTF("      %03xh :", (i<<4));
	    	}
	    	for( j = 0; j < 16; j++ ) {
	    		UPRINTF(" %02x", dummy_512B[((i*16)+j)] );
	    	}
	    	UPRINTF("\n");
	    }
#endif
		// write back 1st hw-setting block
		// byte_length must be 512 bytes
		xfered_blk_cnt = rtk_eMMC_write( *block_no, byte_length, (unsigned int *) dummy_512B, 0 );
	    if( xfered_blk_cnt != 1 ) {
            #ifdef FOR_ICE_LOAD
	    	prints("\nemmc: do_hide_hwsetting_e() write blk 0x");
            print_hex(*block_no);
            prints(" fail\n");
            #else
	    	UPRINTF("\nemmc:%s write blk 0x$08x fail\n", __FUNCTION__, *block_no);
            #endif
	    	return -1;
	    }

	    if( target_part_idx == END_PART_IDX ) {
	    	break;	
	    }
	    target_part_idx--;
	}
	return 0;
}

/* end of file */
