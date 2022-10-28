#include "path.h"
#include "alloc.h"
#include <stdlib.h>

path *path_create() {
    path *p = xmalloc(sizeof(path));
    p->head = NULL;
    p->tail = NULL;

    return p;
}

pathNode *node_create(direction dir) {
    pathNode *n = xmalloc(sizeof(pathNode));
    n->dir = dir;
    n->next = NULL;
    return n;
}

void path_push(path *p, direction dir) {
    pathNode *n = node_create(dir);

    if(p->tail == NULL) {
        p->head = n;
        p->tail = n;
    } else {
        p->tail->next = n;
        p->tail = n;
    }
}

direction path_pop_first(path *p) {
    if(p->head == NULL) return STOP;

    pathNode *n = p->head;
    p->head = n->next;

    direction dir = n->dir;
    free(n);

    return dir;
}

direction path_pop_last(path *p) {
    if(p->head == NULL) return STOP;

    pathNode *curr = p->head;
    pathNode *prev = NULL;
    while(curr->next != NULL) {
        prev = curr;
        curr = curr->next;
    }
    p->tail = prev;

    if (prev != NULL) {
        prev->next = NULL;
    }


    direction dir = curr->dir;
    free(curr);

    return dir;
}
