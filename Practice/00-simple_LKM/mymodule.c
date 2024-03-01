#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>

/* Meta Information */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Dung Ngo");
MODULE_DESCRIPTION("A Hello world Linux kernel module");

/**
 * @brief This function is called, when the module is loaded into the kernel
*/
static int ModuleInit(void) {
    printk("Hello, Kernel\n");
    return 0;
}
/**
 * @brief This function is called, when the module is removed from the kernel
*/
static void ModuleExit(void) {
    printk("Goodbyte, kernel\n");
}
module_init(ModuleInit)
module_exit(ModuleExit)




