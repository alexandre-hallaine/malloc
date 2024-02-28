#pragma once

#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>

#define HEAP_FREE true
#define HEAP_DEFRAG true

#define HEAP_SIZE getpagesize()

typedef struct s_heap t_heap;
typedef struct s_block t_block;

extern t_heap *heap_first;
extern pthread_mutex_t mutex;

// The type represents the number of memory pages needed to store the block.
typedef enum e_heap_type {
    TINY = 2 << 0,
    SMALL = 2 << 8,
    LARGE = 2 << 16
} t_heap_type;

struct s_heap {
    t_heap *next;

    t_heap_type type;
    char zero[8]; // Padding to align the block
};

struct s_block {
    t_block *next;

    size_t size;
    bool free;
};
