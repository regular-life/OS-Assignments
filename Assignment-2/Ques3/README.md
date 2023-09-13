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
   - The module has been loaded on the kernel.
   - Now, write the following command to see the module in action:
     ```bash
     sudo dmesg
     ```
   - A long list will appear on the terminal and you will see the the number of currently active processes at the bottom.
   - To unload the module from the kernel, type the following:
     ```bash
     sudo rmmod code.ko
     ```
5. **Delete module files:**
   To delete all module files, type the following on terminal:
   ```bash
   make clean
   ```

## Understanding the Code
- The code begins by including necessary header files (`<linux/kernel.h>`, `<linux/module.h>`, `<linux/signal.h>`, `<linux/sched.h>`, and `<linux/printk.h>`).
- The `count_running_processes()` function is defined to count the number of running processes using the `for_each_process` macro.
- In the `init_module()` function, the `count_running_processes()` function is called to count the running processes and print the result.
- The `cleanup_module()` function is called when the module is unloaded and simply prints a message indicating that the module has been unloaded.

## Conclusion
This kernel module demonstrates how to count the number of running processes using a custom system call. When loaded, the module provides information about the number of active processes on the system. Understanding kernel module development is essential for low-level system programming.

<br />

---

## Contributors
- Yash Bhardwaj - [GitHub Profile](https://github.com/regular-life)
- Sanyam Garg - [GitHub Profile](https://github.com/SanyamGarg12)

Feel free to reach to any of us at sanyam22448@iiitd.ac.in or yash22586@iiitd.ac.in for any questions or issues related to the above assignment.

