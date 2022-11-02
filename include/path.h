#ifndef PATH_H
#define PATH_H

typedef enum direction {
    STOP,
    UP,
    DOWN,
    LEFT,
    RIGHT,
} direction;

typedef struct pathNode {
    direction dir;
    struct pathNode *next;
} pathNode;

typedef struct path {
    pathNode *head;
    pathNode *tail;
} path;

path *path_create();
void path_push(path *p, direction dir);
direction path_pop_first(path *p);
direction path_pop_last(path *p);

#endif // !PATH_H