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
direction ui_get_input();

#endif // !UI_H
