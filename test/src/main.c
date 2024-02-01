#include "functions.h"

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

void *routine(void *ptr)
{
    ptr = realloc(ptr, sizeof(int));
    printf("global: %d\n", *(int *)ptr);
    return NULL;
}

int main()
{
    int *ptr = malloc(sizeof(int) * 2);
    ptr[0] = 42;
    ptr[1] = 0;

    pthread_t thread;
    pthread_create(&thread, NULL, routine, ptr);
    pthread_join(thread, NULL);
    return 0;
}
