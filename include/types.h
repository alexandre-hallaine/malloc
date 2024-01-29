#pragma once

#include <stddef.h>
#include <stdbool.h>
#include <unistd.h>

#define HEAP_SIZE getpagesize()

typedef struct s_block {
    size_t size;
    bool free;
} t_block;

typedef struct s_heap {
    void *next;

    size_t size;
} t_heap;

extern t_heap *heap_first;
