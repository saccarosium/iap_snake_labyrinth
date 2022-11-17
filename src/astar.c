#include "../include/path.h"
#include "../include/map.h"
#include "../include/queue.h"
#include <stdio.h>

action astar_get_action(node *a, node *b) {
    if(a->x < b->x) return LEFT;
    if(a->x > b->x) return RIGHT;
    if(a->y < b->y) return UP;
    if(a->y > b->y) return DOWN;

    return NONE;
}

path *astar_solve(map *m) {
    queue *q = queue_create(true);
    queue *closed = queue_create(false);

    node *start = map_get_node(m, m->start.y, m->start.x);
    node *end = map_get_node(m, m->end.y, m->end.x);

    queue_push(q, start);

    while(q->lenght > 0) {
        node *current = queue_pop(q);
        queue_print(q);

        printf("current: %d %d\n", current->x, current->y);

        queue_push(closed, current);

        if(map_compare_node(current, end)) {
            printf("HERE\n");
            path *p = path_create();

            node *prev = current;
            current = current->parent;

            while(current) {
                printf("(%d %d)\n", current->x, current->y);
                action act = astar_get_action(prev, current);
                path_push_head(p, act);
                prev = current;
                current = current->parent;
            }

            return p;
        }

        int nodes = 0;
        node **neighbors = map_get_nearby_nodes(m, current->y, current->x, &nodes);
        printf("nodes: %d\n", nodes);
        for(int i = 0; i < nodes; i++) {
            node *neighbor = neighbors[i];
            printf("neighbor: %d %d\n", neighbor->x, neighbor->y);
            if(neighbors[i]->type == WALL) continue;

            int cost = current->cost + 11 - (current->type == COIN ? 10 : 1);

            if(queue_contains(q, neighbor) && cost < neighbor->cost) {
                printf("removed queue %d %d\n", neighbor->x, neighbor->y);
                queue_remove(q, neighbor);
            }

            if(queue_contains(closed, neighbor) && cost < neighbor->cost) {
                printf("removed closed %d %d\n", neighbor->x, neighbor->y);
                queue_remove(closed, neighbor);
            }

            if(!queue_contains(q, neighbor) && !queue_contains(closed, neighbor)) {
                printf("added queue %d %d\n", neighbor->x, neighbor->y);
                neighbor->cost = cost;
                queue_push(q, neighbor);
                neighbor->parent = current;
            }
        }
    }

    printf("empty queue\n");
    return NULL;
}
