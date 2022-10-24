#include <ncurses.h>
#include <string.h>
#include "include.h"

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

void ui_create_menu(win frame) {

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

void ui_create_win(char *maze) {
    int min_col, min_row;
    win term;
    win frame;

    // Minimum
    min_row = 79;
    min_col = 24;

    frame.max_y = 40;
    frame.max_x = 100;

    // Gets the current terminal max x and y
    getbegyx(stdscr, term.min_y, term.min_x);
    getmaxyx(stdscr, term.max_y, term.max_x);

    if (term.max_y < min_col || term.max_x < min_row) {
        frame = term;
        maze = "Too Smoll!";
    } else {
        frame.min_y = (term.max_y - frame.max_y) / 2;
        frame.min_x = (term.max_x - frame.max_x) / 2;
    }

    frame.center.y = frame.max_y / 2;
    frame.center.x = frame.max_x / 2;


    // initialize the WINDOW
    WINDOW *win = newwin(frame.max_y, frame.max_x, frame.min_y, frame.min_x);
    refresh();
    box(win, 0, 0);

    mvwprintw(win, frame.center.y, (frame.max_x - strlen(maze)) / 2, maze);
    wrefresh(win);
}
