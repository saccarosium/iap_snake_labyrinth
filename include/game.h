#ifndef GAME_H
#define GAME_H

#include "../include/map.h"
#include "../include/utils.h"
#include "../include/queue.h"

/**
 * enum specifying every possible game mode
*/
typedef enum game_mode {
    INTERACTIVE,
    AI,
    AI_RIGHT,
    AI_RANDOM,
    CHALLENGE,
} game_mode;

/**
 * @brief struct defining the necessary informations for the game
 *
 * @param player player positions from head to end
 * @param score current score of the game
 * @param drill drill count that can be used
 * @param level current level
 * @param map pointer to the map informations
 * @param mode current mode of the game
*/
typedef struct game {
    queue *player;
    int score;
    int drill;
    int level;
    map *map;
    game_mode mode;
} game;

game *game_init(map *m, error *err);
bool game_ended(game *g);
void game_update(game *g, action act);
node *game_get_player(game *g);
void game_free(game *g);

#endif // !GAME_H
