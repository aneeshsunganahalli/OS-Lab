
# C Header Files and Their Uses

---

## 1. `#include <stdio.h>` - Standard Input/Output
Functions: `printf()`, `scanf()`, `fopen()`, `fclose()`, `fread()`, `fwrite()`

---

## 2. `#include <stdlib.h>` - Standard Library
Functions: `malloc()`, `calloc()`, `free()`, `exit()`, `system()`, `atoi()`, `atof()`, `rand()`, `srand()`

---

## 3. `#include <unistd.h>` - Unix Standard (POSIX)
Functions: `fork()`, `getpid()`, `sleep()`, `read()`, `write()`

---

## 4. `#include <pthread.h>` - POSIX Threads
Functions: `pthread_create()`, `pthread_join()`, `pthread_mutex_lock()`, `pthread_mutex_unlock()`

---

## 5. `#include <string.h>` - String Handling
Functions: `strcpy()`, `strncpy()`, `strlen()`, `strcmp()`, `strcat()`

---

## 6. `#include <math.h>` - Mathematical Functions
Functions: `pow()`, `sqrt()`, `sin()`, `cos()`, `tan()`, `log()`, `exp()`

---

## 7. `#include <ctype.h>` - Character Type Functions
Functions: `isalpha()`, `isdigit()`, `toupper()`, `tolower()`

---

## 8. `#include <limits.h>` - Limits of Integer Types
Constants: `INT_MAX`, `INT_MIN`, `CHAR_BIT`, `LONG_MAX`

---

## 9. `#include <float.h>` - Limits of Floating Point Types
Constants: `FLT_MAX`, `FLT_MIN`, `DBL_EPSILON`

---

## 10. `#include <time.h>` - Time and Date Functions
Functions: `time()`, `difftime()`, `clock()`, `ctime()`, `localtime()`

---

## 11. `#include <errno.h>` - Error Numbers
Variable: `errno`  
Example: `ENOENT` (file not found)

---

## 12. `#include <signal.h>` - Signal Handling
Functions: `signal()`, `raise()`, `kill()`

---

## 13. `#include <assert.h>` - Debug Assertions
Function: `assert()`

---

## 14. `#include <fcntl.h>` - File Control
Used with: `open()`, `fcntl()`, file descriptor flags

---

## 15. `#include <sys/types.h>` - System Data Types
Types: `pid_t`, `size_t`

---

## 16. `#include <sys/ipc.h>` - Inter-Process Communication (IPC)
Used with: shared memory, semaphores, message queues

---

## 17. `#include <sys/shm.h>` - Shared Memory
Functions: `shmget()`, `shmat()`, `shmdt()`, `shmctl()`

---

## 18. `#include <sys/wait.h>` - Wait for Process
Functions: `wait()`, `waitpid()`
