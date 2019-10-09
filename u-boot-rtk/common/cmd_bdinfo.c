/*
 * (C) Copyright 2003
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

/*
 * Boot support
 */
#include <common.h>
#include <command.h>
#include <linux/compiler.h>
#include <asm/arch/rbus/crt_reg.h>
#include <asm/arch/io.h>
#include <asm/arch/ddr.h>

DECLARE_GLOBAL_DATA_PTR;

__maybe_unused
static void print_num(const char *name, ulong value)
{
	printf("%-12s= 0x%08lX\n", name, value);
}

__maybe_unused
static void print_eth(int idx)
{
	char name[10], *val;
	if (idx)
		sprintf(name, "eth%iaddr", idx);
	else
		strcpy(name, "ethaddr");
	val = getenv(name);
	if (!val)
		val = "(not set)";
	printf("%-12s= %s\n", name, val);
}

#ifndef CONFIG_DM_ETH
__maybe_unused
static void print_eths(void)
{
	struct eth_device *dev;
	int i = 0;

	do {
		dev = eth_get_dev_by_index(i);
		if (dev) {
			printf("eth%dname    = %s\n", i, dev->name);
			print_eth(i);
			i++;
		}
	} while (dev);

	printf("current eth = %s\n", eth_get_name());
	printf("ip_addr     = %s\n", getenv("ipaddr"));
}
#endif

__maybe_unused
static void print_lnum(const char *name, unsigned long long value)
{
	printf("%-12s= 0x%.8llX\n", name, value);
}

__maybe_unused
static void print_mhz(const char *name, unsigned long hz)
{
	char buf[32];

	printf("%-12s= %6s MHz\n", name, strmhz(buf, hz));
}

#if defined(CONFIG_PPC)
void __weak board_detail(void)
{
	/* Please define boot_detail() for your platform */
}

int do_bdinfo(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	bd_t *bd = gd->bd;

#ifdef DEBUG
	print_num("bd address",		(ulong)bd);
#endif
	print_num("memstart",		bd->bi_memstart);
	print_lnum("memsize",		bd->bi_memsize);
	print_num("flashstart",		bd->bi_flashstart);
	print_num("flashsize",		bd->bi_flashsize);
	print_num("flashoffset",	bd->bi_flashoffset);
	print_num("sramstart",		bd->bi_sramstart);
	print_num("sramsize",		bd->bi_sramsize);
#if	defined(CONFIG_5xx)  || defined(CONFIG_8xx) || \
	defined(CONFIG_MPC8260) || defined(CONFIG_E500)
	print_num("immr_base",		bd->bi_immr_base);
#endif
	print_num("bootflags",		bd->bi_bootflags);
#if	defined(CONFIG_405EP) || \
	defined(CONFIG_405GP) || \
	defined(CONFIG_440EP) || defined(CONFIG_440EPX) || \
	defined(CONFIG_440GR) || defined(CONFIG_440GRX) || \
	defined(CONFIG_440SP) || defined(CONFIG_440SPE) || \
	defined(CONFIG_XILINX_405)
	print_mhz("procfreq",		bd->bi_procfreq);
	print_mhz("plb_busfreq",	bd->bi_plb_busfreq);
#if	defined(CONFIG_405EP) || defined(CONFIG_405GP) || \
	defined(CONFIG_440EP) || defined(CONFIG_440EPX) || \
	defined(CONFIG_440GR) || defined(CONFIG_440GRX) || \
	defined(CONFIG_440SPE) || defined(CONFIG_XILINX_405)
	print_mhz("pci_busfreq",	bd->bi_pci_busfreq);
#endif
#else	/* ! CONFIG_405GP, CONFIG_405EP, CONFIG_XILINX_405, CONFIG_440EP CONFIG_440GR */
#if defined(CONFIG_CPM2)
	print_mhz("vco",		bd->bi_vco);
	print_mhz("sccfreq",		bd->bi_sccfreq);
	print_mhz("brgfreq",		bd->bi_brgfreq);
#endif
	print_mhz("intfreq",		bd->bi_intfreq);
#if defined(CONFIG_CPM2)
	print_mhz("cpmfreq",		bd->bi_cpmfreq);
#endif
	print_mhz("busfreq",		bd->bi_busfreq);
#endif /* CONFIG_405GP, CONFIG_405EP, CONFIG_XILINX_405, CONFIG_440EP CONFIG_440GR */

#ifdef CONFIG_ENABLE_36BIT_PHYS
#ifdef CONFIG_PHYS_64BIT
	puts("addressing  = 36-bit\n");
#else
	puts("addressing  = 32-bit\n");
#endif
#endif

	print_eth(0);
#if defined(CONFIG_HAS_ETH1)
	print_eth(1);
#endif
#if defined(CONFIG_HAS_ETH2)
	print_eth(2);
#endif
#if defined(CONFIG_HAS_ETH3)
	print_eth(3);
#endif
#if defined(CONFIG_HAS_ETH4)
	print_eth(4);
#endif
#if defined(CONFIG_HAS_ETH5)
	print_eth(5);
#endif

	printf("IP addr     = %s\n", getenv("ipaddr"));
	printf("baudrate    = %6u bps\n", gd->baudrate);
	print_num("relocaddr", gd->relocaddr);
	board_detail();
	return 0;
}

#elif defined(CONFIG_NIOS2)

int do_bdinfo(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	bd_t *bd = gd->bd;

	print_num("mem start",		(ulong)bd->bi_memstart);
	print_lnum("mem size",		(u64)bd->bi_memsize);
	print_num("flash start",	(ulong)bd->bi_flashstart);
	print_num("flash size",		(ulong)bd->bi_flashsize);
	print_num("flash offset",	(ulong)bd->bi_flashoffset);

#if defined(CONFIG_SYS_SRAM_BASE)
	print_num ("sram start",	(ulong)bd->bi_sramstart);
	print_num ("sram size",		(ulong)bd->bi_sramsize);
#endif

#if defined(CONFIG_CMD_NET)
	print_eth(0);
	printf("ip_addr     = %s\n", getenv("ipaddr"));
#endif

	printf("baudrate    = %u bps\n", gd->baudrate);

	return 0;
}

#elif defined(CONFIG_MICROBLAZE)

int do_bdinfo(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	bd_t *bd = gd->bd;
	int i;

	for (i = 0; i < CONFIG_NR_DRAM_BANKS; ++i) {
		print_num("DRAM bank",	i);
		print_num("-> start",	bd->bi_dram[i].start);
		print_num("-> size",	bd->bi_dram[i].size);
	}

	print_num("flash start    ",	(ulong)bd->bi_flashstart);
	print_num("flash size     ",	(ulong)bd->bi_flashsize);
	print_num("flash offset   ",	(ulong)bd->bi_flashoffset);
#if defined(CONFIG_SYS_SRAM_BASE)
	print_num("sram start     ",	(ulong)bd->bi_sramstart);
	print_num("sram size      ",	(ulong)bd->bi_sramsize);
#endif
#if defined(CONFIG_CMD_NET)
	print_eths();
#endif
	printf("baudrate    = %u bps\n", gd->baudrate);
	print_num("relocaddr", gd->relocaddr);
	print_num("reloc off", gd->reloc_off);
	print_num("fdt_blob", (ulong)gd->fdt_blob);
	print_num("new_fdt", (ulong)gd->new_fdt);
	print_num("fdt_size", (ulong)gd->fdt_size);

	return 0;
}

#elif defined(CONFIG_SPARC)

int do_bdinfo(cmd_tbl_t * cmdtp, int flag, int argc, char * const argv[])
{
	bd_t *bd = gd->bd;

#ifdef DEBUG
	print_num("bd address             ", (ulong) bd);
#endif
	print_num("memstart               ", bd->bi_memstart);
	print_lnum("memsize                ", bd->bi_memsize);
	print_num("flashstart             ", bd->bi_flashstart);
	print_num("CONFIG_SYS_MONITOR_BASE       ", CONFIG_SYS_MONITOR_BASE);
	print_num("CONFIG_ENV_ADDR           ", CONFIG_ENV_ADDR);
	printf("CONFIG_SYS_RELOC_MONITOR_BASE = 0x%x (%d)\n", CONFIG_SYS_RELOC_MONITOR_BASE,
	       CONFIG_SYS_MONITOR_LEN);
	printf("CONFIG_SYS_MALLOC_BASE        = 0x%x (%d)\n", CONFIG_SYS_MALLOC_BASE,
	       CONFIG_SYS_MALLOC_LEN);
	printf("CONFIG_SYS_INIT_SP_OFFSET     = 0x%x (%d)\n", CONFIG_SYS_INIT_SP_OFFSET,
	       CONFIG_SYS_STACK_SIZE);
	printf("CONFIG_SYS_PROM_OFFSET        = 0x%x (%d)\n", CONFIG_SYS_PROM_OFFSET,
	       CONFIG_SYS_PROM_SIZE);
	printf("CONFIG_SYS_GBL_DATA_OFFSET    = 0x%x (%d)\n", CONFIG_SYS_GBL_DATA_OFFSET,
	       GENERATED_GBL_DATA_SIZE);

#if defined(CONFIG_CMD_NET)
	print_eth(0);
	printf("ip_addr     = %s\n", getenv("ipaddr"));
#endif
	printf("baudrate               = %6u bps\n", gd->baudrate);
	return 0;
}

#elif defined(CONFIG_M68K)

int do_bdinfo(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	bd_t *bd = gd->bd;

	print_num("memstart",		(ulong)bd->bi_memstart);
	print_lnum("memsize",		(u64)bd->bi_memsize);
	print_num("flashstart",		(ulong)bd->bi_flashstart);
	print_num("flashsize",		(ulong)bd->bi_flashsize);
	print_num("flashoffset",	(ulong)bd->bi_flashoffset);
#if defined(CONFIG_SYS_INIT_RAM_ADDR)
	print_num("sramstart",		(ulong)bd->bi_sramstart);
	print_num("sramsize",		(ulong)bd->bi_sramsize);
#endif
#if defined(CONFIG_SYS_MBAR)
	print_num("mbar",		bd->bi_mbar_base);
#endif
	print_mhz("cpufreq",		bd->bi_intfreq);
	print_mhz("busfreq",		bd->bi_busfreq);
#ifdef CONFIG_PCI
	print_mhz("pcifreq",		bd->bi_pcifreq);
#endif
#ifdef CONFIG_EXTRA_CLOCK
	print_mhz("flbfreq",		bd->bi_flbfreq);
	print_mhz("inpfreq",		bd->bi_inpfreq);
	print_mhz("vcofreq",		bd->bi_vcofreq);
#endif
#if defined(CONFIG_CMD_NET)
	print_eth(0);
#if defined(CONFIG_HAS_ETH1)
	print_eth(1);
#endif
#if defined(CONFIG_HAS_ETH2)
	print_eth(2);
#endif
#if defined(CONFIG_HAS_ETH3)
	print_eth(3);
#endif

	printf("ip_addr     = %s\n", getenv("ipaddr"));
#endif
	printf("baudrate    = %u bps\n", gd->baudrate);

	return 0;
}

#elif defined(CONFIG_BLACKFIN)

int do_bdinfo(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	bd_t *bd = gd->bd;

	printf("U-Boot      = %s\n", bd->bi_r_version);
	printf("CPU         = %s\n", bd->bi_cpu);
	printf("Board       = %s\n", bd->bi_board_name);
	print_mhz("VCO",	bd->bi_vco);
	print_mhz("CCLK",	bd->bi_cclk);
	print_mhz("SCLK",	bd->bi_sclk);

	print_num("boot_params",	(ulong)bd->bi_boot_params);
	print_num("memstart",		(ulong)bd->bi_memstart);
	print_lnum("memsize",		(u64)bd->bi_memsize);
	print_num("flashstart",		(ulong)bd->bi_flashstart);
	print_num("flashsize",		(ulong)bd->bi_flashsize);
	print_num("flashoffset",	(ulong)bd->bi_flashoffset);

	print_eth(0);
	printf("ip_addr     = %s\n", getenv("ipaddr"));
	printf("baudrate    = %u bps\n", gd->baudrate);

	return 0;
}

#elif defined(CONFIG_MIPS)

int do_bdinfo(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	bd_t *bd = gd->bd;

	print_num("boot_params",	(ulong)bd->bi_boot_params);
	print_num("memstart",		(ulong)bd->bi_memstart);
	print_lnum("memsize",		(u64)bd->bi_memsize);
	print_num("flashstart",		(ulong)bd->bi_flashstart);
	print_num("flashsize",		(ulong)bd->bi_flashsize);
	print_num("flashoffset",	(ulong)bd->bi_flashoffset);

	print_eth(0);
	printf("ip_addr     = %s\n", getenv("ipaddr"));
	printf("baudrate    = %u bps\n", gd->baudrate);

	return 0;
}

#elif defined(CONFIG_AVR32)

int do_bdinfo(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	bd_t *bd = gd->bd;

	print_num("boot_params",	(ulong)bd->bi_boot_params);
	print_num("memstart",		(ulong)bd->bi_dram[0].start);
	print_lnum("memsize",		(u64)bd->bi_dram[0].size);
	print_num("flashstart",		(ulong)bd->bi_flashstart);
	print_num("flashsize",		(ulong)bd->bi_flashsize);
	print_num("flashoffset",	(ulong)bd->bi_flashoffset);

	print_eth(0);
	printf("ip_addr     = %s\n", getenv("ipaddr"));
	printf("baudrate    = %u bps\n", gd->baudrate);

	return 0;
}

#elif defined(CONFIG_ARM)

#define DC_SYS_MISC_reg				0xB8008004
#define DC2_SYS_MISC_reg			0xB8003004
#define DC_SECURE_MISC_reg				0x18008740

static int ddr_mhz = 0;

static int do_bdinfo_dss(void)
{
	//uint regValue = 0;

	printf("*** bdinfo dss ***\n");
#ifdef CONFIG_RTD299X //(wilma+ 2013/06/29)
	//DSS1 dc_phy 0xb8008f50
	rtd_outl(SS_12T_LVT_0_reg, 0x00000000); //DSS1 reset
	rtd_outl(SS_12T_LVT_0_reg, 0x00000012); //wire_sel=1'b1, ro_sel=3'b001
	rtd_outl(SS_12T_LVT_0_reg, 0x00000013); //DSS1 enable
	mdelay(500);		// wait done
	regValue = rtd_inl(SS_12T_LVT_1_reg); //count_out[23:4]
	printf("DSS1 DC_PHY   = 0x%05x\n", ((regValue & SS_12T_LVT_1_count_out_mask) >> SS_12T_LVT_1_count_out_shift));

	//DSS2 dc2_phy 0xb8003f50
	rtd_outl(0xb8003f50,0x00000000); //DSS2 reset
	rtd_outl(0xb8003f50,0x00000012); //wire_sel=1'b1, ro_sel=3'b001
	rtd_outl(0xb8003f50,0x00000013); //DSS2 enable
	mdelay(500);		// wait done
	regValue = rtd_inl(0xb8003f54); //count_out[23:4]
	printf("DSS2 DC2_PHY  = 0x%05x\n", ((regValue & 0x00FFFFF0) >> 4));

	//DSS3 SCPU_phy 0xb805_c008
	rtd_outl(0xb805c008,0x00000000); //DSS3 reset
	rtd_outl(0xb805c008,0x00000012); //wire_sel=1'b1, ro_sel=3'b001
	rtd_outl(0xb805c008,0x00000013); //DSS3 enable
	mdelay(500);		// wait done
	regValue = rtd_inl(0xb805c010); //count_out[23:4]
	printf("DSS3 SCPU_PHY = 0x%05x\n", ((regValue & 0x00FFFFF0) >> 4));

	//DSS4 SCPU_phy 0xb805_c000
	rtd_outl(0xb805c000,0x00000000); //DSS4 reset
	rtd_outl(0xb805c000,0x00000012); //wire_sel=1'b1, ro_sel=3'b001
	rtd_outl(0xb805c000,0x00000013); //DSS4 enable
	mdelay(500);		// wait done
	regValue = rtd_inl(0xb805c004); //count_out[23:4]
	printf("DSS4 SCPU_PHY = 0x%05x\n", ((regValue & 0x00FFFFF0) >> 4));

	//DSS5 VCPU 0xb800_0298
	rtd_outl(SS_12T_RVT_0_reg,0x00000000); //DSS5 reset
	rtd_outl(SS_12T_RVT_0_reg,0x03000000); //wire_sel=1'b1, ro_sel=3'b001
	rtd_outl(SS_12T_RVT_0_reg,0x83000000); //DSS5 enable
	mdelay(500);		// wait done
	regValue = rtd_inl(SS_12T_RVT_0_reg); //count_out[19:0]
	printf("DSS5 VCPU     = 0x%05x\n", ((regValue & SS_12T_RVT_0_rvt_12t_count_out_mask) >> SS_12T_RVT_0_rvt_12t_count_out_shift));

	//DSS6 VCPU2 0xb800_0340
	rtd_outl(SS_9T_LVT_0_reg,0x00000000); //DSS6 reset
	rtd_outl(SS_9T_LVT_0_reg,0x03000000); //wire_sel=1'b1, ro_sel=3'b001
	rtd_outl(SS_9T_LVT_0_reg,0x83000000); //DSS6 enable
	mdelay(500);		// wait done
	regValue = rtd_inl(SS_9T_LVT_0_reg); //count_out[19:0]
	printf("DSS6 VCPU2    = 0x%05x\n", ((regValue & SS_9T_LVT_0_lvt_9t_count_out_mask) >> SS_9T_LVT_0_lvt_9t_count_out_shift));

	//DSS7 VCPU2 0xb800_0348
	rtd_outl(SS_9T_RVT_0_reg,0x00000000); //DSS7 reset
	rtd_outl(SS_9T_RVT_0_reg,0x03000000); //wire_sel=1'b1, ro_sel=3'b001
	rtd_outl(SS_9T_RVT_0_reg,0x83000000); //DSS7 enable
	mdelay(500);		// wait done
	regValue = rtd_inl(SS_9T_RVT_0_reg); //count_out[19:0]
	printf("DSS7 VCPU2    = 0x%05x\n", ((regValue & SS_9T_RVT_0_rvt_9t_count_out_mask) >> SS_9T_RVT_0_rvt_9t_count_out_shift));

	//DSS8 tv_sb1 0xb801_c3f0
	rtd_outl(SS_7T_0_reg,0x00000000); //DSS8 reset
	rtd_outl(SS_7T_0_reg,0x03000000); //wire_sel=1'b1, ro_sel=3'b001
	rtd_outl(SS_7T_0_reg,0x83000000); //DSS8 enable
	mdelay(500);		// wait done
	regValue = rtd_inl(SS_7T_0_reg); //count_out[19:0]
	printf("DSS8 TV_SB1   = 0x%05x\n", ((regValue & SS_7T_0_rlvt_7t_count_out_mask) >> SS_7T_0_rlvt_7t_count_out_shift));
#endif
	return 0;
}

/*
 * get_accessible_ddr_size()
 */

unsigned long get_accessible_ddr_size(int unit)
{
#ifdef CONFIG_BOARD_FPGA
	return CONFIG_SYS_RAM_DCU1_SIZE;
#else
	unsigned long ddr_size = (get_total_ddr_size() * 1024) / 8;

	if(unit == UNIT_MEGABYTE)
		return ddr_size;
	else
		return (ddr_size * 0x100000);

	return 0;
#endif //CONFIG_BOARD_FPGA
}

#define DC0_DPI_DLL_CRT_SSC3_reg	0x9800E028
#define DC1_DPI_DLL_CRT_SSC3_reg	0x9800F028
#define DCPHY_DPI_DLL_CRT_SSC3_get_DPI_N_CODE_T(data)   ((0x0000FF00&(data))>>8)

static int do_bdinfo_ddr(void)
{
	char info_dc0[50], info_dc1[50];
	int i;
	printf("*** bdinfo ddr ***\n");

#if defined(CONFIG_RTD1295) || defined(CONFIG_RTD1395)
	for( i = 0; i < MAX_DC_COUNT; i++){
		uint ddr_speed_setting;
		if( i == 0 )
			ddr_speed_setting = DCPHY_DPI_DLL_CRT_SSC3_get_DPI_N_CODE_T(rtd_inl(DC0_DPI_DLL_CRT_SSC3_reg));
		else
			ddr_speed_setting = DCPHY_DPI_DLL_CRT_SSC3_get_DPI_N_CODE_T(rtd_inl(DC1_DPI_DLL_CRT_SSC3_reg));
		
		char range_exceed[16] = "";

		switch (ddr_speed_setting) {
			case 0x2a ... 0xff:
				ddr_mhz = 2400;
				strcpy(range_exceed, "OVER");
				break;
			case 0x25 ... 0x29:
				ddr_mhz = 2400;
				break;
			case 0x20 ... 0x24:
				ddr_mhz = 2133;
				break;
			case 0x1b ... 0x1f:
				ddr_mhz = 1866;
				break;
			case 0x16 ... 0x1a:
				ddr_mhz = 1600;
				break;
			case 0x15:
				ddr_mhz = 1333;
				break;
			case 0x0 ... 0x14 :
				ddr_mhz = 1333;
				strcpy(range_exceed, "UNDER");
				break;
			default:	ddr_mhz = 0;	break;
		}
		
		if( i == 0 )
			sprintf(info_dc0, "DDR        = %s %u MT/s (0x%02x)\n",range_exceed, ddr_mhz, ddr_speed_setting);
		else
			sprintf(info_dc1, "DDR        = %s %u MT/s (0x%02x)\n",range_exceed, ddr_mhz, ddr_speed_setting);
	}

#endif
	
	//printf("DDR        = %s %u MHz (0x%02x)\n",range_exceed, ddr_mhz, ddr_speed_setting);
	print_ddr_info(info_dc0,info_dc1);

	return 0;
}

#define SCPU_PLL_Output_4 	0x3
#define SCPU_PLL_Output_2 	0x2
#define ACPU_PLL_Output_4 	0x3
#define ACPU_PLL_Output_2 	0x2
#define BUS_PLL_Output_4 	0x1
#define BUS_PLL_Output_2 	0x0

static int do_bdinfo_pll(void)
{
	char   msg[64];
	uint value_m, value_n, value_o;
	uint Ncode, Fcode;
	uint freq, tmp;
	uint pdiv;
	uint div = get_PLL_DIV_reg ;
	

	printf("*** bdinfo pll ***\n");
	
	//27MHz*(Ncode+1+Fcode/2048)/(N+1)
	tmp = get_PLL_SSC_DIG_SCPU1_reg;
	Ncode = PLL_SSC_DIG_SCPU1_get_NCODE_T_SCPU(tmp);
	Fcode = PLL_SSC_DIG_SCPU1_get_FCODE_T_SCPU(tmp);
	//freq = 27 * (Ncode + 3 + (Fcode/2048));
	freq = 27 * (Ncode + 3) + (27 * Fcode / 2048);
	sprintf( msg, "%4d MHz", freq );
	printf("SCPU   PLL  = %s\n", msg);
	if( PLL_DIV_get_scpu_freq_sel(div) == SCPU_PLL_Output_4)
		sprintf( msg, "%4d MHz", freq/4);
	else if( PLL_DIV_get_scpu_freq_sel(div) == SCPU_PLL_Output_2)
		sprintf( msg, "%4d MHz", freq/2 );
	else
		sprintf( msg, "%4d MHz", freq );
	printf("SCPU        = %s\n", msg);
	
	//27MHz*(M+2)/(N+1)/(O+1)
	tmp = get_PLL_SSC_DIG_ACPU1_reg;
	Ncode = PLL_SSC_DIG_ACPU1_get_NCODE_T_ACPU(tmp);
	Fcode = PLL_SSC_DIG_ACPU1_get_FCODE_T_ACPU(tmp);
	//freq = 27 * (Ncode + 3 + (Fcode/2048));
	freq = 27 * (Ncode + 3) + (27 * Fcode / 2048);
	sprintf( msg, "%4d MHz", freq );
	printf("ACPU   PLL  = %s\n", msg);	
	if( PLL_DIV_get_acpu_freq_sel(div) == ACPU_PLL_Output_4)
		sprintf( msg, "%4d MHz", freq/4);
	else if( PLL_DIV_get_acpu_freq_sel(div) == ACPU_PLL_Output_2)
		sprintf( msg, "%4d MHz", freq/2 );
	else
		sprintf( msg, "%4d MHz", freq );
	printf("ACPU        = %s\n", msg);

	// get VCPU PLL MNO value
	// 27MHz*(M+2)/(N+1)/(O+1)
	tmp = get_PLL_VCPU1_reg;
	value_m = PLL_VCPU1_get_PLLVCPU_M(tmp);
	value_n = PLL_VCPU1_get_PLLVCPU_N(tmp);
	value_o = PLL_VCPU1_get_REG_PLLVCPU_O(tmp);
	freq = 27 * (value_m+2) / (value_n+1) / (value_o+1);	
	sprintf( msg, "%4d MHz", freq );
	printf("VCPU1  PLL  = %s\n", msg);
	
	// get VCPU PLL MNO value
	// 27MHz*(M+2)/(N+1)/(O+1)
	tmp = get_PLL_VCPU2_reg;
	value_m = PLL_VCPU2_get_PLLVCPU_M(tmp);
	value_n = PLL_VCPU2_get_PLLVCPU_N(tmp);
	value_o = PLL_VCPU2_get_REG_PLLVCPU_O(tmp);
	freq = 27 * (value_m+2) / (value_n+1) / (value_o+1);	
	sprintf( msg, "%4d MHz", freq );
	printf("VCPU2  PLL  = %s\n", msg);

	// get DDSA PLL MNO value
	tmp = get_PLL_SSC_DIG_DDSA1_reg;
	Ncode = PLL_SSC_DIG_DDSA1_get_NCODE_T_DDSA(tmp);
	Fcode = PLL_SSC_DIG_DDSA1_get_FCODE_T_DDSA(tmp);
	pdiv = PLL_SSC_DIG_DDSA1_get_REG_PLLDDSA_ICO_PDIV2(tmp);
	//freq = 27 * (pdiv + 1) * (Ncode + 3 + (Fcode/2048));
	freq = (27 * (pdiv + 1)) * (Ncode + 3) + ((27 * (pdiv + 1)) * Fcode / 2048);
	sprintf( msg, "%4d MHz", freq );
	printf("DDSA   PLL  = %s\n", msg);	
	
	// get DDSB PLL MNO value
	tmp = get_PLL_SSC_DIG_DDSB1_reg;
	Ncode = PLL_SSC_DIG_DDSB1_get_NCODE_T_DDSB(tmp);
	Fcode = PLL_SSC_DIG_DDSB1_get_FCODE_T_DDSB(tmp);
	pdiv = PLL_SSC_DIG_DDSB1_get_REG_PLLDDSB_ICO_PDIV2(tmp);
	//freq = 27 * (pdiv + 1) * (Ncode + 3 + (Fcode/2048));
	freq = (27 * (pdiv + 1)) * (Ncode + 3) + ((27 * (pdiv + 1)) * Fcode / 2048);
	sprintf( msg, "%4d MHz", freq );
	printf("DDSB   PLL  = %s\n", msg);	
	
	// get BUS PLL MNO value
	tmp = get_PLL_SSC_DIG_BUS1_reg;
	Ncode = PLL_SSC_DIG_BUS1_get_NCODE_T_BUS(tmp);
	Fcode = PLL_SSC_DIG_BUS1_get_FCODE_T_BUS(tmp);
	//freq = 27 * (Ncode + 3 + (Fcode/2048));
	freq = 27 * (Ncode + 3) + (27 * Fcode / 2048);
	sprintf( msg, "%4d MHz", freq );
	printf("BUS    PLL  = %s\n", msg);
	
	// get BUS PLL MNO value
	tmp = get_PLL_SSC_DIG_BUSH1_reg;
	Ncode = PLL_SSC_DIG_BUSH1_get_NCODE_T_BUS_H(tmp);
	Fcode = PLL_SSC_DIG_BUSH1_get_FCODE_T_BUS_H(tmp);
	//freq = 27 * (Ncode + 3 + (Fcode/2048));
	freq = 27 * (Ncode + 3) + (27 * Fcode / 2048);
	sprintf( msg, "%4d MHz", freq );
	printf("BUS_H  PLL  = %s\n", msg);

	// get GPU PLL MNO value
	tmp = get_PLL_SSC_DIG_GPU1_reg;
	Ncode = PLL_SSC_DIG_GPU1_get_NCODE_T_GPU(tmp);
	Fcode = PLL_SSC_DIG_GPU1_get_FCODE_T_GPU(tmp);
	//freq = 27 * (Ncode + 3 + (Fcode/2048));
	freq = 27 * (Ncode + 3) + (27 * Fcode / 2048);
	sprintf( msg, "%4d MHz", freq );
	printf("GPU    PLL  = %s\n", msg);
	
	// get VODMA PLL MNO value
	// 27MHz*(M+2)/(N+1)/(O+1)
	tmp = get_PLL_VODMA1_reg;
	value_m = PLL_VODMA1_get_REG_PLLVODMA_M(tmp);
	value_n = PLL_VODMA1_get_REG_PLLVODMA_N(tmp);
	value_o = PLL_VODMA1_get_REG_PLLVODMA_O(tmp);
	freq = 27 * (value_m+2) / (value_n+1) / (value_o+1);	
	sprintf( msg, "%4d MHz", freq );
	printf("VODMA  PLL  = %s\n", msg);

	//27MHz*(Ncode+3+Fcode/8192)/(N+1)
#if 0
	tmp = get_PLL_DDR_SSC1_reg;
	Ncode = PLL_DDR_SSC1_get_SSCDDR_N_CODE(tmp);
	Fcode = PLL_DDR_SSC1_get_SSCDDR_F_CODE(tmp);
	tmp = get_PLL_DDR1_reg;
	value_n = PLL_DDR1_get_PLLDDR_PDIV(tmp);
	freq = (27 * (Ncode +3)+ 27*Fcode/8192) / (value_n+1) ;		
	sprintf( msg, "%4d MHz", freq );
	printf("DDR   PLL   = %s\n", msg);
#endif
		
	return 0;
}

void do_bdinfo_spi (void);
static int do_bdinfo_flash (void)
{
#ifdef CONFIG_CMD_SPI_FLASH_DRIVER
	do_bdinfo_spi();
#endif

	return 0;
}


int do_bdinfo(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	int i;
	bd_t *bd = gd->bd;

	if (argc == 2) {
		if (strcmp(argv[1], "pll") == 0) {
			return do_bdinfo_pll();
		}
		else if (strcmp(argv[1], "ddr") == 0) {
			return do_bdinfo_ddr();
		}
		else if (strcmp(argv[1], "dss") == 0) {
			return do_bdinfo_dss();
		}
		else {
			return CMD_RET_USAGE;
		}
	}

	print_num("arch_number",	bd->bi_arch_number);
	print_num("boot_params",	(ulong)bd->bi_boot_params);

	for (i = 0; i < CONFIG_NR_DRAM_BANKS; ++i) {
		print_num("DRAM bank",	i);
		print_num("-> start",	bd->bi_dram[i].start);
		print_num("-> size",	bd->bi_dram[i].size);
	}

#if defined(CONFIG_CMD_NET)
	print_eth(0);
	printf("ip_addr     = %s\n", getenv("ipaddr"));
#endif
	printf("baudrate    = %d bps\n", gd->baudrate);
#if !(defined(CONFIG_SYS_ICACHE_OFF) && defined(CONFIG_SYS_DCACHE_OFF))
	print_num("TLB addr", gd->arch.tlb_addr);
#endif
#if !defined(CONFIG_RTD299X) && !defined(CONFIG_RTD1195) && !defined(CONFIG_RTD1295) && !defined(CONFIG_RTD1395)
	print_num("relocaddr", gd->relocaddr);
	print_num("reloc off", gd->reloc_off);
	print_num("irq_sp", gd->irq_sp);	/* irq stack pointer */
	print_num("sp start ", gd->start_addr_sp);
	print_num("FB base  ", gd->fb_base);
#endif
	/*
	 * TODO: Currently only support for davinci SOC's is added.
	 * Remove this check once all the board implement this.
	 */
#ifdef CONFIG_CLOCKS
	printf("ARM frequency = %ld MHz\n", gd->bd->bi_arm_freq);
	printf("DSP frequency = %ld MHz\n", gd->bd->bi_dsp_freq);
	printf("DDR frequency = %ld MHz\n", gd->bd->bi_ddr_freq);
#endif

	do_bdinfo_pll();
	do_bdinfo_ddr();
	do_bdinfo_flash();
//	do_bdinfo_dss();

	return 0;
}


#elif defined(CONFIG_SH)

int do_bdinfo(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	bd_t *bd = gd->bd;
	print_num("mem start      ",	(ulong)bd->bi_memstart);
	print_lnum("mem size       ",	(u64)bd->bi_memsize);
	print_num("flash start    ",	(ulong)bd->bi_flashstart);
	print_num("flash size     ",	(ulong)bd->bi_flashsize);
	print_num("flash offset   ",	(ulong)bd->bi_flashoffset);

#if defined(CONFIG_CMD_NET)
	print_eth(0);
	printf("ip_addr     = %s\n", getenv("ipaddr"));
#endif
	printf("baudrate    = %u bps\n", gd->baudrate);
	return 0;
}

#elif defined(CONFIG_X86)

int do_bdinfo(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	int i;
	bd_t *bd = gd->bd;

	print_num("boot_params",	(ulong)bd->bi_boot_params);
	print_num("bi_memstart",	bd->bi_memstart);
	print_num("bi_memsize",		bd->bi_memsize);
	print_num("bi_flashstart",	bd->bi_flashstart);
	print_num("bi_flashsize",	bd->bi_flashsize);
	print_num("bi_flashoffset",	bd->bi_flashoffset);
	print_num("bi_sramstart",	bd->bi_sramstart);
	print_num("bi_sramsize",	bd->bi_sramsize);
	print_num("bi_bootflags",	bd->bi_bootflags);
	print_mhz("cpufreq",		bd->bi_intfreq);
	print_mhz("busfreq",		bd->bi_busfreq);

	for (i = 0; i < CONFIG_NR_DRAM_BANKS; ++i) {
		print_num("DRAM bank",	i);
		print_num("-> start",	bd->bi_dram[i].start);
		print_num("-> size",	bd->bi_dram[i].size);
	}

#if defined(CONFIG_CMD_NET)
	print_eth(0);
	printf("ip_addr     = %s\n", getenv("ipaddr"));
	print_mhz("ethspeed",	    bd->bi_ethspeed);
#endif
	printf("baudrate    = %u bps\n", gd->baudrate);

	return 0;
}

#elif defined(CONFIG_SANDBOX)

int do_bdinfo(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	int i;
	bd_t *bd = gd->bd;

	print_num("boot_params", (ulong)bd->bi_boot_params);

	for (i = 0; i < CONFIG_NR_DRAM_BANKS; ++i) {
		print_num("DRAM bank", i);
		print_num("-> start", bd->bi_dram[i].start);
		print_num("-> size", bd->bi_dram[i].size);
	}

#if defined(CONFIG_CMD_NET)
	print_eth(0);
	printf("ip_addr     = %s\n", getenv("ipaddr"));
#endif
#if defined(CONFIG_LCD) || defined(CONFIG_VIDEO)
	print_num("FB base  ", gd->fb_base);
#endif
	return 0;
}

#elif defined(CONFIG_NDS32)

int do_bdinfo(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	int i;
	bd_t *bd = gd->bd;

	print_num("arch_number",	bd->bi_arch_number);
	print_num("boot_params",	(ulong)bd->bi_boot_params);

	for (i = 0; i < CONFIG_NR_DRAM_BANKS; ++i) {
		print_num("DRAM bank",	i);
		print_num("-> start",	bd->bi_dram[i].start);
		print_num("-> size",	bd->bi_dram[i].size);
	}

#if defined(CONFIG_CMD_NET)
	print_eth(0);
	printf("ip_addr     = %s\n", getenv("ipaddr"));
#endif
	printf("baudrate    = %u bps\n", gd->baudrate);

	return 0;
}

#elif defined(CONFIG_OPENRISC)

int do_bdinfo(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	bd_t *bd = gd->bd;

	print_num("mem start",		(ulong)bd->bi_memstart);
	print_lnum("mem size",		(u64)bd->bi_memsize);
	print_num("flash start",	(ulong)bd->bi_flashstart);
	print_num("flash size",		(ulong)bd->bi_flashsize);
	print_num("flash offset",	(ulong)bd->bi_flashoffset);

#if defined(CONFIG_CMD_NET)
	print_eth(0);
	printf("ip_addr     = %s\n", getenv("ipaddr"));
#endif

	printf("baudrate    = %u bps\n", gd->baudrate);

	return 0;
}

#elif defined(CONFIG_ARC)

int do_bdinfo(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	bd_t *bd = gd->bd;

	print_num("mem start",		bd->bi_memstart);
	print_lnum("mem size",		bd->bi_memsize);

#if defined(CONFIG_CMD_NET)
	print_eth(0);
	printf("ip_addr     = %s\n", getenv("ipaddr"));
#endif
	printf("baudrate    = %d bps\n", gd->baudrate);

	return 0;
}

#else
 #error "a case for this architecture does not exist!"
#endif

/* -------------------------------------------------------------------- */

U_BOOT_CMD(
	bdinfo,	1,	1,	do_bdinfo,
	"print Board Info structure",
	""
);
