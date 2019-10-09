#ifndef _ARM_ASM_MACRO_H_
#define _ARM_ASM_MACRO_H_

//===== Register Write =====
#define ARM_REG_WR(addr, addr_reg, data, data_reg) \
        LDR     addr_reg, =addr; \
        LDR     data_reg, =data; \
        STR     data_reg, [addr_reg]; \

//===== Register Read Without Check =====
#define ARM_REG_RD(addr, addr_reg, data_reg) \
        LDR     addr_reg, =addr; \
        LDR     data_reg, [addr_reg]; \

//===== Register Read With Check =====
#define ARM_CHECK_RD_REG(addr, rd_val, mask, addr_reg, rd_reg, chk_reg) \
        LDR     addr_reg, =addr; \
        LDR     rd_reg, [addr_reg]; \
        LDR     chk_reg,  =mask; \
        AND     rd_reg, rd_reg, chk_reg; \
        LDR     addr_reg, =rd_val; \
        AND     addr_reg, addr_reg, chk_reg; \
        CMP     addr_reg, rd_reg; \
        BNE     DIAG_FAIL; \

//===== Register Write With Read Check =====
#define ARM_CHECK_WR_REG(addr, wr_val, rd_val, mask, reg1, reg2, reg3) \
	LDR     reg1, =addr; \
	LDR     reg2, =wr_val; \
        STR     reg2, [reg1]; \
        LDR     reg3, [reg1]; \
	LDR     reg2, =rd_val; \
        LDR     reg1, =mask; \
        AND     reg3, reg3, reg1; \
        CMP     reg2, reg3; \
        BNE     DIAG_FAIL; \

//===== Delay Loop =====
#define ARM_DELAY(count,reg)  \
        LDR     reg, =count; \
9:      SUB     reg, reg, #1; \
        CMP     reg, #0; \
        BNE     9b;

//===== Push R0-R12 & R14 to STACK =====
#define ARM_PUSH_STACK() \
       STMFD   r13!, {r0-r12,r14}; # r13 is Stack Point \

//===== Pop R0-R12 & R14 to STACK =====
#define ARM_POP_STACK() \
        LDMFD   r13!, {r0-r12,r14}; # r13 is Stack Point \

//===== If Read Value == 00000001~7FFFFFFFF(>0), Jump =====
#define ARM_CHECK_RD_REG_JB(addr, mask, reg1, reg2, jump_label) \
	LDR     reg1, =addr; \
        LDR     reg2, [reg1]; \
        LDR     reg1, =mask; \
        AND     reg2, reg2, reg1; \
        CMP     reg2, #0; \
        BGT     jump_label; \

//===== If Read Value == 80000000~FFFFFFFE(<0), Jump =====
#define ARM_CHECK_RD_REG_JNB(addr, mask, reg1, reg2, jump_label) \
	LDR     reg1, =addr; \
        LDR     reg2, [reg1]; \
        LDR     reg1, =mask; \
	MVN     reg2, reg2; \
        AND     reg2, reg2, reg1; \
        CMP     reg2, #0; \
        BGT     jump_label; \

//===== If Read Value == rd_val, Jump =====
#define ARM_CHECK_RD_REG_JE(addr, rd_val, mask, reg1, reg2, jump_label) \
	LDR     reg1, =addr; \
        LDR     reg2, [reg1]; \
        LDR     reg1, =mask; \
        AND     reg2, reg2, reg1; \
        LDR     reg1, =rd_val; \
        CMP     reg2, reg1; \
        BEQ     jump_label; \

//===== If Read Value !== rd_val, Jump =====
#define ARM_CHECK_RD_REG_JNE(addr, rd_val, mask, reg1, reg2, jump_label) \
        LDR     reg1, =addr; \
        LDR     reg2, [reg1]; \
        LDR     reg1, =mask; \
        AND     reg2, reg2, reg1; \
        LDR     reg1, =rd_val; \
        CMP     reg2, reg1; \
        BNE     jump_label; \

//===== WAIT =====
#define ARM_WAIT(addr,mask,value,reg1,reg2) \
	NOP; \
	NOP; \
	NOP; \
	NOP; \
8:	LDR     reg1, =addr; \
	LDR     reg2, [reg1]; \
	LDR     reg1, =mask; \
        AND     reg2, reg2, reg1; \
        LDR     reg1, =value; \
        CMP     reg2, reg1; \
	BNE     8b; \

// Kevin Add
#define ARM_GET_PERIPH_BASE(reg1) \
    MRC     p15, 4, reg1, c15, c0, 0; \
    ORR     reg1, reg1, #(0xa << 28);

#define ARM_ADR(reg1, value) \
    movw    reg1, ((value & 0x0000ffff) >> 0 ); \
    movt    reg1, ((value & 0xffff0000) >> 16);

#define DELAY(count,reg) \
    mov reg, #(count);   \
9:  sub reg, #1;         \
    cmp reg, #0;         \
    bne 9b               


#endif
