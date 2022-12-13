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

        layout_t *lay;
        if (quit != QUIT)
            lay = ui_init_layout(g);

        while (!game_ended(g) && quit != QUIT) {
            ui_map_print(lay->map, g->map);
            mvwaddch(lay->map->id, g->player.y, g->player.x, 'o');
            wrefresh(lay->map->id);
            int *a = map_get_possible_movements(g->map, g->player.y, g->player.x);

            // print array of possible movements
            // for (int i = 0; i < 4; i++) {
            //     wprintw(stdscr, "%d", a[i]);
            //     refresh();
            // }
            // wprintw(stdscr, "\n");

            action act = path_next(p);

            if (act == NONE) {
                act = ui_get_input();
                if (!a[0] && act == LEFT)
                    act = NONE;
                if (!a[1] && act == RIGHT)
                    act = NONE;
                if (!a[2] && act == UP)
                    act = NONE;
                if (!a[3] && act == DOWN)
                    act = NONE;
                if (act == QUIT) {
                    exit(1);
                } else {
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
