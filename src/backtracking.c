#include "../include/map.h"
#include "../include/path.h"
#include "../include/queue.h"

action backtracking_get_action(node *a, node *b) {
    if (a->x > b->x)
        return LEFT;
    if (a->x < b->x)
        return RIGHT;
    if (a->y > b->y)
        return UP;
    if (a->y < b->y)
        return DOWN;

    return NONE;
}

void print_map_backtracking(map *m, int y, int x) {
    for(int i = 0; i < m->height; i++) {
        for(int j = 0; j < m->width; j++) {
            if(i == y && j == x) {
                printf("X ");
            } else {
                node *n = map_get_node(m, i, j);
                switch (n->type) {
                    case EMPTY:
                        printf("  ");
                        break;
                    case WALL:
                        printf("##");
                        break;
                    case COIN:
                        printf("$ ");
                        break;
                    case UNEVENT:
                        printf("! ");
                        break;
                    case DRILL:
                        printf("T ");
                        break;
                    case USER:
                        printf("o ");
                        break;
                    case END:
                        printf("_ ");
                        break;
                        break;
                }
            }
        }
        printf("\n");
    }
}

void print_queue(queue *q) {
    queueNode *qn = q->head;

    printf("[ %2d ] ", queue_size(q));
    while(qn) {
        printf("(%d %d)", qn->node->y, qn->node->x);
        qn = qn->next;
        if(qn) printf("->");
    }
    printf("\n");
}

void visited_clear(map *visited) {
    for(int i = 0; i < visited->height; i++) {
        for(int j = 0; j < visited->width; j++) {
            map_get_node(visited, i, j)->type = 0;
            // map_set_node_type(map_get_node(visited, i, j), 0);
        }
    }
}

void walk(map *m, int y, int x, int t, map *visited, queue *path, queue *shortest) {
    node *vis = map_get_node(visited, y, x);
    if(vis == NULL || vis->type != 0) {
        // printf("outside/already visited\n");
        // outside/already visited
        return;
    }
    // printf("------------------------\n");
    // print_queue(path);

    node *curr = map_get_node(m, y, x);

    // if(shortest->lenght != 0 && queue_size(path) + 2 >= queue_size(shortest)) {
    // if(shortest->lenght != 0 && path->lenght + 2 >= shortest->lenght) {
    if(shortest->lenght != 0 && queue_size(path) + 2 > queue_size(shortest)) {
        // queue_print(path);
        // printf("%d is longer than %d\n", queue_size(path) + 2, queue_size(shortest));
        // shortest or eq. already found
        return;
    }
    if(curr->x == m->end.x && curr->y == m->end.y) {
        queue_clear(shortest);
        // printf("end\n");

        queueNode *n = path->head;
        while(true) {
            if(n == NULL) break;

            queue_push(shortest, n->node);
            n = n->next;
        }

        queue_push(shortest, curr);
        // queue_print(shortest);
        return;
    }
    if(curr->type == WALL) {
        if(t <= 0) {
            // printf("wall no drill\n");
            return;
        } else {
            t = t - 1;
        }
    }
    if(curr->type == DRILL) {
        t = t + 3;
        // visited_clear(visited);
    }

    map_set_node_type(vis, 1);
    queue_push(path, curr);
    walk(m, y, x + 1, t, visited, path, shortest);
    walk(m, y + 1, x, t, visited, path, shortest);
    walk(m, y, x - 1, t, visited, path, shortest);
    walk(m, y - 1, x, t, visited, path, shortest);
    queue_pop_last(path);
    map_set_node_type(vis, 0);
}

path *backtracking_solve(map *m) {
    path *p = path_create();

    map *visited = map_create(m->height, m->width);
    visited_clear(visited);

    queue *path = queue_create(false);
    queue *shortest = queue_create(false);

    walk(m, m->start.y, m->start.x, 0, visited, path, shortest);

    // for(queueNode *x = shortest->head; x != shortest->tail; x = x->next) {
    //     printf("%d %d\n", x->node->y, x->node->x);
    //     print_map_backtracking(m, x->node->y, x->node->x);
    // }
    // print_queue(shortest);

    queueNode *prev = shortest->head;
    queueNode *curr = prev->next;

    while(curr) {
        action a = backtracking_get_action(prev->node, curr->node);
        path_push(p, a);
        prev = curr;
        curr = curr->next;
    }

    return p;
}
