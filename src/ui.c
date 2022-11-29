#include "../include/ui.h"
#include "../include/ui_error.h"
#include "../include/ui_win.h"
#include "../include/alloc.h"
#include "../include/game.h"
#include "../include/map.h"
#include "../include/options.h"
#include "../include/path.h"
#include <ncurses.h>
#include <stdio.h>
#include <string.h>

void ui_legend_print(win *frame, char *keys) {
    char u = keys[0];
    char d = keys[1];
    char l = keys[2];
    char r = keys[3];
    char *msg =  "%c:UP %c:DOWN %c:LEFT %c:RIGHT";
    if (26 < frame->width) {
        mvwprintw(frame->id, frame->center.y, frame->center.x - (26 / 2), msg, u, d, l, r);
    } else {
        ui_popup_error(WINDOW_TOO_SMALL);
    }
}

void ui_map_refresh() {}

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
                case DRILL:
                    mvwprintw(frame->id, y + i, x + j, "D");
                    break;
                }
            }
            wprintw(frame->id, "\n");
        }
    } else {
        ui_popup_error(WINDOW_TOO_SMALL);
    }
}

void ui_startmenu_print(win *menu, int highlight) {
    char choices[4][10] = { "GAME", "AI", "OPTIONS", "QUIT" };
    int x, y;
    x = menu->center.x - 3;
    y = menu->center.y - 2;
    for (int i = 0; i < 4; ++i) {
        if (highlight == i + 1) {
            wattron(menu->id, A_REVERSE);
            mvwprintw(menu->id, y, x, "%s", choices[i]);
            wattroff(menu->id, A_REVERSE);
        } else {
            mvwprintw(menu->id, y, x, "%s", choices[i]);
        }
        ++y;
    }
    wrefresh(menu->id);
}

void ui_startmenu_init(game *g, action *quit) {
    int highlight = 1;
    int choice = 0;
    opt *opt = options_init();
    win *startmenu = ui_win_term_info();
    ui_startmenu_print(startmenu, highlight);
    while (1) {
        action c = ui_get_input();
        switch (c) {
        case UP:
            if (highlight == 1)
                highlight = 4;
            else
                --highlight;
            break;
        case DOWN:
            if (highlight == 4)
                highlight = 1;
            else
                ++highlight;
            break;
        case ENTER:
            choice = highlight;
            break;
        case QUIT:
            *quit = QUIT;
            break;
        default:
            refresh();
            break;
        }
        ui_startmenu_print(startmenu, highlight);
        switch (choice) {
            case 1:
                g->mode = INTERACTIVE;
                g->opt.keybings = opt->keybings[0];
                ui_win_clear();
                return;
            case 2:
                g->mode = AI;
                ui_win_clear();
                return;
            case 3:
                ui_win_clear();
                return;
            case 4:
                *quit = QUIT;
                ui_win_clear();
                return;
        }
    }
}

void ui_init() {
    initscr();
    curs_set(0);
    noecho();
    cbreak();
    refresh();
}

void ui_init_layout(game *g) {
    win *map = ui_win_create(21, 60, false);
    win *legend = ui_win_create(3, 60, false);
    ui_win_stack(map, legend);
    box(map->id, 0, 0);
    box(legend->id, 0, 0);
    ui_map_print(map, g->map);
    ui_legend_print(legend, g->opt.keybings);
    wrefresh(legend->id);
    wrefresh(map->id);
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
    case 13:
        return ENTER;
    }
    return NONE;
}
