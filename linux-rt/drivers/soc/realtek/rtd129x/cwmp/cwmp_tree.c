#include <linux/init.h>
#include <linux/module.h>
#include <linux/console.h>
#include <linux/interrupt.h>
#include <linux/uaccess.h>
#include <linux/printk.h>
#include <linux/slab.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/compat.h>
#include <asm-generic/string.h>

#include "cwmp_km.h"

static struct CWMP_Module {
    struct CWMP_DirNode * top;
} * gModule = NULL;

static DEFINE_MUTEX(cwmp_lock);

static ssize_t CWMP_FileNode_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf) {
    struct CWMP_FileNode * node = container_of(attr, struct CWMP_FileNode, mKattr);
    int n = 0;
    n += sprintf(buf+n, "%s", CWMP_FileNode_GetString(node));
    return n;
}

static ssize_t CWMP_FileNode_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count) {
    struct CWMP_FileNode * node = container_of(attr, struct CWMP_FileNode, mKattr);
    memcpy(CWMP_FileNode_GetString(node), buf, count);
    return count;
}

struct CWMP_FileNode *            CWMP_FileNode_new         (struct CWMP_DirNode * parent, char * name, umode_t permission) {
    struct CWMP_FileNode * node = (struct CWMP_FileNode *) kzalloc(sizeof(struct CWMP_FileNode), GFP_KERNEL);
    if (!node)
        goto err;

    sprintf(node->mCommName, "%s", name);

    node->mParent               = parent;
    node->mKattr.attr.mode      = permission;
    node->mKattr.attr.name      = node->mCommName;
    node->mKattr.show           = CWMP_FileNode_show;
    node->mKattr.store          = CWMP_FileNode_store;

    INIT_LIST_HEAD(&node->list);

    if (sysfs_create_file(CWMP_DirNode_GetKobject(node->mParent), &(node->mKattr.attr)) != 0)
        goto err;

    return node;
err:
    if (node)
        kfree(node);
    return NULL;
}

void                            CWMP_FileNode_delete      (struct CWMP_FileNode * node) {
    if (node) {
        sysfs_remove_file(CWMP_DirNode_GetKobject(node->mParent), &(node->mKattr.attr));
        kfree(node);
    }
}

char *                          CWMP_FileNode_GetName     (struct CWMP_FileNode * node) {
    if (node)
        return &node->mCommName[0];
    return NULL;
}

struct CWMP_DirNode *             CWMP_FileNode_GetParent   (struct CWMP_FileNode * node) {
    if (node) {
        return node->mParent;
    }
    return NULL;
}

char *                          CWMP_FileNode_GetString   (struct CWMP_FileNode * node) {
    if (node)
        return &node->mStringData[0];
    return NULL;
}

struct list_head *              CWMP_FileNode_GetList     (struct CWMP_FileNode * node) {
    if (node)
        return &node->list;
    return NULL;
}

struct CWMP_DirNode *             CWMP_DirNode_new          (struct CWMP_DirNode * parent, char * name) {
    struct CWMP_DirNode * node = (struct CWMP_DirNode *) kzalloc(sizeof(struct CWMP_DirNode), GFP_KERNEL);
    if (!node)
        goto err;

    sprintf(node->mCommName, "%s", name);
    node->mParent   = parent;
    node->mKobj     = kobject_create_and_add(node->mCommName, CWMP_DirNode_GetKobject(node->mParent));
    if (!node->mKobj)
        goto err;

    INIT_LIST_HEAD(&node->mChildDir_list);
    INIT_LIST_HEAD(&node->mChildFile_list);
    INIT_LIST_HEAD(&node->list);
    return node;
err:
    if (node)
        kfree(node);
    return NULL;
}

void                            CWMP_DirNode_delete       (struct CWMP_DirNode * node) {
    if (node) {
        {
            struct CWMP_FileNode * pFileHandler, * tmp_pFileHandler;
            list_for_each_entry_safe(pFileHandler, tmp_pFileHandler, &node->mChildFile_list, list) {
                list_del(CWMP_FileNode_GetList(pFileHandler));
                CWMP_FileNode_delete(pFileHandler);
            }
        }
        {
            struct CWMP_DirNode * pDirHandler, * tmp_pDirHandler;
            list_for_each_entry_safe(pDirHandler, tmp_pDirHandler, &node->mChildDir_list, list) {
                list_del(CWMP_DirNode_GetList(pDirHandler));
                CWMP_DirNode_delete(pDirHandler);
            }
        }
        //kobject_cleanup(node->mKobj);
        //kobject_put(node->mKobj);
        kobject_del(node->mKobj);
        kfree(node);
    }
}

char *                          CWMP_DirNode_GetName      (struct CWMP_DirNode * node) {
    if (node) {
        return &node->mCommName[0];
    }
    return NULL;
}

struct list_head *              CWMP_DirNode_GetList      (struct CWMP_DirNode * node) {
    if (node)
        return &node->list;
    return NULL;
}

struct kobject *                CWMP_DirNode_GetKobject   (struct CWMP_DirNode * node) {
    if (node) {
        return node->mKobj;
    }
    return NULL;
}

struct CWMP_DirNode *             CWMP_DirNode_GetParent    (struct CWMP_DirNode * node) {
    if (node) {
        return node->mParent;
    }
    return NULL;
}

int                             CWMP_DirNode_CreateDir    (struct CWMP_DirNode * node, char * child_name) {
    if (CWMP_DirNode_FindFile(node, child_name) != NULL ||
            CWMP_DirNode_FindDir(node, child_name) != NULL)
        goto err;

    if (node) {
        struct CWMP_DirNode * child = CWMP_DirNode_new(node, child_name);
        if (!child)
            goto err;
        list_add(CWMP_DirNode_GetList(child), &node->mChildDir_list);
        return 0;
    }
err:
    return -1;
}

int                             CWMP_DirNode_CreateFile   (struct CWMP_DirNode * node, char * child_name, umode_t permission) {
    if (CWMP_DirNode_FindFile(node, child_name) != NULL ||
            CWMP_DirNode_FindDir(node, child_name) != NULL)
        goto err;

    if (node) {
        struct CWMP_FileNode * child = CWMP_FileNode_new(node, child_name, permission);
        if (!child)
            goto err;
        list_add(CWMP_FileNode_GetList(child), &node->mChildFile_list);
        return 0;
    }
err:
    return -1;

}

int                             CWMP_DirNode_RemoveDir    (struct CWMP_DirNode * node, char * child_name) {
    if (node) {
        struct CWMP_DirNode * child = CWMP_DirNode_FindDir(node, child_name);
        if (child) {
            list_del(CWMP_DirNode_GetList(child));
            CWMP_DirNode_delete(child);
            return 0;
        }
    }
    return -1;
}

int                             CWMP_DirNode_RemoveFile   (struct CWMP_DirNode * node, char * child_name) {
    if (node) {
        struct CWMP_FileNode * child = CWMP_DirNode_FindFile(node, child_name);
        if (child) {
            list_del(CWMP_FileNode_GetList(child));
            CWMP_FileNode_delete(child);
            return 0;
        }
    }
    return -1;
}

struct CWMP_DirNode *             CWMP_DirNode_FindDir      (struct CWMP_DirNode * node, char * child_name) {
    if (node) {
        bool meet = false;
        struct CWMP_DirNode * pDirHandler;
        list_for_each_entry(pDirHandler, &node->mChildDir_list, list) {
            if (strcmp(child_name, CWMP_DirNode_GetName(pDirHandler)) == 0) {
                meet = true;
                break;
            }
        }
        if (meet)
            return pDirHandler;

    }
    return NULL;
}

struct CWMP_FileNode *            CWMP_DirNode_FindFile     (struct CWMP_DirNode * node, char * child_name) {
    if (node) {
        bool meet = false;
        struct CWMP_FileNode * pFileHandler;
        list_for_each_entry(pFileHandler, &node->mChildFile_list, list) {
            if (strcmp(child_name, CWMP_FileNode_GetName(pFileHandler)) == 0) {
                meet = true;
                break;
            }
        }
        if (meet)
            return pFileHandler;
    }
    return NULL;
}

struct CWMP_DirNode *             CWMP_DirNode_CreateTOP          (struct kobject * parent, char * name) {
    struct CWMP_DirNode * node = (struct CWMP_DirNode *) kzalloc(sizeof(struct CWMP_DirNode), GFP_KERNEL);
    if (!node)
        goto err;

    sprintf(node->mCommName, "%s", name);
    node->mParent   = NULL;
    node->mKobj     = kobject_create_and_add(node->mCommName, parent);
    if (!node->mKobj)
        goto err;

    INIT_LIST_HEAD(&node->mChildDir_list);
    INIT_LIST_HEAD(&node->mChildFile_list);
    INIT_LIST_HEAD(&node->list);
    return node;
err:
    if (node)
        kfree(node);
    return NULL;
}

void                            CWMP_DirNode_RemoveTOP       (struct CWMP_DirNode * node) {
    return CWMP_DirNode_delete(node);
}

struct CWMP_CmdData *             CWMP_CmdData_new          (char * path, enum cwmp_um_cmd user_cmd) {
    struct CWMP_CmdData * cmdHeader = (struct CWMP_CmdData *) kzalloc(sizeof(struct CWMP_CmdData), GFP_KERNEL);

    if (!cmdHeader)
        goto err;

    {
        char * path_in = path;
        struct CWMP_CmdData * target = NULL;
        const char *delim = ".";
        char * pch;
        pch = strsep(&path_in, delim);
        while (pch != NULL) {
            if (strlen(pch) != 0) {
                if (target == NULL) {
                    target = cmdHeader;
                } else {
                    target->next = (struct CWMP_CmdData *) kzalloc(sizeof(struct CWMP_CmdData), GFP_KERNEL);
                    target = target->next;
                }

                if (!target)
                    goto err;

                sprintf(target->mCommName, "%s", pch);
                target->mType = CWMP_CmdData_Type_Dir;
            }
            pch = strsep (&path_in, delim);
        }

        switch (user_cmd) {
            case eCreateFileNode:
            case eDeleteFileNode:
            case eWriteValue:
            case eReadValue:
                target->mType = CWMP_CmdData_Type_File;
                break;
            default:
                break;
        }
    }

    return cmdHeader;
err:
    if (cmdHeader)
        CWMP_CmdData_delete(cmdHeader);
    return NULL;
}

void                            CWMP_CmdData_delete       (struct CWMP_CmdData * cmd) {
    if (cmd) {
        if (cmd->next)
            CWMP_CmdData_delete(cmd->next);
        kfree(cmd);
    }
}

char *                          CWMP_CmdData_GetName      (struct CWMP_CmdData * cmd) {
    if (cmd) {
        return &cmd->mCommName[0];
    }
    return NULL;
}

bool                            CWMP_CmdData_IsLast       (struct CWMP_CmdData * cmd) {
    if (cmd)
        return (cmd->next == NULL) ? true : false;
    return true;
}

bool                            CWMP_CmdData_IsFile       (struct CWMP_CmdData * cmd) {
    if (cmd) {
        if (CWMP_CmdData_IsLast(cmd) && cmd->mType == CWMP_CmdData_Type_File)
            return true;
    }
    return false;
}

bool                            CWMP_CmdData_IsDir        (struct CWMP_CmdData * cmd) {
    if (cmd) {
        if (!CWMP_CmdData_IsLast(cmd) || cmd->mType == CWMP_CmdData_Type_Dir)
            return true;
    }
    return false;
}


struct CWMP_FileNode *            CWMP_Cmd_FindFile         (struct CWMP_DirNode * parent, struct CWMP_CmdData * cmd) {
    struct CWMP_FileNode * target = NULL;
    //printk("[%s:%d]...\n", __FUNCTION__, __LINE__);
    if (parent && cmd) {
        struct CWMP_DirNode * node = parent;
        struct CWMP_CmdData * tmp_cmd = cmd;

        do {

            if (!node || !tmp_cmd)
                break;

            if (CWMP_CmdData_IsLast(tmp_cmd)) {
                if (CWMP_CmdData_IsFile(tmp_cmd))
                    target = CWMP_DirNode_FindFile(node, CWMP_CmdData_GetName(tmp_cmd));
                break;
            }

            /* into the next dir */
            node = CWMP_DirNode_FindDir(node, CWMP_CmdData_GetName(tmp_cmd));
            tmp_cmd = tmp_cmd->next;
        } while (tmp_cmd != NULL);
    }
    return target;
}

struct CWMP_DirNode *             CWMP_Cmd_FindDir          (struct CWMP_DirNode * parent, struct CWMP_CmdData * cmd) {
    struct CWMP_DirNode * target = NULL;
    if (parent && cmd) {
        struct CWMP_DirNode * node = parent;
        struct CWMP_CmdData * tmp_cmd = cmd;

        do {

            if (!node || !tmp_cmd)
                break;

            if (CWMP_CmdData_IsLast(tmp_cmd)) {
                if (CWMP_CmdData_IsDir(tmp_cmd))
                    target = CWMP_DirNode_FindDir(node, CWMP_CmdData_GetName(tmp_cmd));
                break;
            }

            /* into the next dir */
            node = CWMP_DirNode_FindDir(node, CWMP_CmdData_GetName(tmp_cmd));
            tmp_cmd = tmp_cmd->next;
        } while (tmp_cmd != NULL);
    }
    return target;
}

int                             CWMP_Cmd_CreateNode       (struct CWMP_DirNode * parent, struct CWMP_CmdData * cmd) {
    if (parent && cmd) {
        struct CWMP_DirNode * node = parent;
        struct CWMP_CmdData * tmp_cmd = cmd;
        do {
            if (!tmp_cmd)
                return 0; //break;

            if (CWMP_CmdData_IsDir(tmp_cmd)) {
                struct CWMP_DirNode * tmp;
                CWMP_DirNode_CreateDir(node, CWMP_CmdData_GetName(tmp_cmd));
                tmp = CWMP_DirNode_FindDir(node, CWMP_CmdData_GetName(tmp_cmd));
                if (tmp) {
                    node = tmp;
                    tmp_cmd = tmp_cmd->next;
                    continue;
                } else
                    goto err;
            }

            if (CWMP_CmdData_IsFile(tmp_cmd)) {
                CWMP_DirNode_CreateFile(node, CWMP_CmdData_GetName(tmp_cmd), CWMP_TREE_FILE_PERMISSION);
                return 0;
            }
        } while (tmp_cmd != NULL);
    }
    return 0;
err:
    return -1;
}

void                            CWMP_Cmd_RemoveNode       (struct CWMP_DirNode * parent, struct CWMP_CmdData * cmd) {
    struct CWMP_FileNode *    f_node = CWMP_Cmd_FindFile(parent, cmd);
    struct CWMP_DirNode *     d_node = CWMP_Cmd_FindDir(parent, cmd);
    //mutex_lock(&cwmp_lock);
    if (f_node) {
        CWMP_DirNode_RemoveFile(CWMP_FileNode_GetParent(f_node), CWMP_FileNode_GetName(f_node));
    }
    if (d_node) {
        CWMP_DirNode_RemoveDir(CWMP_DirNode_GetParent(d_node), CWMP_DirNode_GetName(d_node));
    }
    //mutex_unlock(&cwmp_lock);
}

int CWMP_Cmd_Write (struct CWMP_DirNode * parent, struct CWMP_CmdData * cmd, char * value) {
    int ret = -1;
    struct CWMP_FileNode * f_node;
    //printk("[%s:%d]...\n", __FUNCTION__, __LINE__);
    if (parent && cmd && value) {
        struct CWMP_DirNode * node = parent;
        struct CWMP_CmdData * tmp_cmd = cmd;
        ret = CWMP_Cmd_CreateNode(node, tmp_cmd);
        if (ret >= 0) {
            //mutex_lock(&cwmp_lock);
            f_node = CWMP_Cmd_FindFile(node, tmp_cmd);
            if (f_node) {
                //printk("[%s:%d] f_node=%s\n", __FUNCTION__, __LINE__, CWMP_FileNode_GetName(f_node));
                //printk("[%s:%d] string length=%ld\n", __FUNCTION__, __LINE__, (long)strlen(value));
                memcpy(CWMP_FileNode_GetString(f_node), value, strlen(value));
            } else {
                ret = -2;
            }
            //mutex_unlock(&cwmp_lock);
        }
    }
    //printk("[%s:%d].End, ret=%d\n", __FUNCTION__, __LINE__, ret);
    return ret;
}

int CWMP_Cmd_Read (struct CWMP_DirNode * parent, struct CWMP_CmdData * cmd, char * value) {
    int ret = -1;
    char buf[CWMP_TREE_STRING_LEN];
    struct CWMP_FileNode * f_node;
    int len = 0;
    //printk("[%s:%d]...\n", __FUNCTION__, __LINE__);
    if (parent && cmd) {
        struct CWMP_DirNode * node = parent;
        struct CWMP_CmdData * tmp_cmd = cmd;
        //mutex_lock(&cwmp_lock);
        f_node = CWMP_Cmd_FindFile(node, tmp_cmd);
        if (f_node) {
            //printk("[%s:%d] f_node=%s\n", __FUNCTION__, __LINE__, CWMP_FileNode_GetName(f_node));
            len = sprintf(buf, "%s", CWMP_FileNode_GetString(f_node));
            buf[len] = '\0';
            //printk("[%s:%d] content=%s(%d)\n", __FUNCTION__, __LINE__, buf, len);
            if (copy_to_user(value, buf, len)) {
                printk("[%s:%d] copy data to user space FAIL!\n", __FUNCTION__, __LINE__);
            } else {
                ret = len;
            }
        //} else {
        //    printk("[%s:%d] file not found?...\n", __FUNCTION__, __LINE__);
        }
        //mutex_unlock(&cwmp_lock);
    }
    //printk("[%s:%d].End, ret=%d\n", __FUNCTION__, __LINE__, ret);
    return ret;
}

int                             CWMP_SendCmd              (char * path, enum cwmp_um_cmd user_cmd, char * value) {
    int ret = -1;
    struct CWMP_CmdData * cmdData;
    //struct CWMP_CmdData * cmdData = CWMP_CmdData_new(path, user_cmd);
    cmdData = CWMP_CmdData_new(path, user_cmd);
    if (!cmdData)
        goto err;

    mutex_lock(&cwmp_lock);
    switch (user_cmd) {
        case eCreateFileNode:
        case eCreateDirNode:
            ret = CWMP_Cmd_CreateNode(gModule->top, cmdData);
            break;
        case eDeleteFileNode:
        case eDeleteDirNode:
            CWMP_Cmd_RemoveNode(gModule->top, cmdData);
            ret = 0;
            break;
        case eWriteValue:
            ret = CWMP_Cmd_Write(gModule->top, cmdData, value);
            break;
        case eReadValue:
            ret = CWMP_Cmd_Read(gModule->top, cmdData, value);
            break;
        default:
            break;
    }
    mutex_unlock(&cwmp_lock);

    CWMP_CmdData_delete(cmdData);
    return ret;
err:
    if (cmdData)
        CWMP_CmdData_delete(cmdData);
    return ret;
}

int         cwmp_open     (struct inode *inode, struct file *filp) {
    return 0;
}

int         cwmp_close    (struct inode *inode, struct file *filp) {
    return 0;
}

ssize_t     cwmp_read     (struct file *filp, char *buf, size_t size, loff_t *f_pos) {
    return 0;
}

ssize_t     cwmp_write    (struct file *filp, const char *buf, size_t size, loff_t *f_pos) {
    return size;
}

long        cwmp_ioctl    (struct file *filp, unsigned int cmd, unsigned long arg) {
    int ret = -1;
    //printk("[%s:%d] Got an ioctl command (%ld), CWMP_IOC_SENDCMD=%ld\n", __FUNCTION__, __LINE__, (unsigned long)cmd, CWMP_IOC_SENDCMD);
    switch (cmd) {
        case CWMP_IOC_SENDCMD:
            {
                struct cwmp_um_config config;
                char inPath[1024];
                memset(inPath, 0x0, sizeof(inPath));
                memset((void *) &config, 0 , sizeof(struct cwmp_um_config));
                ret = (int) copy_from_user(&config, (void *) arg, sizeof(struct cwmp_um_config));
                if (ret != 0) {
                    printk("[%s:%d] copy_from_user return failed!(%d)\n", __FUNCTION__, __LINE__, ret);
                    break;
                }
                sscanf(config.path, "%s", inPath);
                ret = CWMP_SendCmd(inPath, config.cmd, config.value);
                if (ret < 0) {
                    printk("[%s:%d] CWMP_SendCmd return failed!(%d)\n", __FUNCTION__, __LINE__, ret);
                }
                break;
            }
        default:
            break;
    }
    return ret;
}

#ifdef CONFIG_COMPAT
struct cwmp_um_config32 {
    enum cwmp_um_cmd cmd;
    compat_uptr_t path;
    compat_uptr_t value;
};

#define CWMP_IOC_SENDCMD32  _IOWR(CWMP_IOC_MAGIC, 1, struct cwmp_um_config32)

long cwmp_ioctl_compat (struct file *filp, unsigned int cmd, unsigned long arg) {
    struct cwmp_um_config config;
    struct cwmp_um_config32 * config32 = (struct cwmp_um_config32 *)arg;
    compat_uptr_t path_ptr, value_ptr;
    int ret = -1;
    char inPath[1024];

    //printk("[%s:%d] Got an ioctl command (%ld), CWMP_IOC_SENDCMD=%ld, CWMP_IOC_SENDCMD32=%ld\n", __FUNCTION__, __LINE__, (unsigned long)cmd, CWMP_IOC_SENDCMD, CWMP_IOC_SENDCMD32);
    memset((void *) &config, 0 , sizeof(struct cwmp_um_config));
    memset(inPath, 0x0, sizeof(inPath));

    switch (cmd) {
        case CWMP_IOC_SENDCMD32:
            if (get_user(config.cmd, &config32->cmd)
                || get_user(path_ptr, &config32->path)
                || get_user(value_ptr, &config32->value))
                    return -EFAULT;
            config.path = compat_ptr(path_ptr);
            config.value = compat_ptr(value_ptr);
            sscanf(config.path, "%s", inPath);

            //printk("[%s:%d] cmd=%d, path=%s(%p)(size=%d), value=%s(%p)(size=%d)\n", __FUNCTION__, __LINE__, config.cmd, config.path, config.path, (int)strlen(config.path), config.value, config.value, (int)strlen(config.value));

            ret = CWMP_SendCmd(inPath, config.cmd, config.value);
            if (ret < 0) {
                printk("[%s:%d] CWMP_SendCmd return failed!(%d)\n", __FUNCTION__, __LINE__, ret);
            }
            break;
        default:
            break;
    }

    return ret;
}
#endif

static dev_t            cwmp_dev_num = 0;
static struct device*   cwmp_device;
static struct cdev      cwmp_dev;
struct class *          cwmp_dev_class = NULL;
static struct file_operations cwmp_fops = {
    .owner                  = THIS_MODULE,
    .open                   = cwmp_open,
    .release                = cwmp_close,
    .read                   = cwmp_read,
    .write                  = cwmp_write,
    .unlocked_ioctl         = cwmp_ioctl,
#ifdef CONFIG_COMPAT
    .compat_ioctl           = cwmp_ioctl_compat,
#endif
};

static int cwmp_module_init (void) {
    gModule = (struct CWMP_Module *) kzalloc(sizeof(struct CWMP_Module), GFP_KERNEL);
    if (!gModule)
        goto err;

    gModule->top = CWMP_DirNode_CreateTOP(kernel_kobj, MODULE_NAME);
    if (!gModule->top)
        goto err;

    {
        cdev_init(&cwmp_dev, &cwmp_fops);
        if (alloc_chrdev_region(&cwmp_dev_num, 0, 1, MODULE_NAME)!=0) {
            cdev_del(&cwmp_dev);
            goto err;
        }

        if (cdev_add(&cwmp_dev, cwmp_dev_num, 1)<0) {
            goto err;
        }

        cwmp_dev_class = class_create(THIS_MODULE, MODULE_NAME);

        cwmp_device = device_create(
                cwmp_dev_class,       // class
                NULL,               // parent
                cwmp_dev_num,         // dev number
                NULL,               // driver data
                MODULE_NAME);       // device name
    }

    return 0;
err:
    if (gModule) {
        if (gModule->top)
            CWMP_DirNode_RemoveTOP(gModule->top);
        kfree(gModule);
    }
    return -1;
}

static void cwmp_module_exit(void) {
    {
        device_destroy(cwmp_dev_class, cwmp_device->devt);
        class_destroy(cwmp_dev_class);
        cdev_del(&cwmp_dev);
        unregister_chrdev_region(cwmp_dev_num, 1);
    }

    if (gModule) {
        if (gModule->top)
            CWMP_DirNode_RemoveTOP(gModule->top);
        kfree(gModule);
    }
}

module_init(cwmp_module_init);
module_exit(cwmp_module_exit);
MODULE_LICENSE("GPL");
