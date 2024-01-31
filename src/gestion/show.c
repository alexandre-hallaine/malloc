#include "types.h"

#include <stdio.h>

void show_alloc_mem()
{
    for (t_heap *heap = heap_first; heap != NULL; heap = heap->next)
    {
        printf("%p : heap\n", heap);
        for (t_block *block = (void *)heap + sizeof(t_heap); block != NULL; block = block->next)
            printf(" %p - %p : %lu bytes\n", (void *)block + sizeof(t_block), (void *)block + sizeof(t_block) + block->size, block->size);
    }
}
