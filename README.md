# Memory Manager
A simulation of memory manager operations.

In the C standard library, functions `malloc` and `free` are used for memory allocation and deallocation. This program implements a custom version of memory allocation. Specifically, it implements the following FOUR functions in the C programming language:

* `void *memory_alloc(unsigned int size);`
* `int memory_free(void *valid_ptr);`
* `int memory_check(void *ptr);`
* `void memory_init(void *ptr, unsigned int size);`

The function **memory_alloc** provides services analogous to the standard `malloc`. The input parameters specify the size of the requested contiguous block of memory, and the function returns a pointer to a successfully allocated free memory block, or `NULL` if it is not possible to allocate a contiguous block of the requested size.

The function **memory_free** serves to free an allocated memory block, similar to the `free` function. The function returns 0 if the block was successfully freed (the function executed successfully), or 1 if not. It is assumed that the parameter is always a valid pointer returned by previous calls to `memory_alloc`, which has not yet been freed.

The function **memory_check** is used to check whether the parameter (pointer) is a valid pointer, which was returned by a previous call to `memory_alloc` and has not yet been freed by `memory_free`. The function returns 0 if the pointer is invalid; otherwise, it returns 1.

The function **memory_init** is used to initialize the managed free memory. It is assumed that the function is called exactly once before any other calls to `memory_alloc`, `memory_free`, or `memory_check`. As an input parameter, the function receives a block of memory that can be used to organize and allocate free memory.

The program uses only one global variable to store the pointer to the memory passed to the `memory_init` function. The pointers allocated by `memory_alloc` must be exclusively from the block of memory that was provided to the `memory_init` function.

## Brief Algorithm Description
In my solution, I decided to use an explicit list of free blocks. As a data structure, I used `typedef struct`, which the compiler shows to be 16B in size. This structure is used as a header for the blocks, and several of these structures create a linked list of free blocks.

### Memory_init
Checks if the input pointer is not `NULL`. Sets the global pointer to the start of the total memory. Creates a `master_head`, which contains the total size of the memory. This header is never overwritten. Immediately after it, a second header is created, representing the first empty block.

### Memory_alloc
First, the total memory size is retrieved from `master_head`, and it checks whether more memory is being allocated than the total available memory.

Next, a `while` loop results in two pointers. The first points to the block where memory will be allocated (the block must meet the conditions for allocation; otherwise, it is not selected). The second pointer is the predecessor of the first.

If a suitable block is found, it checks whether the block needs to be split. If so, it selects the allocated part and creates a new empty block containing the remaining memory, which is added to the list of free blocks.

The function returns a pointer to the start of the allocated memory or prints an error message if the memory allocation fails.

### Memory_free
First, it checks if the input parameter of the function is a valid pointer.

The list of free blocks is searched for the pointer that would precede the block being freed. Then, the block to be freed is added to the list of free blocks by redirecting the individual pointers.

Next, it checks whether the freed block can be merged with any adjacent free block in the memory address space. The function first attempts a forward merge and then attempts a backward merge.

### Memory_check
The function traverses the list of free blocks, and if the pointer is not found in it, then the given part is allocated.
