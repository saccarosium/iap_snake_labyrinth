#include "../include/ui.h"
#include "../include/alloc.h"
#include "../include/game.h"
#include "../include/map.h"
#include "../include/path.h"
#include "../include/ui_utils.h"
#include "../include/ui_win.h"
#include <curses.h>
#include <ncurses.h>
#include <stdio.h>
#include <string.h>

void ui_init() {
    initscr();
    curs_set(0);
    noecho();
    cbreak();
    refresh();
}

void ui_end() {
    curs_set(1);
    endwin();
}

void ui_legend_print(win_t *frame) {
    char *msg = "w:UP s:DOWN a:LEFT d:RIGHT";
    if (26 < frame->width) {
        mvwprintw(frame->id, frame->center.y, frame->center.x - strlen(msg),
                  "%s", msg);
    } else {
        ui_popup_error(WINDOW_TOO_SMALL);
    }
}

// Print map onto the given window
void ui_map_print(win_t *frame, map *map, vec2 player) {
    int y = frame->center.y - (map->height / 2);
    int x = frame->center.x - (map->width / 2);
    if (map->height >= frame->height) {
        ui_popup_error(WINDOW_TOO_SMALL);
        return;
    }

    for (int i = 0; i < map->height; i++) {
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
                mvwprintw(frame->id, y + i, x + j, " ");
                break;
            case END:
                mvwprintw(frame->id, y + i, x + j, "_");
                break;
            case DRILL:
                mvwprintw(frame->id, y + i, x + j, "T");
                break;
            }
            if (i == player.y && j == player.x) {
                mvwaddch(frame->id, player.y, player.x, 'o');
            }
        }
        wprintw(frame->id, "\n");
    }
    wrefresh(frame->id);
}

void ui_startmenu_print(win_t *menu, int highlight) {
    char choices[3][15] = {"INTERACTIVE", "AI", "QUIT"};
    int x, y;
    x = menu->center.x - 3;
    y = menu->center.y - 2;
    for (int i = 0; i < 3; ++i) {
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
    win_t *startmenu = ui_win_term_info();
    ui_startmenu_print(startmenu, highlight);
    while (1) {
        action c = ui_get_input();
        switch (c) {
        case UP:
            if (highlight == 1)
                highlight = 3;
            else
                --highlight;
            break;
        case DOWN:
            if (highlight == 3)
                highlight = 1;
            else
                ++highlight;
            break;
        case ENTER:
            choice = highlight;
            break;
        case QUIT:
            *quit = QUIT;
            ui_win_clear();
            return;
        default:
            refresh();
            break;
        }
        ui_startmenu_print(startmenu, highlight);
        switch (choice) {
        case 1:
            g->mode = INTERACTIVE;
            ui_win_clear();
            return;
        case 2:
            g->mode = AI;
            ui_win_clear();
            return;
        case 3:
            *quit = QUIT;
            ui_win_clear();
            return;
        }
    }
}

layout_t *ui_init_layout(game *g) {
    layout_t *lay = xmalloc(sizeof(layout_t));
    win_t *game = ui_win_create(21, 60, false);
    win_t *legend = ui_win_create(3, 60, false);
    win_t *map = ui_win_create(g->map->height + 1, g->map->width + 1, false);
    ui_win_stack(game, legend);
    ui_map_print(map, g->map, g->player);
    ui_legend_print(legend);
    box(game->id, 0, 0);
    box(legend->id, 0, 0);
    wrefresh(legend->id);
    wrefresh(game->id);
    wrefresh(map->id);
    lay->game = game;
    lay->legend = legend;
    lay->map = map;

    return lay;
}

action ui_get_input() {
    char ch = getchar();
    switch (ch) {
    case 'a':
        return LEFT;
    case 'h':
        return LEFT;
    case 'd':
        return RIGHT;
    case 'l':
        return RIGHT;
    case 'w':
        return UP;
    case 'k':
        return UP;
    case 's':
        return DOWN;
    case 'j':
        return DOWN;
    case 'q':
        return QUIT;
    case 13:
        return ENTER;
    }
    return NONE;
}

action ui_check_wall(action act, game *g) {
    if (act == UP) {
        if (map_get_node(g->map, g->player.y - 1, g->player.x)->type == WALL)
            act = NONE;
    }
    if (act ==  DOWN) {
        if (map_get_node(g->map, g->player.y + 1, g->player.x)->type == WALL)
            act = NONE;
    }
    if (act == LEFT) {
        if (map_get_node(g->map, g->player.y, g->player.x - 1)->type == WALL)
            act = NONE;
    }
    if (act == RIGHT) {
        if (map_get_node(g->map, g->player.y, g->player.x + 1)->type == WALL)
            act = NONE;
    }
    return act;
}
