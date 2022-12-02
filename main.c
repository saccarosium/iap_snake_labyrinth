#include "include/backtracking.h"
#include "include/game.h"
#include "include/path.h"
#include <ncurses.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    error err = OK;

    map *m = NULL;
    if (argc == 2 && strcmp(argv[1], "--challenge") == 0) {
        m = map_load_from_stdin(&err);
    }

    if (m == NULL || err != 0) {
        exit(EXIT_FAILURE);
    }

    path *p = NULL;
    if (argc == 2 && strcmp(argv[1], "--challenge") == 0) {
        p = backtracking_solve(m);
    }

    printf("%s\n", path_string(p));

    return 0;
}
