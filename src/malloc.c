#include "functions.h"

t_heap *heap_first = NULL;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// Allocates a new block of memory
void *malloc(size_t size)
{
    t_block *block_found;
    void *ret = NULL;

    pthread_mutex_lock(&mutex);
    block_size_align(&size); // Align the size to be a multiple of 16 bytes
    block_found = block_find(size); // Find a free block of memory

    if (block_found != NULL)
        block_split(block_found, size);

    if (block_found != NULL)
    {
        block_found->free = false;
        ret = (void *)block_found + sizeof(t_block);
    }

    pthread_mutex_unlock(&mutex);
    return ret;
}
