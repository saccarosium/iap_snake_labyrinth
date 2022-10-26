#include <ncurses.h>
#include <string.h>
#include "ui.h"
#include "map.h"
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
    mvprintw(term->center.y, term->center.x - (strlen(error) / 2), "%s", error);
}

win *ui_create_win(int h, int w) {
    win *term = ui_get_term_info();
    win *frame = xmalloc(sizeof(win));

    frame->max_y = h;
    frame->max_x = w;

    if (term->max_y >= frame->max_y && term->max_x >= frame->max_x) {
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

void ui_print_map(win *win, map *map) {
}

direction ui_get_input() {
    char ch;
    ch = getchar();
    switch (ch) {
    case 'h':
        return LEFT;
    case 'l':
        return RIGHT;
    case 'k':
        return UP;
    case 'j':
        return DOWN;
    case 'q':
        break;
    }
    return -1;
}
