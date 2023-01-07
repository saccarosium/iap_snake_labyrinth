#include "../include/map.h"
#include "../include/path.h"
#include "../include/queue.h"
#include <stdio.h>
/**
 * @file 
 * @brief contain function to manage coin and unevent.
*/
/**
 * @brief function that assingns the direction of movement based on the next position.
 * @param a pointer of the current position.
 * @param b pointer of the next position.
 * @return the direction of the movements of the player.
*/
action astar_get_action(node *a, node *b) {
    if (a->x < b->x)
        return LEFT;
    if (a->x > b->x)
        return RIGHT;
    if (a->y < b->y)
        return UP;
    if (a->y > b->y)
        return DOWN;

    return NONE;
}
/**
 * @brief manage the point of the coin and unevent.
 * @param m pointer to the map.
 * @return return the pointer of the path.
*/
path *astar_solve(map *m) {
    queue *q = queue_create(true);
    queue *closed = queue_create(false);

    node *start = map_get_node(m, m->start.y, m->start.x);
    node *end = map_get_node(m, m->end.y, m->end.x);

    queue_push(q, start);

    while (q->lenght > 0) {
        node *current = queue_pop(q);
        // queue_print(q);

        // printf("current: %d %d\n", current->x, current->y);

        queue_push(closed, current);

        if (map_compare_node(current, end)) {
            path *p = path_create();

            node *prev = current;
            current = current->parent;

            while (current) {
                // printf("(%d %d)\n", current->x, current->y);
                action act = astar_get_action(prev, current);
                path_push_head(p, act);
                prev = current;
                current = current->parent;
            }

            return p;
        }

        int nodes = 0;
        node **neighbors =
            map_get_nearby_nodes(m, current->y, current->x, &nodes);
        // printf("nodes: %d\n", nodes);
        for (int i = 0; i < nodes; i++) {
            node *neighbor = neighbors[i];
            // printf("neighbor: %d %d\n", neighbor->x, neighbor->y);
            if (neighbors[i]->type == WALL)
                continue;

            int cost = current->cost
                + 11
                - (current->type == COIN ? 10 : 1)
                + (current->type == UNEVENT ? 100 : 0);

            if (queue_contains(q, neighbor) && cost < neighbor->cost) {
                // printf("removed queue %d %d\n", neighbor->x, neighbor->y);
                queue_remove(q, neighbor);
            }

            if (queue_contains(closed, neighbor) && cost < neighbor->cost) {
                // printf("removed closed %d %d\n", neighbor->x, neighbor->y);
                queue_remove(closed, neighbor);
            }

            if (!queue_contains(q, neighbor) &&
                !queue_contains(closed, neighbor)) {
                // printf("added queue %d %d\n", neighbor->x, neighbor->y);
                neighbor->cost = cost;
                queue_push(q, neighbor);
                neighbor->parent = current;
            }
        }
    }

    return NULL;
}
