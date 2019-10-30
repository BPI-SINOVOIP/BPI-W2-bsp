#ifndef BOOTARRAY_FW_TABLE
#define BOOTARRAY_FW_TABLE

typedef struct {
	unsigned int type;
	unsigned int flash_addr;
	unsigned int length;

	unsigned int emmc_partition:1; //0: UDA, 1: Boot
	unsigned int reserved:31;

} BootArray_FW_Entry ;

typedef enum {
	Invalid_type = 0,
	SCS_NOCS_Certificate,
	PCPU_Certificate,
	ATF_Certificate,
	Nagra_TA_Root_Certificate,
	Nagra_TA_Certificate,
	SMP_TA_Certificate,
	OPC_TA_Certificate,
	System_TA_Certificate,
	User_TA_Certificate,
	DTE_FW_Certificate,
	SCS_Params_Area,
	RTK_Params_Area,
	SCS_Auxcode_Area,
	PCPU_Code,
 	DTE_Bootcode,
	DTE_Bootcode_RTK,
	BL31,
	TEE_OS,
	SCS_Area,
	Certificate_Area,
	AFW_Certificate
} BootArray_FW_Type ;


#endif
