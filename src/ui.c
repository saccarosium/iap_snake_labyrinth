#include "../include/ui.h"
#include "../include/alloc.h"
#include "../include/game.h"
#include "../include/map.h"
#include "../include/options.h"
#include "../include/path.h"
#include <ncurses.h>
#include <stdio.h>
#include <string.h>

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

void ui_decode_error(error error_code, char **msg) {
    switch (error_code) {
    case FILE_OPEN:
        *msg = "Errore in lettura della mappa";
        break;
    case MALLOC_FAILED:
        *msg = "Mallac failed";
        break;
    case UNEXPECTED_EOF:
        *msg = "Errore dimensione";
        break;
    case WRONG_WIDTH:
        *msg = "Errore dimensione";
        break;
    case WRONG_CHARACTER:
        *msg = "Carrattere non consentito";
        break;
    case WINDOW_TOO_SMALL:
        *msg = "The Window is too Small";
        break;
    default:
        *msg = "Errore non riconosciuto";
        break;
    }
}

void ui_popup_error(error error_code) {
    char **msg = NULL;
    ui_decode_error(error_code, msg);
    win *term = ui_win_term_info();
    mvwprintw(term->id, term->center.y, term->center.x - (strlen(*msg) / 2), "%s", *msg);
    wrefresh(term->id);
    exit(-1);
}

void ui_legend_print(win *frame, opt *opt) {
    char u = opt->keybings[1][0];
    char d = opt->keybings[1][1];
    char l = opt->keybings[1][2];
    char r = opt->keybings[1][3];
    char *msg =  "%c:UP %c:DOWN %c:LEFT %c:RIGHT";
    if (26 < frame->width) {
        mvwprintw(frame->id, frame->center.y, frame->center.x - (26 / 2), msg, u, d, l, r);
    } else {
        ui_popup_error(WINDOW_TOO_SMALL);
    }
}

// Print map onto the given window
void ui_map_print(win *frame, map *map) {
    int y = frame->center.y - (map->height / 2);
    int x = frame->center.x - (map->width / 2);
    if (map->height > frame->height) {
        for (int i = 0; i <= map->height; i++) {
            for (int j = 0; j < map->width; j++) {
                switch (map_get_node(map, i, j)->type) {
                case EMPTY:
                    mvwprintw(frame->id, y + i, x + j, " ");
                    break;
                case WALL:
                    mvwprintw(frame->id, y + i, x + j, "#");
                    break;
                case COIN:
                    mvwprintw(frame->id, y + i, x + j, "$");
                    break;
                case UNEVENT:
                    mvwprintw(frame->id, y + i, x + j, "!");
                    break;
                case USER:
                    mvwprintw(frame->id, y + i, x + j, "o");
                    break;
                case END:
                    mvwprintw(frame->id, y + i, x + j, "_");
                    break;
                }
            }
            wprintw(frame->id, "\n");
        }
        wrefresh(frame->id);
    } else {
        ui_popup_error(WINDOW_TOO_SMALL);
    }
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
}

void ui_menu_print(win *menu, int highlight) {
    char *choices[] = {"Game", "AI", "Options", "Quit"};
    int x, y;
    x = menu->center.x - 3;
    y = menu->center.y - 2;
    box(menu->id, 0, 0);
    for (int i = 0; i < 4; ++i) {
        if (highlight == i + 1) /* High light the present choice */
        {
            wattron(menu->id, A_REVERSE);
            mvwprintw(menu->id, y, x, "%s", choices[i]);
            wattroff(menu->id, A_REVERSE);
        } else
            mvwprintw(menu->id, y, x, "%s", choices[i]);
        ++y;
    }
    wrefresh(menu->id);
}

void ui_init(opt *opt) {
    initscr();
    noecho();
    cbreak();
    refresh();
    win *legend = ui_win_create(11, 61, TRUE);
    ui_legend_print(legend, opt);
    wrefresh(legend->id);
    getch();
}

action ui_get_input() {
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
        return QUIT;
    }
    return NONE;
}
