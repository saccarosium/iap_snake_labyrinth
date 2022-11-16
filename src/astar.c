#include "../include/path.h"
#include "../include/map.h"
#include "../include/queue.h"
#include <stdio.h>

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

        printf("(%d %d) == (%d %d)\n", current->x, current->y, end->x, end->y);
        if(map_compare_node(current, end)) {
            path *p = path_create();

            while(current) {
                printf("(%d %d)\n", current->x, current->y);
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

            int cost = current->cost + 10;

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
