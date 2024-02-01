#include "functions.h"

// Align a block size to 16 bytes
void block_size_align(size_t *size)
{
    *size += sizeof(t_block);
    *size = (*size + 15) & ~15;
    *size -= sizeof(t_block);
}

// Find a free block using first fit
t_block *block_find(size_t size)
{
    t_heap_type type = heap_type(size);
    for (t_heap *heap = heap_first; heap != NULL; heap = heap->next)
        if (heap->type == type)
            for (t_block *block = (void *)heap + sizeof(t_heap); block != NULL; block = block->next)
                if (block->free && block->size >= size)
                    return block;

    t_heap *heap = heap_allocate(type);
    if (heap == NULL)
        return NULL;
    return (void *)heap + sizeof(t_heap);
}

// Split the current block into two blocks
void block_split(t_block *block, size_t size)
{
    if (block->size < size + sizeof(t_block))
        return;

    t_block *block_new = (void *)block + sizeof(t_block) + size;
    block_new->next = block->next;
    block_new->size = block->size - size - sizeof(t_block);
    block_new->free = true;

    block->next = block_new;
    block->size = size;
}

// Merge the next block with the current block
void block_merge(t_block *block1, t_block *block2)
{
    block1->size += sizeof(t_block) + block2->size;
    block1->next = block2->next;
}

// Merge all next free blocks
void block_merge_free(t_block *block)
{
    while (block->next != NULL && block->next->free)
        block_merge(block, block->next);
}
