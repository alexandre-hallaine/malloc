#include "types.h"

#include <stddef.h>

#include <sys/mman.h>

t_heap *heap_first = NULL;

t_heap *allocate_heap(size_t size) {
    void *map = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (map == MAP_FAILED)
        return NULL;

    if (heap_first != NULL) {
        t_heap *tmp = heap_first;
        while (tmp->next != NULL)
            tmp = tmp->next;
        tmp->next = map;
    }
    else
        heap_first = map;

    t_heap *heap_new = (t_heap *)map;
    heap_new->next = NULL;
    heap_new->size = size;

    // create the free space block
    t_block *block_first = (t_block *)(map + sizeof(t_heap));
    block_first->size = size - sizeof(t_heap) - sizeof(t_block);
    block_first->free = true;

    return heap_new;
}

void allocate_block(t_block *block, size_t size) {
    // if block is too big, split it
    if (block->size > size) {
        t_block *block_new = (t_block *)((void *)block + sizeof(t_block) + size);
        block_new->size = block->size - sizeof(t_block) - size;
        block_new->free = true;
        block->size = size;
    }

    block->free = false;
}

void *malloc(size_t size) {
    if (size > (size_t)HEAP_SIZE)
        return NULL;

    //find a free block that fits
    t_block *block_found = NULL;
    for (t_heap *heap = heap_first; heap != NULL && block_found == NULL; heap = heap->next)
        for (t_block *block = (t_block *)((void *)heap + sizeof(t_heap));
            (void *)block < (void *)heap + sizeof(t_heap) + heap->size;
            block = (t_block *)((void *)block + sizeof(t_block) + block->size))
            if (block->free && block->size >= size) {
                block_found = block;
                break;
            }

    //if no free block found, allocate a new heap
    if (block_found == NULL) {
        t_heap *heap = allocate_heap(HEAP_SIZE);
        if (heap == NULL)
            return NULL;
        block_found = (t_block *)((void *)heap + sizeof(t_heap));
    }

    allocate_block(block_found, size);
    return (void *)block_found + sizeof(t_block);
}
