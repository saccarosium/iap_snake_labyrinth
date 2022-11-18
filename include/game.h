#ifndef GAME_H
#define GAME_H

#include "../include/map.h"
#include "../include/utils.h"
#include "options.h"

typedef struct game {
    vec2 player;
    int coin;
    map *map;
    saved_opt opt;
} game;

game *game_init(map *m, error *err);
bool game_ended(game *g);
void game_update(game *g, action act);

#endif // !GAME_H
