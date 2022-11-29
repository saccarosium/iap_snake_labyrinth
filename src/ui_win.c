#include "../include/ui_win.h"
#include "../include/ui_error.h"
#include "../include/alloc.h"
#include <ncurses.h>

void ui_win_clear() {
    clear();
    refresh();
}

void ui_win_get_center(win *win) {
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
win *ui_win_term_info() {
    win *term = xmalloc(sizeof(win));
    getbegyx(stdscr, term->y, term->x);
    getmaxyx(stdscr, term->height, term->width);
    term->id = stdscr;
    ui_win_get_center(term);
    return term;
}

// Create a window an returns a pointer to it
win *ui_win_create(int h, int w, bool box) {
    win *term = ui_win_term_info();
    win *frame = xmalloc(sizeof(win));
    frame->height = h;
    frame->width = w;
    if (term->height >= frame->height && term->width >= frame->width) {
        frame->y = (term->height - frame->height) / 2;
        frame->x = (term->width - frame->width) / 2;
        ui_win_get_center(frame);
        // initialize the WINDOW
        frame->id = newwin(frame->height, frame->width, frame->y, frame->x);
        if (box) {
            box(frame->id, 0, 0);
        }
        wrefresh(frame->id);
    } else {
        ui_popup_error(WINDOW_TOO_SMALL);
    }
    return frame;
}

// Stack to windows on top of each other
void ui_win_stack(win *win1, win *win2) {
    win *term = ui_win_term_info();
    mvwin(win2->id, win1->height + win1->y, (term->width - win2->width) / 2);
    wrefresh(win1->id);
    wrefresh(win2->id);
}
