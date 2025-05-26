#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

#define DEVICE_NAME "simplechardev"
static int major;
static char data_buf[100];

static ssize_t dev_read(struct file *file, char __user *ubuf,
                        size_t count, loff_t *ppos)
{
    for (int i = 0; i < sizeof(data_buf) && data_buf[i] != '\0'; i++) {
        if (data_buf[i] >= 'a' && data_buf[i] < 'z') {
            data_buf[i] = data_buf[i] - 'a' + 'A';
        }
    }

    return simple_read_from_buffer(ubuf, count, ppos,
                                   data_buf, sizeof(data_buf));
}

static ssize_t dev_write(struct file *file, const char __user *ubuf,
                         size_t count, loff_t *ppos)
{
    return simple_write_to_buffer(data_buf, sizeof(data_buf),
                                  ppos, ubuf, count);
}

static const struct file_operations fops = {
    .owner   = THIS_MODULE,
    .read    = dev_read,
    .write   = dev_write,
};

static int __init simple_char_init(void)
{
    major = register_chrdev(0, DEVICE_NAME, &fops);
    if (major < 0) {
        pr_err("simplechardev: failed to register\n");
        return major;
    }
    pr_info("simplechardev: registered with major %d\n", major);
    return 0;
}

static void __exit simple_char_exit(void)
{
    unregister_chrdev(major, DEVICE_NAME);
    pr_info("simplechardev: unregistered\n");
}

module_init(simple_char_init);
module_exit(simple_char_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SchonsG");
MODULE_DESCRIPTION("Simple char device");
