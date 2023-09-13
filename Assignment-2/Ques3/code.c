#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/signal.h>
#include <linux/sched.h>
#include <linux/printk.h>

MODULE_AUTHOR("Yash") ;
MODULE_LICENSE("GPL") ;
MODULE_DESCRIPTION("Module to count running processes.") ;

static long long count_running_processes(void)
{
    struct task_struct *task ;
    long long cnt = 0 ;
    
    for_each_node(task)
    {
        cnt ++ ;
    }

    return cnt ;
}

int init_module(void) 
{ 
    long long cnt = count_running_processes() ;
    pr_info("Number of running process: %lld\n", cnt) ;
    return 0 ;
}

void cleanup_module(void) 
{
    pr_info("Module unloaded.\n") ;
} 
