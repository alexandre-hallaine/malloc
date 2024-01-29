#pragma once

#include <stdbool.h>
#include <unistd.h>

#define HEAP_SIZE getpagesize()

typedef struct s_block t_block;
typedef struct s_heap t_heap;

extern t_heap *heap_first;

struct s_block {
    t_block *prev;
    t_block *next;

    size_t size;
    bool free;
};

struct s_heap {
    t_heap *next;

    size_t size;
};
