#include "types.h"

#include <stdio.h>

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

void show_alloc_mem()
{
    for (t_heap *heap = heap_first; heap != NULL; heap = heap->next)
    {
        printf("%s: (map size: %d)\n", heap_type_to_string(heap->type), heap->type * HEAP_SIZE);
        for (t_block *block = (void *)heap + sizeof(t_heap); block != NULL; block = block->next)
            printf("\t%p: %lu bytes, %s\n", block, block->size, block->free ? "free" : "used");
    }
}
