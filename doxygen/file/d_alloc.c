#include "../include/alloc.h"
#include <stdlib.h>

/**
 * @file
 * @brief function that check if memory is allocate.
*/
/**
 * @brief check if the the malloc allocate the memory.
 * @param p pointer to check.
*/
void *checked(void *p) {
    if (p == NULL) {
        exit(EXIT_FAILURE);
    }

    return p;
}

/**
 * @brief alloc memory for a pointer.
 * @param n size of memory to alloc.
*/
void *xmalloc(long long int n) {
    return checked(malloc(n));
}
