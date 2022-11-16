#include <ncurses.h>
#include <stdio.h>
#include "../include/game.h"
#include "../include/ui.h"
#include "../include/path.h"
// #include "../include/astar.h"

int main() {
    error err = OK;
    game *g = game_init("assets/maze1.txt", &err);
    path *p = path_create();

    // path *p = astar_solve(g->map);

    while(!game_ended(g)) {
        direction dir = path_next(p);
        if(dir == NONE){
            // user input
            dir = ui_get_input();
            if(dir == -1) continue;
            path_push(p, dir);
            path_next(p);
        }
        printf("%d\n", dir);
        game_update(g, dir);
    }

    return 0;
}
