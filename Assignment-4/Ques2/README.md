
# Car and Passengers Simulation

## Table of Contents
1. [Introduction](#introduction)
2. [How to Run the Program](#how-to-run-the-program)
3. [Code Logic](#code-logic)
4. [Concurrency Bug Avoidance](#concurrency-bug-avoidance)
5. [Error Handling](error-handling)
6. [Conclusion](#conclusion)

## Introduction
This is a writeup for the simulation of Car and Passenger in C language as part of the **IIITD CSE231 course Operating Systems** - Assignment 4.

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
   - Unzip the file and navigate to "Assignment-4" -> "Ques2".
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
The code models the car and passenger actions as threads, with the car performing loading, running, and unloading procedures. Passengers board and offboard the car based on semaphore synchronization.

### Car Thread (`void* car(void* args)`)
- Loading Process: Simulates the time it takes for passengers to board.
- Passenger Boarding: Signals each passenger thread using a semaphore.
- Ride Simulation: Simulates the ride's duration.
- Unloading Process: Simulates the time it takes for passengers to disembark.

### Passenger Thread (`void* passenger(void* args)`)
- Boarding: Passengers wait for a semaphore signal from the car.
- Ride Completion: Passengers signal the car to indicate ride completion.
- Offboarding: Passengers wait for the car to signal them before offboarding.

## Concurrency Bug Avoidance
1. Semaphores: Used for synchronization between the car and passenger threads.
2. Flags: `load_flag` and `unload_flag` control boarding and offboarding processes.
3. Sleep Function: Used to simulate time.

## Error Handling
The code includes error handling mechanisms using the `perror` function for various operations involving semaphores (`sem_post`, `sem_wait`, `sem_init`, `sem_destroy`) and threads (`pthread_create`, `pthread_join`). In case of any failure during these operations, the program prints a descriptive error message and exits with a status code of 1.



## Conclusion
The code provides a simple simulation of a car and passengers using threads and semaphores. It aims to avoid concurrency bugs and deadlock by careful synchronization. Feel free to modify the code for experimentation.

<br />

---
## Contributors
- Yash Bhardwaj - [GitHub Profile](https://github.com/regular-life)
- Sanyam Garg - [GitHub Profile](https://github.com/SanyamGarg12)

Feel free to reach to any of us at sanyam22448@iiitd.ac.in or yash22586@iiitd.ac.in for any questions or issues related to the above assignment.
