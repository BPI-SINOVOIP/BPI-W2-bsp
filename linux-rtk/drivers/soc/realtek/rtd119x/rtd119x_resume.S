#include <linux/linkage.h>
#include <linux/init.h>
#include <asm/asm-offsets.h>
#include <asm/hardware/cache-l2x0.h>

ENTRY(v7_cpu_resume)
    bl  v7_invalidate_l1
    b   cpu_resume
ENDPROC(v7_cpu_resume)
