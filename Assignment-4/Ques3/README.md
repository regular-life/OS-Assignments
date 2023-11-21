# Cars Crossing Bridge Simulation

## Table of Contents
1. [Introduction](#introduction)
2. [How to Run the Program](#how-to-run-the-program)
3. [Code Logic](#code-logic)
4. [Avoiding concurrency bugs](#avoiding-concurrency-bugs)
5. [Conclusion](#conclusion)
6. [Contributors](#contributors)

## Introduction
This is a writeup for the simulation of crossing of bridge by cars from both directions (left and right) in C language as part of the **IIITD CSE231 course Operating Systems** - Assignment 4.

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
   - Unzip the file and navigate to "Assignment-4" -> "Ques3".
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

## Code Logic
The program models the scenario of cars crossing a narrow bridge over a river, with restrictions on simultaneous crossings by cars from opposite directions. The code defines two thread functions: `left()` for cars approaching from the left side and `right()` for cars from the right side. The main function initializes semaphores to control access to the bridge, and each thread represents a car. The passing function simulates the time it takes for a car to cross the bridge using the sleep function. The semaphores ensure that only a limited number of cars can be on the bridge simultaneously, preventing collisions between cars from opposite directions. Moreover, it is ensured that cars on the right side will only get their turn to travel through the bridge after all the cars on left side have traversed through the bridge.

## Avoding Concurrency Bugs
To avoid concurrency bugs, the code uses semaphores for synchronization. Semaphores provide a mechanism to control access to shared resources. The program carefully manages the entry and exit points for threads using semaphores, ensuring that only `MAX_CARS` number of cars can cross the bridge at a time. The passing function, which simulates the time a car spends crossing the bridge, is executed in a mutually exclusive manner. This prevents race conditions and ensures that the direction of each car is accurately tracked. The use of semaphores helps maintain order and prevents conflicts, ensuring the correct simulation of cars crossing the bridge without violating constraints.

## Conclusion
In conclusion, the implemented C code successfully simulates the crossing of cars over a narrow bridge with constraints on the number of simultaneous crossings and restrictions on opposite-direction traffic. The code utilizes semaphores for synchronization, preventing concurrency bugs and ensuring a realistic simulation. The program provides a foundation for further exploration and improvement, such as incorporating additional features or optimizing the simulation. Overall, the code demonstrates effective synchronization techniques for a multi-threaded simulation.


<br />

---
## Contributors
- Yash Bhardwaj - [GitHub Profile](https://github.com/regular-life)
- Sanyam Garg - [GitHub Profile](https://github.com/SanyamGarg12)

Feel free to reach to any of us at sanyam22448@iiitd.ac.in or yash22586@iiitd.ac.in for any questions or issues related to the above assignment.
