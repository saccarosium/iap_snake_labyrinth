#include "../include/ui.h"
#include "../include/alloc.h"
#include "../include/game.h"
#include "../include/map.h"
#include "../include/path.h"
#include "../include/ui_utils.h"
#include "../include/ui_win.h"
#include <ncurses.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

const int MENU_ITEMS = 15;
const int SPLASH_FRAMES = 66;
const int LAYOUT_WIDTH = 60;

/**********
 * INIT UI
***********/

void ui_init_colors() {
    // If terminal doesn't support colors quit
    if (!has_colors())
        ui_popup_error(NO_COLORS);
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
}

void ui_init() {
    initscr();
    curs_set(0);
    noecho();
    cbreak();
    refresh();
    ui_init_colors();
}

void ui_end() {
    curs_set(1);
    endwin();
}

/**************
 * STARTSCREEN
***************/

void ui_splash_print(win_t *frame, FILE *f) {
    char c;
    while ((c = getc(f)) != EOF)
        waddch(frame->id, c);
    // The function uses microseconds
    wrefresh(frame->id);
}

void ui_splash_init() {
    nodelay(stdscr, TRUE);
    char filename[STRING_LENGHT];
    win_t *splash = ui_win_create(11, 71, true);
    win_t *label = ui_win_create(5, 71, true);
    char *msg = "<Press 'q' or 'c'>";
    ui_win_print_centered(label, msg);
    ui_win_stack(splash, label, 0, 0, false, true);
    wclear(label->id);
    for (int i = 1; i <= SPLASH_FRAMES; i++) {
        char c = getch();
        if (c == 'q' || c == 32 || c == 'c')
            break;
        sprintf(filename, "assets/frames/%d", i);
        FILE *f = fopen(filename, "r");
        ui_splash_print(splash, f);
        usleep(TIMEOUT);
        wclear(splash->id);
        fclose(f);
    }
    ui_screen_clear();
    nodelay(stdscr, FALSE);
    free(splash);
    free(label);
}

/************
 * STARTMENU
*************/

void ui_startmenu_print(win_t *menu, int highlight) {
    char choices[15][25] = {
        "     INTERACTIVE     ",
        "=====================",
        "       LEVEL 1       ",
        "       LEVEL 2       ",
        "       LEVEL 3       ",
        "       LEVEL 4       ",
        "       LEVEL 5       ",
        "=====================",
        "         A_I         ",
        "=====================",
        "     BACKTRACKING    ",
        "     ALWAYS RIGHT    ",
        "       RANDOM        ",
        "=====================",
        "        QUIT         ",
    };
    int y = 1;
    for (int i = 0; i < MENU_ITEMS; ++i) {
        if (highlight == i + 1) {
            wattron(menu->id, A_REVERSE);
            ui_win_print_centered_x(menu, y, choices[i]);
            wattroff(menu->id, A_REVERSE);
        } else {
            ui_win_print_centered_x(menu, y, choices[i]);
        }
        ++y;
    }
    wrefresh(menu->id);
}

void ui_startmenu_init(action *quit, game_mode *mode, int *level) {
    int highlight = 3;
    int choice = 0;
    win_t *startmenu = ui_win_create(MENU_ITEMS + 2, 23, true);
    ui_startmenu_print(startmenu, highlight);
    win_t *legend = ui_win_create(3, 23, true);
    ui_win_stack(startmenu, legend, 0, 0, false, true);
    ui_win_print_centered(legend, "w/k:UP s/j:DOWN");
    ui_win_border(startmenu->id);
    ui_win_border(legend->id);
    while (1) {
        action c = ui_get_input();
        switch (c) {
        case UP:
            if (highlight == 3)
                highlight = MENU_ITEMS;
            else if (highlight == 11)
                highlight -= 4;
            else if (highlight == MENU_ITEMS)
                highlight -= 2;
            else
                --highlight;
            break;
        case DOWN:
            if (highlight == MENU_ITEMS)
                highlight = 3;
            else if (highlight == 7)
                highlight += 4;
            else if (highlight == 13)
                highlight += 2;
            else
                ++highlight;
            break;
        case ENTER:
            choice = highlight;
            break;
        case QUIT:
            *quit = QUIT;
            ui_screen_clear();
            return;
        default:
            refresh();
            break;
        }
        ui_startmenu_print(startmenu, highlight);
        if (choice == 3 || choice == 4 || choice == 5 || choice == 6 || choice == 7) {
            *mode = INTERACTIVE;
            *level = choice - 2;
        } else if (choice == 11) {
            *mode = AI;
        } else if (choice == 12) {
            *mode = AI_RIGHT;
        } else if (choice == 13) {
            *mode = AI_RANDOM;
        } else if (choice == MENU_ITEMS) {
            *quit = QUIT;
        }
        if (choice) {
            ui_screen_clear();
            return;
        }
    }
}

/**************
 * MAIN LAYOUT
***************/

// Print map onto the given window
void ui_map_print(win_t *win, map *map, queue *player) {
    int y = win->center.y - (map->height / 2);
    int x = win->center.x - (map->width / 2);
    if (map->height >= win->height) {
        ui_popup_error(WINDOW_TOO_SMALL);
        return;
    }
    node *p = player->head->node;
    for (int i = 0; i < map->height; i++) {
        for (int j = 0; j < map->width; j++) {
            switch (map_get_node(map, i, j)->type) {
            case EMPTY:
                mvwprintw(win->id, y + i, x + j, " ");
                break;
            case WALL:
                mvwprintw(win->id, y + i, x + j, "#");
                break;
            case COIN:
                wattron(win->id, COLOR_PAIR(3));
                mvwprintw(win->id, y + i, x + j, "$");
                wattroff(win->id, COLOR_PAIR(3));
                break;
            case UNEVENT:
                wattron(win->id, COLOR_PAIR(1));
                mvwprintw(win->id, y + i, x + j, "!");
                wattroff(win->id, COLOR_PAIR(1));
                break;
            case USER:
                mvwprintw(win->id, y + i, x + j, " ");
                break;
            case END:
                mvwprintw(win->id, y + i, x + j, "_");
                break;
            case DRILL:
                mvwprintw(win->id, y + i, x + j, "T");
                break;
            }
        }
        wprintw(win->id, "\n");
    }

    // Print player with tail
    wattron(win->id, A_BOLD);
    for (queueNode *qn = player->head->next; qn != NULL; qn = qn->next) {
        mvwaddch(win->id, qn->node->y + y, qn->node->x + x, '.');
    }
    mvwaddch(win->id, p->y + y, p->x + x, 'o');
    wattroff(win->id, A_BOLD);

    wrefresh(win->id);
}

void ui_legend_print(win_t *win) {
    char *msg = "w/k:UP s/j:DOWN a/h:LEFT d/l:RIGHT";
    ui_win_print_centered(win, msg);
    wrefresh(win->id);
}
void ui_stats_print(win_t *frame, game *g) {
    wattron(frame->id, A_REVERSE);
    mvwprintw(frame->id, 1, 1, " LEVEL:%d | SCORE:%d | DRILL:%d ", g->level, g->score, g->drill);
    wattroff(frame->id, A_REVERSE);
    wrefresh(frame->id);
}

layout_t *ui_layout_init(game *g) {
    layout_t *lay = xmalloc(sizeof(layout_t));
    win_t *game = ui_win_create(21, LAYOUT_WIDTH, true);
    win_t *legend = ui_win_create(3, LAYOUT_WIDTH, true);
    win_t *stats = ui_win_create(3, LAYOUT_WIDTH, true);
    win_t *map = ui_win_create(g->map->height + 1, g->map->width + 1, true);

    ui_win_stack(game, legend, 0, 0, false, true);
    ui_win_stack(game, stats, 1, 0, true, false);

    ui_map_print(map, g->map, g->player);
    ui_legend_print(legend);
    ui_stats_print(stats, g);

    ui_win_border(game->id);
    ui_win_border(legend->id);
    lay->game = game;
    lay->legend = legend;
    lay->map = map;
    lay->stats = stats;

    return lay;
}

void ui_layout_free(layout_t *l) {
    free(l->game);
    free(l->legend);
    free(l->map);
    free(l->stats);
    free(l);
}
