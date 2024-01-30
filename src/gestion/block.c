#include "types.h"

void block_split(t_block *block, size_t size)
{
    t_block *new_block = (void *)block + sizeof(t_block) + size;

    new_block->next = block->next;
    new_block->size = block->size - size - sizeof(t_block);
    new_block->free = true;

    block->next = new_block;
    block->size = size;
}

void block_merge(t_block *block1, t_block *block2)
{
    block1->size += sizeof(t_block) + block2->size;
    block1->next = block2->next;
}
