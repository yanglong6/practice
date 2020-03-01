#include<linux/init.h>
#include<linux/module.h>
#include<linux/cdev.h>
#include<linux/kernel.h>
#include<linux/fs.h>
#include<asm/uaccess.h>
#include<linux/sched.h>
#include<linux/semaphore.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("YANGLONG");
MODULE_DESCRIPTION("a sample driver");

static int  year=22;
static char* name="yanglong";

int hello_major=250;
int hello_minor=0;
int number_of_devices=1;

struct hello_device
{
	char data[128];
	int len;
	wait_queue_head_t rq,wq;
	struct semaphore sem;
	struct cdev cdev;
}hello_device;

module_param(year,int,0400);
module_param(name,charp,0400);
static int hello_open (struct inode *inode, struct file *filp)
{

	filp->private_data = container_of(inode->i_cdev, struct hello_device, cdev);
	printk (KERN_INFO "Hey! device opened\n");
	return 0;
}

static int hello_release (struct inode *inode, struct file *filp)
{

	printk (KERN_INFO "Hmmm... device closed\n");
	return 0;
}

ssize_t hello_read(struct file *file,char *buff,size_t count,loff_t *offp)
{
	ssize_t result=0;
	struct hello_device *dev =file->private_data;

	down(&dev->sem);
	while(dev->len==0)
	{
		up(&dev->sem);
		if(file->f_flags&)
	}
}
struct file_operations hello_fops=
{
	.owner=THIS_MODULE,
	.open=hello_open,
	.release=hello_release,
	.read=hello_read;
	.write=hello_write
};

static void char_reg_setup_cdev(void)
{
	int error;
	dev_t devno;

	devno =MKDEV(hello_major,hello_minor);
	cdev_init(&cdev,&hello_fops);
	cdev.owner=THIS_MODULE;
	error=cdev_add(&cdev,devno,1);
	if(error)
		printk("error char_reg_setup_cdev");
}

static int __init hello_init(void)
{
	int result;
	dev_t devno;

	devno=MKDEV(hello_major,hello_minor);
	result=register_chrdev_region(devno,number_of_devices,"hello");
	if(result<0)
	{
		printk("register failed\n");
		return result;
	}

	char_reg_setup_cdev();
	init_waitqueue_head(&hello_device.rq);
	init_waitqueue_head(&hello_device.wq);
	sema_init(&hello_device.sem,1);
	memset(hello_device.data,0,128);
	hello_device.len=0;

	printk("char device registered\n");
	return 0;
}

static void __exit hello_exit(void)
{
	dev_t devno=MKDEV(hello_major,hello_minor);
	cdev_del(&cdev);
	unregister_chrdev_region(devno,number_of_devices);
	printk("bay \n");
}

module_init(hello_init);
module_exit(hello_exit);
