#ifndef UI_WIN_H
#define UI_WIN_H

#include "map.h"
#include "path.h"
#include "utils.h"
#include "game.h"
#include <ncurses.h>

typedef struct win_t {
    int width;
    int height;
    int x;
    int y;
    vec2 center;
    WINDOW *id;
} win_t;

typedef struct layout_t {
    win_t *game;
    win_t *legend;
    win_t *map;
} layout_t;

void ui_win_clear();
void ui_win_get_center(win_t *win_t);
win_t *ui_win_term_info();
win_t *ui_win_create(int h, int w, bool box);
void ui_win_stack(win_t *win1, win_t *win2);

#endif // !UI_WIN_H
