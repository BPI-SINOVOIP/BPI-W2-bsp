#include <linux/init.h>

static bool secure_dvfs_disabled;
static int __init secure_dvfs_disabled_setup(char *__unused)
{
	secure_dvfs_disabled = true;
	return 0;
}
__setup("secure_dvfs_disabled", secure_dvfs_disabled_setup);


bool secure_dvfs_is_disabled(void)
{
	return secure_dvfs_disabled;
}

