#ifndef PATH_H
#define PATH_H

#include <stdbool.h>

typedef enum action {
    NONE,
    UP,
    DOWN,
    LEFT,
    RIGHT,
    ENTER,
    QUIT,
} action;

typedef struct pathNode {
    action act;
    struct pathNode *next;
} pathNode;

typedef struct path {
    pathNode *head;
    pathNode *tail;
    pathNode *curr;
} path;

path *path_create();
void path_push(path *p, action act);
void path_push_head(path *p, action act);
action path_pop_first(path *p);
action path_pop_last(path *p);
action path_next(path *p);
void path_reset(path *p);
char *path_string(path *p);

#endif // !PATH_H
