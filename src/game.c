#include "../include/game.h"
#include "../include/path.h"
#include "../include/utils.h"
#include "../include/alloc.h"
#include <stdlib.h>

game *game_init(map *m, error *err) {
    game *g = malloc(sizeof(game));
    if (g == NULL) {
        *err = MALLOC_FAILED;
        return NULL;
    }

    g->map = m;

    g->player.x = g->map->start.x;
    g->player.y = g->map->start.y;

    g->coin = 0;
    g->drill = 0;

    return g;
}

bool game_ended(game *g) {
    return g->player.x == g->map->end.x && g->player.y == g->map->end.y;
}

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

void game_update_score(game *g) {
    node *n = map_get_node(g->map, g->player.y, g->player.x);

    if (n->type == COIN) {
        g->coin++;
    } else if (n->type == UNEVENT) {
        g->coin = g->coin / 2;
    } else if (n->type == DRILL){
        g->drill = g->drill + 3;
    }

    n->type = EMPTY;
}

void game_update(game *g, action act) {
    // return false if move doesn't change state
    if (act == NONE || act == ENTER || act == QUIT)
        return;

    int x = g->player.x;
    int y = g->player.y;

    game_next_move(act, &y, &x);

    node *next = map_get_node(g->map, y, x);
    if (next == NULL || next->type == WALL && g->drill < 1)
        return;
    else
        g->drill--;
        
    g->player.x = x;
    g->player.y = y;

    game_update_score(g);
}
