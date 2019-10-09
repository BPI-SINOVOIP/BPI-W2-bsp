
.text
.global start

start:
#    mrs    x0, mpidr_el1
#    ubfx   x0, x0, #0, #24
#    cmp    x0, #0
#    bne    run_secondary
    
#    bl     efusemain
    
    ldr    x8, _back_addr
    str    x30, [x8]            /* save lr to back addr */
    add    x8, x8, #8
    mov    x1, sp
    str    x1, [x8]             /* save sp to back addr + 8 */

    ldr    x1, _stack_start
    mov    sp, x1
    bic    sp, x1, #7
    bl     verifymain

    ldr    x8, _back_addr
    add    x9, x8, #8
    ldr    x2, [x9]
    mov    sp, x2
    ldr    x1, [x8]
    mov    x0, #0
    br    x1

.globl _back_addr
_back_addr:    
    .dword 0x01a00010

.globl _stack_start
_stack_start:    
    .dword 0x02001000

.globl _stack_start1
_stack_start1:
    .dword 0x02500000

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

