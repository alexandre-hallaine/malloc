#include "functions.h"

#include <sys/mman.h>

t_heap *heap_allocate(size_t size)
{
    void *map = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (map == MAP_FAILED)
        return NULL;

    if (heap_first != NULL)
    {
        t_heap *tmp = heap_first;
        while (tmp->next != NULL)
            tmp = tmp->next;
        tmp->next = map;
    }
    else
        heap_first = map;

    t_heap *heap_new = map;
    heap_new->next = NULL;
    heap_new->size = size;

    // create the free space block
    t_block *block_first = map + sizeof(t_heap);
    block_first->next = NULL;
    block_first->size = size - sizeof(t_heap) - sizeof(t_block);
    block_first->free = true;

    return heap_new;
}

void heap_defragment(t_heap *heap)
{
    t_block *block = (void *)heap + sizeof(t_heap);
    while (block != NULL)
        if (block->free && block->next != NULL && block->next->free)
            block_merge(block, block->next);
        else
            block = block->next;
}
