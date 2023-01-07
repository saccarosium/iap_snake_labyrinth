#include "../include/queue.h"
#include "../include/alloc.h"
#include <stdio.h>
/**
 * @file
 * @brief contain function that control the tail.
*/
/**
 * @brief alloc the memory for the tail.
 * @return the pointer q, a pointer with the queue data.
*/
queue *queue_create() {
    queue *q = xmalloc(sizeof(queue));

    q->head = NULL;
    q->tail = NULL;
    q->lenght = 0;

    return q;
}
/**
 * @brief allocate the momery for the position of the queue.
 * @param n pointer with the current node.
 * @return a pointer which contains the node of the queue.
*/
queueNode *queue_node_create(node *n) {
    queueNode *qn = xmalloc(sizeof(queueNode));
    qn->node = n;
    qn->prev = NULL;
    qn->next = NULL;

    return qn;
}
/**
 * @brief increas the queue lenght.
 * @param q pointer with queue information.
 * @param n pointer with the current node.
*/
void queue_push(queue *q, node *n) {
    q->lenght++;

    queueNode *qn = queue_node_create(n);
    if (q->tail == NULL) {
        q->tail = qn;
        q->head = qn;
        return;
    }

    q->tail->next = qn;
    qn->prev = q->tail;
    q->tail = qn;
}
/**
 * @brief increase the queue lenght.
 * @param q pointer with the queue data.
 * @param n pointer with the current node.
*/
void queue_push_head(queue *q, node *n) {
    q->lenght++;
    queueNode *qn = queue_node_create(n);

    qn->next = q->head;
    q->head->prev = qn;
    q->head = qn;
}
/**
 * @brief decrease the queue lenght.
 * @param q pointer with queue data.
 * @return the node n.
*/
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

    node *n = qn->node;
    free(qn);
    return n;
}
/**
 * @brief decrease the queue lenght.
 * @param q pointer with the queue data.
 * @return the node.
*/
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

    node *n = qn->node;
    free(qn);
    return n;
}
/**
 * @brief controll the coordinates of the queue.
 * @param q pointer with the queue information.
 * @param y y coordinates.
 * @param x x coordinates.
 * @return true if the coordinates of queue correspond to the queue position
*/
bool queue_contains_yx(queue *q, int y, int x) {
    for (queueNode *qn = q->head; qn != NULL; qn = qn->next) {
        if (qn->node->x == x && qn->node->y == y) {
            return true;
        }
    }
    return false;
}
/**
 * @brief controll the coordinates of the queue.
 * @param q pointer with the queue information.
 * @param n pointer to the nodes.
 * @return call the control of coordinates.
 */
bool queue_contains(queue *q, node *n) {
    return queue_contains_yx(q, n->y, n->x);
}
/**
 * @brief remove the queue.
 * @param q pointer to queue data.
 * @param n pointer to a node.
*/
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
/**
 * @brief print the tail in the map.
 * @param q pointer with queue data.
*/
void queue_print(queue *q) {
    printf("==== length: %3d ====\n", q->lenght);
    printf("---- head: %20p ----\n", q->head);

    for (queueNode *x = q->head; x != NULL; x = x->next) {
        printf("%20p <- %20p (%4d %4d) -> %20p\n", x->prev, x, x->node->y, x->node->x, x->next);
    }

    printf("---- tail: %20p ----\n", q->tail);
}
/**
 * @brief dealloc the memory of the node tail pointer.
 * @param q pointer with queue data.
*/
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
/**
 * @brief dealloc the memory of the queue pointer.
 * @param q pointer with the queue data.
*/
void queue_free(queue *q) {
    queue_clear(q);
    free(q);
}
/**
 * @brief calculate the lenght of the tail.
 * @param q pointer with the queue data.
 * @return the size of the queue.
*/
int queue_size(queue *q) {
    int size = 0;

    for (queueNode *x = q->head; x != NULL; x = x->next) {
        size += x->node->cost;
    }

    return size;
}
/**
 * @brief check if the tail overlap the head.
 * @param q pointer with the queue data.
 * @return the queue node.
*/
queueNode *queue_overlap(queue *q) {
    for(queueNode *qn = q->head->next; qn != NULL; qn = qn->next) {
        if (map_compare_node(q->head->node, qn->node)) {
            return qn;
        }
    }
    return NULL;
}
/**
 * @brief dealloc the pointer of the queue node.
 * @param q pointer with the queue data.
 * @param qn pointer with the node of queue.
*/
void queue_remove_from(queue *q, queueNode *qn) {
    qn->prev->next = NULL;
    q->tail = qn->prev;

    while(qn != NULL) {
        queueNode *next = qn->next;
        free(qn->node);
        free(qn);
        qn = next;
    }
}