#include "../include/game.h"
#include "../include/path.h"
#include "../include/utils.h"
#include "../include/alloc.h"
#include <stdlib.h>
/**
 * @file
 * @brief File that countains the function relating to the player information.
*/

/**
 * @brief storing the coordinate of a node
 * @param x x coordiantes.
 * @param y y coordinates.
 * @return the pointer of the node.
*/
node *game_node_create(int y, int x) {
    node *n = malloc(sizeof(node));
    n->x = x;
    n->y = y;

    n->cost = 0;
    n->parent = 0;
    n->type = 0;

    return n;
}

/**
 * @brief function that initialize the game, loads the map and create the player
 * @param m pointer to the map.
 * @param err pointer to the exit status of the function (error type defined by the enum error)
 * @return pointer g, pointer with game information.
*/
game *game_init(map *m, error *err) {
    game *g = malloc(sizeof(game));
    if (g == NULL) {
        *err = MALLOC_FAILED;
        return NULL;
    }

    g->map = m;

    g->player = queue_create();
    node *start = game_node_create(g->map->start.y, g->map->start.x);

    queue_push(g->player, start);

    g->score = 1000;
    g->level = 3;
    g->drill = 0;

    return g;
}

/**
 * @brief function that get the position of the player
 * @param g pointer with game information.
 * @return the player position.
*/
node *game_get_player(game *g) {
    return g->player->head->node;
}

/**
 * @brief function that check if the player has reached the end
 * @param g pointer with game information.
 * @return true if the player is at the end of the map.
*/
bool game_ended(game *g) {
    node *player = game_get_player(g);
    return player->x == g->map->end.x && player->y == g->map->end.y;
}

/**
 * @brief function that convert an action to a movement
 * @param act the action the player did.
 * @param y y node coordiantes.
 * @param x x node coordinates.
 */
void game_next_move(action act, int *y, int *x) {
    switch (act) {
    case NONE:
    case ENTER:
    case QUIT:
        return;
    case UP:
        *y -= 1;
        return;
    case DOWN:
        *y += 1;
        return;
    case LEFT:
        *x -= 1;
        return;
    case RIGHT:
        *x += 1;
        return;
    }
}

/**
 * @brief function that  update the score of the game.
 * @param g pointer with game information.
*/
void game_update_score(game *g) {
    node *player = game_get_player(g);
    node *n = map_get_node(g->map, player->y, player->x);

    if (n->type == COIN) {
        g->score += 10;
    } else if (n->type == UNEVENT) {
        g->score = g->score / 2;
    } else if (n->type == DRILL){
        g->drill += 3;
        g->score--;
    } else {
        g->score--;
    }

    n->type = EMPTY;
}

/**
 * @brief function that execute an iteration of the game
 *
 * @param g pointer with game information
 * @param act action that the player did
*/
void game_update(game *g, action act) {
    // return false if move doesn't change state
    if (act == NONE || act == ENTER || act == QUIT)
        return;

    node *player = game_get_player(g);
    int x = player->x;
    int y = player->y;

    game_next_move(act, &y, &x);

    node *next = map_get_node(g->map, y, x);
    if (next == NULL) {
        return;
    }
    if (next->type == WALL) {
        if (g->drill > 0) {
            g->drill--;
        } else {
            return;
        }
    }

    queue_push_head(g->player, game_node_create(y, x));
    if (next->type == COIN) {
        queue_push(g->player, game_node_create(player->y, player->x));
    }
    node *n = queue_pop_last(g->player);
    free(n);

    queueNode *qn = queue_overlap(g->player);
    if (qn != NULL) {
        int removed = queue_remove_from(g->player, qn);
        g->score -= 10 * removed;
    }

    game_update_score(g);
}

/**
 * @brief dealloc memory used by the game.
 * @param g pointer with game information.
*/
void game_free(game *g) {
    map_free(g->map);
    queue_free(g->player);
    free(g);
}
