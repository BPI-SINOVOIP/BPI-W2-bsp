#ifndef __TSIO_H__
#define __TSIO_H__

#define TSIO_400MBPS 3
#define TSIO_200MBPS 2
#define TSIO_100MBPS 1
#define TSIO_50MBPS  0
#define TSIO_LINK_UP    (1<<10)

#define TSIO_H_QUEUE  0
#define TSIO_M_QUEUE  1
#define TSIO_L_QUEUE  2

#define TSIO_TS       0
#define TSIO_BLK      1
#define TSIO_CCP_TS   2
#define TSIO_CCP_BLK  3
#define TSIO_CC       4

#define TSIO_START_TX     (1<<9)
#define TSIO_TX_DONE      (1<<10)
#define TSIO_RX_DONE      (1<<10)
#define TSIO_RX_ERR       (1<<11)

#define TSIO_REG_BASE     0x98019000
#define TSIO_CRTL         0x000
#define TSIO_LINK_STATE   0x010

#define TSIO_PKT          0x044
#define TSIO_CCTX         0x048
#define TSIO_CCTX_IDX     0x04C
#define TSIO_CCTX_CRTL    0x050
#define TSIO_CCRX         0x054
#define TSIO_CCRX_IDX     0x058
#define TSIO_CCRX_CRTL    0x05C

#define TSIO_FIFO_H_BASE  0x014
#define TSIO_FIFO_H_LIMIT 0x018
#define TSIO_FIFO_M_BASE  0x01C
#define TSIO_FIFO_M_LIMIT 0x020
#define TSIO_FIFO_L_BASE  0x024
#define TSIO_FIFO_L_LIMIT 0x028

#define TSIO_FIFO_H_WPTR  0x02C
#define TSIO_FIFO_H_RPTR  0x030
#define TSIO_FIFO_M_WPTR  0x034
#define TSIO_FIFO_M_RPTR  0x038
#define TSIO_FIFO_L_WPTR  0x03C
#define TSIO_FIFO_L_RPTR  0x040

#define TSIO_EXE_INFO     0x084
#define DESP_EXE_INT      0x23C

#define TSIO_H_RX_CNT     0x230
#define TSIO_H_TX_CNT     0x224

#define TSIO_TX_PKT       0x068

#define  TSIO_TX_H_PTL_WR    0x224
#define  TSIO_RX_H_PTL_INFO  0x230

#define  TSIO_PHY_CLK     0x004
#define  TSIO_SID_KEY     0x120

#endif //__TSIO_H