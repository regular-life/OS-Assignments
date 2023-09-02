# Introduction
This is a writeup for the codes of IIITD's CSE231 course Operating Systems - Assignment 1 Question 1.


# Table of Contents
1. [Question A](#a)
2. [Question B](#a)
3. [Question B_Bonus](#b_bonus)

<br />

# A.
## Understanding the Code:
- The code starts by including the necessary header files (`<stdio.h>`, `<stdlib.h>`, `<unistd.h>`, and `<sys/wait.h>`).
- The main function begins by calling `fork()` to create a new process. The `fork()` function returns different values for the parent and child processes.
- If `fork()` fails (returns a negative value), the parent process will print an error message.
- If `fork()` succeeds and returns a positive value, the parent process proceeds into the first else if block. The parent process prints its own PID using `getpid()` **[statement A executed]** . Then, it waits for the child process to finish using `wait(NULL)`. The `wait()` function ensures that the parent process pauses and does not proceed until the child process completes.
- If `fork()` succeeds and returns 0, the code is executed in the child process. The child process prints its own PID using `getpid()` and the parent's PID using `getppid()` **[statement C & D executed]** .
- Once the child process finishes execution, the parent process continues and prints the child's PID stored in child_pid **[statement B executed]**.


## Conclusion:
This code effectively demonstrates the creation of a parent-child relationship using `fork()` and the synchronization of their execution using `wait()`. It provides insight into how processes are created and managed in a Unix-like operating system, emphasizing the importance of synchronization in controlling the order of execution. Understanding this foundational concept is crucial for developing more complex programs that involve multiple concurrent processes.

<br />

# B.
## Understanding the Code:
- The code begins by importing the necessary header files (`<stdio.h>`, `<stdlib.h>`, `<unistd.h>`, `<fcntl.h>`, `<sys/types.h>`, and `<sys/wait.h>`).
- The factorial function is defined to calculate the factorial of a given number n. It initializes ans to 1 and iterates through the numbers from 2 to n, updating ans with each multiplication. The function then prints the calculated factorial value. (Standard Iterative method for calculation of Factorial.)
- The fibonacci function computes and prints the first n elements of the Fibonacci series. It initializes prev to 0 and curr to 1. It then iteratively updates curr by adding prev and shifts the values for the next iteration. (Classic Iterative method for calculating Fibonacci Numbers.)
- The `main()` function creates a child process using `vfork()`. An error message is displayed if the `vfork()` call fails (returns a negative value).
- If `vfork()` succeeds and returns 0, the code is executed within the child process. The child process calls the factorial function to compute and print the factorial of 4.
- If `vfork()` succeeds and returns a positive value (not 0), the code is executed within the parent process. The parent process invokes the fibonacci function to calculate and print the first 16 elements of the Fibonacci series.
- The parent process waits for the child process to complete its computations using the `wait(NULL)` system call - which is the inbuilt command in `vfork()`.
      
## Conclusion:
This code exemplifies the usage of the `vfork()` system call to create a parent-child relationship, where each process performs distinct computations. The program offers insights into concurrent processing and synchronization by computing factorials and generating the Fibonacci series. The parent's wait for the child process to finish exemplifies the importance of coordination when managing multiple processes. Understanding these concepts is pivotal for developing programs that leverage the parallelism offered by modern operating systems.


<br />

# B_Bonus.
## Understanding the Code:
- The code begins by importing the necessary header files (`<stdio.h>`, `<stdlib.h>`, `<unistd.h>`, `<fcntl.h>`, `<sys/types.h>`, and `<sys/wait.h>`).
- The factorial function is defined to calculate the factorial of a given number n. It initializes ans to 1 and iterates through the numbers from 2 to n, updating ans with each multiplication. The function then prints the calculated factorial value. (Standard Iterative method for calculation of Factorial.)
- The fibonacci function computes and prints the first n elements of the Fibonacci series. It initializes prev to 0 and curr to 1. It then iteratively updates curr by adding prev and shifts the values for the next iteration. (Classic Iterative method for calculating Fibonacci Numbers.)
- Inside the `main()` function, a child process is created using the `fork()` system call. An error message is displayed if the `fork()` call fails (returns a negative value).
- If `fork()` succeeds and returns a positive value (not 0), the code executes within the parent process. The parent process employs the fibonacci function to calculate and print the first 16 elements of the Fibonacci series.
- If `fork()` succeeds and returns 0, the code executes within the child process. The child process invokes the factorial function to compute and print the factorial of 4.
      
## Conclusion:
This code exemplifies how the `fork()` system calls can be utilized to establish parent-child relationships, where each process undertakes distinct computations. The program offers insights into concurrent processing and synchronization by calculating factorials and generating the Fibonacci series. The unique feature here is that the child process waits for the parent process to finish its computations, showcasing the significance of coordination in managing multiple processes. Grasping these fundamental concepts is pivotal for developing programs that harness the parallelism facilitated by modern operating systems.
