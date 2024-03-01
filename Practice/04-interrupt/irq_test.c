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

static irq_hander_t testing_irq_handler(unsigned int irq, void *dev_id, struct pt_regs *regs) {
    printk("irq_test: Interrupt was triggered and ISR was called!\n")
    return (irq_handler_t) IRQ_HANDLED; 
}

static int __init ModuleInit(void) {
    int ret = 0;
    printk("irq_test: loading module....\n");

    
    ret = request_irq(irq_number, (irq_hander_t)testing_irq_handler, IRQF_TRIGGER_RISING, "tesing_irq", NULL);
    if(0 != ret) {
        printk("Error!\nCan not request interrupt nr.: %d\n", irq_number);
    }

    printk("Done!\n");
	printk("Testing device is mapped to IRQ Nr.: %d\n", irq_number);
    return 0;
}   

static void __exit ModuleExit(void) {
    printk("irq_test: unloading module.....\n");
    free_irq(irq_number, NULL);
}


module_init(ModuleInit);
module_exit(module_exit);

