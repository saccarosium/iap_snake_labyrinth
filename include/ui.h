#ifndef UI_H
#define UI_H

#include "map.h"
#include "path.h"
#include "utils.h"
#include "game.h"
#include <curses.h>

typedef struct win {
    int width;
    int height;
    int x;
    int y;
    vec2 center;
    WINDOW *id;
} win;

void ui_init();
void ui_popup_error(error error_code);
void ui_decode_error(error error_code, char **msg);
void ui_startmenu_init(game *g, action *quit);
action ui_get_input();

#endif // !UI_H
