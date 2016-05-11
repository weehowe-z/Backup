#include <linux/module.h>	/* Needed by all modules */
#include <linux/kernel.h>	/* Needed for KERN_INFO */
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <asm/uaccess.h>

#define proc_name  "mtest"

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Memory management");
MODULE_AUTHOR("weehowe.z@gmail.com");

char buf[128];

struct proc_dir_entry *entry;


static int proc_show(struct seq_file *m, void *v) {
	printk(KERN_INFO "/proc/%s read called\n", proc_name);
	seq_printf(m, "%s", buf);
  return 0;
}

static int proc_open(struct inode *inode, struct  file *file) {
  return single_open(file, proc_show, NULL);
}

static ssize_t proc_write(struct file *file, const char __user *buffer, size_t count, loff_t *data){
	printk(KERN_INFO "/proc/%s write called\n", proc_name);
	if (count > sizeof(buf)) return -EINVAL;
	if (copy_from_user(buf, buffer, count)) return -EFAULT;
	return count;
}

static const struct file_operations proc_fops = {
  .owner = THIS_MODULE,
  .open = proc_open,
  .read = seq_read,
	.write = proc_write,
  .llseek = seq_lseek,
  .release = single_release,
};

int init_module()
{
	entry = proc_create(proc_name, 0, NULL, &proc_fops);

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
