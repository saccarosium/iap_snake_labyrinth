#include "../include/game.h"
#include "../include/path.h"
#include "../include/utils.h"
#include <stdlib.h>

game *game_init(char *filename, error *err) {
    game *g = malloc(sizeof(game));
    if(g == NULL) {
        *err = MALLOC_FAILED;
        return NULL;
    }

    g->map = map_load_from_file(filename, err);
    if(*err != MAP_OK) {
        free(g);
        return NULL;
    }

    g->player.x = g->map->start.x;
    g->player.y = g->map->start.y;

    g->coin = 0;

    return g;
}

bool game_ended(game *g) {
    return g->player.x == g->map->end.x && g->player.y == g->map->end.y;
}

void game_next_move(direction dir, int *x, int *y) {
    switch (dir) {
    case NONE:
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

void game_update_score(game *g) {
    node *n = map_get_node(g->map, g->player.x, g->player.y);

    if(n->type == COIN) {
        g->coin++;
    } else if(n->type == UNEVENT) {
        g->coin = g->coin / 2;
    }

    n->type = EMPTY;
}

void game_update(game *g, direction dir) {
    if(dir == NONE) return;

    int x = g->player.x;
    int y = g->player.y;

    game_next_move(dir, &x, &y);

    node *next = map_get_node(g->map, x, y);
    if(next == NULL || next->type == WALL) return;

    g->player.x = x;
    g->player.y = y;

    game_update_score(g);
}
