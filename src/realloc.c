#include "functions.h"

void *realloc(void *ptr, size_t size)
{
    if (ptr == NULL)
        return malloc(size);
    block_size_align(&size);

    t_block *block = ptr - sizeof(t_block);
    for (t_block *tmp = block->next; tmp != NULL; tmp = tmp->next)
        if (tmp->free)
            block_merge(block, tmp);
        else
            break;

    if (block->size > size)
        block_split(block, size);
    if (block->size >= size)
        return ptr;

    void *new = malloc(size);
    if (new == NULL)
        return NULL;

    for (size_t i = 0; i < block->size; i++)
        ((char *)new)[i] = ((char *)ptr)[i];

    free(ptr);
    return new;
}
