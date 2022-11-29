#ifndef UI_WIN_H
#define UI_WIN_H

#include "map.h"
#include "path.h"
#include "utils.h"
#include "game.h"
#include <ncurses.h>

typedef struct win {
    int width;
    int height;
    int x;
    int y;
    vec2 center;
    WINDOW *id;
} win;

void ui_win_clear();
void ui_win_get_center(win *win);
win *ui_win_term_info();
win *ui_win_create(int h, int w, bool box);
void ui_win_stack(win *win1, win *win2);

#endif // !UI_WIN_H
