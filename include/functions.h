#pragma once

#include "types.h"

t_heap *heap_allocate(size_t size);
void heap_defragment(t_heap *heap);

void block_split(t_block *block, size_t size);
void block_merge(t_block *block1, t_block *block2);
