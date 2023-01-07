#ifndef PATH_H
#define PATH_H

#include <stdbool.h>

/**
 * enum specifying every possible type of action
 */
typedef enum action {
    NONE,
    UP,
    DOWN,
    LEFT,
    RIGHT,
    ENTER,
    QUIT,
} action;

/**
 * @brief the linked list node representing an action
 *
 * @param act an action
 * @params next a pointer to the next node of the list
*/
typedef struct pathNode {
    action act;
    struct pathNode *next;
} pathNode;

/**
 * @brief a linked list for storing a series of actions
 *
 * @param head the first element of the list
 * @param tail the last element of the list
 * @param curr the current element of the list
*/
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
char path_action_to_char(action act);
char *path_string(path *p);
void path_free(path *p);

#endif // !PATH_H
