#include "../include/astar.h"
#include "../include/backtracking.h"
#include "../include/game.h"
#include "../include/path.h"
#include "../include/ui.h"
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    error err = OK;

    map *m = NULL;
    if (argc == 2 && strcmp(argv[1], "--challenge") == 0) {
        m = map_load_from_stdin(&err);
    } else {
        m = map_load_from_file("assets/maze1.txt", &err);
    }

    if (m == NULL || err != 0) {
        exit(EXIT_FAILURE);
    }

    game *g = game_init(m, &err);
    if (g == NULL || err != 0) {
        exit(EXIT_FAILURE);
    }

    path *p = NULL;
    if (argc == 2 && strcmp(argv[1], "--challenge") == 0) {
        g->mode = CHALLENGE;
        p = backtracking_solve(g->map);
    } else {
        p = path_create();
    }

    action quit = NONE;

    if (g->mode != CHALLENGE) {

        ui_init();
        ui_startmenu_init(g, &quit);

        while (!game_ended(g) && quit != QUIT) {
            ui_init_layout(g);

            action act = path_next(p);

            if (act == NONE) {
                // user input
                act = ui_get_input();
                if (act == -1 || act == 0)
                    continue;
                else if (act == ENTER) {
                } else if (act == QUIT) {
                    exit(1);
                } else {
                    // do not add to path if game returned false
                    path_push(p, act);
                    path_next(p);
                }
            }
            game_update(g, act);
        }
    } else if (g->mode == CHALLENGE) {
        printf("%s\n", path_string(p));
    }

    return 0;
}
