#ifndef __CLK_REALTEK_REGMAP_RTD119X_H
#define __CLK_REALTEK_REGMAP_RTD119X_H

#define CLOCK_ENABLE1                   (0x00C)
#define CLOCK_ENABLE2                   (0x010)
#define GROUP1_CK_SEL                   (0x018)
#define PLL_DIV                         (0x030)
#define VE_CKSEL                        (0x04C)
#define PLL_SCPU1                       (0x100)
#define PLL_SCPU2                       (0x104)
#define PLL_SCPU3                       (0x108)
#define PLL_VPU1                        (0x114)
#define PLL_VPU2                        (0x118)
#define PLL_BUS1                        (0x164)
#define PLL_BUS2                        (0x168)
#define PLL_BUS3                        (0x16C)
#define PLL_DCSB1                       (0x1B4)
#define PLL_DCSB2                       (0x1B8)
#define PLL_DCSB3                       (0x1BC)
#define PLL_GPU1                        (0x1C0)
#define PLL_GPU2                        (0x1C4)

/* PLL_DIV */
#define SCPU_FREQ_SEL_SHIFT             (7)
#define SCPU_FREQ_SEL_WIDTH             (2)
#define SCPU_FREQ_DIV1                  (0)
#define SCPU_FREQ_DIV2                  (2)
#define SCPU_FREQ_DIV4                  (3)

#define BUS_FREQ_SEL_SHIFT              (0)
#define BUS_FREQ_SEL_WIDTH              (1)
#define BUS_FREQ_DIV1                   (0)
#define BUS_FREQ_DIV2                   (1)

/* VE_CKSEL */
#define CLK_VE2_BPU_SEL_SHIFT           (6)
#define CLK_VE2_BPU_SEL_WIDTH           (2)
#define CLK_VE2_SEL_SHIFT               (2)
#define CLK_VE2_SEL_WIDTH               (2)
#define CLK_VE1_SEL_SHIFT               (0)
#define CLK_VE1_SEL_WIDTH               (2)

#endif
