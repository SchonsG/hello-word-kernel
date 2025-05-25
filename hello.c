#include <linux/init.h>      // macros for init/exit
#include <linux/kernel.h>    // printk()
#include <linux/module.h>    // core header for modules

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SchonsG");
MODULE_DESCRIPTION("Hello World LKM");
MODULE_VERSION("0.1");

static int __init hello_init(void)
{
    printk(KERN_INFO "hello: Hello, Linux kernel world!\n");
    return 0;  // 0 = success
}

static void __exit hello_exit(void)
{
    printk(KERN_INFO "hello: Goodbye, Linux kernel world!\n");
}

module_init(hello_init);
module_exit(hello_exit);

