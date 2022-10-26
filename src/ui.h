#ifndef UI_H
#define UI_H

#include "map.h"
#include <curses.h>

typedef struct center {
    int x;
    int y;
} center;

typedef struct win {
    int max_x;
    int max_y;
    int min_x;
    int min_y;
    center center;
    WINDOW *winid;
} win;

void ui_init();
direction ui_get_input();

#endif // !UI_H
