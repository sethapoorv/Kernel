/*Device file creation*/

#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/module.h>
#include<linux/kdev_t.h>
#include<linux/fs.h>
#include<linux/device.h>
#include<linux/cdev.h>


/*Creating Major & Minor number dynamically, not assigning the values below*/
dev_t dog = 0;

/*Making a structure class pointer for storing the address of the class structure for creating the device file*/
static struct class *device_class;

/*Making the cdev structure*/
static struct cdev JK_cdev;

/*Creating file operations function prototypes*/
static int	__init  file_init(void);
static void	__exit file_exit(void);
static int	JK_open(struct inode *inode, struct file *file);
static int	JK_release(struct inode *inode, struct file *file);
static ssize_t  JK_read(struct file *filp, char __user *buf, size_t len, loff_t * off);
static ssize_t  JK_write(struct file *filp, const char *buf, size_t len, loff_t * off);

/*Making file opersation structure, assigning the operations*/
static struct file_operations fops =
{
	.owner   = THIS_MODULE,
	.open    = JK_open,
	.release = JK_release,
	.read    = JK_read,
	.write   = JK_write,
};

/*Making various functions which will be called when we perform file operations*/

/*Open function, it will be called when we open the Device file*/
static int JK_open(struct inode *inode, struct file *file)
{
	pr_info("Looks like the open function has been called successfully!\n");
	return 0;
}

/*Release function, it will be called when we release/close the Device file*/
static int JK_release(struct inode *inode, struct file *file)
{
	pr_info("Looks like the release function has been called successfully!");
	return 0;
}

/*Read function, it will be called when we read the Device file*/
static ssize_t JK_read(struct file *filp, char __user *buf, size_t len, loff_t * off)
{
	pr_info("Looks like the read function has been called succesfully!");
	return 0;
}

/*Write function, it will be called when we write the Device file*/
static ssize_t JK_write(struct file *filp, const char *buf, size_t len, loff_t * off)
{
	pr_info("Looks like the write function has been called succesfully!");
	return len;
}

/*Making function to allocate the Major number dynamically*/
static int __init file_init(void)
{
        /*Allocating Major number dynamically*/

        if((alloc_chrdev_region(&dog, 0, 1, "Apoorv")) <0 ){
                pr_err("Oops! Module could not be loaded into the Kernel!\n");
                return -1;
	}
        pr_info("MAJOR = %d MINOR = %d\n", MAJOR(dog), MINOR(dog));
        pr_info("Major & Minor number has been assigned succesfully!\n");

	/*Creating the cdev structure*/
	cdev_init(&JK_cdev, &fops);

	/*Adding character device to the the system*/
	if((cdev_add(&JK_cdev, dog, 1)) <0 ) {
		pr_err("Cannot add device to the system\n");
		goto r_class;
	}

        /*Creating the class for Device file*/

        if((device_class = class_create(THIS_MODULE, "Seth_class")) == NULL){
                pr_err("Oops! Class could not be created for the device file, better check your code\n!");
                goto r_class;
        }
        pr_info("Class has been created successfully for the device file!");

        /*Creating the device file for Application*/

        if((device_create(device_class, NULL, dog, NULL, "Seth_device")) == NULL){
                pr_err("Oops! Device file could not be created, check your code bro!\n");
                goto r_dev;
        }
        pr_info("Kernel module has been created successfully!Congratulations bro!\n");
        return 0;

r_dev:
        device_destroy(device_class, dog);
r_class:
        unregister_chrdev_region(dog ,1);
        return-1;
}

/*Exit function for the module*/

static void  __exit file_exit(void)
{
        device_destroy(device_class, dog);
        class_destroy(device_class);
	cdev_del(&JK_cdev);
        unregister_chrdev_region(dog, 1);
        pr_info("Kernel has been succesfully removed!");
}

module_init(file_init);
module_exit(file_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Apoorv Seth");
MODULE_DESCRIPTION("Module build for creating and assigning Major and Minor numbers");
MODULE_VERSION("1.0");

