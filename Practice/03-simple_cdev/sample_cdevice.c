#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <linux/uaccess.h>

#define DEVICE_NAME "sample_dev"
#define AUTHOR "DungNgo"
#define DESC "This is sample cdevice"

MODULE_LICENSE("GPL");
MODULE_AUTHOR(AUTHOR);
MODULE_DESCRIPTION(DESC);
MODULE_VERSION("0.01");

static dev_t dev_num;
struct class* my_class;
struct device* my_device;
struct cdev my_cdev;

static int sample_open(struct inode *inode, struct file *file) 
{
	pr_info("open is called\n");
	return 0;
}

static int sample_close(struct inode *inode, struct file *file)
{
	pr_info("close is called\n");
	return 0;
}

static ssize_t sample_read(struct file *flip, char __user *user_buf, size_t len, loff_t *offs)
{
        pr_info("read\n");
        return 0;
}
static ssize_t sample_write(struct file *flip, const char __user *user_buf, size_t len, loff_t *offs)
{
	pr_info("write\n");
        return 0;
}


static struct file_operations fops = {
	.owner = THIS_MODULE,
	.open = sample_open,
	.release = sample_close,
	.read = sample_read,
	.write = sample_write,
};

static int __init sample_init(void)
{
	int ret;
	ret =  alloc_chrdev_region(&dev_num, 0, 1, "sample_cdevie");
	my_class = class_create(THIS_MODULE, DEVICE_NAME);
	cdev_init(&my_cdev, &fops);
	my_cdev.owner = THIS_MODULE;
	cdev_add(&my_cdev, dev_num, 1);
	my_device = device_create(my_class, NULL, dev_num, NULL, DEVICE_NAME);
	printk("Hello kernel!\n");
	return ret;
}

static void __exit sample_exit(void) 
{
	cdev_del(&my_cdev);
	device_destroy(my_class, dev_num);
	class_destroy(my_class);
	unregister_chrdev(dev_num, DEVICE_NAME);
	printk("Good bye!\n");

}


module_init(sample_init);
module_exit(sample_exit);

