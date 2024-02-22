#include "functions.h"

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

void *routine(void *ptr)
{
    int *value = realloc(ptr, sizeof(int) * 2);
    value[1] = 42;
    return NULL;
}

int main()
{
    char *ptr = malloc(sizeof(int));
    for (size_t i = 0; i < sizeof(int); i++)
        ptr[i] = 0x42;

    pthread_t thread;
    pthread_create(&thread, NULL, routine, ptr);
    pthread_join(thread, NULL);

    show_alloc_mem();
    return 0;
}
