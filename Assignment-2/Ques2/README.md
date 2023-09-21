# Custom Process Scheduler Benchmarking

This program demonstrates the use of Linux's scheduling policies for different processes. It creates three child processes, each of which performs a counting task. The goal is to benchmark these processes based on different scheduling policies and priorities. The execution times for each process are measured, and the results are displayed in a histogram.

## Table of Contents
1. [Introduction](#introduction)
2. [How to Run the Application](#how-to-run-the-application)
3. [Process Descriptions](#process-descriptions)
4. [Compilation and Execution](#compilation-and-execution)
5. [Error Handling](#error-handling)
6. [Conclusion](#conclusion)

## Introduction
This program creates three child processes and assigns them different scheduling policies and priorities. Each child process performs a counting task from 1 to 2^32. The parent process measures the execution times of these child processes and displays the results in a histogram.

## How to Run the Application
1. **Environment:**
   - Ensure that you are running this program in a Linux environment.

2. **Compilation:**
   - Compile the program using the provided Makefile:
     ```bash
     make all
     ```

3. **Execution:**
   - Run the program using the following command:
     ```bash
     sudo taskset -c 3 ./a.out
     ```
     - The `taskset` command ensures that the program runs on a specific CPU core (`core 3` in this example).

4. **View Results:**
   - After execution, the program generates a histogram to compare the execution times of processes with different scheduling policies.
   - The histogram is displayed using Python and Matplotlib.

## Process Descriptions
1. **Process 1 (SCHED_OTHER):**
   - This process uses the SCHED_OTHER scheduling policy with standard priority (nice: 0).

2. **Process 2 (SCHED_RR):**
   - This process uses the SCHED_RR scheduling policy with default priority.

3. **Process 3 (SCHED_FIFO):**
   - This process uses the SCHED_FIFO scheduling policy with default priority.

## Compilation and Execution
The program is compiled using the provided Makefile, and the `a.out` executable is generated. To execute the program, use the `taskset` command to assign it to a specific CPU core.

## Error Handling
The program includes error handling for various scenarios, such as failed fork operations. Error messages are printed to stderr in case of errors.

## Conclusion
This program demonstrates the use of different scheduling policies in Linux for managing and benchmarking processes. By comparing the execution times of processes with different scheduling policies, it provides insights into process scheduling in the Linux operating system.
