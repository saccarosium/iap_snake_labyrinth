#ifndef GAME_H
#define GAME_H

#include "../include/map.h"
#include "../include/utils.h"
#include "options.h"

typedef enum game_mode {
    INTERACTIVE,
    AI,
} game_mode;

typedef struct game {
    vec2 player;
    int coin;
    int drill;
    map *map;
    saved_opt opt;
    game_mode mode;
} game;

game *game_init(map *m, error *err);
bool game_ended(game *g);
void game_update(game *g, action act);

#endif // !GAME_H
