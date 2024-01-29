#include "libft.h"

#include <stddef.h>
#include <stdio.h>

void *malloc(size_t size) {
    ft_putstr_fd("malloc called\n", 2);
    (void)size;
    return NULL;
}
