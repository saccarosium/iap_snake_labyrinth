#ifndef QUEUE_H
#define QUEUE_H

#include "map.h"
typedef struct queueNode {
    node *node;
    struct queueNode *next;
    struct queueNode *prev;
} queueNode;

typedef struct queue {
    queueNode *head;
    queueNode *tail;
    int lenght;
    bool priority;
} queue;

queue *queue_create();
void queue_push(queue *q, node *n);
void queue_push_head(queue *q, node *n);
node *queue_pop(queue *q);
node *queue_pop_last(queue *q);
bool queue_contains_yx(queue *q, int y, int x);
bool queue_contains(queue *q, node *n);
void queue_remove(queue *q, node *n);
void queue_clear(queue *q);
void queue_free(queue *q);
int queue_size(queue *q);
queueNode *queue_overlap(queue *q);
int queue_remove_from(queue *q, queueNode *qn);

void queue_print(queue *q);
#endif // !QUEUE_H
