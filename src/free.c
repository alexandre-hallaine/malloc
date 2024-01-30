#include "functions.h"

void free(void *ptr)
{
    if (ptr == NULL)
        return;

    t_block *block = ptr - sizeof(t_block);
    block->free = true;

    t_heap *heap = heap_get(ptr);
    if (heap == NULL)
        return;

    heap_defragment(heap);

    t_block *block_first = (void *)heap + sizeof(t_heap);
    if (block_first->size == heap->size - sizeof(t_block))
        heap_free(heap);
}
