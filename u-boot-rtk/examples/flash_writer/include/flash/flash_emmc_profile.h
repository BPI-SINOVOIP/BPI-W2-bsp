#ifndef __FLASH_EMMC_PROFILE_H__
#define __FLASH_EMMC_PROFILE_H__

struct mmc_ocr {
    unsigned char start:1;
    unsigned char transmission:1;
    unsigned char check1:6;
    unsigned int  reg;
    unsigned char check2:7;
    unsigned char end:1;
};

struct mmc_cid {
	unsigned int		manfid;
	char			    prod_name[8];
	unsigned int		serial;
	unsigned short		oemid;
	unsigned short		year;
	unsigned char		hwrev;
	unsigned char		fwrev;
	unsigned char		month;
};

struct mmc_csd {
	unsigned char		csd_ver;
	unsigned char		csd_ver2;// from EXT_CSD
	unsigned char		mmca_vsn;
	unsigned short		cmdclass;
	unsigned short		tacc_clks;
	unsigned int		tacc_ns;
	unsigned int		r2w_factor;
	unsigned int		max_dtr;
	unsigned int		read_blkbits;
	unsigned int		write_blkbits;
	unsigned int		capacity;
	unsigned int		read_partial:1,
				        read_misalign:1,
				        write_partial:1,
				        write_misalign:1;
};

struct mmc_ext_csd {
	unsigned char       rev;
	unsigned int		sa_timeout;		/* Units: 100ns */
	unsigned int		hs_max_dtr;
	unsigned int		sectors;
};

//struct sd_scr {
//	unsigned char		sda_vsn;
//	unsigned char		bus_widths;
//#define SD_SCR_BUS_WIDTH_1	(1<<0)
//#define SD_SCR_BUS_WIDTH_4	(1<<2)
//};

struct sd_switch_caps {
	unsigned int		hs_max_dtr;
};

//struct mmc_card {
typedef struct {
	unsigned int		sector_addressing;
	unsigned int		rca;		    /* relative card address of device */
	unsigned int		state;		    /* (our) card state */
#define MMC_STATE_PRESENT	(1<<0)		/* present in sysfs */
#define MMC_STATE_READONLY	(1<<1)		/* card is read-only */
#define MMC_STATE_HIGHSPEED	(1<<2)		/* card is in high speed mode */
#define MMC_STATE_BLOCKADDR	(1<<3)		/* card uses block-addressing */

#define MMC_STATE_ONE_BLK	(1<<4)		/* writting use one block mode */
#define MMC_STATE_IDENT_RDY	(1<<5)		/* for check identify state, */
#define MMC_STATE_CMD24_ERR	(1<<6)		/* for cmd24 error handling */

	UINT32			raw_cid[4];	            /* raw card CID */
	UINT32			raw_csd[4];	            /* raw card CSD */
	//UINT32			raw_scr[2];	            /* raw card SCR */

	struct mmc_ocr		    ocr;		/* operation condition register */
	struct mmc_cid		    cid;		/* card identification */
	struct mmc_csd		    csd;		/* card specific */
	struct mmc_ext_csd	    ext_csd;	/* mmc v4 extended card specific */
	//struct sd_scr		    scr;		/* extra SD information */
	struct sd_switch_caps	sw_caps;	/* switch (CMD6) caps */

}e_device_type;

#define mmc_card_mmc(c)		        ((c)->type == MMC_TYPE_MMC)
#define mmc_card_sd(c)		        ((c)->type == MMC_TYPE_SD)
#define mmc_card_sdio(c)	        ((c)->type == MMC_TYPE_SDIO)

#define mmc_card_present(c)	        ((c)->state & MMC_STATE_PRESENT)
#define mmc_card_readonly(c)	    ((c)->state & MMC_STATE_READONLY)
#define mmc_card_highspeed(c)	    ((c)->state & MMC_STATE_HIGHSPEED)
#define mmc_card_blockaddr(c)	    ((c)->state & MMC_STATE_BLOCKADDR)

#define mmc_card_one_blk(c)	        ((c)->state & MMC_STATE_ONE_BLK)    //liao
#define mmc_card_ident_rdy(c)	    ((c)->state & MMC_STATE_IDENT_RDY)  //liao
#define mmc_card_cmd24_err(c)	    ((c)->state & MMC_STATE_CMD24_ERR)  //liao

#define mmc_card_set_present(c)	    ((c)->state |= MMC_STATE_PRESENT)
#define mmc_card_set_readonly(c)    ((c)->state |= MMC_STATE_READONLY)
#define mmc_card_set_highspeed(c)   ((c)->state |= MMC_STATE_HIGHSPEED)
#define mmc_card_set_blockaddr(c)   ((c)->state |= MMC_STATE_BLOCKADDR)

#define mmc_card_set_one_blk(c)	    ((c)->state |= MMC_STATE_ONE_BLK)   //liao
#define mmc_card_set_ident_rdy(c)	((c)->state |= MMC_STATE_IDENT_RDY) //liao
#define mmc_card_set_cmd24_err(c)	((c)->state |= MMC_STATE_CMD24_ERR) //liao

#endif /* __FLASH_EMMC_PROFILE_H__ */
