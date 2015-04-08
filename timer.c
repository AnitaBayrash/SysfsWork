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
static struct timer_list timer;

int timer_period = 0;

void timer_callback(unsigned long argument)
{
	printk(KERN_INFO "Hello, world!\n");
    	mod_timer(&timer, jiffies + msecs_to_jiffies(timer_period)); 
}

static ssize_t timer_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
        return sprintf(buf, "%d\n", timer_period);
}

static ssize_t timer_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{
        sscanf(buf, "%d", &timer_period);

       	if (timer_period == 0)
		del_timer_sync(&timer);
	else
		mod_timer(&timer, jiffies + msecs_to_jiffies(timer_period)); 

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
	setup_timer(&timer, timer_callback, 0);
	return return_value;
}

module_init(timer_initialize);

static void __exit timer_exit(void)
{
	del_timer_sync(&timer);
        kobject_put(timer_kobject);
}

module_exit(timer_exit);
