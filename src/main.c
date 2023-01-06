#include "../include/astar.h"
#include "../include/backtracking.h"
#include "../include/game.h"
#include "../include/path.h"
#include "../include/ui.h"
#include "../include/ui_win.h"
#include "../include/ui_utils.h"
#include "../include/right.h"
#include "../include/random.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    error err = OK;

    game_mode mode = INTERACTIVE;
    if (argc == 2 && strcmp(argv[1], "--challenge") == 0)
        mode = CHALLENGE;

    if (mode == CHALLENGE) {
        map *m = map_load_from_stdin(&err);
        if (m == NULL || err != 0) {
            exit(EXIT_FAILURE);
        }

        path *p = backtracking_solve(m);
        char *string = path_string(p);
        printf("%s\n", string);

        free(string);
        path_free(p);

        return 0;
    }

    action quit = NONE;
    int level = 0;

    ui_init();
    ui_splash_init();
    ui_startmenu_init(&quit, &mode, &level);

    if (quit == QUIT) {
        ui_end();
        return 0;
    }

    char map_file[STRING_LENGHT];
    sprintf(map_file, "assets/maze%d.txt", level);
    map *m = map_load_from_file(map_file, &err);

    if (m == NULL || err != 0) {
        exit(EXIT_FAILURE);
    }

    game *g = game_init(m, &err);
    if (g == NULL || err != 0) {
        exit(EXIT_FAILURE);
    }

    path *p;
    if (g->mode == AI) {
        p = backtracking_solve(g->map);
    } else if (g->mode == AI_RIGHT) {
        p = right_solve(g->map);
    } else if (g->mode == AI_RANDOM) {
        p = random_solve(g->map);
    } else {
        p = path_create();
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
        if (g->mode != INTERACTIVE) {
            usleep(TIMEOUT);
        }
    }

    if (game_ended(g) && quit != QUIT) {
        ui_map_print(lay->map, g->map, g->player);
        ui_win_clear(lay->legend->id, true);
        ui_win_print_centered_x(lay->legend, 0, " MOVES ");
        ui_win_print_centered(lay->legend, path_string(p));
        wrefresh(lay->legend->id);
        getch();
    }

    ui_end();

    path_free(p);
    game_free(g);
    ui_layout_free(lay);

    return 0;
}
