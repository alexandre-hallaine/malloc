#include "functions.h"

// Free a block of memory
void free(void *ptr)
{
    if (ptr == NULL)
        return;

    t_heap *heap = heap_get(ptr);
    if (heap == NULL)
        return;

    t_block *block = ptr - sizeof(t_block);
    block->free = true;

    heap_defragment(heap);
    heap_free(heap);
}
