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
    win_t *stats;
    win_t *map;
} layout_t;

void ui_screen_clear();
void ui_win_get_center(win_t *win_t);
void ui_win_clear(WINDOW *win, bool border);
void ui_win_border(WINDOW *win);
void ui_win_print_centered(win_t *win, char *msg);
void ui_win_print_centered_x(win_t *win, int y, char *msg);
void ui_win_stack(win_t *main, win_t *moving, int y_offset, int x_offset, bool up, bool down);
win_t *ui_win_term_info();
win_t *ui_win_create(int h, int w, bool centered);

#endif // !UI_WIN_H
