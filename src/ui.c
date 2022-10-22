#include <ncurses.h>

typedef struct center {
    int x;
    int y;
} center;

typedef struct win {
    int width;
    int height;
    int x;
    int y;
    center center;
} win;

void ui_create_win(const char *maze) {
    int min_height, min_width;
    win term;
    win frame;

    min_width = 79;
    min_height = 24;

    frame.height = 40;
    frame.width = 50;

    // Gets the current terminal max x and y
    getmaxyx(stdscr, term.y, term.x);
    getmaxyx(stdscr, term.height, term.width);

    if (term.y < min_height || term.x < min_width) {
        frame = term;
        maze = "Too Small!";
    } else {
        frame.y = (term.y - frame.height) / 2;
        frame.x = (term.x - frame.width) / 2;
        frame.center.y = (frame.y + frame.height) / 2;
        frame.center.x = (frame.x + frame.width) / 2;
    }

    WINDOW *win = newwin(frame.height, frame.width, frame.y, frame.x);
    refresh();
    box(win, 0, 0);

    mvwprintw(win, 10, 10, maze);
    wrefresh(win);
}
