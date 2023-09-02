# Introduction
This is a writeup for the implementation of three custom shell commands (`word`, `dir`, and `date`) in C as part of the IIITD's CSE231 course Operating Systems - Assignment 1.

# Table of Contents
1. [word Command](#word-command)
2. [dir Command](#dir-command)
3. [date Command](#date-command)
4. [Compilation and Execution](#compilation-and-execution)
5. [Error Handling](#error-handling)
6. [Conclusion](#conclusion)

<br />

# word Command
   ## Understanding the Code:
   The `word` command is a built-in command that reads the number of words in a text file. The command can also take optional arguments for specific functionality:
   - `-n`: Ignores new line characters when counting words.
   - `-d`: Compares word counts between two text files.
   
   ## Implementation Details:
   The `word.c` program uses file I/O operations to read characters from the given files, counting words based on space and period characters. It supports the specified `-n` and `-d` options. For `-d`, the program compares the word counts of two files and indicates the difference.
   
   ## Conclusion:
   This code effectively calculates word counts in text files while handling various options like ignoring new lines and comparing counts between files. Understanding this code is essential for implementing similar text-processing utilities.

<br />

# dir Command
   ## Understanding the Code:
   The `dir` command creates a directory and changes the working path to that directory. It can take optional arguments for specific functionality:
   - `-r`: Removes the directory if it already exists and then creates a new one.
   - `-v`: Prints messages for each step in the command's execution.
   
   ## Implementation Details:
   The `dir.c` program uses the `mkdir()` system call to create directories and the `chdir()` system call to change the working directory. It handles the optional arguments `-r` and `-v` as specified.
   
   ## Conclusion:
   This code effectively manages directories, including options to remove existing directories and display verbose messages. Understanding this code is crucial for implementing directory manipulation utilities.

<br />

# date Command
   ## Understanding the Code:
   The `date` command returns a file's last modified date and time. It supports optional arguments for specific functionality:
   - `-d`: Displays the time described by a given string (e.g., '2 days ago', 'tomorrow').
   - `-R`: Outputs the date and time in RFC 5322 format.
   
   ## Implementation Details:
   The `date.c` program uses the `stat()` system call to retrieve file information, including modification time. It handles optional arguments `-d` and `-R` as specified. For `-d`, the program adjusts the time based on the given string and displays the result.
   
   ## Conclusion:
   This code effectively retrieves and formats file modification times, including options for date manipulation and RFC 5322 formatting. Understanding this code is essential for developing time-related utilities in shell scripting.

<br />

# Compilation and Execution
The `shell.c` program is the main shell that handles user input and invokes the corresponding command programs based on the provided command names and arguments. It uses the `fork()` and `execvp()` system calls to create child processes and execute the specified commands.

<br />

# Error Handling
The implemented commands include error handling for scenarios such as missing files, incorrect command syntax, and invalid options. Error messages are printed to stderr in case of errors.

<br />

# Conclusion
The Unix system shell commands (`word`, `dir`, and `date`) have been successfully implemented with C programming. The project demonstrates the use of system calls like `fork()`, `execvp()`, and `wait()` for process management, file operations, and command execution. The error handling ensures graceful handling of various scenarios, providing a reliable user experience. This project showcases the integration of custom shell commands into a Unix-like environment and provides a solid foundation for further exploration and expansion of shell functionalities.
