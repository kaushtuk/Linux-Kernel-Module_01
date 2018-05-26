#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/slab.h>
#include <linux/types.h>

struct birthday1 {
	int day;
	int month;
	int year;
	struct list_head list;
};
struct birthday2 {
	int hour;
	int minute;
	struct list_head list;
};
static LIST_HEAD(birthday_list);

/* This function is called when the module is loaded. */
int simple_init(void)
{
    {
        struct birthday1 *person;
        int i;

        //1st person
        person=kmalloc(sizeof(*person), GFP_KERNEL);
        person->day=2;
        person->month=8;
        person->year=1995;
        INIT_LIST_HEAD(&person->list);
        list_add_tail(&person->list, &birthday_list);

        for(i=0;i<4;i++) {
            struct birthday1 *temp;
            temp=kmalloc(sizeof(*person), GFP_KERNEL);
            temp->day=person->day+1;
            temp->month=person->day+8;
            temp->year=person->day+1995;
            INIT_LIST_HEAD(&temp->list);
            list_add_tail(&temp->list, &birthday_list);
            person=temp;
        }
    }
    {
        struct birthday2 *person;
        int i;

        //1st person

        person=kmalloc(sizeof(*person), GFP_KERNEL);
        person->hour=2;
        person->minute=8;
        INIT_LIST_HEAD(&person->list);
        list_add_tail(&person->list, &birthday_list);

        for(i=0;i<4;i++) {
            struct birthday2 *temp;
            temp=kmalloc(sizeof(*person), GFP_KERNEL);
            temp->hour=person->hour+1;
            temp->minute=person->minute+8;
            INIT_LIST_HEAD(&temp->list);
            list_add_tail(&temp->list, &birthday_list);
            person=temp;
        }
    }
    {
        struct birthday1 *ptr1;
        struct birthday2 *ptr2;
        int i=5;
        printk(KERN_INFO "Loading Module: birthday\n");
        list_for_each_entry(ptr1, &birthday_list, list) {
            i--;
            if(i>=0) {
                printk(KERN_INFO "%d/%d/%d:birthday date added\n",ptr1->day,ptr1->month,ptr1->year);
            } else {
                break;
            }
        }
        i=5;
        list_for_each_entry(ptr2, &birthday_list, list) {
            i--;
            if(i<0) {
                printk(KERN_INFO "%d:%d:birthday time added\n",ptr2->hour,ptr2->minute);
            }
        }
    }
       return 0;
}

/* This function is called when the module is removed. */
void simple_exit(void) {
    struct birthday1 *ptr1, *next1;
    struct birthday2 *ptr2, *next2;
    int i=5;
    printk(KERN_INFO "Removing Module: birthday\n");
    list_for_each_entry_safe(ptr1, next1, &birthday_list, list) {
        i--;
        if(i>=0) {
            printk(KERN_INFO "%d/%d/%d:birthday date removed\n",ptr1->day,ptr1->month,ptr1->year);
            list_del(&ptr1->list);
            kfree(ptr1);
        } else {
            break;
        }
    }
    list_for_each_entry_safe(ptr2, next2, &birthday_list, list) {
        printk(KERN_INFO "%d:%d:birthday time removed\n",ptr2->hour,ptr2->minute);
        list_del(&ptr2->list);
        kfree(ptr2);
    }
}

/* Macros for registering module entry and exit points. */
module_init( simple_init );
module_exit( simple_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");

