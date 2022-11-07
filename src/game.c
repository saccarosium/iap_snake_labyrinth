#include "../include/game.h"
#include "../include/path.h"
#include "../include/alloc.h"

game *game_init(char *filename) {
    game *g = xmalloc(sizeof(game));

    g->map = map_load_from_file(filename);
    if(g->map != NULL) {
        free(g);
        return NULL;
    }

    g->player.x = g->map->start.x;
    g->player.y = g->map->start.y;

    g->path = path_create();
    g->coin = 0;

    return g;
}
