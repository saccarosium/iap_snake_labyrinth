#include "../include/path.h"
#include "../include/alloc.h"
#include <stdbool.h>
#include <stdlib.h>
/**
 * @file
 * @brief contain the function to control the path.
*/
/**
 * @brief alloc the path pointer.
 * @return return the pointer
*/
path *path_create() {
    path *p = xmalloc(sizeof(path));
    p->head = NULL;
    p->tail = NULL;
    p->curr = NULL;

    return p;
}
/**
 * @brief alloc the node pointer
 * @param act action that the player do.
 * @return the pointer of the node.
*/
pathNode *node_create(action act) {
    pathNode *n = xmalloc(sizeof(pathNode));
    n->act = act;
    n->next = NULL;
    return n;
}
/**
 * @brief update information of the path
 * @param p the path pointer
 * @param act action done by the player.
*/
void path_push(path *p, action act) {
    pathNode *n = node_create(act);

    if (p->tail == NULL) {
        p->head = n;
        p->tail = n;
    } else {
        p->tail->next = n;
        p->tail = n;
    }

    if (p->curr == NULL)
        p->curr = n;
}
/**
 * @brief update information for the head path.
 * @param p pointer of the path.
 * @param act action done.
*/
void path_push_head(path *p, action act) {
    pathNode *n = node_create(act);

    pathNode *pn = p->head;
    p->head = n;
    if (p->tail == NULL) {
        p->tail = n;
    } else {
        n->next = pn;
    }

    p->curr = p->head;
}
/**
 * @brief function for the first movement
 * @param p pointer of thee path.
 * @return the action to do
*/
action path_pop_first(path *p) {
    if (p->head == NULL)
        return NONE;

    pathNode *n = p->head;
    p->head = n->next;

    action act = n->act;
    free(n);

    return act;
}
/**
 * @brief function for the last movement
 * @param p pointer of the path.
 * @return the action to do.
*/
action path_pop_last(path *p) {
    if (p->head == NULL)
        return NONE;

    pathNode *curr = p->head;
    pathNode *prev = NULL;
    while (curr->next != NULL) {
        prev = curr;
        curr = curr->next;
    }
    p->tail = prev;

    if (prev != NULL) {
        prev->next = NULL;
    }

    action act = curr->act;
    free(curr);

    return act;
}
/**
 * @brief function for the next path
 * @param p pointer of thee path.
 * @return the next action to do
 */
action path_next(path *p) {
    if (p->curr == NULL)
        return NONE;
    action act = p->curr->act;
    p->curr = p->curr->next;

    return act;
}
/**
 * @brief reset the path.
 * @param p pointer of the path.
*/
void path_reset(path *p) {
    p->curr = p->head;
}
/**
 * @brief convert the action to a keybind.
 * @param act the action that the player do.
 * @return the keybind corresponding to action.
*/
char path_action_to_char(action act) {
    switch (act) {
    case NONE:
    case ENTER:
    case QUIT:
        return ' ';
    case UP:
        return 'N';
    case DOWN:
        return 'S';
    case LEFT:
        return 'W';
    case RIGHT:
        return 'E';
    }
    return ' ';
}
/**
 * @brief generate an array for the path moves.
 * @param p pointer of thee path.
 * @return return the array of the moves of the path
*/
char *path_string(path *p) {
    path_reset(p);

    int length = 0;
    while (path_next(p))
        length += 1;

    path_reset(p);
    char *string = xmalloc(length + 1);

    for (int i = 0; i < length; i++) {
        string[i] = path_action_to_char(path_next(p));
    }
    string[length] = '\0';

    return string;
}
/**
 * @brief dealloc memory of the path.
 * @param p pointer of thee path.
*/
void path_free(path *p) {
    pathNode *n = p->head;
    while (n != NULL) {
        pathNode *next = n->next;
        free(n);
        n = next;
    }

    free(p);
}
