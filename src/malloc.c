#include "functions.h"

t_heap *heap_first = NULL;

void *malloc(size_t size)
{
    block_size_align(&size);
    t_heap_type type = heap_type(size);
    if (size > type * HEAP_SIZE - sizeof(t_heap) - sizeof(t_block))
        return NULL;

    // find a free block that fits
    t_block *block_found = block_find(size);
    if (block_found == NULL)
        return NULL;

    block_split(block_found, size);
    block_found->free = false;

    return (void *)block_found + sizeof(t_block);
}
