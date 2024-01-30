#include "functions.h"

void free(void *ptr)
{
    if (ptr == NULL)
        return;

    t_block *block = ptr - sizeof(t_block);
    block->free = true;

    // find the heap that contains the block and defragment it
    for (t_heap *heap = heap_first; heap != NULL; heap = heap->next)
    {
        t_block *block_first = (void *)heap + sizeof(t_heap);
        if ((void *)block >= (void *)block_first && (void *)block < (void *)block_first + heap->size)
            heap_defragment(heap);
    }
}
