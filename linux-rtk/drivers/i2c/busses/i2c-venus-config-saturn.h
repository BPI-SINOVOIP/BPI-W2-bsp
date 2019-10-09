#ifndef __I2C_VENUS_CONFIG_SATURN_H__
#define __I2C_VENUS_CONFIG_SATURN_H__

#include "platform.h"

#define MODLE_NAME        "Saturn"
#define I2C_PHY_CNT       7

#ifdef CONFIG_I2C_RTK
#include "mars.h"
#include "saturn.h"
#endif

//////////////////////////////////////////////////////////////////////////////////////////
// I2C 0
//////////////////////////////////////////////////////////////////////////////////////////

static const venus_i2c_reg_map saturn_i2c0_reg = 
{       
    .I2C_ISR           		= ISO_IO_PORT_BASE + MARS_ISO_ISR,
    .I2C_INT           		= MARS_ISO_ISR_I2C0,
    .IC_CON            		= ISO_IO_PORT_BASE + MARS_ISO_IC0_CON,
    .IC_TAR            		= ISO_IO_PORT_BASE + MARS_ISO_IC0_TAR,
    .IC_SAR            		= ISO_IO_PORT_BASE + MARS_ISO_IC0_SAR,
    .IC_HS_MADDR       		= ISO_IO_PORT_BASE + MARS_ISO_IC0_HS_MADDR,
    .IC_DATA_CMD       		= ISO_IO_PORT_BASE + MARS_ISO_IC0_DATA_CMD,
    .IC_SS_SCL_HCNT    	= ISO_IO_PORT_BASE + MARS_ISO_IC0_SS_SCL_HCNT,
    .IC_SS_SCL_LCNT    	= ISO_IO_PORT_BASE + MARS_ISO_IC0_SS_SCL_LCNT,
    .IC_FS_SCL_HCNT    	= ISO_IO_PORT_BASE + MARS_ISO_IC0_FS_SCL_HCNT,
    .IC_FS_SCL_LCNT    		= ISO_IO_PORT_BASE + MARS_ISO_IC0_FS_SCL_LCNT,
    .IC_INTR_STAT      		= ISO_IO_PORT_BASE + MARS_ISO_IC0_INTR_STAT,
    .IC_INTR_MASK      		= ISO_IO_PORT_BASE + MARS_ISO_IC0_INTR_MASK,
    .IC_RAW_INTR_STAT  	= ISO_IO_PORT_BASE + MARS_ISO_IC0_RAW_INTR_STAT,
    .IC_RX_TL          		= ISO_IO_PORT_BASE + MARS_ISO_IC0_RX_TL,
    .IC_TX_TL          		= ISO_IO_PORT_BASE + MARS_ISO_IC0_TX_TL,
    .IC_CLR_INTR       		= ISO_IO_PORT_BASE + MARS_ISO_IC0_CLR_INTR,
    .IC_CLR_RX_UNDER   	= ISO_IO_PORT_BASE + MARS_ISO_IC0_CLR_RX_UNDER,
    .IC_CLR_RX_OVER    	= ISO_IO_PORT_BASE + MARS_ISO_IC0_CLR_RX_OVER,
    .IC_CLR_TX_OVER    	= ISO_IO_PORT_BASE + MARS_ISO_IC0_CLR_TX_OVER,
    .IC_CLR_RD_REQ     		= ISO_IO_PORT_BASE + MARS_ISO_IC0_CLR_RD_REQ,
    .IC_CLR_TX_ABRT    	= ISO_IO_PORT_BASE + MARS_ISO_IC0_CLR_TX_ABRT,
    .IC_CLR_RX_DONE    	= ISO_IO_PORT_BASE + MARS_ISO_IC0_CLR_RX_DONE,
    .IC_CLR_ACTIVITY   		= ISO_IO_PORT_BASE + MARS_ISO_IC0_CLR_ACTIVITY,
    .IC_CLR_STOP_DET   	= ISO_IO_PORT_BASE + MARS_ISO_IC0_CLR_STOP_DET,
    .IC_CLR_START_DET  	= ISO_IO_PORT_BASE + MARS_ISO_IC0_CLR_START_DET,
    .IC_CLR_GEN_CALL   	= ISO_IO_PORT_BASE + MARS_ISO_IC0_CLR_GEN_CALL,
    .IC_ENABLE         		= ISO_IO_PORT_BASE + MARS_ISO_IC0_ENABLE,
    .IC_STATUS         		= ISO_IO_PORT_BASE + MARS_ISO_IC0_STATUS,
    .IC_TXFLR          		= ISO_IO_PORT_BASE + MARS_ISO_IC0_TXFLR,
    .IC_RXFLR          		= ISO_IO_PORT_BASE + MARS_ISO_IC0_RXFLR,
    .IC_SDA_HOLD          	= ISO_IO_PORT_BASE + 	MARS_ISO_IC0_SDA_HOLD,
    .IC_TX_ABRT_SOURCE 	= ISO_IO_PORT_BASE + MARS_ISO_IC0_TX_ABRT_SOURCE,
    .IC_SLV_DATA_NACK_ONLY= ISO_IO_PORT_BASE + MARS_ISO_IC0_SLV_DATA_NACK_ONLY,
    .IC_DMA_CR         		= ISO_IO_PORT_BASE + MARS_ISO_IC0_DMA_CR,
    .IC_DMA_TDLR       		= ISO_IO_PORT_BASE + MARS_ISO_IC0_DMA_TDLR,
    .IC_DMA_RDLR       		= ISO_IO_PORT_BASE + MARS_ISO_IC0_DMA_RDLR,
    .IC_SDA_SETUP          	= ISO_IO_PORT_BASE + MARS_ISO_IC0_SDA_SETUP,
    .IC_ACK_GENERAL_CALL 	= ISO_IO_PORT_BASE + MARS_ISO_IC0_ACK_GENERAL_CALL,
    .IC_ENABLE_STATUS       	= ISO_IO_PORT_BASE + MARS_ISO_IC0_ENABLE_STATUS,
    .IC_COMP_PARAM_1  	= ISO_IO_PORT_BASE + MARS_ISO_IC0_COMP_PARAM_1,
    .IC_COMP_VERSION   	= ISO_IO_PORT_BASE + MARS_ISO_IC0_COMP_VERSION,
    .IC_COMP_TYPE      		= ISO_IO_PORT_BASE + MARS_ISO_IC0_COMP_TYPE,
    .IC_SDA_DEL        		= ISO_IO_PORT_BASE + SATURN_ISO_I2C0_SDA_DEL,          // for Saturn Only
};

static const venus_i2c_port saturn_i2c0_port[] = 
{
    {
        // PHY1 SRC-0
        .gpio_mapped   = 0, 
        .g2c_scl       = venus_gpio_id(MIS_GPIO, 61),
        .g2c_sda       = venus_gpio_id(MIS_GPIO, 62),
        .input_mux[0]  = {0},   
        .input_mux[1]  = {0},                   
        .pin_mux[0]    = {0xFE007310, 0xF<<24, 0x5<<24, 0},
        .pin_mux[1]    = {0},                
    },    
};
    



//////////////////////////////////////////////////////////////////////////////////////////
// I2C 1
//////////////////////////////////////////////////////////////////////////////////////////

static const venus_i2c_reg_map saturn_i2c1_reg = 
{       
    .I2C_ISR           		= MISC_IO_PORT_BASE + MARS_MIS_ISR,
    .I2C_INT           		= MARS_MIS_ISR_I2C1,
    .IC_CON            		= MISC_IO_PORT_BASE + MARS_MIS_IC1_CON,
    .IC_TAR            		= MISC_IO_PORT_BASE + MARS_MIS_IC1_TAR,
    .IC_SAR            		= MISC_IO_PORT_BASE + MARS_MIS_IC1_SAR,
    .IC_HS_MADDR       		= MISC_IO_PORT_BASE + MARS_MIS_IC1_HS_MADDR,
    .IC_DATA_CMD       		= MISC_IO_PORT_BASE + MARS_MIS_IC1_DATA_CMD,
    .IC_SS_SCL_HCNT    	= MISC_IO_PORT_BASE + MARS_MIS_IC1_SS_SCL_HCNT,
    .IC_SS_SCL_LCNT    	= MISC_IO_PORT_BASE + MARS_MIS_IC1_SS_SCL_LCNT,
    .IC_FS_SCL_HCNT    	= MISC_IO_PORT_BASE + MARS_MIS_IC1_FS_SCL_HCNT,
    .IC_FS_SCL_LCNT    		= MISC_IO_PORT_BASE + MARS_MIS_IC1_FS_SCL_LCNT,
    .IC_INTR_STAT      		= MISC_IO_PORT_BASE + MARS_MIS_IC1_INTR_STAT,
    .IC_INTR_MASK      		= MISC_IO_PORT_BASE + MARS_MIS_IC1_INTR_MASK,
    .IC_RAW_INTR_STAT  	= MISC_IO_PORT_BASE + MARS_MIS_IC1_RAW_INTR_STAT,
    .IC_RX_TL          		= MISC_IO_PORT_BASE + MARS_MIS_IC1_RX_TL,
    .IC_TX_TL          		= MISC_IO_PORT_BASE + MARS_MIS_IC1_TX_TL,
    .IC_CLR_INTR       		= MISC_IO_PORT_BASE + MARS_MIS_IC1_CLR_INTR,
    .IC_CLR_RX_UNDER   	= MISC_IO_PORT_BASE + MARS_MIS_IC1_CLR_RX_UNDER,
    .IC_CLR_RX_OVER    	= MISC_IO_PORT_BASE + MARS_MIS_IC1_CLR_RX_OVER,
    .IC_CLR_TX_OVER    	= MISC_IO_PORT_BASE + MARS_MIS_IC1_CLR_TX_OVER,
    .IC_CLR_RD_REQ     		= MISC_IO_PORT_BASE + MARS_MIS_IC1_CLR_RD_REQ,
    .IC_CLR_TX_ABRT    	= MISC_IO_PORT_BASE + MARS_MIS_IC1_CLR_TX_ABRT,
    .IC_CLR_RX_DONE    	= MISC_IO_PORT_BASE + MARS_MIS_IC1_CLR_RX_DONE,
    .IC_CLR_ACTIVITY   		= MISC_IO_PORT_BASE + MARS_MIS_IC1_CLR_ACTIVITY,
    .IC_CLR_STOP_DET   	= MISC_IO_PORT_BASE + MARS_MIS_IC1_CLR_STOP_DET,
    .IC_CLR_START_DET  	= MISC_IO_PORT_BASE + MARS_MIS_IC1_CLR_START_DET,
    .IC_CLR_GEN_CALL   	= MISC_IO_PORT_BASE + MARS_MIS_IC1_CLR_GEN_CALL,
    .IC_ENABLE         		= MISC_IO_PORT_BASE + MARS_MIS_IC1_ENABLE,
    .IC_STATUS         		= MISC_IO_PORT_BASE + MARS_MIS_IC1_STATUS,
    .IC_TXFLR          		= MISC_IO_PORT_BASE + MARS_MIS_IC1_TXFLR,
    .IC_RXFLR          		= MISC_IO_PORT_BASE + MARS_MIS_IC1_RXFLR,
    .IC_SDA_HOLD          	= MISC_IO_PORT_BASE + 	MARS_MIS_IC1_SDA_HOLD,
    .IC_TX_ABRT_SOURCE 	= MISC_IO_PORT_BASE + MARS_MIS_IC1_TX_ABRT_SOURCE,
    .IC_SLV_DATA_NACK_ONLY= MISC_IO_PORT_BASE + MARS_MIS_IC1_SLV_DATA_NACK_ONLY,
    .IC_DMA_CR         		= MISC_IO_PORT_BASE + MARS_MIS_IC1_DMA_CR,
    .IC_DMA_TDLR       		= MISC_IO_PORT_BASE + MARS_MIS_IC1_DMA_TDLR,
    .IC_DMA_RDLR       		= MISC_IO_PORT_BASE + MARS_MIS_IC1_DMA_RDLR,
    .IC_SDA_SETUP          	= MISC_IO_PORT_BASE + MARS_MIS_IC1_SDA_SETUP,
    .IC_ACK_GENERAL_CALL 	= MISC_IO_PORT_BASE + MARS_MIS_IC1_ACK_GENERAL_CALL,
    .IC_ENABLE_STATUS       	= MISC_IO_PORT_BASE + MARS_MIS_IC1_ENABLE_STATUS,
    .IC_COMP_PARAM_1  	= MISC_IO_PORT_BASE + MARS_MIS_IC1_COMP_PARAM_1,
    .IC_COMP_VERSION   	= MISC_IO_PORT_BASE + MARS_MIS_IC1_COMP_VERSION,
    .IC_COMP_TYPE      		= MISC_IO_PORT_BASE + MARS_MIS_IC1_COMP_TYPE,
    .IC_SDA_DEL        		= MISC_IO_PORT_BASE + SATURN_MIS_I2C1_SDA_DEL,          // for Saturn Only
};

static const venus_i2c_port saturn_i2c1_port[] = 
{
    {
        // PHY1 SRC-0
        .gpio_mapped   = 0, 
        .g2c_scl       = 51,//venus_gpio_id(MIS_GPIO, 61),
        .g2c_sda       = 52,//venus_gpio_id(MIS_GPIO, 62),
        .input_mux[0]  = {0},   
        .input_mux[1]  = {0},                   
#ifdef CONFIG_MACH_RTK1192
        .pin_mux[0]    = {0xFE01A90C, 0xF<<0, 0x5<<0, 0},
#else
        .pin_mux[0]    = {0xFE00036c, 0xF<<0, 0x5<<0, 0},
#endif
        .pin_mux[1]    = {0},                
    },    
};
    
    
//////////////////////////////////////////////////////////////////////////////////////////
// I2C 2
//////////////////////////////////////////////////////////////////////////////////////////    
static const venus_i2c_reg_map saturn_i2c2_reg = 
{    
    .I2C_ISR           = MISC_IO_PORT_BASE + MARS_MIS_ISR,
    .I2C_INT           = MARS_MIS_ISR_I2C2,
    .IC_CON            = MISC_IO_PORT_BASE + MARS_MIS_IC2_CON,
    .IC_TAR            = MISC_IO_PORT_BASE + MARS_MIS_IC2_TAR,
    .IC_SAR            = MISC_IO_PORT_BASE + MARS_MIS_IC2_SAR,
    .IC_HS_MADDR       = MISC_IO_PORT_BASE + MARS_MIS_IC2_HS_MADDR,
    .IC_DATA_CMD       = MISC_IO_PORT_BASE + MARS_MIS_IC2_DATA_CMD,
    .IC_SS_SCL_HCNT    = MISC_IO_PORT_BASE + MARS_MIS_IC2_SS_SCL_HCNT,
    .IC_SS_SCL_LCNT    = MISC_IO_PORT_BASE + MARS_MIS_IC2_SS_SCL_LCNT,
    .IC_FS_SCL_HCNT    = MISC_IO_PORT_BASE + MARS_MIS_IC2_FS_SCL_HCNT,
    .IC_FS_SCL_LCNT    = MISC_IO_PORT_BASE + MARS_MIS_IC2_FS_SCL_LCNT,
    .IC_INTR_STAT      = MISC_IO_PORT_BASE + MARS_MIS_IC2_INTR_STAT,
    .IC_INTR_MASK      = MISC_IO_PORT_BASE + MARS_MIS_IC2_INTR_MASK,
    .IC_RAW_INTR_STAT  = MISC_IO_PORT_BASE + MARS_MIS_IC2_RAW_INTR_STAT,
    .IC_RX_TL          = MISC_IO_PORT_BASE + MARS_MIS_IC2_RX_TL,
    .IC_TX_TL          = MISC_IO_PORT_BASE + MARS_MIS_IC2_TX_TL,
    .IC_CLR_INTR       = MISC_IO_PORT_BASE + MARS_MIS_IC2_CLR_INTR,
    .IC_CLR_RX_UNDER   = MISC_IO_PORT_BASE + MARS_MIS_IC2_CLR_RX_UNDER,
    .IC_CLR_RX_OVER    = MISC_IO_PORT_BASE + MARS_MIS_IC2_CLR_RX_OVER,
    .IC_CLR_TX_OVER    = MISC_IO_PORT_BASE + MARS_MIS_IC2_CLR_TX_OVER,
    .IC_CLR_RD_REQ     = MISC_IO_PORT_BASE + MARS_MIS_IC2_CLR_RD_REQ,
    .IC_CLR_TX_ABRT    = MISC_IO_PORT_BASE + MARS_MIS_IC2_CLR_TX_ABRT,
    .IC_CLR_RX_DONE    = MISC_IO_PORT_BASE + MARS_MIS_IC2_CLR_RX_DONE,
    .IC_CLR_ACTIVITY   = MISC_IO_PORT_BASE + MARS_MIS_IC2_CLR_ACTIVITY,
    .IC_CLR_STOP_DET   = MISC_IO_PORT_BASE + MARS_MIS_IC2_CLR_STOP_DET,
    .IC_CLR_START_DET  = MISC_IO_PORT_BASE + MARS_MIS_IC2_CLR_START_DET,
    .IC_CLR_GEN_CALL   = MISC_IO_PORT_BASE + MARS_MIS_IC2_CLR_GEN_CALL,
    .IC_ENABLE         = MISC_IO_PORT_BASE + MARS_MIS_IC2_ENABLE,
    .IC_STATUS         = MISC_IO_PORT_BASE + MARS_MIS_IC2_STATUS,
    .IC_TXFLR          = MISC_IO_PORT_BASE + MARS_MIS_IC2_TXFLR,
    .IC_RXFLR          = MISC_IO_PORT_BASE + MARS_MIS_IC2_RXFLR,
    .IC_SDA_HOLD          = MISC_IO_PORT_BASE + 	MARS_MIS_IC2_SDA_HOLD,
    .IC_TX_ABRT_SOURCE = MISC_IO_PORT_BASE + MARS_MIS_IC2_TX_ABRT_SOURCE,
    .IC_SLV_DATA_NACK_ONLY          = MISC_IO_PORT_BASE + MARS_MIS_IC2_SLV_DATA_NACK_ONLY,
    .IC_DMA_CR         = MISC_IO_PORT_BASE + MARS_MIS_IC2_DMA_CR,
    .IC_DMA_TDLR       = MISC_IO_PORT_BASE + MARS_MIS_IC2_DMA_TDLR,
    .IC_DMA_RDLR       = MISC_IO_PORT_BASE + MARS_MIS_IC2_DMA_RDLR,
    .IC_SDA_SETUP          = MISC_IO_PORT_BASE + MARS_MIS_IC2_SDA_SETUP,
    .IC_ACK_GENERAL_CALL          = MISC_IO_PORT_BASE + MARS_MIS_IC2_ACK_GENERAL_CALL,
    .IC_ENABLE_STATUS          = MISC_IO_PORT_BASE + MARS_MIS_IC2_ENABLE_STATUS,
    .IC_COMP_PARAM_1   = MISC_IO_PORT_BASE + MARS_MIS_IC2_COMP_PARAM_1,
    .IC_COMP_VERSION   = MISC_IO_PORT_BASE + MARS_MIS_IC2_COMP_VERSION,
    .IC_COMP_TYPE      = MISC_IO_PORT_BASE + MARS_MIS_IC2_COMP_TYPE,
    .IC_SDA_DEL        = MISC_IO_PORT_BASE + SATURN_MIS_I2C2_SDA_DEL,          // for Saturn Only
};  
              
static const venus_i2c_port saturn_i2c2_port[] = 
{
    {
        // PHY2 SRC-0
        .gpio_mapped   = 0, 
        .g2c_scl       = venus_gpio_id(MIS_GPIO, 63),
        .g2c_sda       = venus_gpio_id(MIS_GPIO, 64),
        .input_mux[0]  = {0},   
        .input_mux[1]  = {0},                   
#ifdef CONFIG_MACH_RTK1192
        .pin_mux[0]    = {0xFE01A908, 0x33<<18, 0x33<<18, 0x22<<18},
#else
        .pin_mux[0]    = {0xFE000368, 0x33<<18, 0x33<<18, 0x22<<18},
#endif
        .pin_mux[1]    = {0},                
    },    
};                                    

 
//////////////////////////////////////////////////////////////////////////////////////////
// I2C 3
//////////////////////////////////////////////////////////////////////////////////////////    
static const venus_i2c_reg_map saturn_i2c3_reg = 
{    
    .I2C_ISR           = MISC_IO_PORT_BASE + MARS_MIS_ISR,
    .I2C_INT           = MARS_MIS_ISR_I2C3,
    .IC_CON            = MISC_IO_PORT_BASE + MARS_MIS_IC3_CON,
    .IC_TAR            = MISC_IO_PORT_BASE + MARS_MIS_IC3_TAR,
    .IC_SAR            = MISC_IO_PORT_BASE + MARS_MIS_IC3_SAR,
    .IC_HS_MADDR       = MISC_IO_PORT_BASE + MARS_MIS_IC3_HS_MADDR,
    .IC_DATA_CMD       = MISC_IO_PORT_BASE + MARS_MIS_IC3_DATA_CMD,
    .IC_SS_SCL_HCNT    = MISC_IO_PORT_BASE + MARS_MIS_IC3_SS_SCL_HCNT,
    .IC_SS_SCL_LCNT    = MISC_IO_PORT_BASE + MARS_MIS_IC3_SS_SCL_LCNT,
    .IC_FS_SCL_HCNT    = MISC_IO_PORT_BASE + MARS_MIS_IC3_FS_SCL_HCNT,
    .IC_FS_SCL_LCNT    = MISC_IO_PORT_BASE + MARS_MIS_IC3_FS_SCL_LCNT,
    .IC_INTR_STAT      = MISC_IO_PORT_BASE + MARS_MIS_IC3_INTR_STAT,
    .IC_INTR_MASK      = MISC_IO_PORT_BASE + MARS_MIS_IC3_INTR_MASK,
    .IC_RAW_INTR_STAT  = MISC_IO_PORT_BASE + MARS_MIS_IC3_RAW_INTR_STAT,
    .IC_RX_TL          = MISC_IO_PORT_BASE + MARS_MIS_IC3_RX_TL,
    .IC_TX_TL          = MISC_IO_PORT_BASE + MARS_MIS_IC3_TX_TL,
    .IC_CLR_INTR       = MISC_IO_PORT_BASE + MARS_MIS_IC3_CLR_INTR,
    .IC_CLR_RX_UNDER   = MISC_IO_PORT_BASE + MARS_MIS_IC3_CLR_RX_UNDER,
    .IC_CLR_RX_OVER    = MISC_IO_PORT_BASE + MARS_MIS_IC3_CLR_RX_OVER,
    .IC_CLR_TX_OVER    = MISC_IO_PORT_BASE + MARS_MIS_IC3_CLR_TX_OVER,
    .IC_CLR_RD_REQ     = MISC_IO_PORT_BASE + MARS_MIS_IC3_CLR_RD_REQ,
    .IC_CLR_TX_ABRT    = MISC_IO_PORT_BASE + MARS_MIS_IC3_CLR_TX_ABRT,
    .IC_CLR_RX_DONE    = MISC_IO_PORT_BASE + MARS_MIS_IC3_CLR_RX_DONE,
    .IC_CLR_ACTIVITY   = MISC_IO_PORT_BASE + MARS_MIS_IC3_CLR_ACTIVITY,
    .IC_CLR_STOP_DET   = MISC_IO_PORT_BASE + MARS_MIS_IC3_CLR_STOP_DET,
    .IC_CLR_START_DET  = MISC_IO_PORT_BASE + MARS_MIS_IC3_CLR_START_DET,
    .IC_CLR_GEN_CALL   = MISC_IO_PORT_BASE + MARS_MIS_IC3_CLR_GEN_CALL,
    .IC_ENABLE         = MISC_IO_PORT_BASE + MARS_MIS_IC3_ENABLE,
    .IC_STATUS         = MISC_IO_PORT_BASE + MARS_MIS_IC3_STATUS,
    .IC_TXFLR          = MISC_IO_PORT_BASE + MARS_MIS_IC3_TXFLR,
    .IC_RXFLR          = MISC_IO_PORT_BASE + MARS_MIS_IC3_RXFLR,
    .IC_SDA_HOLD          = MISC_IO_PORT_BASE + 	MARS_MIS_IC3_SDA_HOLD,
    .IC_TX_ABRT_SOURCE = MISC_IO_PORT_BASE + MARS_MIS_IC3_TX_ABRT_SOURCE,
    .IC_SLV_DATA_NACK_ONLY          = MISC_IO_PORT_BASE + MARS_MIS_IC3_SLV_DATA_NACK_ONLY,
    .IC_DMA_CR         = MISC_IO_PORT_BASE + MARS_MIS_IC3_DMA_CR,
    .IC_DMA_TDLR       = MISC_IO_PORT_BASE + MARS_MIS_IC3_DMA_TDLR,
    .IC_DMA_RDLR       = MISC_IO_PORT_BASE + MARS_MIS_IC3_DMA_RDLR,
    .IC_SDA_SETUP          = MISC_IO_PORT_BASE + MARS_MIS_IC3_SDA_SETUP,
    .IC_ACK_GENERAL_CALL          = MISC_IO_PORT_BASE + MARS_MIS_IC3_ACK_GENERAL_CALL,
    .IC_ENABLE_STATUS          = MISC_IO_PORT_BASE + MARS_MIS_IC3_ENABLE_STATUS,
    .IC_COMP_PARAM_1   = MISC_IO_PORT_BASE + MARS_MIS_IC3_COMP_PARAM_1,
    .IC_COMP_VERSION   = MISC_IO_PORT_BASE + MARS_MIS_IC3_COMP_VERSION,
    .IC_COMP_TYPE      = MISC_IO_PORT_BASE + MARS_MIS_IC3_COMP_TYPE,
    .IC_SDA_DEL        = MISC_IO_PORT_BASE + SATURN_MIS_I2C3_SDA_DEL,          // for Saturn Only
};  
              
static const venus_i2c_port saturn_i2c3_port[] = 
{
    {
        // PHY3 SRC-0
        .gpio_mapped   = 1, //0, 
        .g2c_scl       = 42, //venus_gpio_id(MIS_GPIO, 63),
        .g2c_sda       = 40, //venus_gpio_id(MIS_GPIO, 64),
        .input_mux[0]  = {0},   
        .input_mux[1]  = {0},                   
#ifdef CONFIG_MACH_RTK1192
        .pin_mux[0]    = {0xFE01A908, 0x33<<16, 0x33<<16, 0x22<<16},
#else
        .pin_mux[0]    = {0xFE000368, 0x33<<16, 0x33<<16, 0x22<<16},
#endif
        .pin_mux[1]    = {0},                
    },    
};                                    

 
//////////////////////////////////////////////////////////////////////////////////////////
// I2C 4
//////////////////////////////////////////////////////////////////////////////////////////    
static const venus_i2c_reg_map saturn_i2c4_reg = 
{    
    .I2C_ISR           = MISC_IO_PORT_BASE + MARS_MIS_ISR,
    .I2C_INT           = MARS_MIS_ISR_I2C4,
    .IC_CON            = MISC_IO_PORT_BASE + MARS_MIS_IC4_CON,
    .IC_TAR            = MISC_IO_PORT_BASE + MARS_MIS_IC4_TAR,
    .IC_SAR            = MISC_IO_PORT_BASE + MARS_MIS_IC4_SAR,
    .IC_HS_MADDR       = MISC_IO_PORT_BASE + MARS_MIS_IC4_HS_MADDR,
    .IC_DATA_CMD       = MISC_IO_PORT_BASE + MARS_MIS_IC4_DATA_CMD,
    .IC_SS_SCL_HCNT    = MISC_IO_PORT_BASE + MARS_MIS_IC4_SS_SCL_HCNT,
    .IC_SS_SCL_LCNT    = MISC_IO_PORT_BASE + MARS_MIS_IC4_SS_SCL_LCNT,
    .IC_FS_SCL_HCNT    = MISC_IO_PORT_BASE + MARS_MIS_IC4_FS_SCL_HCNT,
    .IC_FS_SCL_LCNT    = MISC_IO_PORT_BASE + MARS_MIS_IC4_FS_SCL_LCNT,
    .IC_INTR_STAT      = MISC_IO_PORT_BASE + MARS_MIS_IC4_INTR_STAT,
    .IC_INTR_MASK      = MISC_IO_PORT_BASE + MARS_MIS_IC4_INTR_MASK,
    .IC_RAW_INTR_STAT  = MISC_IO_PORT_BASE + MARS_MIS_IC4_RAW_INTR_STAT,
    .IC_RX_TL          = MISC_IO_PORT_BASE + MARS_MIS_IC4_RX_TL,
    .IC_TX_TL          = MISC_IO_PORT_BASE + MARS_MIS_IC4_TX_TL,
    .IC_CLR_INTR       = MISC_IO_PORT_BASE + MARS_MIS_IC4_CLR_INTR,
    .IC_CLR_RX_UNDER   = MISC_IO_PORT_BASE + MARS_MIS_IC4_CLR_RX_UNDER,
    .IC_CLR_RX_OVER    = MISC_IO_PORT_BASE + MARS_MIS_IC4_CLR_RX_OVER,
    .IC_CLR_TX_OVER    = MISC_IO_PORT_BASE + MARS_MIS_IC4_CLR_TX_OVER,
    .IC_CLR_RD_REQ     = MISC_IO_PORT_BASE + MARS_MIS_IC4_CLR_RD_REQ,
    .IC_CLR_TX_ABRT    = MISC_IO_PORT_BASE + MARS_MIS_IC4_CLR_TX_ABRT,
    .IC_CLR_RX_DONE    = MISC_IO_PORT_BASE + MARS_MIS_IC4_CLR_RX_DONE,
    .IC_CLR_ACTIVITY   = MISC_IO_PORT_BASE + MARS_MIS_IC4_CLR_ACTIVITY,
    .IC_CLR_STOP_DET   = MISC_IO_PORT_BASE + MARS_MIS_IC4_CLR_STOP_DET,
    .IC_CLR_START_DET  = MISC_IO_PORT_BASE + MARS_MIS_IC4_CLR_START_DET,
    .IC_CLR_GEN_CALL   = MISC_IO_PORT_BASE + MARS_MIS_IC4_CLR_GEN_CALL,
    .IC_ENABLE         = MISC_IO_PORT_BASE + MARS_MIS_IC4_ENABLE,
    .IC_STATUS         = MISC_IO_PORT_BASE + MARS_MIS_IC4_STATUS,
    .IC_TXFLR          = MISC_IO_PORT_BASE + MARS_MIS_IC4_TXFLR,
    .IC_RXFLR          = MISC_IO_PORT_BASE + MARS_MIS_IC4_RXFLR,
    .IC_SDA_HOLD          = MISC_IO_PORT_BASE + 	MARS_MIS_IC4_SDA_HOLD,
    .IC_TX_ABRT_SOURCE = MISC_IO_PORT_BASE + MARS_MIS_IC4_TX_ABRT_SOURCE,
    .IC_SLV_DATA_NACK_ONLY          = MISC_IO_PORT_BASE + MARS_MIS_IC4_SLV_DATA_NACK_ONLY,
    .IC_DMA_CR         = MISC_IO_PORT_BASE + MARS_MIS_IC4_DMA_CR,
    .IC_DMA_TDLR       = MISC_IO_PORT_BASE + MARS_MIS_IC4_DMA_TDLR,
    .IC_DMA_RDLR       = MISC_IO_PORT_BASE + MARS_MIS_IC4_DMA_RDLR,
    .IC_SDA_SETUP          = MISC_IO_PORT_BASE + MARS_MIS_IC4_SDA_SETUP,
    .IC_ACK_GENERAL_CALL          = MISC_IO_PORT_BASE + MARS_MIS_IC4_ACK_GENERAL_CALL,
    .IC_ENABLE_STATUS          = MISC_IO_PORT_BASE + MARS_MIS_IC4_ENABLE_STATUS,
    .IC_COMP_PARAM_1   = MISC_IO_PORT_BASE + MARS_MIS_IC4_COMP_PARAM_1,
    .IC_COMP_VERSION   = MISC_IO_PORT_BASE + MARS_MIS_IC4_COMP_VERSION,
    .IC_COMP_TYPE      = MISC_IO_PORT_BASE + MARS_MIS_IC4_COMP_TYPE,
    .IC_SDA_DEL        = MISC_IO_PORT_BASE + SATURN_MIS_I2C4_SDA_DEL,          // for Saturn Only
};  
              
static const venus_i2c_port saturn_i2c4_port[] = 
{
    {
        // PHY4 SRC-0
        .gpio_mapped   = 0, 
        .g2c_scl       = venus_gpio_id(MIS_GPIO, 63),
        .g2c_sda       = venus_gpio_id(MIS_GPIO, 64),
        .input_mux[0]  = {0},   
        .input_mux[1]  = {0},                   
#ifdef CONFIG_MACH_RTK1192
        .pin_mux[0]    = {0xFE01A90C, 0xF<<4, 0x5<<4, 0},
#else
        .pin_mux[0]    = {0xFE00036c, 0xF<<4, 0x5<<4, 0},
#endif
        .pin_mux[1]    = {0},                
    },    
};                                    

 
//////////////////////////////////////////////////////////////////////////////////////////
// I2C 5
//////////////////////////////////////////////////////////////////////////////////////////    
static const venus_i2c_reg_map saturn_i2c5_reg = 
{    
    .I2C_ISR          		 		= MISC_IO_PORT_BASE + MARS_MIS_ISR,
    .I2C_INT           			= MARS_MIS_ISR_I2C5,
    .IC_CON            			= MISC_IO_PORT_BASE + MARS_MIS_IC5_CON,
    .IC_TAR            			= MISC_IO_PORT_BASE + MARS_MIS_IC5_TAR,
    .IC_SAR            			= MISC_IO_PORT_BASE + MARS_MIS_IC5_SAR,
    .IC_HS_MADDR       			= MISC_IO_PORT_BASE + MARS_MIS_IC5_HS_MADDR,
    .IC_DATA_CMD       			= MISC_IO_PORT_BASE + MARS_MIS_IC5_DATA_CMD,
    .IC_SS_SCL_HCNT    		= MISC_IO_PORT_BASE + MARS_MIS_IC5_SS_SCL_HCNT,
    .IC_SS_SCL_LCNT    		= MISC_IO_PORT_BASE + MARS_MIS_IC5_SS_SCL_LCNT,
    .IC_FS_SCL_HCNT   	 		= MISC_IO_PORT_BASE + MARS_MIS_IC5_FS_SCL_HCNT,
    .IC_FS_SCL_LCNT    			= MISC_IO_PORT_BASE + MARS_MIS_IC5_FS_SCL_LCNT,
    .IC_INTR_STAT      			= MISC_IO_PORT_BASE + MARS_MIS_IC5_INTR_STAT,
    .IC_INTR_MASK      			= MISC_IO_PORT_BASE + MARS_MIS_IC5_INTR_MASK,
    .IC_RAW_INTR_STAT  		= MISC_IO_PORT_BASE + MARS_MIS_IC5_RAW_INTR_STAT,
    .IC_RX_TL          			= MISC_IO_PORT_BASE + MARS_MIS_IC5_RX_TL,
    .IC_TX_TL          			= MISC_IO_PORT_BASE + MARS_MIS_IC5_TX_TL,
    .IC_CLR_INTR       			= MISC_IO_PORT_BASE + MARS_MIS_IC5_CLR_INTR,
    .IC_CLR_RX_UNDER   		= MISC_IO_PORT_BASE + MARS_MIS_IC5_CLR_RX_UNDER,
    .IC_CLR_RX_OVER    		= MISC_IO_PORT_BASE + MARS_MIS_IC5_CLR_RX_OVER,
    .IC_CLR_TX_OVER    		= MISC_IO_PORT_BASE + MARS_MIS_IC5_CLR_TX_OVER,
    .IC_CLR_RD_REQ     			= MISC_IO_PORT_BASE + MARS_MIS_IC5_CLR_RD_REQ,
    .IC_CLR_TX_ABRT    		= MISC_IO_PORT_BASE + MARS_MIS_IC5_CLR_TX_ABRT,
    .IC_CLR_RX_DONE    		= MISC_IO_PORT_BASE + MARS_MIS_IC5_CLR_RX_DONE,
    .IC_CLR_ACTIVITY   			= MISC_IO_PORT_BASE + MARS_MIS_IC5_CLR_ACTIVITY,
    .IC_CLR_STOP_DET   		= MISC_IO_PORT_BASE + MARS_MIS_IC5_CLR_STOP_DET,
    .IC_CLR_START_DET  		= MISC_IO_PORT_BASE + MARS_MIS_IC5_CLR_START_DET,
    .IC_CLR_GEN_CALL   		= MISC_IO_PORT_BASE + MARS_MIS_IC5_CLR_GEN_CALL,
    .IC_ENABLE         			= MISC_IO_PORT_BASE + MARS_MIS_IC5_ENABLE,
    .IC_STATUS         			= MISC_IO_PORT_BASE + MARS_MIS_IC5_STATUS,
    .IC_TXFLR          			= MISC_IO_PORT_BASE + MARS_MIS_IC5_TXFLR,
    .IC_RXFLR          			= MISC_IO_PORT_BASE + MARS_MIS_IC5_RXFLR,
    .IC_SDA_HOLD          		= MISC_IO_PORT_BASE + MARS_MIS_IC5_SDA_HOLD,
    .IC_TX_ABRT_SOURCE 		= MISC_IO_PORT_BASE + MARS_MIS_IC5_TX_ABRT_SOURCE,
    .IC_SLV_DATA_NACK_ONLY   	= MISC_IO_PORT_BASE + MARS_MIS_IC5_SLV_DATA_NACK_ONLY,
    .IC_DMA_CR         			= MISC_IO_PORT_BASE + MARS_MIS_IC5_DMA_CR,
    .IC_DMA_TDLR       			= MISC_IO_PORT_BASE + MARS_MIS_IC5_DMA_TDLR,
    .IC_DMA_RDLR       			= MISC_IO_PORT_BASE + MARS_MIS_IC5_DMA_RDLR,
    .IC_SDA_SETUP          		= MISC_IO_PORT_BASE + MARS_MIS_IC5_SDA_SETUP,
    .IC_ACK_GENERAL_CALL		= MISC_IO_PORT_BASE + MARS_MIS_IC5_ACK_GENERAL_CALL,
    .IC_ENABLE_STATUS 		= MISC_IO_PORT_BASE + MARS_MIS_IC5_ENABLE_STATUS,
    .IC_COMP_PARAM_1   		= MISC_IO_PORT_BASE + MARS_MIS_IC5_COMP_PARAM_1,
    .IC_COMP_VERSION   		= MISC_IO_PORT_BASE + MARS_MIS_IC5_COMP_VERSION,
    .IC_COMP_TYPE      			= MISC_IO_PORT_BASE + MARS_MIS_IC5_COMP_TYPE,
    .IC_SDA_DEL        			= MISC_IO_PORT_BASE + SATURN_MIS_I2C5_SDA_DEL,          // for Saturn Only
};  
              
static const venus_i2c_port saturn_i2c5_port[] = 
{
    {
        // PHY5 SRC-0
        .gpio_mapped   = 0, 
        .g2c_scl       = venus_gpio_id(MIS_GPIO, 63),
        .g2c_sda       = venus_gpio_id(MIS_GPIO, 64),
        .input_mux[0]  = {0},   
        .input_mux[1]  = {0},                   
#ifdef CONFIG_MACH_RTK1192
		.pin_mux[0]    = {0xFE01A90C, 0xF<<8, 0x5<<8, 0},
#else
        .pin_mux[0]    = {0xFE00036c, 0xF<<8, 0x5<<8, 0},
#endif
        .pin_mux[1]    = {0},                
    },    
};                                    



 
//////////////////////////////////////////////////////////////////////////////////////////
// I2C 6
//////////////////////////////////////////////////////////////////////////////////////////    
static const venus_i2c_reg_map saturn_i2c6_reg = 
{    
    .I2C_ISR           = ISO_IO_PORT_BASE + MARS_ISO_ISR,
    .I2C_INT           = MARS_ISO_ISR_I2C6,
    .IC_CON            = ISO_IO_PORT_BASE + MARS_ISO_IC6_CON,
    .IC_TAR            = ISO_IO_PORT_BASE + MARS_ISO_IC6_TAR,
    .IC_SAR            = ISO_IO_PORT_BASE + MARS_ISO_IC6_SAR,
    .IC_HS_MADDR       = ISO_IO_PORT_BASE + MARS_ISO_IC6_HS_MADDR,
    .IC_DATA_CMD       = ISO_IO_PORT_BASE + MARS_ISO_IC6_DATA_CMD,
    .IC_SS_SCL_HCNT    = ISO_IO_PORT_BASE + MARS_ISO_IC6_SS_SCL_HCNT,
    .IC_SS_SCL_LCNT    = ISO_IO_PORT_BASE + MARS_ISO_IC6_SS_SCL_LCNT,
    .IC_FS_SCL_HCNT    = ISO_IO_PORT_BASE + MARS_ISO_IC6_FS_SCL_HCNT,
    .IC_FS_SCL_LCNT    = ISO_IO_PORT_BASE + MARS_ISO_IC6_FS_SCL_LCNT,
    .IC_INTR_STAT      = ISO_IO_PORT_BASE + MARS_ISO_IC6_INTR_STAT,
    .IC_INTR_MASK      = ISO_IO_PORT_BASE + MARS_ISO_IC6_INTR_MASK,
    .IC_RAW_INTR_STAT  = ISO_IO_PORT_BASE + MARS_ISO_IC6_RAW_INTR_STAT,
    .IC_RX_TL          = ISO_IO_PORT_BASE + MARS_ISO_IC6_RX_TL,
    .IC_TX_TL          = ISO_IO_PORT_BASE + MARS_ISO_IC6_TX_TL,
    .IC_CLR_INTR       = ISO_IO_PORT_BASE + MARS_ISO_IC6_CLR_INTR,
    .IC_CLR_RX_UNDER   = ISO_IO_PORT_BASE + MARS_ISO_IC6_CLR_RX_UNDER,
    .IC_CLR_RX_OVER    = ISO_IO_PORT_BASE + MARS_ISO_IC6_CLR_RX_OVER,
    .IC_CLR_TX_OVER    = ISO_IO_PORT_BASE + MARS_ISO_IC6_CLR_TX_OVER,
    .IC_CLR_RD_REQ     = ISO_IO_PORT_BASE + MARS_ISO_IC6_CLR_RD_REQ,
    .IC_CLR_TX_ABRT    = ISO_IO_PORT_BASE + MARS_ISO_IC6_CLR_TX_ABRT,
    .IC_CLR_RX_DONE    = ISO_IO_PORT_BASE + MARS_ISO_IC6_CLR_RX_DONE,
    .IC_CLR_ACTIVITY   = ISO_IO_PORT_BASE + MARS_ISO_IC6_CLR_ACTIVITY,
    .IC_CLR_STOP_DET   = ISO_IO_PORT_BASE + MARS_ISO_IC6_CLR_STOP_DET,
    .IC_CLR_START_DET  = ISO_IO_PORT_BASE + MARS_ISO_IC6_CLR_START_DET,
    .IC_CLR_GEN_CALL   = ISO_IO_PORT_BASE + MARS_ISO_IC6_CLR_GEN_CALL,
    .IC_ENABLE         = ISO_IO_PORT_BASE + MARS_ISO_IC6_ENABLE,
    .IC_STATUS         = ISO_IO_PORT_BASE + MARS_ISO_IC6_STATUS,
    .IC_TXFLR          = ISO_IO_PORT_BASE + MARS_ISO_IC6_TXFLR,
    .IC_RXFLR          = ISO_IO_PORT_BASE + MARS_ISO_IC6_RXFLR,
    .IC_SDA_HOLD          = ISO_IO_PORT_BASE + 	MARS_ISO_IC6_SDA_HOLD,
    .IC_TX_ABRT_SOURCE = ISO_IO_PORT_BASE + MARS_ISO_IC6_TX_ABRT_SOURCE,
    .IC_SLV_DATA_NACK_ONLY          = ISO_IO_PORT_BASE + MARS_ISO_IC6_SLV_DATA_NACK_ONLY,
    .IC_DMA_CR         = ISO_IO_PORT_BASE + MARS_ISO_IC6_DMA_CR,
    .IC_DMA_TDLR       = ISO_IO_PORT_BASE + MARS_ISO_IC6_DMA_TDLR,
    .IC_DMA_RDLR       = ISO_IO_PORT_BASE + MARS_ISO_IC6_DMA_RDLR,
    .IC_SDA_SETUP          = ISO_IO_PORT_BASE + MARS_ISO_IC6_SDA_SETUP,
    .IC_ACK_GENERAL_CALL          = ISO_IO_PORT_BASE + MARS_ISO_IC6_ACK_GENERAL_CALL,
    .IC_ENABLE_STATUS          = ISO_IO_PORT_BASE + MARS_ISO_IC6_ENABLE_STATUS,
    .IC_COMP_PARAM_1   = ISO_IO_PORT_BASE + MARS_ISO_IC6_COMP_PARAM_1,
    .IC_COMP_VERSION   = ISO_IO_PORT_BASE + MARS_ISO_IC6_COMP_VERSION,
    .IC_COMP_TYPE      = ISO_IO_PORT_BASE + MARS_ISO_IC6_COMP_TYPE,
    .IC_SDA_DEL        = ISO_IO_PORT_BASE + SATURN_ISO_I2C6_SDA_DEL,          // for Saturn Only
};  
              
static const venus_i2c_port saturn_i2c6_port[] = 
{
    {
        // PHY5 SRC-0
        .gpio_mapped   = 0, 
        .g2c_scl       = venus_gpio_id(MIS_GPIO, 63),
        .g2c_sda       = venus_gpio_id(MIS_GPIO, 64),
        .input_mux[0]  = {0},   
        .input_mux[1]  = {0},                   
        .pin_mux[0]    = {0xFE007314, 0xF<<0, 0x5<<0, 0},
        .pin_mux[1]    = {0},                
    },    
};                                    




static venus_i2c_phy i2c_phy[] = 
{    
    { &saturn_i2c0_reg, sizeof(saturn_i2c0_port)/sizeof(venus_i2c_port), saturn_i2c0_port},
    { &saturn_i2c1_reg, sizeof(saturn_i2c1_port)/sizeof(venus_i2c_port), saturn_i2c1_port},
    { &saturn_i2c2_reg, sizeof(saturn_i2c2_port)/sizeof(venus_i2c_port), saturn_i2c2_port},
    { &saturn_i2c3_reg, sizeof(saturn_i2c3_port)/sizeof(venus_i2c_port), saturn_i2c3_port},
    { &saturn_i2c4_reg, sizeof(saturn_i2c4_port)/sizeof(venus_i2c_port), saturn_i2c4_port},
    { &saturn_i2c5_reg, sizeof(saturn_i2c5_port)/sizeof(venus_i2c_port), saturn_i2c5_port},
    { &saturn_i2c6_reg, sizeof(saturn_i2c6_port)/sizeof(venus_i2c_port), saturn_i2c6_port},
};
               

#endif //__I2C_VENUS_CONFIG_SATURN_H__
