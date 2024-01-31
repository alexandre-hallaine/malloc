#include "functions.h"

#include <sys/mman.h>

t_heap *heap_allocate(t_heap_type type)
{
    size_t size = type * HEAP_SIZE;
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
    heap_new->type = type;
    heap_new->size = size - sizeof(t_heap);

    // create the free space block
    t_block *block_first = map + sizeof(t_heap);
    block_first->next = NULL;
    block_first->size = size - sizeof(t_heap) - sizeof(t_block);
    block_first->free = true;

    return heap_new;
}

void heap_free(t_heap *heap)
{
    if (heap_first == heap)
        heap_first = heap->next;
    else
    {
        t_heap *prev = NULL;
        for (prev = heap_first; prev != NULL; prev = prev->next)
            if (prev->next == heap)
                break;

        if (prev == NULL)
            return;
        prev->next = heap->next;
    }

    munmap(heap, heap->size);
}

t_heap *heap_get(void *address)
{
    for (t_heap *heap = heap_first; heap != NULL; heap = heap->next)
    {
        void *first = (void *)heap + sizeof(t_heap);
        if (address >= first && address < first + heap->size)
            return heap;
    }
    return NULL;
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

t_heap_type heap_type(size_t block_size)
{
    block_size *= 100;
    if (block_size <= (size_t)TINY * HEAP_SIZE)
        return TINY;
    else if (block_size <= (size_t)SMALL * HEAP_SIZE)
        return SMALL;
    else
        return LARGE;
}
