/*Major & Minor number*/

#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/module.h>
#include<linux/fs.h>


/*Creating custom Major & Minor number dev, assigning the values*/

dev_t dev = MKDEV(224,0);

/*Making the initialisation module*/

static int __init number_init(void)
{
	register_chrdev_region(dev, 1, "Apoorv");
	pr_info("MAJOR = %d MINOR = %d\n", MAJOR(dev), MINOR(dev));
	pr_info("Kernel module has been succesfully inserted!\n");
	return 0;
}

static void  __exit number_exit(void)
{
	unregister_chrdev_region(dev, 1);
	pr_info("Kernel has been succesfully removed!");
}

module_init(number_init);
module_exit(number_exit);

MODULE_LICENSE("GPU");
MODULE_AUTHOR("Apoorv Seth");
MODULE_DESCRIPTION("Module build for creating and assigning Major and Minor numbers");
MODULE_VERSION("1.0");
