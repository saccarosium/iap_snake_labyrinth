#include <ncurses.h>
#include <string.h>
#include "ui.h"
#include "alloc.h"

win *ui_get_term_info() {
    win *term = xmalloc(sizeof(win));
    // Gets the current terminal info
    getbegyx(stdscr, term->min_y, term->min_x);
    getmaxyx(stdscr, term->max_y, term->max_x);
    term->winid = stdscr;
    term->center.x = term->max_x / 2;
    term->center.y = term->max_y / 2;
    return term;
}

void ui_size_error(win *term) {
    char *error = "Screen too small!";
    // win *term = ui_get_term_info();
    mvprintw(term->center.y, (term->max_x - strlen(error)) / 2, "%s", error);
}

win *ui_create_win(int h, int w) {
    int min_col, min_row;
    win *term = ui_get_term_info();
    win *frame = xmalloc(sizeof(win));

    // Minimum
    min_row = 79;
    min_col = 24;

    frame->max_y = h;
    frame->max_x = w;

    if (term->max_y >= min_col || term->max_x >= min_row) {
        frame->min_y = (term->max_y - frame->max_y) / 2;
        frame->min_x = (term->max_x - frame->max_x) / 2;

        frame->center.y = frame->max_y / 2;
        frame->center.x = frame->max_x / 2;

        // initialize the WINDOW
        frame->winid = newwin(frame->max_y, frame->max_x, frame->min_y, frame->min_x);
        refresh();
        box(frame->winid, 0, 0);
        wrefresh(frame->winid);
    } else {
        ui_size_error(term);
    }
    return frame;
}

void ui_init() {
    ui_create_win(40, 100);
}
