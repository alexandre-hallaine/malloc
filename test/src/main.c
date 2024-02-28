#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void error(const char *msg)
{
    fprintf(stderr, "Error: %s\n", msg);
    exit(1);
}

int main()
{
    void *ptr = malloc(8);
    uintptr_t addr = (uintptr_t)ptr;

    if (addr == 0)
        error("malloc returned NULL");
    if ((addr & 0x10) != 0)
        error("malloc returned unaligned address");

    free(ptr);
    ptr = malloc(8);
    if ((uintptr_t)ptr != addr)
        error("malloc did not return the same address after free");

    ptr = realloc(ptr, 1024 * 1024 * 128);
    if (ptr == NULL)
        error("realloc returned NULL with the size of 128M");

    printf("malloc, free, realloc: OK\n");
    return 0;
}
