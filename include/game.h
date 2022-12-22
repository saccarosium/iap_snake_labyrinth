#ifndef GAME_H
#define GAME_H

#include "../include/map.h"
#include "../include/utils.h"
#include "../include/queue.h"

typedef enum game_mode {
    INTERACTIVE,
    AI,
    CHALLENGE,
} game_mode;

typedef struct game {
    queue *player;
    int coin;
    int drill;
    map *map;
    game_mode mode;
} game;

game *game_init(map *m, error *err);
bool game_ended(game *g);
void game_update(game *g, action act);
node *game_get_player(game *g);

#endif // !GAME_H
