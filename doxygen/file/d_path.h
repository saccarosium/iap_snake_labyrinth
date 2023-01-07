#ifndef PATH_H
#define PATH_H

#include <stdbool.h>
/**
 * @file
 * @brief contain the function to control the path.
*/
/**
 * @brief type of moves
 * @param NONE do nothing
 * @param UP go up
 * @param DOWN go down
 * @param LEFT go left
 * @param RIGHT go right
 * @param ENTER enter to selected level
 * @param QUIT quit the game
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
 * @brief menage node of moves
 * @param act type of action
 * @param next pointer to next move
*/
typedef struct pathNode {
    action act;
    struct pathNode *next;
} pathNode;
/**
 * @brief node of snake
 * @param head snake head node pointer
 * @param tail snake tail node poiter
 * @param curr current pointer
*/
typedef struct path {
    pathNode *head;
    pathNode *tail;
    pathNode *curr;
} path;
/**
 * @brief alloc the path pointer.
 * @return return the pointer
*/
path *path_create();
/**
 * @brief update information of the path
 * @param p the path pointer
 * @param act action done by the player.
*/
void path_push(path *p, action act);
/**
 * @brief update information for the head path.
 * @param p pointer of the path.
 * @param act action done.
*/
void path_push_head(path *p, action act);
/**
 * @brief function for the first movement
 * @param p pointer of thee path.
 * @return the action to do
*/
action path_pop_first(path *p);
/**
 * @brief function for the last movement
 * @param p pointer of the path.
 * @return the action to do.
*/
action path_pop_last(path *p);
/**
 * @brief function for the next path
 * @param p pointer of thee path.
 * @return the next action to do
 */
action path_next(path *p);
/**
 * @brief reset the path.
 * @param p pointer of the path.
*/
void path_reset(path *p);
/**
 * @brief convert the action to a keybind.
 * @param act the action that the player do.
 * @return the keybind corresponding to action.
*/
char path_action_to_char(action act);
/**
 * @brief generate an array for the path moves.
 * @param p pointer of thee path.
 * @return return the array of the moves of the path
*/
char *path_string(path *p);
/**
 * @brief generate an array for the path moves.
 * @param p pointer of thee path.
 * @return return the array of the moves of the path
*/
void path_free(path *p);

#endif // !PATH_H
