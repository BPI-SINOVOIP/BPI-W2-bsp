#ifndef _DIAG_H_20121212_LUCAS
#define _DIAG_H_20121212_LUCAS
#ifdef SCPU_ARM

void diag_fail();
void diag_pass();
#else
void diag_pass() {
	asm("la   $8, 0x80003000");
	asm("jr   $8");
	asm(".align 5; nop");
}

void diag_fail() {
	asm("la   $8, 0x80003020");
	asm("jr   $8");
	asm(".align 5; nop");
}
#endif
#endif
