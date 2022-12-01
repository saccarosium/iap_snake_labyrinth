// 893189 894579 894360 896954
#include "./include/astar.h"
#include "./include/game.h"
#include "./include/path.h"
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

    printf("%s\n", path_string(p));

    return 0;
}
