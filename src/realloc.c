#include "functions.h"

// Expands or shrinks a block of memory (or allocates a new one if can't). Data is preserved.
void *realloc(void *ptr, size_t size)
{
    t_heap *heap;
    t_heap_type type;
    t_block *block = ptr - sizeof(t_block);
    void *ret = NULL;

    pthread_mutex_lock(&mutex);
    heap = heap_get(ptr);
    block_size_align(&size);
    type = heap_type(size);

    if (heap == NULL || block->free)
        return NULL;

    if (heap->type == type)
    {
        block_merge_free(block);
        block_split(block, size);

        if (block->size >= size)
            ret = ptr;
    }

    pthread_mutex_unlock(&mutex);
    if (ret != NULL)
        return ret;

    ret = malloc(size);
    if (ret == NULL)
        return NULL;

    for (size_t i = 0; i < block->size; i++)
        ((char *)ret)[i] = ((char *)ptr)[i];

    free(ptr);
    return ret;
}
