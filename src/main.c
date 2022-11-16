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
        action act = path_next(p);
        if(act == NONE){
            // user input
            act = ui_get_input();
            if(act == -1) continue;
            if(act == ENTER) {
                //
            } else if(act == QUIT) {
                //
            } else {
                path_push(p, act);
                path_next(p);
            }
        }
        printf("%d\n", act);
        game_update(g, act);
    }

    return 0;
}
