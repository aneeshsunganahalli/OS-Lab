# C Header Files and OS Concepts

This README organizes commonly used C headers with a focus on **operating system concepts**, including process management, inter-process communication, memory management, and file handling.

---

## 1. Standard Input/Output
**Header:** `#include <stdio.h`  
**Functions:**  
- `printf()`, `scanf()`, `fprintf()`, `fscanf()`  
- `fopen()`, `fclose()`, `fread()`, `fwrite()`  
- `puts()`, `gets()`, `perror()`  

**Use:** Basic I/O operations, reading/writing files and console output.

---

## 2. Standard Library
**Header:** `#include <stdlib.h>`  
**Functions:**  
- Dynamic memory: `malloc()`, `calloc()`, `free()`  
- Process control: `exit()`, `system()`  
- Conversions: `atoi()`, `atof()`, `strtol()`  
- Random numbers: `rand()`, `srand()`  

**Use:** Memory allocation, process termination, conversions, randomization.

---

## 3. Unix Standard / POSIX
**Header:** `#include <unistd.h>`  
**Functions:**  
- Process management: `fork()`, `getpid()`, `getppid()`, `_exit()`  
- File I/O: `read()`, `write()`, `close()`, `lseek()`  
- Sleep and delays: `sleep()`, `usleep()`  
- Pipe and IPC support: `pipe()`, `dup()`, `dup2()`  

**Use:** Process creation, low-level file I/O, sleep, and pipes.

---

## 4. Process Control
**Headers:** `#include <sys/types.h>`, `#include <sys/wait.h>`  
**Functions / Types:**  
- `pid_t` (process ID type)  
- `wait()`, `waitpid()` – wait for child processes  
- `getpriority()`, `setpriority()` – process priority  

**Use:** Managing child processes and process termination.

---

## 5. Signal Handling
**Header:** `#include <signal.h>`  
**Functions:**  
- `signal()`, `sigaction()` – register signal handlers  
- `kill()`, `raise()` – send signals to processes  

**Use:** Handling interrupts, termination, and custom signals.

---

## 6. Shared Memory and IPC
**Headers:** `#include <sys/ipc.h>`, `#include <sys/shm.h>`  
**Functions:**  
- `shmget()` – create/get shared memory segment  
- `shmat()` – attach shared memory  
- `shmdt()` – detach shared memory  
- `shmctl()` – control operations on shared memory  

**POSIX version:** `#include <sys/mman.h>`, `#include <fcntl.h>`  
**Functions:**  
- `shm_open()` – create/open shared memory object  
- `mmap()` – map memory to address space  
- `munmap()` – unmap memory  
- `shm_unlink()` – delete shared memory object  

**Use:** Inter-process communication through shared memory.

---

## 7. Directory and File Handling
**Headers:** `#include <dirent.h>`, `#include <fcntl.h>`  
**Functions:**  
- Directory operations: `opendir()`, `readdir()`, `closedir()`  
- File operations: `open()`, `creat()`, `fcntl()`  
- Low-level file I/O: `read()`, `write()`, `lseek()`, `close()`  

**Use:** Managing files and directories at a system level.

---

## 8. Memory and Limits
**Headers:** `#include <limits.h>`, `#include <float.h>`  
**Constants:**  
- Integer limits: `INT_MAX`, `INT_MIN`, `CHAR_BIT`  
- Floating point limits: `FLT_MAX`, `DBL_EPSILON`  

**Use:** Determining size limits for data types and arrays.

---

## 9. String Handling
**Header:** `#include <string.h>`  
**Functions:**  
- Copying & concatenation: `strcpy()`, `strncpy()`, `strcat()`  
- Comparison: `strcmp()`, `strncmp()`  
- Search: `strstr()`, `strchr()`  
- Length: `strlen()`  

**Use:** Working with C-style strings and buffers.

---

## 10. Character Utilities
**Header:** `#include <ctype.h>`  
**Functions:**  
- `isalpha()`, `isdigit()`, `isalnum()`  
- `toupper()`, `tolower()`  

**Use:** Character classification and conversion.

---

## 11. Time and Clocks
**Header:** `#include <time.h>`  
**Functions:**  
- `time()`, `difftime()`, `clock()`  
- `ctime()`, `localtime()`, `gmtime()`  

**Use:** Measure time, get timestamps, and handle date/time.

---

## 12. Error Handling
**Header:** `#include <errno.h>`  
**Variables / Constants:**  
- `errno` – global error variable  
- Predefined error codes: `ENOENT`, `EACCES`, etc.  
- Use with `perror()` to print error messages  

---

## 13. Assertions
**Header:** `#include <assert.h>`  
**Function:** `assert(condition)` – terminate if condition is false  

**Use:** Debugging and validating assumptions in code.

---

## 14. POSIX Threads
**Header:** `#include <pthread.h>`  
**Functions:**  
- `pthread_create()`, `pthread_join()` – create and join threads  
- `pthread_mutex_lock()`, `pthread_mutex_unlock()` – thread synchronization  

**Use:** Multi-threaded programming and synchronization.

---

## 15. Mathematics
**Header:** `#include <math.h>`  
**Functions:**  
- `pow()`, `sqrt()`, `sin()`, `cos()`, `tan()`, `log()`, `exp()`  

---

### ✅ Summary

This guide organizes C headers around **operating system concepts**:

- **Process Management:** `fork()`, `wait()`, `getpid()`, `signal()`  
- **Inter-Process Communication:** `shmget()`, `shmat()`, `shm_open()`, `mmap()`  
- **Memory & Limits:** `malloc()`, `free()`, `INT_MAX`, `FLT_MAX`  
- **File & Directory Handling:** `open()`, `read()`, `write()`, `opendir()`, `readdir()`  
- **Threads & Synchronization:** `pthread_create()`, `pthread_mutex_lock()`  
- **Time & Utilities:** `time()`, `sleep()`, `strlen()`, `strcpy()`
