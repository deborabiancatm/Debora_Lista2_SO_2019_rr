// Código de referência: http://tuxthink.blogspot.com/2014/02/creating-linked-list-in-liinux-kernel.html

#include <linux/list.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/device.h> 
#include <linux/uaccess.h> 
#include <linux/string.h>
#include <linux/slab.h>

MODULE_DESCRIPTION("Todolist using list.h");

typedef struct todo_list {
	struct list_head list;
	int id;
	char activity[250];
}todolist;

todolist *tmp;
todolist mylist;
struct list_head *ptr, *q;

static int __init list_init(void) {
	int i;	
	INIT_LIST_HEAD(&mylist.list);

	printk(KERN_INFO "TODO LIST MODULE\n\n");

	for(i = 0; i <= 10; i++){
		tmp = kmalloc (sizeof(todolist), GFP_ATOMIC);
		tmp->id = i;
		strcpy(tmp->activity,"TESTE INSERCAO");
		list_add(&tmp->list, &mylist.list);
	}

	list_for_each(ptr, &mylist.list){
		tmp = list_entry(ptr, todolist, list);
		printk(KERN_INFO "ID: %d\n",tmp->id);
		printk(KERN_INFO "Activity: %s\n\n",tmp->activity);
	}

	list_for_each_safe(ptr, q, &mylist.list){
		tmp = list_entry(ptr, todolist, list);
		printk(KERN_INFO "Removing:\n");
		printk(KERN_INFO "ID: %d\n",tmp->id);
		printk(KERN_INFO "Activity: %s\n\n",tmp->activity);
		list_del(ptr);
	}
	kfree(tmp);
	return 0;
}

static void __exit list_exit(void) {
	printk(KERN_INFO "JUST DO IT, bye\n");
}

module_init(list_init);
module_exit(list_exit);