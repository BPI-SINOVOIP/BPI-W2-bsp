#ifndef __LINUX_REGULATOR_SY8827E_H
#define __LINUX_REGULATOR_SY8827E_H

#define SY8827E_REG_VSEL0               (0x00)
#define SY8827E_REG_VSEL1               (0x01)
#define SY8827E_REG_CONTROL             (0x02)
#define SY8827E_REG_ID0                 (0x03)
#define SY8827E_REG_ID1                 (0x04)
#define SY8827E_REG_PGOOD               (0x05)

/* register definition */
#define SY8827E_BUCK_EN0_MASK           (0x80)
#define SY8827E_BUCK_EN0_SHIFT          (7)
#define SY8827E_BUCK_EN0_WIDTH          (1)
#define SY8827E_MODE0_MASK              (0x40)
#define SY8827E_MODE0_SHIFT             (6)
#define SY8827E_MODE0_WIDTH             (1)
#define SY8827E_NSEL0_MASK              (0x3F)
#define SY8827E_NSEL0_SHIFT             (0)
#define SY8827E_NSEL0_WIDTH             (6)
#define SY8827E_BUCK_EN1_MASK           (0x80)
#define SY8827E_BUCK_EN1_SHIFT          (7)
#define SY8827E_BUCK_EN1_WIDTH          (1)
#define SY8827E_MODE1_MASK              (0x40)
#define SY8827E_MODE1_SHIFT             (6)
#define SY8827E_MODE1_WIDTH             (1)
#define SY8827E_NSEL1_MASK              (0x3F)
#define SY8827E_NSEL1_SHIFT             (0)
#define SY8827E_NSEL1_WIDTH             (6)

#endif
