# Malloc

Welcome to my implementation of the classic memory management functions `malloc`, `free`, and `realloc`! This project was completed as part of my studies at 42 Paris, and I am excited to share it with you.

## Getting Started

To get started with this project, follow these simple steps:

1. Clone the repository to your local machine using Git or download the zip file.
2. Navigate to the root directory of the project in your terminal.
3. Run `make` to build the shared object library (`.so`) for the project.
4. To run the program, execute `sh run.sh` followed by the desired command.

## Functions Implemented

`void *malloc(size_t size)`: Allocates a memory block of the specified size and returns a pointer to the beginning of the block. Returns NULL if the request cannot be satisfied.

`void free(void *ptr)`: Deallocates the memory block pointed to by the given pointer and marks it as available for further allocation. Takes no action if ptr is NULL.

`void *realloc(void *ptr, size_t size)`: Changes the size of the previously allocated memory block pointed to by ptr to the specified size. Preserves content in the overlapping portion between the original and adjusted sizes; beyond that limit, behavior is undefined. Newly appended regions aren't initialized upon expanding memory blocks. Acts like malloc() when presented with a null pointer.

## Testing

A set of tests has been included in the `test` directory to ensure proper functionality of the implemented functions. These tests cover various scenarios and edge cases to validate the correctness and robustness of the code. You may run the tests by executing `sh run.sh test/test` after building the project and the test.

Happy coding, and enjoy exploring the world of dynamic memory management!