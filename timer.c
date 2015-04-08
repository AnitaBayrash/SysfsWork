#include <linux/kobject.h>
#include <linux/string.h>
#include <linux/sysfs.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/timer.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Anita Bayrash <anitikki@gmail.com>");
MODULE_DESCRIPTION("Timer Module");

static struct kobject *timer_kobject;

int timer_period = 0;

static ssize_t timer_show(struct kobject *kobj, struct kobj_attribute *attr, char *buffer)
{
        return sprintf(buffer, "%d\n", timer_period);
}

static ssize_t timer_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buffer, size_t count)
{
        sscanf(buffer, "%d", &timer_period);
	return count;
}

static struct kobj_attribute timer_attribute = __ATTR(timer_period, 0666, timer_show, timer_store);
 
static struct attribute *attributes[] = {
        &timer_attribute.attr,
        NULL,
};

static struct attribute_group attribute_timer_group = {
        .attrs = attributes,
};
 
static int __init timer_initialize(void)
{
	int return_value;
	timer_kobject = kobject_create_and_add("timer", NULL);
	return_value = sysfs_create_group(timer_kobject, &attribute_timer_group);
	if (return_value)
	       kobject_put(timer_kobject);
	return return_value;
}

module_init(timer_initialize);

static void __exit timer_exit(void)
{
	kobject_put(timer_kobject);
}

module_exit(timer_exit);
