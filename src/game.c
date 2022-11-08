#include "../include/game.h"
#include "../include/path.h"
#include "../include/alloc.h"
#include "../include/utils.h"

game *game_init(char *filename) {
    game *g = xmalloc(sizeof(game));

    error error;
    g->map = map_load_from_file(filename, &error);
    if(error != MAP_OK) {
        free(g);
        return NULL;
    }

    g->player.x = g->map->start.x;
    g->player.y = g->map->start.y;

    g->path = path_create();
    g->coin = 0;

    return g;
}
