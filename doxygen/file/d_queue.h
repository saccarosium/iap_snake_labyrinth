#ifndef QUEUE_H
#define QUEUE_H

#include "map.h"
/**
 * @file
 * @brief contain function that control the tail.
*/
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
/**
 * @brief alloc the memory for the tail.
 * @return the pointer q, a pointer with the queue data.
*/
queue *queue_create();
/**
 * @brief increas the queue lenght.
 * @param q pointer with queue information.
 * @param n pointer with the current node.
*/
void queue_push(queue *q, node *n);
/**
 * @brief increase the queue lenght.
 * @param q pointer with the queue data.
 * @param n pointer with the current node.
*/
void queue_push_head(queue *q, node *n);
/**
 * @brief decrease the queue lenght.
 * @param q pointer with queue data.
 * @return the node n.
*/
node *queue_pop(queue *q);
/**
 * @brief decrease the queue lenght.
 * @param q pointer with the queue data.
 * @return the node.
*/
node *queue_pop_last(queue *q);
/**
 * @brief controll the coordinates of the queue.
 * @param q pointer with the queue information.
 * @param y y coordinates.
 * @param x x coordinates.
 * @return true if the coordinates of queue correspond to the queue position
*/
bool queue_contains_yx(queue *q, int y, int x);
/**
 * @brief controll the coordinates of the queue.
 * @param q pointer with the queue information.
 * @param n pointer to the nodes.
 * @return call the control of coordinates.
 */
bool queue_contains(queue *q, node *n);
/**
 * @brief remove the queue.
 * @param q pointer to queue data.
 * @param n pointer to a node.
*/
void queue_remove(queue *q, node *n);
/**
 * @brief dealloc the memory of the node tail pointer.
 * @param q pointer with queue data.
*/
void queue_clear(queue *q);
/**
 * @brief dealloc the memory of the queue pointer.
 * @param q pointer with the queue data.
*/
void queue_free(queue *q);
/**
 * @brief calculate the lenght of the tail.
 * @param q pointer with the queue data.
 * @return the size of the queue.
*/
int queue_size(queue *q);
/**
 * @brief check if the tail overlap the head.
 * @param q pointer with the queue data.
 * @return the queue node.
*/
queueNode *queue_overlap(queue *q);
/**
 * @brief dealloc the pointer of the queue node.
 * @param q pointer with the queue data.
 * @param qn pointer with the node of queue.
*/
void queue_remove_from(queue *q, queueNode *qn);
/**
 * @brief print the tail in the map.
 * @param q pointer with queue data.
*/
void queue_print(queue *q);
#endif // !QUEUE_H
