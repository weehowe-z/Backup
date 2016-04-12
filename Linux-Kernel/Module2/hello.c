#include <linux/module.h>	/* Needed by all modules */
#include <linux/kernel.h>	/* Needed for KERN_INFO */

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Wenhao Zhu");

static long myint = 5130309717;

module_param(myint, long, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
MODULE_PARM_DESC(myint, "An integer");

int init_module(void)
{
	printk(KERN_INFO "Hello ZWH\n");
	printk(KERN_INFO "My student id is an integer: %ld\n", myint);
	return 0;
}

void cleanup_module(void)
{
	printk(KERN_INFO "Goodbye world.\n");
}
