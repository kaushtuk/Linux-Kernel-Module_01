#include <linux/sched.h>
#include <linux/sched/signal.h>
#include <linux/module.h>
#include <linux/kernel.h>

void dfs(struct task_struct * current_task)
{
    struct task_struct *task;
    struct list_head *list;
    list_for_each(list, &current_task->children) {
        task = list_entry(list, struct task_struct, sibling);
        /* task points to the next child in the list */
        printk(KERN_INFO "%-16s:%10d:(%d)\n",task->comm,task->pid,task->real_parent->pid);
        if(task != NULL)
            dfs(task);
    }
}

/* This function is called when the module is loaded. */
int simple_init(void)
{
    printk(KERN_INFO "%-16s:%10d\n",init_task.comm,init_task.pid);
    dfs(&init_task);
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

