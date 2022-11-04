#include "../include/path.h"
#include "../include/alloc.h"
#include <stdbool.h>
#include <stdlib.h>

path *path_create() {
    path *p = xmalloc(sizeof(path));
    p->head = NULL;
    p->tail = NULL;
    p->curr = NULL;

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

    if(p->curr == NULL) p->curr = n;
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

direction path_next(path *p) {
    if(p->curr == NULL) return NONE;
    direction dir = p->curr->dir;
    p->curr = p->curr->next;

    return dir;
}

bool path_has_ended(path *p) {
    if(p->curr == NULL) return false;
    return p->curr->dir == STOP;
}
