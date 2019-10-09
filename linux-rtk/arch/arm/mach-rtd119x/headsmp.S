#include <linux/linkage.h>
#include <linux/init.h>

	.section ".text.head", "ax"

ENTRY(rtk119x_secondary_startup)
	b	secondary_startup
ENDPROC(rtk119x_secondary_startup)

	.align 2
1:	.long	.
	.long	pen_release
