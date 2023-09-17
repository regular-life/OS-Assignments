# Kernel Module to count running processes

<br />

## Table of Contents
1. [Introduction](#introduction)
2. [How to Run the Application](#how-to-run-the-application)
3. [Understanding the Code](#understanding-the-code)
4. [Conclusion](#conclusion)
5. [Contributors](#contributors)

## Introduction
This is a writeup for making kernel module in C language as part of the **IIITD CSE231 course Operating Systems** - Assignment 2.

## How to run the application
1. **Prequisites:**
   - Linux based OS.
   - GCC compiler on the system.
   - Linux-header files on the system.
2. **Cloning the Repository:**
   - Clone the repository to your local machine using the following command:
     ```bash
     git clone https://github.com/regular-life/OS-Assignments.git
     ```
     **OR**
   - Download the .zip file from https://github.com/regular-life/AP-Assignments.
3. **Opening the Project:**
   - Unzip the file and navigate to "Assignment-2" -> "Ques3".
   - Right-click on the screen and select "Go to terminal here" (or any other similar option).
4. **Running the program:**
   - Write the following command on terminal:
     ```bash
     make all
     ```
   - The kernel module files have been made.
   - Now, write the following command on terminal to load the module in kernel:
     ```bash
      sudo insmod code.ko
     ```
   - The module has been loaded on the kernel. To verify, type the following on terminal and search for `code` in the list (It's likely to appear at the top):
     ```bash
     sudo lsmod
     ```
   - Now, write the following command to see the module in action:
     ```bash
     sudo dmesg
     ```
     ![Error](https://github.com/regular-life/OS-Assignments/blob/main/Assignment-2/Ques3/Module_Loaded.png)
   - A long list will appear on the terminal and you will see the the number of currently active processes at the bottom.
   - To unload the module from the kernel, type the following:
     ```bash
     sudo rmmod code.ko
     ```
   - To verify that the module has been unloaded, type the following on terminal:
     ```bash
     sudo lsmod
     ```
   - After unloading, write the following on terminal:
     ```bash
     sudo dmesg
     ```
     ![Error](https://github.com/regular-life/OS-Assignments/blob/main/Assignment-2/Ques3/Module_Unloaded.png)
5. **Delete module files:**
   To delete all module files, type the following on terminal:
   ```bash
   make clean
   ```

## Understanding the Code
The given code is a Linux kernel module designed to count and display information about running processes. It interacts with the kernel's process management infrastructure to achieve this. Let's break down the code and understand its functionality step by step:
### Module Initialization
   ```c
    MODULE_AUTHOR("Yash") ;
    MODULE_LICENSE("GPL") ;
    MODULE_DESCRIPTION("Module to count running processes.") ;
   ```
   These lines specify metadata about the module, such as the author, license, and description.

### count_running_processes Function
   ```c
   static long long count_running_processes(void)
   {
      long long cnt = 0 ;
      rcu_read_lock() ;
      for (int i = 0 ; i <= 100000000 ; i ++)
      {
         struct task_struct *task = pid_task(find_vpid(i), PIDTYPE_PID) ;
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
  ```

- This function is the heart of the module, responsible for counting and displaying running processes.
- It initializes a counter cnt and acquires a read lock on the RCU (Read-Copy-Update) mechanism using `rcu_read_lock()`. RCU is a mechanism used in the Linux kernel for efficient and safe read-side access to shared data structures.
- It then iterates through a range of process IDs (PIDs), from 0 to 100,000,000.
- For each PID, it attempts to find the corresponding process using `find_vpid(i)` and specifies that it's searching for a process with type `PIDTYPE_PID`.
- If a valid process structure is found (`if (task)`), it checks if the process is in the `TASK_RUNNING` state (`if (task->__state == 0)`). The `TASK_RUNNING `state indicates that the process is currently runnable and active.
- If the process is indeed running, it increments the counter `cnt` and prints information about the process using `printk`. This includes the process's name (`task->comm`) and its PID (`task->pid`).
- Finally, it releases the RCU read lock using `rcu_read_unlock()` and returns the count of running processes.

### Module Initialization and Cleanup
   ```c
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
   ```
- These functions are responsible for module initialization and cleanup.
- `display_init` is called when the module is loaded. It invokes `count_running_processes` to count running processes, then prints this count along with a success message using `printk`.
- `display_cleanup` is called when the module is unloaded. It simply prints a message to indicate successful unloading.

### Module Entry and Exit Points
   ```c
   module_init(display_init) ;
   module_exit(display_cleanup) ;
   ```
- These lines specify the entry and exit points for the module. `module_init` specifies the function to call during module initialization, and `module_exit` specifies the function to call during module cleanup.

## Conclusion
This kernel module demonstrates how to count the number of running processes using a custom system call. When loaded, the module provides information about the number of active processes on the system. Understanding kernel module development is essential for low-level system programming.

<br />

---

## Contributors
- Yash Bhardwaj - [GitHub Profile](https://github.com/regular-life)
- Sanyam Garg - [GitHub Profile](https://github.com/SanyamGarg12)

Feel free to reach to any of us at sanyam22448@iiitd.ac.in or yash22586@iiitd.ac.in for any questions or issues related to the above assignment.

