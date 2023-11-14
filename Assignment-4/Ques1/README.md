# Dining Philosophers Problem: Deadlock-Free Solution

<br />

## Table of Contents
1. [Introduction](#introduction)
2. [How to Run the Program](#how-to-run-the-program)
3. [Why deadlocks can occur in the problem setup](why-deadlocks-can-occur-in-the-problem-setup)
4. [How your proposed solution avoids deadlock](how-your-proposed-solution-avoids-deadlock)
5. [Fairness of the solution](fairness-of-the-solution)
6. [Conclusion](#conclusion)
7. [Contributors](#contributors)

## Introduction
This is a writeup for the solution of The Dining Philospher's Problem in C language as part of the **IIITD CSE231 course Operating Systems** - Assignment 4.

## How to Run the Program
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
   - Download the .zip file from https://github.com/regular-life/OS-Assignments.
3. **Opening the Project:**
   - Unzip the file and navigate to "Assignment-4" -> "Ques1".
   - Right-click on the screen and select "Go to terminal here" (or any other similar option).
4. **Running the program:**
   - Make executables by the following command:
     ```bash
     make install
     ```
   - Run the executables by the following command:
     ```bash
     make run
     ```
5. **Delete the executables:**
   ```bash
   make clean
   ```

## Why deadlocks can occur in the problem setup
  - Deadlocks can occur when all the philosphers simultaneously try to pick forks on their left or all on right. This happens because all philosphers are trying to eat, but are unable to.
  - Deadlock can also occur when a person gets his forks, but there is no available bowl, the people next to him have the bowls, but neither have the required forks to eat.

## How your proposed solution avoids deadlock
  - The code uses a global mutex `overall_lock` to control access to critical sections where philosophers interact with shared resources (bowls and forks). This global mutex ensures that only one philosopher at a time can check for available bowls and try to pick up forks. This approach helps prevent circular waiting and, consequently, avoids deadlocks.
    ```c
    pthread_mutex_t overall_lock = PTHREAD_MUTEX_INITIALIZER;
    ```
  - The main solution revolves around the idea that a philospher only consumes food if there is atleast one available bowl and the relevant forks he needs are free to use.
## Fairness of the solution
  - The solution is fair since as soon as a philospher consumes a bit of food, the bowl becomes available for use.
  - Basically, a philospher consumes food for an infinite number of times to prevent starvation.
  - Moreover, at max 2 philosphers can eat food concurrently ensuring that every philospher gets their chance ASAP.

## Conclusion
The provided code attempts to address the Dining Philosophers problem by using a global mutex to control access to shared resources. The solution aims to prevent deadlocks and maintain fairness, allowing multiple philosophers to eat concurrently based on the availability of bowls and forks. However, some minor adjustments could improve the efficiency and readability of the code.

<br />

---

## Contributors
- Yash Bhardwaj - [GitHub Profile](https://github.com/regular-life)
- Sanyam Garg - [GitHub Profile](https://github.com/SanyamGarg12)

Feel free to reach to any of us at sanyam22448@iiitd.ac.in or yash22586@iiitd.ac.in for any questions or issues related to the above assignment.
