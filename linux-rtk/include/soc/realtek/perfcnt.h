#ifndef __SOC_REALTEK_PERFCNT_H_INCLUDED
#define __SOC_REALTEK_PERFCNT_H_INCLUDED

struct device_node;
struct perfcnt_device;

#define PERFCNT_MAX_DATA                (5)

struct perfcnt_data {
	u32 data[PERFCNT_MAX_DATA];
};

struct perfcnt {
	struct device *dev;
	struct perfcnt_device *pcdev;
	struct list_head list;
	struct list_head suspend;
};

/* consumer api */
struct perfcnt *perfcnt_get(struct device *dev, const char *id);
void perfcnt_put(struct perfcnt *pc);
int perfcnt_set_conf(struct perfcnt *pc, u32 id, u32 conf);
int perfcnt_get_data(struct perfcnt *pc, u32 id, struct perfcnt_data *data);
int perfcnt_start(struct perfcnt *pc);
int perfcnt_stop(struct perfcnt *pc);
int perfcnt_reset(struct perfcnt *pc);
int perfcnt_last_duration(struct perfcnt *pc, u32 *period_ms);

int perfcnt_request(struct perfcnt *new_pc);
int perfcnt_release(struct perfcnt *old_pc);

int perfcnt_register_notifier(struct perfcnt *pc, struct notifier_block *nb);
int perfcnt_unregister_notifier(struct perfcnt *pc, struct notifier_block *nb);

#define PERFCNT_EVENT_PRE_CHANGE         0x1
#define PERFCNT_EVENT_POST_CHANGE        0x2

struct perfcnt_change_data {
	struct perfcnt *old_pc;
	struct perfcnt *new_pc;
};

struct perfcnt_ops;
struct perfcnt_data;

struct perfcnt_device {
	struct list_head   list;
	struct device      *dev;
	struct device_node *np;
	int                num_cnt;
	const struct perfcnt_ops *ops;
	u64                time_begin;
	u64                time_end;
	u32                is_start;
	struct blocking_notifier_head notifier;
	struct perfcnt     *cur_pc;
	struct list_head   list_idle;
	struct list_head   list_suspend;
};

struct perfcnt_ops {
	int (*start)(struct perfcnt_device *pcdev);
	int (*stop)(struct perfcnt_device *pcdev);
	int (*reset)(struct perfcnt_device *pcdev);
	int (*set_conf)(struct perfcnt_device *pcdev, u32 id, u32 conf);
	int (*get_data)(struct perfcnt_device *pcdev, u32 id, struct perfcnt_data *data);
};

/* provider api */
int perfcnt_register(struct perfcnt_device *pcdev);
void perfcnt_unregister(struct perfcnt_device *pcdev);

int perfcnt_suspend(struct perfcnt_device *pcdev);
int perfcnt_resume(struct perfcnt_device *pcdev);

#endif /* __SOC_REALTEK_PERFCNT_H_INCLUDED */
