#ifndef __RTK_BUFLOCK_H__
#define __RTK_BUFLOCK_H__

#include <linux/ioctl.h>

enum buflock_status {
    E_BUFLOCK_ST_ERROR,
    E_BUFLOCK_ST_NORMAL,
    E_BUFLOCK_ST_TOUCH,
    E_BUFLOCK_ST_LOCK,
    E_BUFLOCK_ST_UNLOCK,
    E_BUFLOCK_ST_RELEASE,
};

typedef unsigned char   buflock_status_t;
typedef unsigned int    buflock_fwid_t;

struct buflock_alloc_data {
    buflock_fwid_t fwid;
};

struct buflock_import_data {
    buflock_fwid_t fwid;
};

struct buflock_free_data {
    buflock_fwid_t fwid;
};

struct buflock_status_data {
    buflock_fwid_t      fwid;
    buflock_status_t    status;
};

#define BUFLOCK_IOC_MAGIC       'B'
#define BUFLOCK_IOC_ALLOC       _IOWR(BUFLOCK_IOC_MAGIC, 1, struct buflock_alloc_data)
#define BUFLOCK_IOC_FREE        _IOWR(BUFLOCK_IOC_MAGIC, 2, struct buflock_free_data)
#define BUFLOCK_IOC_IMPORT      _IOWR(BUFLOCK_IOC_MAGIC, 3, struct buflock_import_data)
#define BUFLOCK_IOC_SET_STATUS  _IOWR(BUFLOCK_IOC_MAGIC, 4, struct buflock_status_data)
#define BUFLOCK_IOC_GET_STATUS  _IOWR(BUFLOCK_IOC_MAGIC, 5, struct buflock_status_data)

#endif /* __RTK_BUF_LOCK_H__ */
