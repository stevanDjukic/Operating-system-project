# Multithreaded Operating System Kernel
 
Project Overview
This project implements a small but fully functional operating system kernel that supports multithreading. The kernel provides memory allocation, thread management, semaphores, asynchronous context switching.

The kernel is designed as a library-based system, meaning that the user application and kernel share the same address space and form a statically linked executable, which is preloaded into memory. This architecture is common in embedded systems, where a predefined program (including the OS) is deployed on target hardware.

# Platform & Development Environment:
  - Processor Architecture: RISC-V (RV64IMA)

  - Target System: Educational RISC-V processor emulator

  - Host System: A modified version of the xv6 operating system

  - Languages: C, C++ (with optional RISC-V assembly for low-level features)

  - Build System: Makefile-based compilation

# Core Features
1) Thread Management
  - Support for user-level threads
  - Thread creation and termination
  - Thread dispatching

2) Memory Management
  - Allocation and deallocation of memory blocks
  - Custom memory allocator using continual allocation with block-based allocation
  - Memory blocks are managed in a linear manner, minimizing fragmentation

3) Synchronization Mechanisms
  - Counting semaphores for thread coordination
  - Blocking and non-blocking semaphore operations

4) System Call Interface
  - Layered API (ABI, C API, and C++ API) for user interaction
  - Implementation of system calls using software interrupts
    
5) Console I/O
  - Keyboard input handling
  - Character-based console output
    
# System Architecture
The kernel is structured into multiple layers:
  - Application Layer: User-level programs (test applications)
  - C++ API: Object-oriented interface for thread and semaphore management
  - C API: Low-level procedural interface for system calls
  - ABI (Application Binary Interface): Direct system call interface through RISC-V registers
  - Kernel Layer: Core functionalities for thread scheduling, memory management, and hardware interaction
  - Hardware Access Layer: Communication with the virtualized RISC-V hardware (provided via hw.lib)
