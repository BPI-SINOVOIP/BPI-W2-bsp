#ifndef CWMP_UM_H
#define CWMP_UM_H
#include <linux/ioctl.h>

enum cwmp_um_cmd {
    eCreateFileNode,
    eCreateDirNode,
    eDeleteFileNode,
    eDeleteDirNode,
    eWriteValue,
    eReadValue,
    eMaxUmCmd,
};

struct cwmp_um_config {
    enum cwmp_um_cmd cmd;
    char * path;
    char * value;
};

#define CWMP_IOC_MAGIC  't'
#define CWMP_IOC_SENDCMD  _IOWR(CWMP_IOC_MAGIC, 1, struct cwmp_um_config)
//#define CWMP_IOC_SENDCMD  _IO(CWMP_IOC_MAGIC, 1)

#endif /* End of CWMP_UM_H */
