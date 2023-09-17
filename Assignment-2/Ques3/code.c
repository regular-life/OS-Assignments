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
    for (int i = 0 ; i <= 32768 ; i ++)
    {
        struct task_struct *task = pid_task(find_vpid(i), PIDTYPE_PID) ;
        //check if process is running
        if (task)
        {
            cnt++;
            //pr_info("Process %s with pid %d is running.\n", task->comm, task->pid) ;
        }
    }
    return cnt ;
}

int init_module(void) 
{ 
    long long cnt = count_running_processes() ;
    pr_info("Module loaded successfully.\nNumber of running process: %lld\n", cnt) ;
    return 0 ;
}

void cleanup_module(void) 
{
    pr_info("Module unloaded successfully.\n") ;
} 
