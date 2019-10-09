#include "BootPartition_wrapper.h"




t_ExitStatus BootPart_wrapper_read(void *device,unsigned char * buf,unsigned int from_block,unsigned int size){

	if( ! do_read_e(device,&from_block,buf,size, MMC_PART_BOOT_1))
		return EXIT_SUCCESS;
	else 
		return EXIT_FAILURE;
}

t_ExitStatus BootPart_wrapper_write(void * device, unsigned char* buf, unsigned int dest_block,unsigned int size){

	if( ! do_write_e( device,buf,&dest_block,size,0,MMC_PART_BOOT_1))
		return EXIT_SUCCESS;
	else 
		return EXIT_FAILURE;
}

t_ExitStatus BootPart_wrapper_VerifyData(void* device ,unsigned char * compare_src ,unsigned int from_block,unsigned size){

	unsigned char * read_buf = REF_MALLOC_BASE;
	if( do_read_e(device,&from_block,read_buf,size, MMC_PART_BOOT_1))
		return EXIT_FAILURE;

	
	if (compare_memory((unsigned char *)compare_src, read_buf, size)) {
		return EXIT_FAILURE;
	}	
	return EXIT_SUCCESS;
}


t_ExitStatus InitBootPartitionOpes(unsigned char device_type,t_BootPart_obj *obj){

	switch(device_type){
		case FLASH_TYPE_EMMC:
			obj->read		 = BootPart_wrapper_read;
			obj->write		 = BootPart_wrapper_write;
			obj->verify_data = BootPart_wrapper_VerifyData;
			break;

		default:
			break;
	}
	return EXIT_SUCCESS;	
}







