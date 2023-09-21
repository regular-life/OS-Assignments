#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/signal.h>
#include <linux/sched.h>
#include <linux/printk.h>
#include <linux/init.h>
#include <linux/pid.h>
#include <linux/cred.h>
#include <linux/moduleparam.h>

MODULE_AUTHOR("Yash") ;
MODULE_LICENSE("GPL") ;
MODULE_DESCRIPTION("Module to count running processes.") ;

static long long count_running_processes(void)
{
    long long cnt = 0 ;
    rcu_read_lock() ;
    for (int i = 0 ; i <= 100000000 ; i ++)
    {
        struct task_struct *task = pid_task(find_vpid(i), PIDTYPE_PID) ;
        //check if process is running
        if (task)
        {
            if (task->__state == 0)
            {
                cnt ++ ;
                printk(KERN_INFO "%s %d \n", task->comm, task->pid) ;
            }
        }
    }
    rcu_read_unlock() ;
    return cnt ;
}

static int __init display_init(void)
{ 
    long long cnt = count_running_processes() ;
    printk(KERN_INFO "Module loaded successfully.\nNumber of running process: %lld\n", cnt) ;
    return 0 ;
}

static void __exit display_cleanup(void)
{
    printk(KERN_INFO "Module unloaded successfully.\n") ;
}

module_init(display_init) ;
module_exit(display_cleanup) ;
