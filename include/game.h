#ifndef GAME_H
#define GAME_H

#include "../include/map.h"
#include "../include/path.h"

typedef struct player {
    int x;
    int y;
} player;

typedef struct game {
    player player;
    int coin;
    map *map;
    path *path;
} game;

game *game_init(char *filename);

#endif // !GAME_H
