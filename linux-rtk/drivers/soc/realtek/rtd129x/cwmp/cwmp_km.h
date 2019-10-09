#ifndef CWMP_KERNEL_H
#define CWMP_KERNEL_H

#include <linux/scatterlist.h>
#include "cwmp_um.h"

#define MODULE_NAME                 "cwmp_tree"

#define CWMP_TREE_COMM_LEN            256
#define CWMP_TREE_FILE_PERMISSION     660
//#define CWMP_TREE_STRING_LEN          CWMP_TREE_COMM_LEN
#define CWMP_TREE_STRING_LEN          1024

struct CWMP_FileNode;
struct CWMP_DirNode;
struct CWMP_CmdData;

struct CWMP_FileNode {
    struct kobj_attribute       mKattr;
    struct CWMP_DirNode *         mParent;
    char                        mCommName [CWMP_TREE_COMM_LEN];
    char                        mStringData [CWMP_TREE_STRING_LEN];
    struct list_head            list;
};

struct CWMP_FileNode *            CWMP_FileNode_new         (struct CWMP_DirNode * parent, char * name, umode_t permission);
void                            CWMP_FileNode_delete      (struct CWMP_FileNode * node);
char *                          CWMP_FileNode_GetName     (struct CWMP_FileNode * node);
struct CWMP_DirNode *             CWMP_FileNode_GetParent   (struct CWMP_FileNode * node);
char *                          CWMP_FileNode_GetString   (struct CWMP_FileNode * node);
struct list_head *              CWMP_FileNode_GetList     (struct CWMP_FileNode * node);

struct CWMP_DirNode {
    struct kobject *            mKobj;
    struct CWMP_DirNode *         mParent;
    char                        mCommName [CWMP_TREE_COMM_LEN];
    struct list_head            mChildDir_list;
    struct list_head            mChildFile_list;
    struct list_head            list;
};

struct CWMP_DirNode *             CWMP_DirNode_new          (struct CWMP_DirNode * parent, char * name);
void                            CWMP_DirNode_delete       (struct CWMP_DirNode * node);
char *                          CWMP_DirNode_GetName      (struct CWMP_DirNode * node);
struct list_head *              CWMP_DirNode_GetList      (struct CWMP_DirNode * node);
struct kobject *                CWMP_DirNode_GetKobject   (struct CWMP_DirNode * node);
struct CWMP_DirNode *             CWMP_DirNode_GetParent    (struct CWMP_DirNode * node);
int                             CWMP_DirNode_CreateDir    (struct CWMP_DirNode * node, char * child_name);
int                             CWMP_DirNode_CreateFile   (struct CWMP_DirNode * node, char * child_name, umode_t permission);
int                             CWMP_DirNode_RemoveDir    (struct CWMP_DirNode * node, char * child_name);
int                             CWMP_DirNode_RemoveFile   (struct CWMP_DirNode * node, char * child_name);
struct CWMP_DirNode *             CWMP_DirNode_FindDir      (struct CWMP_DirNode * node, char * child_name);
struct CWMP_FileNode *            CWMP_DirNode_FindFile     (struct CWMP_DirNode * node, char * child_name);

enum CWMP_Node_Type {
    IS_NULL = 0,
    IS_DIR,
    IS_FILE,
};

enum CWMP_CmdData_Type {
    CWMP_CmdData_Type_Dir,
    CWMP_CmdData_Type_File,
};

struct CWMP_CmdData {
    char                        mCommName [CWMP_TREE_COMM_LEN];
    enum CWMP_CmdData_Type        mType;
    struct CWMP_CmdData *         next;
};

struct CWMP_CmdData *             CWMP_CmdData_new          (char * path, enum cwmp_um_cmd user_cmd);
void                            CWMP_CmdData_delete       (struct CWMP_CmdData * cmd);
char *                          CWMP_CmdData_GetName      (struct CWMP_CmdData * cmd);
bool                            CWMP_CmdData_IsLast       (struct CWMP_CmdData * cmd);
bool                            CWMP_CmdData_IsFile       (struct CWMP_CmdData * cmd);
bool                            CWMP_CmdData_IsDir        (struct CWMP_CmdData * cmd);

struct CWMP_FileNode *            CWMP_Cmd_FindFile         (struct CWMP_DirNode * parent, struct CWMP_CmdData * cmd);
struct CWMP_DirNode *             CWMP_Cmd_FindDir          (struct CWMP_DirNode * parent, struct CWMP_CmdData * cmd);
int                             CWMP_Cmd_CreateNode       (struct CWMP_DirNode * parent, struct CWMP_CmdData * cmd);
void                            CWMP_Cmd_RemoveNode       (struct CWMP_DirNode * parent, struct CWMP_CmdData * cmd);
int                             CWMP_SendCmd              (char * path, enum cwmp_um_cmd user_cmd, char * value);

int                             cwmp_open                 (struct inode *inode, struct file *filp);
int                             cwmp_close                (struct inode *inode, struct file *filp);
ssize_t                         cwmp_read                 (struct file *filp, char *buf, size_t size, loff_t *f_pos);
ssize_t                         cwmp_write                (struct file *filp, const char *buf, size_t size, loff_t *f_pos);
long                            cwmp_ioctl                (struct file *filp, unsigned int cmd, unsigned long arg);
long cwmp_ioctl_compat (struct file *filp, unsigned int cmd, unsigned long arg);

#endif /* End of CWMP_KERNEL_H */
