#include "../include/right.h"
#include "../include/map.h"
#include "../include/path.h"
#include <stdio.h>

vec2 next_move(vec2 pos, action act) {
    int x = pos.x;
    int y = pos.y;

    switch (act) {
    case UP:
        y -= 1;
        break;
    case DOWN:
        y += 1;
        break;
    case RIGHT:
        x += 1;
        break;
    case LEFT:
        x -= 1;
        break;
    default:
        break;
    }

    vec2 nextpos = {.y = y, .x = x};
    return nextpos;
}

path *right_solve(map *m) {
    path *p = path_create();
    action next_inside[] = {
        [UP] = LEFT,
        [DOWN] = RIGHT,
        [LEFT] = DOWN,
        [RIGHT] = UP,
    };
    action next_outside[] = {
        [UP] = RIGHT,
        [DOWN] = LEFT,
        [LEFT] = UP,
        [RIGHT] = DOWN,
    };

    vec2 pos = {.y = m->start.y, .x = m->start.x};

    action movement = RIGHT;

    while (true) {
        if (pos.y == m->end.y && pos.x == m->end.x) {
            break;
        }

        vec2 nextpos = next_move(pos, next_outside[movement]);
        node *nextnode = map_get_node(m, nextpos.y, nextpos.x);

        vec2 posahead = next_move(pos, movement);
        node *nodeahead = map_get_node(m, posahead.y, posahead.x);

        if (nextnode != NULL && nextnode->type != WALL) {
            movement = next_outside[movement];
        } else if (nodeahead == NULL || nodeahead->type == WALL) {
            movement = next_inside[movement];
        }

        posahead = next_move(pos, movement);
        nodeahead = map_get_node(m, posahead.y, posahead.x);
        if (nodeahead != NULL && nodeahead->type != WALL) {
            pos = next_move(pos, movement);
            path_push(p, movement);
        }
    }

    return p;
}
