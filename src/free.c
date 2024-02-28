#include "functions.h"

// Free a block of memory
void free(void *ptr)
{
    t_block *block;
    t_heap *heap;

    pthread_mutex_lock(&mutex);
    heap = heap_get(ptr);

    if (heap != NULL)
    {
        block = ptr - sizeof(t_block);
        block->free = true;

        heap_defragment(heap);
        heap_free(heap);
    }

    pthread_mutex_unlock(&mutex);
}
