#pragma once

#include "types.h"

void    *malloc(size_t size);
void    free(void *ptr);

// gestion/heap.c
t_heap_type heap_type(size_t block_size);
t_heap      *heap_allocate(t_heap_type type);
void        heap_free(t_heap *heap);
t_heap      *heap_get(void *address);
void        heap_defragment(t_heap *heap);

// gestion/block.c
void    block_size_align(size_t *size);
t_block *block_find(size_t size);
void    block_split(t_block *block, size_t size);
void    block_merge(t_block *block1, t_block *block2);
void    block_merge_free(t_block *block);

// gestion/heap.c
void    show_alloc_mem();
