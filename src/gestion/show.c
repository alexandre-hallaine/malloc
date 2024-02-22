#include "types.h"

#include <stdint.h>

size_t ft_strlen(const char *str)
{
    size_t	len = 0;
    while (str[len])
        len++;
    return len;
}

// Write a number to the standard output using a given base
void print_number(char *base, unsigned int number) {
    unsigned char base_len = ft_strlen(base);

    if (number / base_len != 0)
        print_number(base, number / base_len);

    write(0, base + number % base_len, 1);
}

// Write the hexadecimal representation of a memory block to the standard output
void print_memory_data(const unsigned char *address, size_t num_bytes) {
    for (size_t i = 0; i < num_bytes; i += 8) {
        if (i)
            write(0, "\n", 1);

        write(0, "0x", 2);
        print_number("0123456789abcdef", (uintptr_t)address);
        write(0, ": ", 2);

        for (unsigned char j = 0; j < 8; j++) {
            if (j)
                write(0, " ", 1);

            unsigned char value = address[i + j];
            if (!(value & 0xF0))
                write(0, "0", 1);
            print_number("0123456789abcdef", value);
        }
    }
    write(0, "\n", 1);
}

// Write the type of the heap to the standard output
void print_heap_type(t_heap_type type) {
    switch (type) {
        case TINY:
            write(0, "TINY", 4);
            break;
        case SMALL:
            write(0, "SMALL", 5);
            break;
        case LARGE:
            write(0, "LARGE", 5);
            break;
        default:
            write(0, "UNKNOWN", 7);
    }
}

// Show metadata of the allocated memory
void show_alloc_mem()
{
    for (t_heap *heap = heap_first; heap != NULL; heap = heap->next)
    {
        print_heap_type(heap->type);
        write(0, ": (map size: ", 13);
        print_number("0123456789", heap->type * HEAP_SIZE);
        write(0, ")\n", 2);

        for (t_block *block = (void *)heap + sizeof(t_heap); block != NULL; block = block->next)
            if (!block->free)
            {
                write(0, "\t0x", 3);
                print_number("0123456789abcdef", (uintptr_t)block);
                write(0, ": ", 3);
                print_number("0123456789", block->size);
                write(0, " bytes\n", 7);
            }
    }
}

// Show hexadecimal representation of the allocated memory
void show_alloc_mem_ex()
{
    for (t_heap *heap = heap_first; heap != NULL; heap = heap->next)
        for (t_block *block = (void *)heap + sizeof(t_heap); block != NULL; block = block->next)
            if (!block->free)
                print_memory_data((void *)block + sizeof(t_block), block->size);
}
