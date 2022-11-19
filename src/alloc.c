#include "../include/alloc.h"
#include <stdlib.h>

void *checked(void *p) {
    if (p == NULL) {
        exit(EXIT_FAILURE);
    }

    return p;
}

void *xmalloc(long long int n) {
    return checked(malloc(n));
}
