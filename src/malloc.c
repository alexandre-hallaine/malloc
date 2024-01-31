#include "functions.h"

#include <sys/mman.h>

t_heap *heap_first = NULL;

void *malloc(size_t size)
{
    block_size_align(&size);
    if (size > (size_t)HEAP_SIZE)
        return NULL;

    // find a free block that fits
    t_block *block_found = NULL;
    for (t_heap *heap = heap_first; heap != NULL && block_found == NULL; heap = heap->next)
        for (t_block *block = (void *)heap + sizeof(t_heap); block != NULL && block_found == NULL; block = block->next)
            if (block->free && block->size >= size)
                block_found = block;

    // if no free block found, allocate a new heap
    if (block_found == NULL)
    {
        t_heap *heap = heap_allocate(HEAP_SIZE);
        if (heap == NULL)
            return NULL;
        block_found = (void *)heap + sizeof(t_heap);
    }

    if (block_found->size > size)
        block_split(block_found, size);
    block_found->free = false;

    return (void *)block_found + sizeof(t_block);
}
