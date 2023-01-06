#include "../include/ui_win.h"
#include "../include/ui_utils.h"
#include "../include/alloc.h"
#include <string.h>
#include <ncurses.h>

// Clear the screen
void ui_screen_clear() {
    clear();
    refresh();
}

// Clear the contents of a specific window
void ui_win_clear(WINDOW *win, bool border) {
    wclear(win);
    if (border) ui_win_border(win);
}

// Updates position a window
void ui_win_update_pos(win_t *win) {
    win_t *term = ui_win_term_info();
    win->y = (term->height - win->height) / 2;
    win->x = (term->width - win->width) / 2;
}

// Calculate the center of a spcific window
void ui_win_get_center(win_t *win) {
    win->center.y = win->height / 2;
    if (win->height % 2 == 0) {
        win->center.y -= 1;
    }
    win->center.x = win->width / 2;
    if (win->width % 2 == 0) {
        win->center.x -= 1;
    }
}

// Gets the current terminal info
win_t *ui_win_term_info() {
    win_t *term = xmalloc(sizeof(win_t));
    getbegyx(stdscr, term->y, term->x);
    getmaxyx(stdscr, term->height, term->width);
    term->id = stdscr;
    ui_win_get_center(term);
    return term;
}

// Create a window an returns a pointer to it
win_t *ui_win_create(int h, int w, bool centered) {
    win_t *term = ui_win_term_info();
    win_t *win = xmalloc(sizeof(win_t));
    win->height = h;
    win->width = w;
    if (term->height >= win->height && term->width >= win->width) {
        if (centered) {
            win->y = (term->height - win->height) / 2;
            win->x = (term->width - win->width) / 2;
        } else {
            win->y = 0;
            win->x = 0;
        }
        ui_win_get_center(win);
        // initialize the WINDOW
        win->id = newwin(win->height, win->width, win->y, win->x);
        wrefresh(win->id);
    } else {
        ui_popup_error(WINDOW_TOO_SMALL);
    }
    free(term);
    return win;
}

// Stack to windows on top of each other
void ui_win_stack(win_t *main, win_t *moving, int y_offset, int x_offset, bool up, bool down) {
    if (up)
        mvwin(moving->id, main->y - moving->height + y_offset, moving->x);
    else if (down)
        mvwin(moving->id, main->y + main->height - y_offset, moving->x);
    ui_win_update_pos(moving);
    wrefresh(main->id);
    wrefresh(moving->id);
}

void ui_win_border(WINDOW *win) {
    box(win, 0, 0);
    wrefresh(win);
}

// Print a string at the center of the screen both in the x and y axes
void ui_win_print_centered(win_t *win, char *msg) {
    mvwprintw(win->id, win->center.y, win->center.x - (strlen(msg) / 2), "%s", msg);
}

// Print a string at the center of the screen only in the x axe
void ui_win_print_centered_x(win_t *win, int y, char *msg) {
    mvwprintw(win->id, y, win->center.x - (strlen(msg) / 2), "%s", msg);
}
