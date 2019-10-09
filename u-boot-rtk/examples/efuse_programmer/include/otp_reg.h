/************************************************************************
 *
 *  otp_reg.h
 *
 *  Defines for Nike OTP registers
 *
 ************************************************************************/

#ifndef OTP_REG_H
#define OTP_REG_H

#define RTD129x_CHIP_REVISION_A00 (0x00000000) 
#define RTD129x_CHIP_REVISION_A01 (0x00010000)
#define RTD129x_CHIP_REVISION_B00 (0x00020000)

///////////kilopass OTP//////////////
#define OTP_EF_CTRL_ST_BUSY     (1<<16)


/************************************************************************
 *  Definition
 ************************************************************************/
typedef enum {
        OTP_AES_KS,
        OTP_AES_KH,
        OTP_AES_KN
    } otp_aes_enum_t;

#endif
