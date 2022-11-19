#include "../include/astar.h"
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
        p = astar_solve(g->map);
    } else {
        p = path_create();
    }

    while (!game_ended(g)) {
        action act = path_next(p);

        if (act == NONE) {
            // user input
            act = ui_get_input();
            if (act == -1 || act == 0)
                continue;
            else if (act == ENTER) {
                //
            } else if (act == QUIT) {
                //
            } else {
                // do not add to path if game returned false
                path_push(p, act);
                path_next(p);
            }
        }

        printf("%d\n", act);
        game_update(g, act);
        // printf("%d %d\n", g->player.y, g->player.x);
    }

    // printf("coin: %d\n", g->coin);
    printf("%s\n", path_string(p));

    return 0;
}
