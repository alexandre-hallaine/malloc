#include "functions.h"
#include "libft.h"

void *realloc(void *ptr, size_t size)
{
    if (ptr == NULL)
        return malloc(size);

    t_block *block = ptr - sizeof(t_block);
    for (t_block *tmp = block->next; tmp != NULL; tmp = tmp->next)
        if (tmp->free)
            block_merge(block, tmp);
        else
            break;

    if (block->size > size)
        block_split(block, size);
    if (block->size == size)
        return ptr;

    void *new = malloc(size);
    if (new == NULL)
        return NULL;

    ft_memcpy(new, ptr, block->size);
    free(ptr);
    return new;
}
