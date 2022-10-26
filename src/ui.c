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
    mvwprintw(term->winid, term->center.y, term->center.x - (strlen(error) / 2), "%s", error);
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

        // refresh();
        wrefresh(frame->winid);
    } else {
        ui_size_error(term);
    }
    return frame;
}

void ui_stack_win(win *win1, win *win2) {
    win *term = ui_get_term_info();
    // mvwin(win1->winid, 1, (term->max_x - win1->max_x) / 2);
    mvwin(win2->winid, win1->max_y + win1->min_y, (term->max_x - win2->max_x) / 2);
    wrefresh(win1->winid);
    wrefresh(win2->winid);
}

void ui_print_map() {
}

void ui_create_menu() {
}

void ui_print_legend(win *frame) {
    char *direction = "k: UP j: DOWN h: LEFT l: RIGHT q: QUIT";
    mvwprintw(frame->winid, frame->center.y, frame->center.x - (strlen(direction) / 2), "%s", direction);
}

void ui_init() {
    win *game_win = ui_create_win(20, 60);
    win *menu_win = ui_create_win(3, 60);
    ui_stack_win(game_win, menu_win);
    box(game_win->winid, 0, 0);
    box(menu_win->winid, 0, 0);
    ui_print_legend(menu_win);
    wrefresh(game_win->winid);
    wrefresh(menu_win->winid);
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
