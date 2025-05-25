#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/moduleparam.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SchonsG");
MODULE_DESCRIPTION("Hello World LKM");
MODULE_VERSION("0.1");

// Entry vars
MODULE_PARM_DESC(msg, "Hello who?");
static char *msg = "";
module_param(msg, charp, 0644);

static int __init hello_init(void)
{
    printk(KERN_INFO "hello: Hello, %s!\n", msg);
    return 0;  // 0 = success
}

static void __exit hello_exit(void)
{
    printk(KERN_INFO "hello: Goodbye, %s!\n", msg);
}

module_init(hello_init);
module_exit(hello_exit);

