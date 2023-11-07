# MeMS - Memory Management System

This project implements a Memory Management System (MeMS) where memory allocation, deallocation, and statistical analysis can be performed. MeMS provides functionalities for efficient memory handling and utilization.

## Table of Contents
1. [Introduction](#introduction)
2. [Setup and Initialization](#setup-and-initialization)
3. [Usage and Functionality](#usage-and-functionality)
4. [Memory Allocation and Deallocation](#memory-allocation-and-deallocation)
5. [Statistical Analysis](#statistical-analysis)
6. [Compilation and Execution](#compilation-and-execution)
7. [Error Handling](#error-handling)
8. [Conclusion](#conclusion)
9. [Contributors](#contributors)

## Introduction
The MeMS system is designed to efficiently manage memory by utilizing mmap system calls and a custom data structure that tracks memory segments as HOLE (unused) or PROCESS (allocated). The system handles memory allocation, deallocation, and provides statistical information about the memory utilization.

## Setup and Initialization
The memory management system requires initialization using `mems_init()` to set up the main parameters for the MeMS system. Additionally, to release allocated memory and clean up resources, use `mems_finish()`.

## Usage and Functionality
The system provides various functionalities:
- `mems_malloc(size_t size)`: Allocates memory using mmap or from the free list.
- `mems_print_stats()`: Prints statistical information about memory utilization and free segments.
- `mems_get(void *v_ptr)`: Retrieves the physical address mapped to a given virtual address.
- `mems_free(void *v_ptr)`: Frees up memory pointed by the virtual address and adds it back to the free list.

## Memory Allocation and Deallocation
- `HOLE_alloc(size_t size)`: Allocates memory by reusing a segment from the free list or using mmap for new memory allocation.
- `InsertDict(void *virtual_address, void *physical_address)`: Inserts virtual and physical addresses into the dictionary.
- `searchDict(void *virtual_address)`: Searches for the physical address mapped to the virtual address in the dictionary.

## Statistical Analysis
`mems_print_stats()` displays information such as:
- Pages utilized by `mems_malloc`.
- Amount of unused memory (segments in the free list).
- Details about each node in the main chain and each segment in the sub-chain.

## Compilation and Execution
The MeMS system code can be included in your project. Ensure necessary system headers are included, and the `mems.h` file is properly referenced in your source code. 

## Error Handling
The system includes error messages for critical operations like memory allocation failure, key not found in the dictionary during removal, etc.

## Conclusion
MeMS offers an efficient memory management system that tracks memory allocation and deallocation, provides statistical insights, and helps manage memory in a structured manner.

---

## Contributors
- [Your Name] - [GitHub Profile](Link to your GitHub profile)

For any queries or further information, please reach out to the contributors listed above.
