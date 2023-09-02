# Arithmetic Calculator Bash Script

<br />

## Introduction
This is a writeup for the implementation of Arithmetic Calculator using File I/O in Bash Script as part of the **IIITD CSE231 course Operating Systems** - Assignment 1.

## Table of Contents
1. [How to Run the Application](#how-to-run-the-application)
2. [Understanding the Code](#understanding-the-code)
3. [Conclusion](#conclusion)
4. [Contributors](contributors)

## How to run the application
1. **Prerequisites:**
   - This program can only run on Linux.
   - gcc library.
2. **Cloning the Repository:**
   - Clone the repository to your local machine using the following command:
     ```bash
     git clone https://github.com/regular-life/OS-Assignments.git
     ```
     **OR**
   - Download the .zip file from https://github.com/regular-life/AP-Assignments.
3. **Opening the Project:**
   - Unzip the file and navigate to "Assignment-1" -> "Ques3".
   - Right-click on the screen and select "Go to terminal here" (or any other similar option).
4. **Running the program:**
   - Now make a file "input.txt" in the same directory which has text in the following format:
     ```text
     number_1 number_2 operation
     ```
   - "input.txt" can have multiple lines of input in the same format.
   - Operations supported : xor, product, compare.
   - Write the following command on terminal:
     ```bash
     make run
     ```
   - Type the following command on terminal:
     ```bash
     Calculator
     ```
   - "output.txt" created in the directory "Result" will have outputs for all the inputs in "input.txt"

---
<br />

## Understanding the Code

The script's operation can be broken down into the following steps:

1. **Directory and File Handling:**
   - The script first checks if the directory "Result" exists. If not, it creates the directory.
   - If the "Result" directory exists, the script checks if the file "output.txt" exists within it. If it does, the existing file is removed to ensure clean output.

2. **Input Processing:**
   - The script reads each line from the "input.txt" file, which contains input data for arithmetic calculations.
   - Each line is split using space as a delimiter, and the individual values are assigned to variables a, b, and operation.

3. **Arithmetic Calculation:**
   - Based on the operation provided in the input, the script performs calculations.
   - It stores the result of each calculation in the ans variable.

4. **Output Generation:**
   - The script constructs a descriptive message, op, indicating the operation and input values.
   - For each set of inputs, the script appends the op and ans to the "output.txt" file in the "Result" directory.

5. **Looping Through Input Data:**
   - The script repeats these steps for each line in the "input.txt" file until there are no more lines.

<br />

## Conclusion

This Bash script effectively acts as an arithmetic calculator by reading input from "input.txt," performing calculations based on the provided operation, and saving the results to "output.txt" in the "Result" directory. The script efficiently handles multiple sets of inputs, and using loops, conditionals, and file operations demonstrates its functionality as a math calculator. This project showcases the power and flexibility of Bash scripting for automating tasks and processing data.

<br />

---
## Contributors
- Yash Bhardwaj - [GitHub Profile](https://github.com/regular-life)
- Sanyam Garg - [GitHub Profile](https://github.com/SanyamGarg12)

Feel free to reach to any of us at sanyam22448@iiitd.ac.in or yash22586@iiitd.ac.in for any questions or issues related to the above assignment.
