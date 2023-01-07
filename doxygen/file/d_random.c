#include "../include/random.h"
#include "../include/map.h"
#include "../include/path.h"
#include <stdlib.h>
#include <time.h>
/**
 * @file
 * @brief function that generate random moves 
*/
/**
 * @brief generate a random moveset.
 * @param m pointer of the map.
 * @return pointer of the path.
*/
path *random_solve(map *m) {
    srand(time(NULL));
    path *p = path_create();

    vec2 pos = {.y = m->start.y, .x = m->start.x};

    action actions[] = {
        UP,
        DOWN,
        LEFT,
        RIGHT,
    };

    while (true) {
        if (pos.y == m->end.y && pos.x == m->end.x) {
            break;
        }

        vec2 nextpos = pos;
        int direction = rand() % 4;

        switch (direction) {
            case 0:
                nextpos.y -= 1;
                break;
            case 1:
                nextpos.y += 1;
                break;
            case 2:
                nextpos.x -= 1;
                break;
            case 3:
                nextpos.x += 1;
                break;
        }

        node *n = map_get_node(m, nextpos.y, nextpos.x);
        if (n != NULL && n->type != WALL) {
            path_push(p, actions[direction]);
            pos = nextpos;
        }
    }

    return p;
}
