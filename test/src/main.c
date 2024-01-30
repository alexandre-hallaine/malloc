#include <stdlib.h>
#include <stdio.h>

int main() {
    void *ret1 = malloc(8);
    void *ret2 = malloc(8);
    printf("basic allocation:\n%p\n%p\n", ret1, ret2);

    free(ret1);
    free(ret2);
    void *ret3 = malloc(16);
    printf("merge:\n%p\n", ret3);

    return EXIT_SUCCESS;
}
