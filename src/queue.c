#include "../include/queue.h"
#include "../include/alloc.h"
#include <stdio.h>

queue *queue_create(bool priority) {
    queue *q = xmalloc(sizeof(queue));

    q->head = NULL;
    q->tail = NULL;
    q->lenght = 0;
    q->priority = priority;

    return q;
}

queueNode *queue_node_create(node *n) {
    queueNode *qn = xmalloc(sizeof(queueNode));
    qn->node = n;
    qn->prev = NULL;
    qn->next = NULL;

    return qn;
}

void queue_insert_before(queue *q, queueNode *base, queueNode *qn) {
    qn->next = base;

    if (base->prev == NULL) {
        q->head = qn;
    } else {
        queueNode *temp = base->prev;
        temp->next = qn;
        qn->prev = temp;
    }

    base->prev = qn;
}

bool queue_insert_priority(queue *q, queueNode *qn) {
    for (queueNode *x = q->head; x != NULL; x = x->next) {
        if (x->node->cost > qn->node->cost) {
            queue_insert_before(q, x, qn);
            return true;
        }
    }
    return false;
}

void queue_insert_last(queue *q, queueNode *qn) {
    q->tail->next = qn;
    qn->prev = q->tail;
    q->tail = qn;
}

void queue_push(queue *q, node *n) {
    q->lenght++;

    queueNode *qn = queue_node_create(n);
    if (q->tail == NULL) {
        q->tail = qn;
        q->head = qn;
        return;
    }

    if (q->priority == true) {
        bool inserted = queue_insert_priority(q, qn);
        if (inserted)
            return;
    }

    queue_insert_last(q, qn);
}

void queue_push_head(queue *q, node *n) {
    q->lenght++;
    queueNode *qn = queue_node_create(n);

    qn->next = q->head;
    q->head->prev = qn;
    q->head = qn;
}

node *queue_pop(queue *q) {
    if (q->lenght == 0)
        return NULL;

    q->lenght--;
    queueNode *qn = q->head;
    if (q->lenght == 0) {
        q->head = NULL;
        q->tail = NULL;
    } else {
        q->head = q->head->next;
        q->head->prev = NULL;
    }

    return qn->node;
}

node *queue_pop_last(queue *q) {
    if (q->lenght == 0)
        return NULL;

    q->lenght--;
    queueNode *qn = q->tail;
    if (q->lenght == 0) {
        q->head = NULL;
        q->tail = NULL;
    } else {
        q->tail = q->tail->prev;
        q->tail->next = NULL;
    }

    return qn->node;
}

bool queue_contains_yx(queue *q, int y, int x) {
    for (queueNode *qn = q->head; qn != NULL; qn = qn->next) {
        if (qn->node->x == x && qn->node->y == y) {
            return true;
        }
    }
    return false;
}

bool queue_contains(queue *q, node *n) {
    return queue_contains_yx(q, n->y, n->x);
}

void queue_remove(queue *q, node *n) {
    for (queueNode *x = q->head; x != NULL; x = x->next) {
        if (map_compare_node(x->node, n)) {
            q->lenght--;
            if (x->prev != NULL) {
                x->prev->next = x->next;
            } else {
                q->head = x->next;
            }

            if (x->next != NULL) {
                x->next->prev = x->prev;
            } else {
                q->tail = x->prev;
            }
        }
    }
}

void queue_print(queue *q) {
    printf("==== length: %3d ====\n", q->lenght);
    printf("---- head: %20p ----\n", q->head);

    for (queueNode *x = q->head; x != NULL; x = x->next) {
        printf("%20p <- %20p (%4d %4d) -> %20p\n", x->prev, x, x->node->y, x->node->x, x->next);
    }

    printf("---- tail: %20p ----\n", q->tail);
}

void queue_clear(queue *q) {
    queueNode *n = q->head;
    while(true) {
        if(n == NULL) break;
        queueNode *next = n->next;
        free(n);
        n = next;
    }

    q->head = NULL;
    q->tail = NULL;
    q->lenght = 0;
}

int queue_size(queue *q) {
    int size = 0;

    for (queueNode *x = q->head; x != NULL; x = x->next) {
        size += x->node->cost;
    }

    return size;
}
