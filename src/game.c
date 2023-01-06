#include "../include/game.h"
#include "../include/path.h"
#include "../include/utils.h"
#include "../include/alloc.h"
#include <stdlib.h>

node *game_node_create(int y, int x) {
    node *n = malloc(sizeof(node));
    n->x = x;
    n->y = y;

    n->cost = 0;
    n->parent = 0;
    n->type = 0;

    return n;
}

game *game_init(map *m, error *err) {
    game *g = malloc(sizeof(game));
    if (g == NULL) {
        *err = MALLOC_FAILED;
        return NULL;
    }

    g->map = m;

    g->player = queue_create(false);
    node *start = game_node_create(g->map->start.y, g->map->start.x);

    queue_push(g->player, start);

    g->score = 1000;
    g->drill = 0;

    return g;
}

node *game_get_player(game *g) {
    return g->player->head->node;
}

bool game_ended(game *g) {
    node *player = game_get_player(g);
    return player->x == g->map->end.x && player->y == g->map->end.y;
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
    node *player = game_get_player(g);
    node *n = map_get_node(g->map, player->y, player->x);

    if (n->type == COIN) {
        g->score += 10;
    } else if (n->type == UNEVENT) {
        g->score = g->score / 2;
    } else if (n->type == DRILL){
        g->drill += 3;
        g->score--;
    } else {
        g->score--;
    }

    n->type = EMPTY;
}

void game_update(game *g, action act) {
    // return false if move doesn't change state
    if (act == NONE || act == ENTER || act == QUIT)
        return;

    node *player = game_get_player(g);
    int x = player->x;
    int y = player->y;

    game_next_move(act, &y, &x);

    node *next = map_get_node(g->map, y, x);
    if (next == NULL) {
        return;
    }
    if (next->type == WALL) {
        if (g->drill > 0) {
            g->drill--;
        } else {
            return;
        }
    }

    queue_push_head(g->player, game_node_create(y, x));
    if (next->type == COIN) {
        queue_push(g->player, game_node_create(player->y, player->x));
    }
    node *n = queue_pop_last(g->player);
    free(n);

    queueNode *qn = queue_overlap(g->player);
    if (qn != NULL) {
        queue_remove_from(g->player, qn);
    }

    game_update_score(g);
}

void game_free(game *g) {
    map_free(g->map);
    queue_free(g->player);
    free(g);
}
