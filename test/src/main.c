#include "types.h"

#include <stdlib.h>
#include <stdio.h>

void heap_print(t_heap *heap)
{
    printf("heap: %p (size: %lu)\n", heap, heap->size);
    for (t_block *block = (void *)heap + sizeof(t_heap); block != NULL; block = block->next)
        printf("  block: %p (size: %lu, free: %d)\n", block, block->size, block->free);
}

int main()
{
    void *ptr1 = malloc(HEAP_SIZE - sizeof(t_heap) - sizeof(t_block));
    t_heap *heap = ptr1 - sizeof(t_block) - sizeof(t_heap);

    printf("Simple allocation:\n");
    heap_print(heap);
    free(ptr1);

    ptr1 = malloc(8);
    void *ptr2 = malloc(8);
    void *ptr3 = malloc(8);
    heap = ptr1 - sizeof(t_block) - sizeof(t_heap);

    printf("Multiple allocations:\n");
    heap_print(heap);

    free(ptr2);
    free(ptr3);
    printf("After multiple free:\n");
    heap_print(heap);

    ptr1 = realloc(ptr1, 16);
    printf("After reusing free space:\n");
    heap_print(heap);

    free(ptr1);
}
