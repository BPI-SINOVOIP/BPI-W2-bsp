#include <stdio.h>
#include "../../include/project_config_f.h"
#include "../../bootarray_fw_table.h"
#include <string.h>
#define SCPU_ROMCODE_MAX_SIZE	(172*1024)
#define PCPU_ROMCODE_MAX_SIZE	(16*1024)
#define ACPU_ROMCODE_MAX_SIZE	(4*1024)
#define RSA_SIG_LENGTH			(256)

#define EMMC_BLOCK_SIZE 					(512UL)
#define EMMC_BLOCK_SIZE_SHIFT				(9)
#define EMMC_BOOTARRAY_FW_TABLE_ADDR        (0x00020000)

#define EMMC_BOOTARRAY_FW_TABLE_BLK					(EMMC_BOOTARRAY_FW_TABLE_ADDR>>EMMC_BLOCK_SIZE_SHIFT)	// 0x100


#define NAND_BLOCK_SIZE_128KB				(128 * 1024UL)
#define NAND_BLOCK_SIZE_256KB				(256 * 1024UL)
#define NAND_BOOTARRAY_FW_TABLE_BLK			(6)
#define TEE_OS_MAX_SIZE                     (768 * 1024UL)
#define DTE_BOOOTCODE_MAX_SIZE              (1536 * 1024UL)
#define DTE_BOOOTCODE_RTK_MAX_SIZE          (1536 * 1024UL)

void printUsage()
{
	printf("bindAllbins fw_table: Generate BootArray FW Table. \n");
	printf("bindAllbins: output bind.bin for SPI and uda_emmc.bind.bin/boot_emmc.bind.bin for EMMC. \n");
}

//file path
char *Out_file="./Bind/bind.bin";
char *UDA_eMMC_Out_file="./Bind/uda_emmc.bind.bin";
char *BOOT_eMMC_Out_file="./Bind/boot_emmc.bind.bin";
char *NAND_Out_file="./Bind/nand.bind.bin";

char *scpu_romcode_file="./Bind/scpu_reset_rom.bin";
char *pcpu_romcode_file="./Bind/pcpu_reset_rom.bin";
char *acpu_romcode_file="./Bind/acpu_reset_rom.bin";

//Bootarray fw table
char *eMMC_bootarray_fw_table_file="./Bind/eMMC_bootarray_fw_table.bin";
char *eMMC_bootarray_fw_table_file_final="./Bind/eMMC_bootarray_fw_table_final.bin";
char *spi_bootarray_fw_table_file="./Bind/spi_bootarray_fw_table.bin";
char *spi_bootarray_fw_table_file_final="./Bind/spi_bootarray_fw_table_final.bin";
char *nand_bootarray_fw_table_file_128KB="./Bind/nand_bootarray_fw_table_128KB.bin";
char *nand_bootarray_fw_table_file_final_128KB="./Bind/nand_bootarray_fw_table_final_128KB.bin";
char *nand_bootarray_fw_table_file_256KB="./Bind/nand_bootarray_fw_table_256KB.bin";
char *nand_bootarray_fw_table_file_final_256KB="./Bind/nand_bootarray_fw_table_final_256KB.bin";

//Certificate
char *NOCS_Certificate_file="./Bind/NOCS_Certificate_final.bin";
char *ATF_Certificate_file="./Bind/ATF_Certificate_final.bin";
char *PCPU_Certificate_file="./Bind/PCPU_Certificate_final.bin";
char *DTE_FW_Certificate_file="./Bind/DTE_FW_Certificate_final.bin";
char *AFW_Certificate_file="./Bind/AFW_Certificate_final.bin";


//Params Area
char *SCS_Params_Area_file="./Bind/SCS_Params_Area_final.bin";
char *RTK_Params_Area_file="./Bind/RTK_Params_Area_final.bin";

char *Auxcode_Area_file="./Bind/Auxcode_Area_final.bin";
char *DTE_Bootcode_Area_file = "./Bind/DTE_Bootcode_Area_final.bin";

char *Secure_OS_file="./Bind/Secure_OS_Area_final.bin";
char *BL31_file="./Bind/BL31_Area_final.bin";

//PCPU FW
char *PCPU_Code_Area_file="./Bind/PCPU_Code_Area_final.bin";

//dte_bootcode_rtk_area
char *dte_bootcode_rtk_area_file="./Bind/DTE_Bootcode_RTK_Area_final.bin";


//===========================================
//romcode on spi
unsigned int scpu_romcode_less = 0;
unsigned int pcpu_romcode_less = 0;
unsigned int acpu_romcode_less = 0;
unsigned int scpu_romcode_size = 0;
unsigned int pcpu_romcode_size = 0;
unsigned int acpu_romcode_size = 0;

unsigned int nocs_certificate_size = 0;
unsigned int atf_certificate_size = 0;
unsigned int pcpu_certificate_size = 0;
unsigned int dte_fw_certificate_size = 0;
unsigned int afw_certificate_size = 0;
unsigned int scs_params_area_size = 0;
unsigned int rtk_params_area_size = 0;
unsigned int auxcode_area_size = 0;

unsigned int dte_bootcode_area_size = 0;
unsigned int dte_bootcode_rtk_area_size = 0;

unsigned int bl31_size = 0;
unsigned int secure_secure_os_size = 0;
unsigned int pcpu_code_area_size = 0;

unsigned int tmp_r = 0;
unsigned int tmp_w = 0;
unsigned int ARM_alignByte = 0;
unsigned int MIPS_alignByte = 0;


//file descriptor
FILE*	ptr_OUT=NULL;
FILE*	ptr_UDA_EMMC_OUT=NULL;
FILE*	ptr_BOOT_EMMC_OUT=NULL;
FILE*	ptr_NAND_OUT=NULL;
FILE*	ptr_scpu_romcode=NULL;
FILE*	ptr_pcpu_romcode=NULL;
FILE*	ptr_acpu_romcode=NULL;
FILE*	ptr_Parameter=NULL;
FILE* 	ptr_eMMC_FW_Table=NULL;
FILE* 	ptr_spi_FW_Table=NULL;
FILE* 	ptr_nand_FW_Table_128KB=NULL;
FILE* 	ptr_nand_FW_Table_256KB=NULL;
FILE*	ptr_NOCS_Certificate=NULL;
FILE*	ptr_ATF_Certificate=NULL;
FILE*	ptr_PCPU_Certificate=NULL;
FILE*	ptr_DTE_FW_Certificate=NULL;
FILE*	ptr_AFW_Certificate=NULL;
FILE*	ptr_SCS_Params_Area=NULL;
FILE*	ptr_RTK_Params_Area=NULL;
FILE*	ptr_Auxcode_Area=NULL;
FILE*	ptr_DTE_Bootcode_Area=NULL;
FILE*	ptr_DTE_Bootcode_RTK_Area=NULL;
FILE*   ptr_Secure_OS=NULL;
FILE*   ptr_BL31=NULL;
FILE* 	ptr_PCPU_Code_Area=NULL;

/* ================================== */


#define FW_TABLE_MAGIC 					0x00001615
#define FW_TABLE_VERSION 				0x0
#define FW_TABLE_SIZE_WO_PADDING 		704
#define EMMC_BOOTARRAY_FW_TABLE_BLOCK 	0x100

#define SPI_BASE_ADDR					(0x88100000UL)
#define SPI_SCPU_RESETROM_SIZE			(0x2B000UL) //172KB
#define SPI_PCPU_RESETROM_SIZE			(0x4000UL) //16KB
#define SPI_ACPU_RESETROM_SIZE			(0x1000UL) //4KB

#define SPI_CODE_PART1_1				(SPI_BASE_ADDR)	//SCPU rom start
#define SPI_CODE_PART1_2				(SPI_BASE_ADDR+SPI_SCPU_RESETROM_SIZE) //PCPU rom start
#define SPI_CODE_PART1_3				(SPI_CODE_PART1_2+SPI_PCPU_RESETROM_SIZE) //ACPU rom start

#define SPI_ENV_PARAM_ADDR              (SPI_CODE_PART1_3+SPI_ACPU_RESETROM_SIZE)
#define SPI_MAX_PARAM_SIZE				(0x800UL)

unsigned int align_to_boundary(unsigned int size, unsigned int block_size)
{
    return (size % block_size ? size / block_size + 1 : size / block_size);
}

unsigned int align_to_boundary_length(unsigned int size, unsigned int block_size)
{
    return (size % block_size ? (size / block_size + 1)*block_size : (size / block_size)*block_size );
}



void Generate_eMMCBootArrayFWTable(){
	unsigned int padding_len=0;
	printf("generate eMMC BootArray_FW_Table : %s \n", eMMC_bootarray_fw_table_file);
	char buf[1024]={0};
	BootArray_FW_Entry entry = {0};
	memset(buf,0x00,1024);
	tmp_r=tmp_w=0;
	int w_ret=0;
	int i=0;

	//bootarray fw table header
	unsigned int table_header = FW_TABLE_MAGIC, block_no = 0;
	w_ret = 4 * fwrite(&table_header, 4, 1, ptr_eMMC_FW_Table);
	table_header = FW_TABLE_VERSION;
	w_ret += 4 * fwrite(&table_header, 4, 1, ptr_eMMC_FW_Table);
	w_ret += 8 * fwrite(buf, 8, 1, ptr_eMMC_FW_Table);


	/****************UDA Partition's entries *****************/

	//UDA block no = 0x100 + 2 (table size = 1024)
	block_no = EMMC_BOOTARRAY_FW_TABLE_BLK + 2;

	//ATF Certificate
	entry.type = ATF_Certificate;
	entry.flash_addr = block_no * EMMC_BLOCK_SIZE;
	entry.length = atf_certificate_size;
	entry.emmc_partition = 0;
	w_ret += 16 * fwrite(&entry, 16, 1, ptr_eMMC_FW_Table);
	block_no = (entry.flash_addr / EMMC_BLOCK_SIZE) + align_to_boundary(entry.length, EMMC_BLOCK_SIZE);

	//PCPU Certificate
	entry.type = PCPU_Certificate;
	entry.flash_addr = block_no * EMMC_BLOCK_SIZE;
	entry.length = pcpu_certificate_size;
	entry.emmc_partition = 0;
	w_ret += 16 * fwrite(&entry, 16, 1, ptr_eMMC_FW_Table);
	block_no = (entry.flash_addr / EMMC_BLOCK_SIZE) + align_to_boundary(entry.length, EMMC_BLOCK_SIZE);

	//DTE_FW Certificate
	entry.type = DTE_FW_Certificate;
	entry.flash_addr = block_no * EMMC_BLOCK_SIZE;
	entry.length = dte_fw_certificate_size;
	entry.emmc_partition = 0;
	w_ret += 16 * fwrite(&entry, 16, 1, ptr_eMMC_FW_Table);
	block_no = (entry.flash_addr / EMMC_BLOCK_SIZE) + align_to_boundary(entry.length, EMMC_BLOCK_SIZE);

	//AFW Certificate
	entry.type = AFW_Certificate;
	entry.flash_addr = block_no * EMMC_BLOCK_SIZE;
	entry.length = afw_certificate_size;
	entry.emmc_partition = 0;
	w_ret += 16 * fwrite(&entry, 16, 1, ptr_eMMC_FW_Table);
	block_no = (entry.flash_addr / EMMC_BLOCK_SIZE) + align_to_boundary(entry.length, EMMC_BLOCK_SIZE);

	//RTK_Params_Area
	entry.type = RTK_Params_Area;
	entry.flash_addr = block_no * EMMC_BLOCK_SIZE;
	entry.length = rtk_params_area_size;
	entry.emmc_partition = 0;
	w_ret += 16 * fwrite(&entry, 16, 1, ptr_eMMC_FW_Table);
	block_no = (entry.flash_addr / EMMC_BLOCK_SIZE) + align_to_boundary(entry.length, EMMC_BLOCK_SIZE);

	//PCPU FW Code Area
	entry.type = PCPU_Code;
	entry.flash_addr = block_no * EMMC_BLOCK_SIZE;
	entry.length = pcpu_code_area_size;
	entry.emmc_partition = 0;
	w_ret += 16 * fwrite(&entry, 16, 1, ptr_eMMC_FW_Table);
	block_no = (entry.flash_addr / EMMC_BLOCK_SIZE) + align_to_boundary(entry.length, EMMC_BLOCK_SIZE);

	if (ptr_BL31){
		entry.type = BL31;
		entry.flash_addr =block_no * EMMC_BLOCK_SIZE;
		entry.length = bl31_size;
		entry.emmc_partition = 0;
		w_ret += 16 * fwrite(&entry, 16, 1, ptr_eMMC_FW_Table);
		block_no = (entry.flash_addr / EMMC_BLOCK_SIZE) + align_to_boundary(entry.length, EMMC_BLOCK_SIZE);
	}

	if (ptr_Secure_OS){
		entry.type = TEE_OS;
		entry.flash_addr = block_no * EMMC_BLOCK_SIZE;
		entry.length = secure_secure_os_size;
		entry.emmc_partition = 0;
		w_ret += 16 * fwrite(&entry, 16, 1, ptr_eMMC_FW_Table);
		block_no = (entry.flash_addr / EMMC_BLOCK_SIZE) + align_to_boundary(entry.length, EMMC_BLOCK_SIZE);
	}

	//DTE_Bootcode_RTK
	entry.type = DTE_Bootcode_RTK;
	entry.flash_addr = block_no * EMMC_BLOCK_SIZE;
	entry.length = dte_bootcode_rtk_area_size;
	entry.emmc_partition = 0;
	w_ret += 16 * fwrite(&entry, 16, 1, ptr_eMMC_FW_Table);
	block_no = (entry.flash_addr / EMMC_BLOCK_SIZE) + align_to_boundary(entry.length, EMMC_BLOCK_SIZE);

	padding_len = FW_TABLE_SIZE_WO_PADDING - w_ret;
	fwrite(buf, padding_len, 1, ptr_eMMC_FW_Table);

}

#define SPI_BOOTARRAY_FW_TABLE_ADDR (SPI_ENV_PARAM_ADDR + SPI_MAX_PARAM_SIZE)
#define SPI_SCS_DATA_ADDR (SPI_BOOTARRAY_FW_TABLE_ADDR + 0x400)
#define SPI_SCS_DATA_SECTION_SIZE (0x58000) //based on SCS_Total_Area_Size_1 352KB
#define SPI_RTK_DATA_ADDR (SPI_SCS_DATA_ADDR + SPI_SCS_DATA_SECTION_SIZE)



void Generate_SPIBootArrayFWTable(){
	unsigned int padding_len=0;
	printf("generate spi BootArray_FW_Table : %s \n", spi_bootarray_fw_table_file);
	char buf[1024]={0};
	BootArray_FW_Entry entry = {0};
	memset(buf,0x00,1024);
	tmp_r=tmp_w=0;
	int w_ret=0;
	int i=0;

	//bootarray fw table header
	unsigned int table_header = FW_TABLE_MAGIC;
	w_ret = 4 * fwrite(&table_header, 4, 1, ptr_spi_FW_Table);
	table_header = FW_TABLE_VERSION;
	w_ret += 4 * fwrite(&table_header, 4, 1, ptr_spi_FW_Table);
	w_ret += 8 * fwrite(buf, 8, 1, ptr_spi_FW_Table);

	//ATF Certificate
	entry.type = ATF_Certificate;
	entry.flash_addr = SPI_RTK_DATA_ADDR;
	entry.length = atf_certificate_size;
	w_ret += 16 * fwrite(&entry, 16, 1, ptr_spi_FW_Table);

	//PCPU Certificate
	entry.type = PCPU_Certificate;
	entry.flash_addr = entry.flash_addr + entry.length;
	entry.length = pcpu_certificate_size;
	w_ret += 16 * fwrite(&entry, 16, 1, ptr_spi_FW_Table);

	//DTE_FW Certificate
	entry.type = DTE_FW_Certificate;
	entry.flash_addr = entry.flash_addr + entry.length;
	entry.length = dte_fw_certificate_size;
	w_ret += 16 * fwrite(&entry, 16, 1, ptr_spi_FW_Table);

	//AFW Certificate
	entry.type = AFW_Certificate;
	entry.flash_addr = entry.flash_addr + entry.length;
	entry.length = afw_certificate_size;
	w_ret += 16 * fwrite(&entry, 16, 1, ptr_spi_FW_Table);

	//RTK_Params_Area
	entry.type = RTK_Params_Area;
	entry.flash_addr = entry.flash_addr + entry.length;
	entry.length = rtk_params_area_size;
	w_ret += 16 * fwrite(&entry, 16, 1, ptr_spi_FW_Table);

	//PCPU Code Area
	entry.type = PCPU_Code;
	entry.flash_addr = entry.flash_addr + entry.length;
	entry.length = pcpu_code_area_size;
	w_ret += 16 * fwrite(&entry, 16, 1, ptr_spi_FW_Table);

	if (ptr_BL31){
		entry.type = BL31;
		entry.flash_addr = entry.flash_addr + entry.length;
		entry.length = bl31_size;
		w_ret += 16 * fwrite(&entry, 16, 1, ptr_spi_FW_Table);
	}

	if (ptr_Secure_OS){
		entry.type = TEE_OS;
		entry.flash_addr = entry.flash_addr + entry.length;
		entry.length = secure_secure_os_size;
		w_ret += 16 * fwrite(&entry, 16, 1, ptr_spi_FW_Table);
	}

	//DTE_Bootcode_RTK
	entry.type = DTE_Bootcode_RTK;
	entry.flash_addr = entry.flash_addr + entry.length;
	entry.length = dte_bootcode_rtk_area_size;
	w_ret += 16 * fwrite(&entry, 16, 1, ptr_spi_FW_Table);

	padding_len = FW_TABLE_SIZE_WO_PADDING - w_ret;
	fwrite(buf, padding_len, 1, ptr_spi_FW_Table);

}

void Generate_NANDBootArrayFWTable(){
	unsigned int padding_len=0;
	char buf[1024]={0};
	BootArray_FW_Entry entry = {0};
	memset(buf,0x00,1024);
	tmp_r=tmp_w=0;
	int w_ret=0;
	int i=0;

	unsigned int NAND_BLOCK_SIZE[] = {NAND_BLOCK_SIZE_128KB, NAND_BLOCK_SIZE_256KB};
	unsigned int block_no = NAND_BOOTARRAY_FW_TABLE_BLK;
	FILE *pFW_Table_File = NULL;

	for (i = 0; i < sizeof(NAND_BLOCK_SIZE)/sizeof(NAND_BLOCK_SIZE[0]); i++) {
		block_no = NAND_BOOTARRAY_FW_TABLE_BLK;
		pFW_Table_File = NULL;
		w_ret = 0;

		if (i == 0) {
			pFW_Table_File = ptr_nand_FW_Table_128KB;
			printf("generate nand BootArray_FW_Table : %s\n", nand_bootarray_fw_table_file_128KB);
		}
		else {
			pFW_Table_File = ptr_nand_FW_Table_256KB;
			printf("generate nand BootArray_FW_Table : %s\n", nand_bootarray_fw_table_file_256KB);
		}

		//bootarray fw table header
		unsigned int table_header = FW_TABLE_MAGIC;
		w_ret = 4 * fwrite(&table_header, 4, 1, pFW_Table_File);
		table_header = FW_TABLE_VERSION;
		w_ret += 4 * fwrite(&table_header, 4, 1, pFW_Table_File);
		w_ret += 8 * fwrite(buf, 8, 1, pFW_Table_File);
		block_no = block_no + 1;

		//SCS_Area: NOCS Certificate & SCS_Params_Area
		entry.type = SCS_Area;
		entry.flash_addr = block_no;
		entry.length = nocs_certificate_size + scs_params_area_size;
		w_ret += 16 * fwrite(&entry, 16, 1, pFW_Table_File);
		block_no = block_no + 1;

		//Auxcode_Area
		entry.type = SCS_Auxcode_Area;
		entry.flash_addr = block_no;
		entry.length = auxcode_area_size;
		w_ret += 16 * fwrite(&entry, 16, 1, pFW_Table_File);
		block_no = block_no + 1;

		//DTE_Bootcode
		entry.type = DTE_Bootcode;
		entry.flash_addr = block_no;
		entry.length = dte_bootcode_area_size;
		w_ret += 16 * fwrite(&entry, 16, 1, pFW_Table_File);
		block_no = block_no + align_to_boundary(DTE_BOOOTCODE_MAX_SIZE, NAND_BLOCK_SIZE[i]);

		//Certificate_Area:
		//    ATF_Certificate
		//    PCPU_Certificate
		//    AFW_Certificate
		//    DTE_FW_Certificate
		entry.type = Certificate_Area;
		entry.flash_addr = block_no;
		entry.length = atf_certificate_size + pcpu_certificate_size + afw_certificate_size + dte_fw_certificate_size;
		w_ret += 16 * fwrite(&entry, 16, 1, pFW_Table_File);
		block_no = block_no + 1;

		//RTK_Params_Area
		entry.type = RTK_Params_Area;
		entry.flash_addr = block_no;
		entry.length = rtk_params_area_size;
		w_ret += 16 * fwrite(&entry, 16, 1, pFW_Table_File);
		block_no = block_no + 1;

		if (ptr_BL31) {
			entry.type = BL31;
			entry.flash_addr = block_no;
			entry.length = bl31_size;
			w_ret += 16 * fwrite(&entry, 16, 1, pFW_Table_File);
		}
		block_no = block_no + 1;	// even no bl31, we need to reserved the space for layout consistency

		if (ptr_Secure_OS) {
			entry.type = TEE_OS;
			entry.flash_addr = block_no;
			entry.length = secure_secure_os_size;
			w_ret += 16 * fwrite(&entry, 16, 1, pFW_Table_File);
		}
		block_no = block_no + align_to_boundary(TEE_OS_MAX_SIZE, NAND_BLOCK_SIZE[i]);	// even no tee os, we need to reserved the space for layout consistency

		//DTE_Bootcode_RTK
		entry.type = DTE_Bootcode_RTK;
		entry.flash_addr = block_no;
		entry.length = dte_bootcode_rtk_area_size;
		w_ret += 16 * fwrite(&entry, 16, 1, pFW_Table_File);

		padding_len = FW_TABLE_SIZE_WO_PADDING - w_ret;
		fwrite(buf, padding_len, 1, pFW_Table_File);
	}

}

int file_write_to_file(FILE *pSrc, FILE *pDst, int *total_read_bytes, int *total_written_bytes)
{
	int read_bytes = 0;
	int written_bytes = 0;
	char buf[1] = {0};

	do {
		read_bytes = 1 * fread(buf, 1, 1, pSrc);

		if (read_bytes > 0) {
			*total_read_bytes += read_bytes;

			written_bytes = read_bytes * fwrite(buf, read_bytes, 1, pDst);
			if (written_bytes != read_bytes) {
				return -1;
			}

			*total_written_bytes += written_bytes;
		}
		else {
			return -1;
		}
	} while (read_bytes > 0);

	return 0;
}

void Bind_NAND_Binary()
{
	int total_read_bytes = 0;
	int total_written_bytes = 0;

	printf("NAND Bind Binary...\n");

	fseek(ptr_scpu_romcode, 0, SEEK_SET);
	fseek(ptr_pcpu_romcode, 0, SEEK_SET);
	fseek(ptr_acpu_romcode, 0, SEEK_SET);
	fseek(ptr_NOCS_Certificate, 0, SEEK_SET);
	fseek(ptr_ATF_Certificate, 0, SEEK_SET);
	fseek(ptr_PCPU_Certificate, 0, SEEK_SET);
	fseek(ptr_DTE_FW_Certificate, 0, SEEK_SET);
	fseek(ptr_AFW_Certificate, 0, SEEK_SET);
	fseek(ptr_SCS_Params_Area, 0, SEEK_SET);
	fseek(ptr_RTK_Params_Area, 0, SEEK_SET);
	fseek(ptr_Auxcode_Area, 0, SEEK_SET);
	fseek(ptr_DTE_Bootcode_Area, 0, SEEK_SET);
	fseek(ptr_DTE_Bootcode_RTK_Area, 0, SEEK_SET);
	if(ptr_Secure_OS) fseek(ptr_Secure_OS, 0, SEEK_SET);
	if(ptr_BL31) fseek(ptr_BL31, 0, SEEK_SET);
	if(ptr_PCPU_Code_Area) fseek(ptr_PCPU_Code_Area, 0, SEEK_SET);

	//write nand bootarray fw table
	total_read_bytes = 0;
	total_written_bytes = 0;
	file_write_to_file(ptr_nand_FW_Table_128KB, ptr_NAND_OUT, &total_read_bytes, &total_written_bytes);
	printf("bind nand bootarray fw table 128KB %s\n", nand_bootarray_fw_table_file_final_128KB);
	total_read_bytes = 0;
	total_written_bytes = 0;
	file_write_to_file(ptr_nand_FW_Table_256KB, ptr_NAND_OUT, &total_read_bytes, &total_written_bytes);
	printf("bind nand bootarray fw table 256KB %s\n", nand_bootarray_fw_table_file_final_256KB);

	//write SCS_Area
	total_read_bytes = 0;
	total_written_bytes = 0;
	file_write_to_file(ptr_NOCS_Certificate, ptr_NAND_OUT, &total_read_bytes, &total_written_bytes);
	printf("NOCS_Certificate r=%08x, w=%08x\n", total_read_bytes, total_written_bytes);
	total_read_bytes = 0;
	total_written_bytes = 0;
	file_write_to_file(ptr_SCS_Params_Area, ptr_NAND_OUT, &total_read_bytes, &total_written_bytes);
	printf("SCS_Params_Area r=%08x, w=%08x\n", total_read_bytes, total_written_bytes);

	//write Auxcode_Area
	total_read_bytes = 0;
	total_written_bytes = 0;
	file_write_to_file(ptr_Auxcode_Area, ptr_NAND_OUT, &total_read_bytes, &total_written_bytes);
	printf("Auxcode_Area r=%08x, w=%08x\n", total_read_bytes, total_written_bytes);

	//write DTE_Bootcode
	total_read_bytes = 0;
	total_written_bytes = 0;
	file_write_to_file(ptr_DTE_Bootcode_Area, ptr_NAND_OUT, &total_read_bytes, &total_written_bytes);
	printf("DTE_Bootcode_Area r=%08x, w=%08x\n", total_read_bytes, total_written_bytes);

	//write Certificate_Area
	//   ATF_Certificate
	total_read_bytes = 0;
	total_written_bytes = 0;
	file_write_to_file(ptr_ATF_Certificate, ptr_NAND_OUT, &total_read_bytes, &total_written_bytes);
	printf("ATF_Certificate r=%08x, w=%08x\n", total_read_bytes, total_written_bytes);
	//   PCPU_Certificate
	total_read_bytes = 0;
	total_written_bytes = 0;
	file_write_to_file(ptr_PCPU_Certificate, ptr_NAND_OUT, &total_read_bytes, &total_written_bytes);
	printf("PCPU_Certificate r=%08x, w=%08x\n", total_read_bytes, total_written_bytes);
	//   AFW_Certificate
	total_read_bytes = 0;
	total_written_bytes = 0;
	file_write_to_file(ptr_AFW_Certificate, ptr_NAND_OUT, &total_read_bytes, &total_written_bytes);
	printf("AFW_Certificate r=%08x, w=%08x\n", total_read_bytes, total_written_bytes);
	//   DTE_FW_Certificate
	total_read_bytes = 0;
	total_written_bytes = 0;
	file_write_to_file(ptr_DTE_FW_Certificate, ptr_NAND_OUT, &total_read_bytes, &total_written_bytes);
	printf("DTE_FW_Certificate r=%08x, w=%08x\n", total_read_bytes, total_written_bytes);

	//write RTK_Params_Area
	total_read_bytes = 0;
	total_written_bytes = 0;
	file_write_to_file(ptr_RTK_Params_Area, ptr_NAND_OUT, &total_read_bytes, &total_written_bytes);
	printf("RTK_Params_Area r=%08x, w=%08x\n", total_read_bytes, total_written_bytes);

	//write BL31
	if (ptr_BL31) {
		total_read_bytes = 0;
		total_written_bytes = 0;
		file_write_to_file(ptr_BL31, ptr_NAND_OUT, &total_read_bytes, &total_written_bytes);
		printf("BL31 r=%08x, w=%08x\n", total_read_bytes, total_written_bytes);
	}

	//write Tee_OS
	if (ptr_Secure_OS) {
		total_read_bytes = 0;
		total_written_bytes = 0;
		file_write_to_file(ptr_Secure_OS, ptr_NAND_OUT, &total_read_bytes, &total_written_bytes);
		printf("Secure_OS r=%08x, w=%08x\n", total_read_bytes, total_written_bytes);
	}

	//write DTE_Bootcode_RTK
	total_read_bytes = 0;
	total_written_bytes = 0;
	file_write_to_file(ptr_DTE_Bootcode_RTK_Area, ptr_NAND_OUT, &total_read_bytes, &total_written_bytes);
	printf("DTE_Bootcode_RTK_Area r=%08x, w=%08x\n", total_read_bytes, total_written_bytes);
}

int main(int argc, char * const argv[])
{

	int ret=0,w_ret=0,i=0, tmp = 0;
	char buf[1024]={0};
	//attribute
	int genBootArrayFWTable = 0;
	int rsa_signature_length = RSA_SIG_LENGTH;
	unsigned int spi_scs_len = 0;


	for (i=1;i<argc;i++)
	{
		if (strcmp(argv[i], "fw_table") == 0)
		{
			printf("bindAllbins : generate fw_table \n");
			genBootArrayFWTable = 1;
		}
		else{
			printf("Invalid argument: %s \n", argv[i]);
		}
	}

	ptr_OUT = fopen(Out_file, "wb");
	ptr_UDA_EMMC_OUT = fopen(UDA_eMMC_Out_file, "wb");
	ptr_BOOT_EMMC_OUT = fopen(BOOT_eMMC_Out_file, "wb");
	ptr_NAND_OUT = fopen(NAND_Out_file, "wb");
	ptr_scpu_romcode = fopen(scpu_romcode_file, "rb");
	ptr_pcpu_romcode = fopen(pcpu_romcode_file, "rb");
	ptr_acpu_romcode = fopen(acpu_romcode_file, "rb");

	if (genBootArrayFWTable == 1)
	{
		ptr_eMMC_FW_Table = fopen(eMMC_bootarray_fw_table_file, "wb");
		ptr_spi_FW_Table = fopen(spi_bootarray_fw_table_file, "wb");
		ptr_nand_FW_Table_128KB = fopen(nand_bootarray_fw_table_file_128KB, "wb");
		ptr_nand_FW_Table_256KB = fopen(nand_bootarray_fw_table_file_256KB, "wb");
	}
	else
	{
		ptr_eMMC_FW_Table = fopen(eMMC_bootarray_fw_table_file_final, "rb");
		ptr_spi_FW_Table = fopen(spi_bootarray_fw_table_file_final, "rb");
		ptr_nand_FW_Table_128KB = fopen(nand_bootarray_fw_table_file_final_128KB, "rb");
		ptr_nand_FW_Table_256KB = fopen(nand_bootarray_fw_table_file_final_256KB, "rb");
	}

	ptr_NOCS_Certificate = fopen(NOCS_Certificate_file, "rb");
	ptr_ATF_Certificate = fopen(ATF_Certificate_file, "rb");
	ptr_PCPU_Certificate = fopen(PCPU_Certificate_file, "rb");
	ptr_DTE_FW_Certificate = fopen(DTE_FW_Certificate_file, "rb");
	ptr_AFW_Certificate = fopen(AFW_Certificate_file, "rb");
	ptr_SCS_Params_Area = fopen(SCS_Params_Area_file, "rb");
	ptr_RTK_Params_Area = fopen(RTK_Params_Area_file, "rb");
	ptr_Auxcode_Area = fopen(Auxcode_Area_file, "rb");
	ptr_DTE_Bootcode_Area = fopen(DTE_Bootcode_Area_file, "rb");
	ptr_Secure_OS = fopen(Secure_OS_file, "rb");
	ptr_BL31 = fopen(BL31_file, "rb");
	ptr_PCPU_Code_Area = fopen(PCPU_Code_Area_file, "rb");
	ptr_DTE_Bootcode_RTK_Area = fopen(dte_bootcode_rtk_area_file, "rb");

	if ( ptr_OUT == NULL || ptr_UDA_EMMC_OUT == NULL || ptr_BOOT_EMMC_OUT == NULL || ptr_eMMC_FW_Table == NULL || ptr_spi_FW_Table == NULL
		|| ptr_nand_FW_Table_128KB == NULL || ptr_nand_FW_Table_256KB == NULL
		|| ptr_scpu_romcode == NULL || ptr_pcpu_romcode == NULL || ptr_acpu_romcode == NULL
		|| ptr_NOCS_Certificate == NULL || ptr_ATF_Certificate == NULL || ptr_PCPU_Certificate == NULL || ptr_DTE_FW_Certificate == NULL || ptr_AFW_Certificate == NULL
		|| ptr_SCS_Params_Area == NULL || ptr_RTK_Params_Area == NULL || ptr_Auxcode_Area == NULL || ptr_PCPU_Code_Area == NULL
		|| ptr_DTE_Bootcode_Area == NULL || ptr_DTE_Bootcode_RTK_Area == NULL)

	{
		printf("file open error\n");
		goto error_out;
	}
	//seek to each file end
	fseek(ptr_scpu_romcode, 1, SEEK_END);
	fseek(ptr_pcpu_romcode, 1, SEEK_END);
	fseek(ptr_acpu_romcode, 1, SEEK_END);
	fseek(ptr_NOCS_Certificate, 1, SEEK_END);
	fseek(ptr_ATF_Certificate, 1, SEEK_END);
	fseek(ptr_PCPU_Certificate, 1, SEEK_END);
	fseek(ptr_DTE_FW_Certificate, 1, SEEK_END);
	fseek(ptr_AFW_Certificate, 1, SEEK_END);
	fseek(ptr_SCS_Params_Area, 1, SEEK_END);
	fseek(ptr_RTK_Params_Area, 1, SEEK_END);
	fseek(ptr_Auxcode_Area, 1, SEEK_END);
	fseek(ptr_DTE_Bootcode_RTK_Area, 1, SEEK_END);
	if(ptr_DTE_Bootcode_Area) fseek(ptr_DTE_Bootcode_Area, 1, SEEK_END);
	if(ptr_Secure_OS) fseek(ptr_Secure_OS, 1, SEEK_END);
    if(ptr_BL31) fseek(ptr_BL31, 1, SEEK_END);
	if(ptr_PCPU_Code_Area) fseek(ptr_PCPU_Code_Area, 1, SEEK_END);

	//tell the each file size
	scpu_romcode_size = ftell(ptr_scpu_romcode)-1;
	pcpu_romcode_size = ftell(ptr_pcpu_romcode)-1;
	acpu_romcode_size = ftell(ptr_acpu_romcode)-1;
	nocs_certificate_size =  ftell(ptr_NOCS_Certificate)-1;
	atf_certificate_size =  ftell(ptr_ATF_Certificate)-1;
	pcpu_certificate_size =  ftell(ptr_PCPU_Certificate)-1;
	dte_fw_certificate_size =  ftell(ptr_DTE_FW_Certificate)-1;
	afw_certificate_size =  ftell(ptr_AFW_Certificate)-1;
	scs_params_area_size =  ftell(ptr_SCS_Params_Area)-1;
	rtk_params_area_size =  ftell(ptr_RTK_Params_Area)-1;
	auxcode_area_size =  ftell(ptr_Auxcode_Area)-1;
	dte_bootcode_area_size = ftell(ptr_DTE_Bootcode_Area)-1;
	dte_bootcode_rtk_area_size = ftell(ptr_DTE_Bootcode_RTK_Area)-1;
	if(ptr_Secure_OS) secure_secure_os_size = ftell(ptr_Secure_OS)-1;
    if(ptr_BL31) bl31_size = ftell(ptr_BL31)-1;
	if(ptr_PCPU_Code_Area) pcpu_code_area_size = ftell(ptr_PCPU_Code_Area)-1;

	printf("scpu_romcode size = %08x, pcpu_romcode size = %08x, acpu_romcode size = %08x\n", scpu_romcode_size, pcpu_romcode_size, acpu_romcode_size);
	printf("nocs_certificate_size = %08x, atf_certificate_size = %08x, pcpu_certificate_size = %08x, dte_fw_certificate_size = %08x, afw_certificate_size = %08x\n", nocs_certificate_size, atf_certificate_size, pcpu_certificate_size, dte_fw_certificate_size, afw_certificate_size);
	printf("scs_params_area_size = %08x, rtk_params_area_size = %08x, auxcode_area_size = %08x\n", scs_params_area_size, rtk_params_area_size, auxcode_area_size);
	printf("dte_bootcod_area size = %08x, dte_bootcode_rtk_area size = %08x\n", dte_bootcode_area_size, dte_bootcode_rtk_area_size);

	if(ptr_Secure_OS != NULL)
		printf("secure os size = %08x\n", secure_secure_os_size);
    if(ptr_BL31 != NULL)
		printf("bl31 size = %08x\n", bl31_size);
	if(ptr_PCPU_Code_Area != NULL)
		printf("pcpu code area size=%08x\n", pcpu_code_area_size);

	fseek(ptr_scpu_romcode, 0, SEEK_SET);
	fseek(ptr_pcpu_romcode, 0, SEEK_SET);
	fseek(ptr_acpu_romcode, 0, SEEK_SET);
	fseek(ptr_NOCS_Certificate, 0, SEEK_SET);
	fseek(ptr_ATF_Certificate, 0, SEEK_SET);
	fseek(ptr_PCPU_Certificate, 0, SEEK_SET);
	fseek(ptr_DTE_FW_Certificate, 0, SEEK_SET);
	fseek(ptr_AFW_Certificate, 0, SEEK_SET);
	fseek(ptr_SCS_Params_Area, 0, SEEK_SET);
	fseek(ptr_RTK_Params_Area, 0, SEEK_SET);
	fseek(ptr_Auxcode_Area, 0, SEEK_SET);
	fseek(ptr_DTE_Bootcode_Area, 0, SEEK_SET);
	fseek(ptr_DTE_Bootcode_RTK_Area, 0, SEEK_SET);
	if(ptr_Secure_OS) fseek(ptr_Secure_OS, 0, SEEK_SET);
    if(ptr_BL31) fseek(ptr_BL31, 0, SEEK_SET);
	if(ptr_PCPU_Code_Area) fseek(ptr_PCPU_Code_Area, 0, SEEK_SET);
	if (genBootArrayFWTable == 1)
	{
		Generate_eMMCBootArrayFWTable();
		Generate_SPIBootArrayFWTable();
		Generate_NANDBootArrayFWTable();
		goto error_out;
	}

	if ((scpu_romcode_size > SCPU_ROMCODE_MAX_SIZE) || (pcpu_romcode_size > PCPU_ROMCODE_MAX_SIZE) ||
		(acpu_romcode_size > ACPU_ROMCODE_MAX_SIZE))
	{
		printf("exceed max romcode size \n");
		goto error_out;
	}

	scpu_romcode_less = SCPU_ROMCODE_MAX_SIZE - scpu_romcode_size;
	pcpu_romcode_less = PCPU_ROMCODE_MAX_SIZE - pcpu_romcode_size;
	acpu_romcode_less = ACPU_ROMCODE_MAX_SIZE - acpu_romcode_size;
	printf("scpu romcode less size = %08x, pcpu romcode less size = %08x, acpu romcode less size = %08x\n",
		scpu_romcode_less, pcpu_romcode_less, acpu_romcode_less);

	//write scpu romcode
	do
	{
		ret = fread(buf, 1, 1, ptr_scpu_romcode);
		tmp_r+=ret;
		if (ret > 0)
		{
			w_ret = fwrite(buf, ret, 1, ptr_OUT);
			tmp_w+=w_ret;
		}
	} while (ret > 0);
	printf("scpu romcode r=%08x, w=%08x\n", tmp_r, tmp_w);
	tmp_r=tmp_w=0;
	memset(buf,0xff,1024);
	for(i=0;i<scpu_romcode_less;i++)
		w_ret = fwrite(buf, 1, 1, ptr_OUT);

	//write pcpu romcode
	do
	{
		ret = fread(buf, 1, 1, ptr_pcpu_romcode);
		tmp_r+=ret;
		if (ret > 0)
		{
			w_ret = fwrite(buf, ret, 1, ptr_OUT);
			tmp_w+=w_ret;
		}
	} while (ret > 0);
	printf("pcpu romcode r=%08x, w=%08x\n", tmp_r, tmp_w);
	tmp_r=tmp_w=0;
	memset(buf,0xff,1024);
	for(i=0;i<pcpu_romcode_less;i++)
		w_ret = fwrite(buf, 1, 1, ptr_OUT);

	//write acpu romcode
	do
	{
		ret = fread(buf, 1, 1, ptr_acpu_romcode);
		tmp_r+=ret;
		if (ret > 0)
		{
			w_ret = fwrite(buf, ret, 1, ptr_OUT);
			tmp_w+=w_ret;
		}
	} while (ret > 0);
	printf("acpu romcode r=%08x, w=%08x\n", tmp_r, tmp_w);
	tmp_r=tmp_w=0;
	memset(buf,0xFF,1024);
	for(i=0;i<acpu_romcode_less;i++)
		w_ret = fwrite(buf, 1, 1, ptr_OUT);

	//write parameter
	if (ptr_Parameter == NULL)
	{
		memset(buf,0xff,1024);
		for(i=0;i<0x800;i++)
		{
			w_ret = fwrite(buf, 1, 1, ptr_OUT);
			tmp_w+=w_ret;
		}
	}
	else
	{
	  	do
		{
			ret = fread(buf, 1, 1, ptr_Parameter);
			tmp_r+=ret;
			if (ret > 0)
			{
				w_ret = fwrite(buf, ret, 1, ptr_OUT);
				tmp_w+=w_ret;
			}
		} while (ret > 0);
	}
	printf("parameter r=%08x, w=%08x\n", tmp_r, tmp_w);
	tmp_r=tmp_w=0;
	memset(buf,0x00,1024);

	//write eMMC bootarray fw table
	do
	{
		ret = fread(buf, 1, 1, ptr_eMMC_FW_Table);
		tmp_r+=ret;
		if (ret > 0)
		{
			w_ret = fwrite(buf, ret, 1, ptr_UDA_EMMC_OUT);
			tmp_w+=w_ret;
		}
	} while (ret > 0);

	tmp_r=tmp_w=0;

	//write spi bootarray fw table
	do
	{
		ret = fread(buf, 1, 1, ptr_spi_FW_Table);
		tmp_r+=ret;
		if (ret > 0)
		{
			w_ret = fwrite(buf, ret, 1, ptr_OUT);
			tmp_w+=w_ret;
		}
	} while (ret > 0);

	printf("bind eMMC bootarray fw table %s\n", eMMC_bootarray_fw_table_file_final);
	printf("bind spi bootarray fw table %s\n", spi_bootarray_fw_table_file_final);
	tmp_r=tmp_w=0;

	//not necessary to write padding for eMMC block, because bootarray_fw_table_file_final is 1KB
	//write NOCS_Certificate
	do
	{
		ret = fread(buf, 1, 1, ptr_NOCS_Certificate);
		tmp_r+=ret;
		if (ret > 0)
		{
			fwrite(buf, ret, 1, ptr_BOOT_EMMC_OUT);
			w_ret = fwrite(buf, ret, 1, ptr_OUT);
			tmp_w+=w_ret;
		}
	} while (ret > 0);
	printf("NOCS Certificate r=%08x, w=%08x\n", tmp_r, tmp_w);
	//not necessary to write padding for eMMC block, because nocs_certificate_final is 1KB
	tmp_r=tmp_w=0;
	spi_scs_len += 1024;

	//write SCS Params Area
	do
	{
		ret = fread(buf, 1, 1, ptr_SCS_Params_Area);
		tmp_r+=ret;
		if (ret > 0)
		{
			fwrite(buf, ret, 1, ptr_BOOT_EMMC_OUT);
			w_ret = fwrite(buf, ret, 1, ptr_OUT);
			tmp_w+=w_ret;
		}
	} while (ret > 0);
	printf("SCS_Params_Area r=%08x, w=%08x\n", tmp_r, tmp_w);
	//SCS data: align 512B boundary for both of SPI and eMMC
	tmp = tmp_w % EMMC_BLOCK_SIZE;
	if (tmp > 0){
		memset(buf,0xff,EMMC_BLOCK_SIZE - tmp);
		fwrite(buf, EMMC_BLOCK_SIZE - tmp, 1, ptr_BOOT_EMMC_OUT);
		fwrite(buf, EMMC_BLOCK_SIZE - tmp, 1, ptr_OUT);
	}
	tmp_r=tmp_w=0;
	spi_scs_len += align_to_boundary_length(scs_params_area_size, EMMC_BLOCK_SIZE);

	//write Auxcode Area
	do
	{
		ret = fread(buf, 1, 1, ptr_Auxcode_Area);
		tmp_r+=ret;
		if (ret > 0)
		{
			fwrite(buf, ret, 1, ptr_BOOT_EMMC_OUT);
			w_ret = fwrite(buf, ret, 1, ptr_OUT);
			tmp_w+=w_ret;
		}
	} while (ret > 0);
	printf("Auxcode_Area r=%08x, w=%08x\n", tmp_r, tmp_w);
	//SCS data: align 512B boundary for both of SPI and eMMC
	tmp = tmp_w % EMMC_BLOCK_SIZE;
	if (tmp > 0){
		memset(buf,0xff,EMMC_BLOCK_SIZE - tmp);
		fwrite(buf, EMMC_BLOCK_SIZE - tmp, 1, ptr_BOOT_EMMC_OUT);
		fwrite(buf, EMMC_BLOCK_SIZE - tmp, 1, ptr_OUT);
	}
	tmp_r=tmp_w=0;
	spi_scs_len += align_to_boundary_length(auxcode_area_size, EMMC_BLOCK_SIZE);

	//write DTE_Bootcode_Area
	do
	{
		ret = fread(buf, 1, 1, ptr_DTE_Bootcode_Area);
		tmp_r+=ret;
		if (ret > 0)
		{
			fwrite(buf, ret, 1, ptr_BOOT_EMMC_OUT);
			w_ret = fwrite(buf, ret, 1, ptr_OUT);
			tmp_w+=w_ret;
		}
	} while (ret > 0);
	printf("dte_bootcode_area r=%08x, w=%08x\n", tmp_r, tmp_w);
	//align 512B boundary for eMMC
	tmp = tmp_w % EMMC_BLOCK_SIZE;
	if (tmp > 0){
		memset(buf,0xff,EMMC_BLOCK_SIZE - tmp);
		fwrite(buf, EMMC_BLOCK_SIZE - tmp, 1, ptr_BOOT_EMMC_OUT);
	}
	tmp_r=tmp_w=0;
	spi_scs_len += dte_bootcode_area_size;

	if (spi_scs_len < SPI_SCS_DATA_SECTION_SIZE){
		memset(buf,0xff,1);
		for (; spi_scs_len < SPI_SCS_DATA_SECTION_SIZE; spi_scs_len++){
			fwrite(buf, 1, 1, ptr_OUT);
		}
	}

	//write ATF_Certificate
	do
	{
		ret = fread(buf, 1, 1, ptr_ATF_Certificate);
		tmp_r+=ret;
		if (ret > 0)
		{
			fwrite(buf, ret, 1, ptr_UDA_EMMC_OUT);
			w_ret = fwrite(buf, ret, 1, ptr_OUT);
			tmp_w+=w_ret;
		}
	} while (ret > 0);
	printf("ATF Certificate r=%08x, w=%08x\n", tmp_r, tmp_w);
	//not necessary to write padding for eMMC block, because atf_certificate_final is 1KB
	tmp_r=tmp_w=0;

	//write PCPU_Certificate
	do
	{
		ret = fread(buf, 1, 1, ptr_PCPU_Certificate);
		tmp_r+=ret;
		if (ret > 0)
		{
			fwrite(buf, ret, 1, ptr_UDA_EMMC_OUT);
			w_ret = fwrite(buf, ret, 1, ptr_OUT);
			tmp_w+=w_ret;
		}
	} while (ret > 0);
	printf("PCPU Certificate r=%08x, w=%08x\n", tmp_r, tmp_w);
	//not necessary to write padding for eMMC block, because pcpu_certificate_final is 1KB
	tmp_r=tmp_w=0;


	//write DTE_FW_Certificate
	do
	{
		ret = fread(buf, 1, 1, ptr_DTE_FW_Certificate);
		tmp_r+=ret;
		if (ret > 0)
		{
			fwrite(buf, ret, 1, ptr_UDA_EMMC_OUT);
			w_ret = fwrite(buf, ret, 1, ptr_OUT);
			tmp_w+=w_ret;
		}
	} while (ret > 0);
	printf("DTE_FW Certificate r=%08x, w=%08x\n", tmp_r, tmp_w);
	//not necessary to write padding for eMMC block, because dte_fw_certificate_final is 1KB
	tmp_r=tmp_w=0;


	//write AFW_Certificate
	do
	{
		ret = fread(buf, 1, 1, ptr_AFW_Certificate);
		tmp_r+=ret;
		if (ret > 0)
		{
			fwrite(buf, ret, 1, ptr_UDA_EMMC_OUT);
			w_ret = fwrite(buf, ret, 1, ptr_OUT);
			tmp_w+=w_ret;
		}
	} while (ret > 0);
	printf("AFW Certificate r=%08x, w=%08x\n", tmp_r, tmp_w);
	//not necessary to write padding for eMMC block, because dte_fw_certificate_final is 1KB
	tmp_r=tmp_w=0;

	//write RTK Params Area
	do
	{
		ret = fread(buf, 1, 1, ptr_RTK_Params_Area);
		tmp_r+=ret;
		if (ret > 0)
		{
			fwrite(buf, ret, 1, ptr_UDA_EMMC_OUT);
			w_ret = fwrite(buf, ret, 1, ptr_OUT);
			tmp_w+=w_ret;
		}
	} while (ret > 0);
	printf("RTK_Params_Area r=%08x, w=%08x\n", tmp_r, tmp_w);
	//align emmc boundary
	tmp = tmp_w % EMMC_BLOCK_SIZE;
	if (tmp > 0){
		memset(buf,0xff,EMMC_BLOCK_SIZE - tmp);
		fwrite(buf, EMMC_BLOCK_SIZE - tmp, 1, ptr_UDA_EMMC_OUT);
	}
	tmp_r=tmp_w=0;

	//write PCPU code
	if (ptr_PCPU_Code_Area){
		do
		{
			ret = fread(buf, 1, 1, ptr_PCPU_Code_Area);
			tmp_r+=ret;
			if (ret > 0)
			{
				fwrite(buf, ret, 1, ptr_UDA_EMMC_OUT);
				w_ret = fwrite(buf, ret, 1, ptr_OUT);
				tmp_w+=w_ret;
			}
		} while (ret > 0);
		printf("pcpu fw r=%08x, w=%08x\n", tmp_r, tmp_w);
		//align emmc boundary
		tmp = tmp_w % EMMC_BLOCK_SIZE;
		if (tmp > 0){
			memset(buf,0xff,EMMC_BLOCK_SIZE - tmp);
			fwrite(buf, EMMC_BLOCK_SIZE - tmp, 1, ptr_UDA_EMMC_OUT);
		}
		tmp_r=tmp_w=0;
	}
	
	 //write bl31
	if (ptr_BL31){
		do
		{
			ret = fread(buf, 1, 1, ptr_BL31);
			tmp_r+=ret;
			if (ret > 0)
			{
				fwrite(buf, ret, 1, ptr_UDA_EMMC_OUT);
				w_ret = fwrite(buf, ret, 1, ptr_OUT);
				tmp_w+=w_ret;
			}
		} while (ret > 0);
		printf("bl31 r=%08x, w=%08x\n", tmp_r, tmp_w);
		//align emmc boundary
		tmp = tmp_w % EMMC_BLOCK_SIZE;
		if (tmp > 0){
			memset(buf,0xff,EMMC_BLOCK_SIZE - tmp);
			fwrite(buf, EMMC_BLOCK_SIZE - tmp, 1, ptr_UDA_EMMC_OUT);
		}
		tmp_r=tmp_w=0;
	}

	//write secure_os
	if (ptr_Secure_OS){
		do
		{
			ret = fread(buf, 1, 1, ptr_Secure_OS);
			tmp_r+=ret;
			if (ret > 0)
			{
				fwrite(buf, ret, 1, ptr_UDA_EMMC_OUT);
				w_ret = fwrite(buf, ret, 1, ptr_OUT);
				tmp_w+=w_ret;
			}
		} while (ret > 0);
		printf("secure_os r=%08x, w=%08x\n", tmp_r, tmp_w);
		//align emmc boundary
		tmp = tmp_w % EMMC_BLOCK_SIZE;
		if (tmp > 0){
			memset(buf,0xff,EMMC_BLOCK_SIZE - tmp);
			fwrite(buf, EMMC_BLOCK_SIZE - tmp, 1, ptr_UDA_EMMC_OUT);
		}
		tmp_r=tmp_w=0;
	}

	//write DTE_Bootcode_RTK
	do
	{
		ret = fread(buf, 1, 1, ptr_DTE_Bootcode_RTK_Area);
		tmp_r+=ret;
		if (ret > 0)
		{
			fwrite(buf, ret, 1, ptr_UDA_EMMC_OUT);
			w_ret = fwrite(buf, ret, 1, ptr_OUT);
			tmp_w+=w_ret;
		}
	} while (ret > 0);
	printf("DTE_Bootcode_RTK_Area r=%08x, w=%08x\n", tmp_r, tmp_w);
	//align emmc boundary
	tmp = tmp_w % EMMC_BLOCK_SIZE;
	if (tmp > 0){
		memset(buf,0xff,EMMC_BLOCK_SIZE - tmp);
		fwrite(buf, EMMC_BLOCK_SIZE - tmp, 1, ptr_UDA_EMMC_OUT);
	}
	tmp_r=tmp_w=0;

	Bind_NAND_Binary();

error_out:
	if (ptr_OUT)
		fclose(ptr_OUT);
	if (ptr_UDA_EMMC_OUT)
		fclose(ptr_UDA_EMMC_OUT);
	if (ptr_BOOT_EMMC_OUT)
		fclose(ptr_BOOT_EMMC_OUT);
	if (ptr_Parameter)
		fclose(ptr_Parameter);
	if (ptr_scpu_romcode)
		fclose(ptr_scpu_romcode);
	if (ptr_pcpu_romcode)
		fclose(ptr_pcpu_romcode);
	if (ptr_acpu_romcode)
		fclose(ptr_acpu_romcode);
	if (ptr_eMMC_FW_Table)
		fclose(ptr_eMMC_FW_Table);
	if (ptr_spi_FW_Table)
		fclose(ptr_spi_FW_Table);
	if (ptr_nand_FW_Table_128KB)
		fclose(ptr_nand_FW_Table_128KB);
	if (ptr_nand_FW_Table_256KB)
		fclose(ptr_nand_FW_Table_256KB);
	if (ptr_NOCS_Certificate)
		fclose(ptr_NOCS_Certificate);
	if (ptr_ATF_Certificate)
		fclose(ptr_ATF_Certificate);
	if (ptr_PCPU_Certificate)
		fclose(ptr_PCPU_Certificate);
	if (ptr_DTE_FW_Certificate)
		fclose(ptr_DTE_FW_Certificate);
	if (ptr_AFW_Certificate)
		fclose(ptr_AFW_Certificate);
	if (ptr_SCS_Params_Area)
		fclose(ptr_SCS_Params_Area);
	if (ptr_RTK_Params_Area)
		fclose(ptr_RTK_Params_Area);
	if (ptr_Auxcode_Area)
		fclose(ptr_Auxcode_Area);
	if (ptr_DTE_Bootcode_Area)
		fclose(ptr_DTE_Bootcode_Area);
	if (ptr_DTE_Bootcode_RTK_Area)
		fclose(ptr_DTE_Bootcode_RTK_Area);
	if (ptr_Secure_OS)
		fclose(ptr_Secure_OS);
	if (ptr_PCPU_Code_Area)
		fclose(ptr_PCPU_Code_Area);
    if (ptr_BL31)
		fclose(ptr_BL31);
}
