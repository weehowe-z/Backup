// #include <linux/kernel.h> /* Needed for KERN_INFO */
// #include <linux/module.h> /* Needed by all modules */
// #include <linux/init.h> /*Needed for init and cleanup functions*/
//
// static int __init hello_init(void)
// {
//   printk(KERN_INFO "hello ZWH!\n");
//   return 0;
// }
//
// static void __exit hello_exit(void)
// {
//   printk(KERN_INFO "Goodbye!\n");
// }
// moudle_init(hello_init);
// moudle_exit(hello_exit);



/*
 *  hello-1.c - The simplest kernel module.
 */
#include <linux/module.h>	/* Needed by all modules */
#include <linux/kernel.h>	/* Needed for KERN_INFO */

int init_module(void)
{
	printk(KERN_INFO "Hello ZWH\n");
	/*
	* A non 0 return means init_module failed; module can't be loaded.
	*/
	return 0;
}

void cleanup_module(void)
{
	printk(KERN_INFO "Goodbye world 1.\n");
}
