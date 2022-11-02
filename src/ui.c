#include <ncurses.h>
#include <string.h>
#include "../include/ui.h"
#include "../include/map.h"
#include "../include/alloc.h"

// Gets the current terminal info
win *ui_win_term_info() {
    win *term = xmalloc(sizeof(win));
    getbegyx(stdscr, term->y, term->x);
    getmaxyx(stdscr, term->height, term->width);
    term->winid = stdscr;
    term->center.x = term->width / 2;
    term->center.y = term->height / 2;
    return term;
}

void ui_win_size_error(win *term) {
    char *error = "Screen too small!";
    mvwprintw(term->winid, term->center.y, term->center.x - (strlen(error) / 2), "%s", error);
}

void ui_legend_print(win *frame) {
    char *direction = "k: UP j: DOWN h: LEFT l: RIGHT q: QUIT";
    mvwprintw(frame->winid, frame->center.y, frame->center.x - (strlen(direction) / 2), "%s", direction);
}

void ui_map_print() {
}

// Create a window an returns a pointer to it
win *ui_win_create(int h, int w) {
    win *term = ui_win_term_info();
    win *frame = xmalloc(sizeof(win));
    frame->height = h;
    frame->width = w;
    if (term->height >= frame->height && term->width >= frame->width) {
        frame->y = (term->height - frame->height) / 2;
        frame->x = (term->width - frame->width) / 2;
        frame->center.y = frame->height / 2;
        frame->center.x = frame->width / 2;
        // initialize the WINDOW
        frame->winid = newwin(frame->height, frame->width, frame->y, frame->x);
        wrefresh(frame->winid);
    }
    return frame;
}

// Stack to windows on top of each other
void ui_win_stack(win *win1, win *win2) {
    win *term = ui_win_term_info();
    mvwin(win2->winid, win1->height + win1->y, (term->width - win2->width) / 2);
}

void ui_init() {
    win *game_win = ui_win_create(20, 60);
    win *menu_win = ui_win_create(3, 60);
    ui_win_stack(game_win, menu_win);
    box(game_win->winid, 0, 0);
    box(menu_win->winid, 0, 0);
    ui_legend_print(menu_win);
    wrefresh(game_win->winid);
    wrefresh(menu_win->winid);
}

direction ui_input_get() {
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
