#pragma once

#include <stdbool.h>
#include <unistd.h>

#define HEAP_LIMIT true
#define HEAP_DEFRAG true

#define HEAP_SIZE getpagesize()

typedef struct s_block t_block;
typedef struct s_heap t_heap;

extern t_heap *heap_first;

typedef enum e_heap_type {
    TINY = 1,
    SMALL = 16,
    LARGE = 16 * 16
} t_heap_type;

struct s_block {
    t_block *next;

    size_t size;
    bool free;
};

struct s_heap {
    t_heap *next;

    t_heap_type type;
};
