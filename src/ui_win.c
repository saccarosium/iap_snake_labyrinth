#include "../include/ui_win.h"
#include "../include/ui_utils.h"
#include "../include/alloc.h"
#include <ncurses.h>

void ui_win_clear() {
    clear();
    refresh();
}

void ui_win_update_pos(win_t *frame) {
    win_t *term = ui_win_term_info();
    frame->y = (term->height - frame->height) / 2;
    frame->x = (term->width - frame->width) / 2;
}

void ui_win_get_center(win_t *win_t) {
    win_t->center.y = win_t->height / 2;
    if (win_t->height % 2 == 0) {
        win_t->center.y -= 1;
    }
    win_t->center.x = win_t->width / 2;
    if (win_t->width % 2 == 0) {
        win_t->center.x -= 1;
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
win_t *ui_win_create(int h, int w, bool box) {
    win_t *term = ui_win_term_info();
    win_t *frame = xmalloc(sizeof(win_t));
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
    free(term);
    return frame;
}

// Stack to windows on top of each other
void ui_win_stack(win_t *win1, win_t *win2, int offset, bool up, bool down) {
    win_t *term = ui_win_term_info();
    if (up)
        mvwin(win2->id, win1->y + win1->height - offset, (term->width - win2->width) / 2);
    else if (down)
        mvwin(win2->id, win1->y - win2->height + offset, (term->width - win2->width) / 2);

    ui_win_update_pos(win2);
    wrefresh(win1->id);
    wrefresh(win2->id);
}

void ui_win_border(WINDOW *frame) {
    box(frame, 0, 0);
    wrefresh(frame);
}
