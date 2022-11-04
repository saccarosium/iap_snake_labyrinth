#ifndef UI_H
#define UI_H

#include "map.h"
#include "path.h"
#include <curses.h>

typedef struct center {
    int x;
    int y;
} center;

typedef struct win {
    int width;
    int height;
    int x;
    int y;
    center center;
    WINDOW *winid;
} win;

void ui_init();
void ui_popup_error(int error_code);
direction ui_get_input();

#endif // !UI_H
