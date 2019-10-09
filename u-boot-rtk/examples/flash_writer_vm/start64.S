.text
.global start

start:
    mrs     x0, mpidr_el1
    ubfx    x0, x0, #0, #24
    cmp    x0, #0
    bne    run_secondary
    mov    x3, sp
    lsr    x3, x3, #24
    cmp    x3, #16
    beq    reset
    bl     disable_dcache 
    bl     dvrmain

.globl _stack_start
_stack_start:    
    .dword 0x02000000

.globl _stack_start1
_stack_start1:
    .dword 0x02500000


reset:
    ldr    x1, =_stack_start
    bic    sp, x1, #7
    b      dvrmain

run_secondary:
    ldr    x1, =_stack_start1
    mov    sp, x1
    msr    daifset, #1
    msr    daifset, #2
    mov    x0, x0
    mov    x0, x0
    mov    x0, x0
9:
    b      9b
    mov    x0, x0
    mov    x0, x0
    mov    x0, x0

