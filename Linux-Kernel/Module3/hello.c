#include <linux/module.h>	/* Needed by all modules */
#include <linux/kernel.h>	/* Needed for KERN_INFO */
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

#define proc_name  "myproc"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Wenhao Zhu");

struct proc_dir_entry *entry;

static int hello_proc_show(struct seq_file *m, void *v) {
  seq_printf(m, "Hello this is a new proc!\n");
  return 0;
}

static int hello_proc_open(struct inode *inode, struct  file *file) {
  return single_open(file, hello_proc_show, NULL);
}

static const struct file_operations hello_proc_fops = {
  .owner = THIS_MODULE,
  .open = hello_proc_open,
  .read = seq_read,
  .llseek = seq_lseek,
  .release = single_release,
};

int init_module()
{
	entry = proc_create(proc_name, 0, NULL, &hello_proc_fops);

	if (!entry) {
		remove_proc_entry(proc_name, NULL);
		printk(KERN_ALERT "Error: Could not initialize /proc/%s\n",proc_name);
		return -ENOMEM;
	}


	printk(KERN_INFO "/proc/%s created\n", proc_name);
	return 0;	/* everything is ok */
}

void cleanup_module()
{
	remove_proc_entry(proc_name,NULL);
	printk(KERN_INFO "/proc/%s removed\n", proc_name);
}
