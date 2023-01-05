#include "../include/astar.h"
#include "../include/backtracking.h"
#include "../include/game.h"
#include "../include/path.h"
#include "../include/ui.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    error err = OK;

    game_mode mode = INTERACTIVE;
    if (argc == 2 && strcmp(argv[1], "--challenge") == 0)
        mode = CHALLENGE;

    map *m = NULL;
    if (mode == CHALLENGE) {
        m = map_load_from_stdin(&err);
    } else {
        m = map_load_from_file("assets/maze2.txt", &err);
    }

    if (m == NULL || err != 0) {
        exit(EXIT_FAILURE);
    }

    game *g = game_init(m, &err);
    if (g == NULL || err != 0) {
        exit(EXIT_FAILURE);
    }
    g->mode = mode;

    if (g->mode == CHALLENGE) {
        path *p = backtracking_solve(g->map);
        char *string = path_string(p);
        printf("%s\n", string);

        free(string);
        path_free(p);
        game_free(g);

        return 0;
    }

    action quit = NONE;
    path *p = path_create();

    ui_init();
    ui_splash_init();
    ui_startmenu_init(g, &quit);

    if (quit == QUIT) {
        ui_end();
        return 0;
    }

    layout_t *lay = ui_layout_init(g);

    while (!game_ended(g) && quit != QUIT) {
        ui_map_print(lay->map, g->map, g->player);
        ui_stats_print(lay->stats, g);

        action act = path_next(p);

        if (act == NONE) {
            act = ui_get_input();
            if (act == QUIT) {
                quit = QUIT;
            }
            path_push(p, act);
            path_next(p);
        }
        game_update(g, act);
    }
    ui_end();

    path_free(p);
    game_free(g);
    ui_layout_free(lay);

    return 0;
}
