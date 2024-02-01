#include "functions.h"

#include <stdlib.h>
#include <stdio.h>

int main()
{
    void *ptr1 = malloc(1024);
    printf("Simple allocation:\n");
    show_alloc_mem();
    free(ptr1);

    printf("\n");
    ptr1 = malloc(8);
    void *ptr2 = malloc(32);
    void *ptr3 = malloc(16);
    printf("Multiple allocations:\n");
    show_alloc_mem();
    free(ptr2);

    printf("\n");
    ptr1 = realloc(ptr1, 25);
    printf("After reusing block:\n");
    show_alloc_mem();

    printf("\n");
    free(ptr1);
    free(ptr3);
    printf("After freeing all blocks:\n");
    show_alloc_mem();
}
