#ifndef UI_WIN_H
#define UI_WIN_H

#include "map.h"
#include "path.h"
#include "utils.h"
#include "game.h"
#include <ncurses.h>

/**
 * @brief struct defining the position and size of a window
 *
 * @params width width of the window
 * @params height height of the window
 * @params x offset from the left of the screen
 * @params y offset from the top of the screen
 * @params center position of the center
 * @params id window id from curses
*/
typedef struct win_t {
    int width;
    int height;
    int x;
    int y;
    vec2 center;
    WINDOW *id;
} win_t;


/**
 * @brief struct containing what should be printed
 *
 * @params game pointer to game window
 * @params legend pointer to legend window
 * @params stats pointe to statistics window
 * @params map pointer to map window
 *
 * @see win_t
*/
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
