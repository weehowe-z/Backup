#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/slab.h>/*For kmalloc*/
#include <asm/uaccess.h> /*For copy_from_user*/

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Mtest Module");
MODULE_AUTHOR("Wenhao Zhu");

char *msg;
int len, temp;

// static int hello_proc_show(struct seq_file *m, void *v) {
//   seq_printf(m, "Hello proc!\n");
//   return 0;
// }

// static int hello_proc_open(struct inode *inode, struct  file *file) {
//   return single_open(file, hello_proc_show, NULL);
// }

static ssize_t read_proc(struct file *filp,char *buf,size_t count,loff_t *offp )
{
  if(count>temp){
    count=temp;
  }
  temp=temp-count;
  copy_to_user(buf,msg, count);
  if(count==0)
  temp=len;
  return count;
}

static ssize_t write_proc(struct file *filp,const char *buf,size_t count,loff_t *offp)
{
  copy_from_user(msg,buf,count);
  printk(KERN_INFO "In write");
  len = count;
  temp = len;
  return count;
}

static const struct file_operations proc_fops = {
  .owner = THIS_MODULE,
  // .open = hello_proc_open,
  .read = read_proc,
  // .llseek = seq_lseek,
  // .release = single_release,
  .write = write_proc
};

static int __init proc_init(void) {
  proc_create("hello_proc", 0644, NULL, &proc_fops);
  msg=kmalloc(GFP_KERNEL,10*sizeof(char));
  return 0;
}

static void __exit proc_exit(void) {
  remove_proc_entry("hello_proc", NULL);
}

module_init(proc_init);
module_exit(proc_exit);
