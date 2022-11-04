#include "../include/game.h"
#include "../include/path.h"
#include "../include/alloc.h"

game *game_init(char *filename) {
    game *g = xmalloc(sizeof(game));

    int err = 0;
    g->map = map_load_from_file(filename, &err);
    if(err != 0) {
        free(g);
        return NULL;
    }

    g->path = path_create();
    g->coin = 0;

    return g;
}
