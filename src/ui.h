#ifndef UI_H
#define UI_H

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

#endif // !UI_H
