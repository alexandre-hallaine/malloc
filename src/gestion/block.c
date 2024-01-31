#include "types.h"

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

void block_merge(t_block *block1, t_block *block2)
{
    block1->size += sizeof(t_block) + block2->size;
    block1->next = block2->next;
}

void block_size_align(size_t *size)
{
    *size += sizeof(t_block);
    *size = (*size + 15) & ~15; // align to 16 bytes
    *size -= sizeof(t_block);
}
