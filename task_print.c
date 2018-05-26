#include <linux/sched.h>
#include <linux/sched/signal.h>
#include <linux/module.h>
#include <linux/kernel.h>


/* This function is called when the module is loaded. */
int simple_init(void)
{
    struct task_struct *task;
    for_each_process(task) {
        printk(KERN_INFO "%-16s:%10d:%20ld\n",task->comm,task->pid,task->state);
        /* on each iteration task points to the next task */
    }
    return 0;
}

/* This function is called when the module is removed. */
void simple_exit(void) {
}

/* Macros for registering module entry and exit points. */
module_init( simple_init );
module_exit( simple_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");

