#include <stdlib.h>
#include <stdio.h>

int main() {
    void *ret = malloc(8);
    if (ret == NULL)
        return EXIT_FAILURE;

    printf("%p\n", ret);
    return EXIT_SUCCESS;
}
