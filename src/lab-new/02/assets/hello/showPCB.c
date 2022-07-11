#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>


static int __init show_PCB_init(void)
{
    struct task_struct * now;
    now = current;

    pr_info("comm: %s\n", now->comm);
    pr_info("state: %d\n", now->pid);
    pr_info("exit_signal: %d\n", now->exit_signal);
    pr_info("pdeath_signal: %d\n", now->pdeath_signal);

    return 0;
}

static void __exit show_PCB_exit(void)
{
    pr_info("Goodbye, world.\n");
}

module_init(show_PCB_init);
module_exit(show_PCB_exit);

MODULE_LICENSE("GPL");
