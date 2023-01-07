#ifndef GAME_H
#define GAME_H

#include "../include/map.h"
#include "../include/utils.h"
#include "../include/queue.h"

#define DEFAULT_MAP "assets/maze3.txt"
#define DEFAULT_LEVEL 3
/**
 * @file
 * @brief File that countains the function relating to the player information. 
*/
/**
 * @brief specifying the type of game 
 * @param INTERACTIVE interactive mode
 * @param AI Ai mode
 * @param AI_RIGHT always right mode
 * @param AI_RANDOM Ai random mode
 * @param CHALLENGE challenge mode
*/
typedef enum game_mode {
    INTERACTIVE,
    AI,
    AI_RIGHT,
    AI_RANDOM,
    CHALLENGE,
} game_mode;
/**
 * @brief
 * @param player pointer of the player
 * @param score point of the game
 * @param drill number of drill
 * @param level number of the level
 * @param map poiter of the map
 * @param mode type of the game
*/
typedef struct game {
    queue *player;
    int score;
    int drill;
    int level;
    map *map;
    game_mode mode;
} game;
/**
 * @brief function that load the map in a new pointer.
 * @param m pointer to the map.
 * @param err pointer to the exit status of the function (error type defined by the enum error)
 * @return pointer g, pointer with game information.
*/
game *game_init(map *m, error *err);
/**
 * @brief function that check if the player finish the game.
 * @param g pointer with game information.
 * @return  true if player reach the end of the map.
*/
bool game_ended(game *g);
/**
 * @brief function that updates the score of the game.
 * @param g pointer with game information.
 * @param act action that the player do.
*/
void game_update(game *g, action act);
/**
 * @brief function that get information about the player.
 * @param g pointer with game information.
 * @return the player position.
*/
node *game_get_player(game *g);
/**
 * @brief free memori used by the game.
 * @param g pointer with game information.
*/
void game_free(game *g);

#endif // !GAME_H
