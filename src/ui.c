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
#include <unistd.h>

void ui_init_colors() {
    // If terminal doesn't support colors quit
    if (!has_colors()) {
        printw("Terminal doesn't support colors");
        getch();
        exit(-1);
    }
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
    nodelay(stdscr, TRUE);
    refresh();
    ui_init_colors();
}

void ui_end() {
    curs_set(1);
    endwin();
}

void ui_stats_print(win_t *frame, game *g) {
    wattron(frame->id, A_REVERSE);
    mvwprintw(frame->id, 1, 1, " SCORE:%d ", g->coin);
    wattroff(frame->id, A_REVERSE);
    wrefresh(frame->id);
}

void ui_legend_print(win_t *frame) {
    char *msg = "w/k:UP s/j:DOWN a/h:LEFT d/l:RIGHT";
    mvwprintw(frame->id, frame->center.y, frame->center.x - (strlen(msg) / 2), "%s", msg);
    wrefresh(frame->id);
}

void ui_splash_print(win_t *frame, FILE *f) {
    char c;
    while ((c = getc(f)) != EOF)
        waddch(frame->id, c);
    // The function uses microseconds
    usleep(70 * 1000);
    wrefresh(frame->id);
    wclear(frame->id);
}

void ui_splash_init() {
    FILE *f;
    char filename[20];
    win_t *wow = ui_win_create(11, 71, false);
    for (int i = 1; i <= 66; i++) {
        char c = getch();
        if (c == 'q') break;
        sprintf(filename, "assets/frames/%d", i);
        f = fopen(filename, "r");
        ui_splash_print(wow, f);
        fclose(f);
    }
    ui_win_clear();
}

// Print map onto the given window
void ui_map_print(win_t *frame, map *map, queue *player) {
    int y = frame->center.y - (map->height / 2);
    int x = frame->center.x - (map->width / 2);
    if (map->height >= frame->height) {
        ui_popup_error(WINDOW_TOO_SMALL);
        return;
    }

    node *p = player->head->node;

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
                wattron(frame->id, COLOR_PAIR(3));
                mvwprintw(frame->id, y + i, x + j, "$");
                wattroff(frame->id, COLOR_PAIR(3));
                break;
            case UNEVENT:
                wattron(frame->id, COLOR_PAIR(1));
                mvwprintw(frame->id, y + i, x + j, "!");
                wattroff(frame->id, COLOR_PAIR(1));
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
        }
        wprintw(frame->id, "\n");
    }

    wattron(frame->id, A_BOLD);
    for (queueNode *qn = player->head->next; qn != NULL; qn = qn->next) {
        mvwaddch(frame->id, qn->node->y + y, qn->node->x + x, 'o');
    }
    mvwaddch(frame->id, p->y + y, p->x + x, 'O');
    wattroff(frame->id, A_BOLD);

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

layout_t *ui_layout_init(game *g) {
    layout_t *lay = xmalloc(sizeof(layout_t));
    win_t *game = ui_win_create(21, 60, false);
    win_t *legend = ui_win_create(3, 60, false);
    win_t *stats = ui_win_create(3, 60, false);
    win_t *map = ui_win_create(g->map->height + 1, g->map->width + 1, false);

    ui_win_stack(game, legend, 0, true, false);
    ui_win_stack(game, stats, 1, false, true);

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
