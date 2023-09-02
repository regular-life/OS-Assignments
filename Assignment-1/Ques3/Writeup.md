# Arithmetic Calculator Bash Script

## Introduction
This is a writeup for the implementation of Arithmetic Calculator using File I/O in Bash Script as part of the **IIITD CSE231 course Operating Systems** - Assignment 1.

## Table of Contents
1. [Understanding the Code](#understanding-the-code)
2. [Conclusion](#conclusion)

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
