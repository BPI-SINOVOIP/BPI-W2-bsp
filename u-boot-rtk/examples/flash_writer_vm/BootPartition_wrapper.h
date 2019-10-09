#ifndef __BOOTPARTITION_WRAPPER__
#define __BOOTPARTITION_WRAPPER__

#include "flashdev_e.h"
#include "dvrboot_inc/util.h"

typedef signed int			    INT32;
typedef unsigned  int		    UINT32;

typedef enum{
	EXIT_SUCCESS =0,
	EXIT_FAILURE =1
}t_ExitStatus;



#define RESERVED_FOR_CUSTOMIZATION      4  //blocks

//it should be 1 block more then reserved area,but it starts from 0,so dont need to
#define BOOTPART_HEADER_LOCATION        RESERVED_FOR_CUSTOMIZATION 


typedef struct bootpartition_object{
	t_ExitStatus (*read)(void *,unsigned char *,unsigned int,unsigned int);  //read from boot 1
	t_ExitStatus (*write)(void * , unsigned char* , unsigned int ,unsigned int );//write to boot 1
	t_ExitStatus (*verify_data)(void* ,unsigned char *, unsigned int, unsigned int); //combination of read/write
}t_BootPart_obj;


extern t_ExitStatus InitBootPartitionOpes(unsigned char device_type,t_BootPart_obj *obj);

#endif










