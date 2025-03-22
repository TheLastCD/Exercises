#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>


static int hello_init(void){
	printk(KERN_ALERT, "Hello from Driver\n");
	return 0;
}

static void hello_exit(void){
	printk(KERN_INFO, "Goodbye from Driver \n");
}


module_init(hello_init);
module_exit(hello_exit);

MODULE_AUTHOR("Bingus");
MODULE_LICENCE("GPL");
MODULE_DESCRIPTION("My silly driver");
