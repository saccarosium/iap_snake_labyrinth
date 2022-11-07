#ifndef GAME_H
#define GAME_H

#include "../include/map.h"
#include "../include/path.h"
#include "../include/utils.h"

typedef struct game {
    vec2 player;
    int coin;
    map *map;
    path *path;
} game;

game *game_init(char *filename);

#endif // !GAME_H
