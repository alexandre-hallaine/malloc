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

    t_block *block_first = (void *)heap + sizeof(t_heap);
    if (block_first->size == heap->type * HEAP_SIZE - sizeof(t_block) - sizeof(t_heap))
        heap_free(heap);
}
