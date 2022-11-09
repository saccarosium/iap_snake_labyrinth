#include <ncurses.h>

int main() {
    /* Template:
    ui *u = ui_init();

    // ui menu (choose gamemode)

    error *err = OK;
    game *g = game_init(&err);

    // error loading game
    if(err != OK) {
        ui_error(u, err);
    }

    // game loop
    while(!game_ended(g)) {
        char keypress = ui_get_input();
        game_update(g, keypress, &err);
        // game update puo' ritornare un errore?

        ui_update(g, err);
        if(err != OK) break;
    }

    if(err != OK) {
        // stuff
    }

    game_cleanup(g);
    ui_cleanup(u);
    */
    return 0;
}
