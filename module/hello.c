#include <linux/module.h>   /* everything a module needs: macros, module_init, etc. */
#include <linux/kernel.h>   /* pr_info and the logging levels */

MODULE_LICENSE("GPL");              /* keep the kernel happy: no taint, full symbols */
MODULE_AUTHOR("Peter");             /* optional: your name in the module info */
MODULE_DESCRIPTION("Hello, kernel"); /* optional: shows up in modinfo */
MODULE_VERSION("0.1");              /* optional */

static int __init hello_init(void)
{
    pr_info("Hello, kernel! Pax OS reporting from kernelspace.\n");
    return 0;   /* 0 = loaded successfully; anything else = load fails */
}

static void __exit hello_exit(void)
{
    pr_info("Goodbye, kernel.\n");
}

module_init(hello_init);   /* tells the kernel: call THIS on insmod */
module_exit(hello_exit);   /* and THIS on rmmod */