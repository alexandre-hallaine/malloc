#include "types.h"

#include <stdio.h>

// Get the string representation of a heap type
char *heap_type_to_string(t_heap_type type)
{
    switch (type)
    {
    case TINY:
        return "TINY";
    case SMALL:
        return "SMALL";
    case LARGE:
        return "LARGE";
    default:
        return "UNKNOWN";
    }
}

// Show metadata of the allocated memory
void show_alloc_mem()
{
    for (t_heap *heap = heap_first; heap != NULL; heap = heap->next)
    {
        printf("%s: (map size: %d)\n", heap_type_to_string(heap->type), heap->type * HEAP_SIZE);
        for (t_block *block = (void *)heap + sizeof(t_heap); block != NULL; block = block->next)
            printf("\t%p: %lu bytes, %s\n", block, block->size, block->free ? "free" : "used");
    }
}

// Show hexadecimal representation of the allocated memory
void show_alloc_mem_ex()
{
    for (t_heap *heap = heap_first; heap != NULL; heap = heap->next)
        for (t_block *block = (void *)heap + sizeof(t_heap); block != NULL; block = block->next)
            if (!block->free)
            {
                void *ptr = (void *)block + sizeof(t_block);
                for (size_t i = 0; i < block->size; i++)
                {
                    if (i % 8 == 0)
                        printf("%p: ", ptr + i);
                    printf("%02x ", *(char *)(ptr + i));
                    if (i % 8 == 7)
                        printf("\n");
                }
            }
}
