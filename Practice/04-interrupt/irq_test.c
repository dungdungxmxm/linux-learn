#include <linux/module.h>
#include <linux/init.h>
#include <linux/interrupt.h>

/* Meta information */
MODULE_LISENCE("GPL");
MODULE_AUTHOR("DungNgo");
MODULE_DESCRIPTION("This module for testing register irq");
MODULE_VERSION("0.0.1");

// Ramdoml sample irq number (NOT running)
unsigned int irq_number = 19;

static int __init ModuleInit(void) {
    printf("irq_test: loading module....\n");

    return 0;
}   

static void __exit ModuleExit(void) {
    printf("irq_test: unloading module.....\n");
}


module_init(ModuleInit);
module_exit(module_exit);

