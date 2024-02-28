#include "functions.h"

// Update the block size to be aligned with 16 bytes
void block_size_align(size_t *size)
{
    *size += sizeof(t_block);
    *size = (*size + 15) & ~15;
    *size -= sizeof(t_block);
}

// Find a free block using first fit
t_block *block_find(size_t size)
{
    t_heap *heap;
    t_heap_type type = heap_type(size);

    if (size > type * HEAP_SIZE - sizeof(t_heap) - sizeof(t_block)) // if the size is too big for a single block
        return NULL;

    for (heap = heap_first; heap != NULL; heap = heap->next)
        if (heap->type == type)
            for (t_block *block = (void *)heap + sizeof(t_heap); block != NULL; block = block->next)
                if (block->free && block->size >= size)
                    return block;

    heap = heap_allocate(type); // if no free block found, allocate a new heap
    if (heap == NULL)
        return NULL;
    return (void *)heap + sizeof(t_heap);
}

// Split the current block into two blocks
void block_split(t_block *block, size_t size)
{
    t_block *block_new  = (void *)block + sizeof(t_block) + size;

    if (block->size < size + sizeof(t_block)) // if you cant handle the next metadata
        return;

    block_new->next = block->next;
    block_new->size = block->size - size - sizeof(t_block);
    block_new->free = true;

    block->size = size;
    block->next = block_new;
}

// Merge the next block with the current block
void block_merge(t_block *block1, t_block *block2)
{
    block1->next = block2->next;
    block1->size += sizeof(t_block) + block2->size;
}

// Merge all next free blocks
void block_merge_free(t_block *block)
{
    while (block->next != NULL && block->next->free)
        block_merge(block, block->next);
}
