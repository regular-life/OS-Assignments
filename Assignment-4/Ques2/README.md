
# Car and Passengers Simulation

## Table of Contents
1. [Introduction](#introduction)
2. [How to Run the Code](#how-to-run-the-code)
3. [Code Logic](#code-logic)
4. [Concurrency Bug Avoidance](#concurrency-bug-avoidance)
5. [Conclusion](#conclusion)

## Introduction
This C code simulates a scenario where a car has limited capacity, and passengers eagerly await their turn to take a ride. The car and passenger actions are modeled as threads, and synchronization is achieved using semaphores.

## How to Run the Code
1. **Compile the Code:**
   - Open a terminal and navigate to the directory containing the code.
   - Compile the code using the following command:
     ```bash
     gcc -o car_simulation car_simulation.c -lpthread
     ```

2. **Run the Executable:**
   - Run the compiled executable:
     ```bash
     ./car_simulation
     ```

3. **Input Parameters:**
   - Enter the capacity of the car when prompted.
   - Enter the total number of passengers when prompted.

4. **Output:**
   - The program will simulate the car and passenger threads, printing messages to the console.

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
3. Sleep Function: Used to simulate time and avoid race conditions.

## Conclusion
The code provides a simple simulation of a car and passengers using threads and semaphores. It aims to avoid concurrency bugs and deadlock by careful synchronization. Feel free to modify the code for experimentation.

<br />

---
## Contributors
- Yash Bhardwaj - [GitHub Profile](https://github.com/regular-life)
- Sanyam Garg - [GitHub Profile](https://github.com/SanyamGarg12)

Feel free to reach to any of us at sanyam22448@iiitd.ac.in or yash22586@iiitd.ac.in for any questions or issues related to the above assignment.
