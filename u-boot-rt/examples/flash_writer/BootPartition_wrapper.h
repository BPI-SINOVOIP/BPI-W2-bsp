#ifndef __BOOTPARTITION_WRAPPER__                                                           
#define __BOOTPARTITION_WRAPPER__
 
#include "flashdev_e.h"
#include "dvrboot_inc/util.h"
 
typedef signed int              INT32;
typedef unsigned  int           UINT32;
 
typedef enum{
     EXIT_SUCCESS =0,
     EXIT_FAILURE =1
}t_ExitStatus;

#define RESERVED_FOR_CUSTOMIZATION      4  //blocks

//it should be 1 block more then reserved area,but it starts from 0,so dont need to add 1
#define BOOTPART_HEADER_LOCATION        RESERVED_FOR_CUSTOMIZATION 


/***********************
 * header for boot partition
 * contents:
 * ========================
 * 
 * | header size        |  4   B
 *   -------------------
 * | uboot64 size       |  4   B
 *   -------------------
 * | tee size           |  4   B
 *   -------------------
 * | bl31 size          |  4   B
 *   -------------------
 * | RSA_FW size        |  4   B
 *  --------------------
 * | RSA_TEE size       |  4   B
 *  --------------------
 * | padding            |  488 B
 *  
 * ===========================
 */ 
typedef struct boot_partition_header{
	int header_size;
	int bootcode_size;
	int tee_os_size;
	int bl31_size;
	int RSA_FW_size;
	int RSA_TEE_size;
	char padding[488];
	//fix uboot 64
}t_boot_header __attribute__ ((aligned (4)));

typedef struct bootpartition_object{
   t_ExitStatus (*read)(void *,unsigned char *,unsigned int,unsigned int);  //read from boot     1
   t_ExitStatus (*write)(void * , unsigned char* , unsigned int ,unsigned int );//write to b    oot 1
   t_ExitStatus (*verify_data)(void* ,unsigned char *, unsigned int, unsigned int); //combin    ation of read/write
}t_BootPart_obj;


//used to initialize bootpartition opration objects
extern t_ExitStatus InitBootPartitionOpes(unsigned char device_type,t_BootPart_obj *obj);  

#endif








