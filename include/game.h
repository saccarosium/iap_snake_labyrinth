#ifndef GAME_H
#define GAME_H

#include "../include/map.h"
#include "../include/utils.h"
#include "../include/queue.h"

#define DEFAULT_MAP "assets/maze3.txt"
#define DEFAULT_LEVEL 3

typedef enum game_mode {
    INTERACTIVE,
    AI,
    AI_RIGHT,
    AI_RANDOM,
    CHALLENGE,
} game_mode;

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
