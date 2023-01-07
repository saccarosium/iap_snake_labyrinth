#include "../include/map.h"
#include "../include/path.h"
#include "../include/queue.h"

/**
 * @file
 * @brief this file contains functions to generate optimized moves
*/

/**
 * @brief generate an action from two nodes
 * @param a start node
 * @param a end node
 */
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

/**
 * @brief clear the visited coordinates
 * @param map visited pointer
 */
void visited_clear(map *visited) {
    for(int i = 0; i < visited->height; i++) {
        for(int j = 0; j < visited->width; j++) {
            map_get_node(visited, i, j)->type = 0;
        }
    }
}

/**
 * @brief function that calculate a single step recursively
 * @param m pointer to the map.
 * @param y y coordinates node
 * @param x x coordinates node.
 * @param t number of drill.
 * @param visited pointer of visited coordinates.
 * @param path pointer of the current path
 * @param shortest pointer of the shortest way.
*/
void walk(map *m, int y, int x, int t, map *visited, queue *path, queue *shortest) {
    node *vis = map_get_node(visited, y, x);
    if(vis == NULL || vis->type != 0) {
        // outside/already visited
        return;
    }

    node *curr = map_get_node(m, y, x);

    if(curr->x == m->end.x && curr->y == m->end.y) {
        if(shortest->lenght != 0 && queue_size(path) + 2 > queue_size(shortest)) {
            // shortest or eq. already found
            return;
        }

        queue_clear(shortest);

        queueNode *n = path->head;
        while(true) {
            if(n == NULL) break;

            queue_push(shortest, n->node);
            n = n->next;
        }

        queue_push(shortest, curr);
        return;
    }
    if(curr->type == WALL) {
        if(t <= 0) {
            return;
        } else {
            t = t - 1;
        }
    }
    if(curr->type == DRILL) {
        t = t + 3;
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

/**
 * @brief function that calculate the shortest way.
 * @param m pointer of the map.
 * @return return the pointer of the shortest path
*/
path *backtracking_solve(map *m) {
    path *p = path_create();

    map *visited = map_create(m->height, m->width);
    visited_clear(visited);

    queue *path = queue_create(false);
    queue *shortest = queue_create(false);

    walk(m, m->start.y, m->start.x, 0, visited, path, shortest);

    queueNode *prev = shortest->head;
    queueNode *curr = prev->next;

    while(curr) {
        action a = backtracking_get_action(prev->node, curr->node);
        path_push(p, a);
        prev = curr;
        curr = curr->next;
    }

    queue_free(path);
    queue_free(shortest);
    map_free(visited);

    return p;
}
