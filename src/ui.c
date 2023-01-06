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

#define MENU_ITEMS 11
#define SPLASH_FRAMES 66

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

void ui_stats_print(win_t *frame, game *g) {
    wattron(frame->id, A_REVERSE);
    mvwprintw(frame->id, 1, 1, " LEVEL:%d | SCORE:%d | DRILL:%d ", g->level, g->score, g->drill);
    wattroff(frame->id, A_REVERSE);
    wrefresh(frame->id);
}

void ui_legend_print(win_t *frame) {
    char *msg = "w/k:UP s/j:DOWN a/h:LEFT d/l:RIGHT";
    ui_win_print_centered(frame, msg);
    wrefresh(frame->id);
}

void ui_splash_print(win_t *frame, FILE *f) {
    char c;
    while ((c = getc(f)) != EOF)
        waddch(frame->id, c);
    // The function uses microseconds
    usleep(100 * 1000);
    wrefresh(frame->id);
    wclear(frame->id);
}

void ui_splash_init() {
    nodelay(stdscr, TRUE);
    FILE *f;
    char filename[20];
    win_t *splash = ui_win_create(11, 71, false);
    win_t *label = ui_win_create(5, 71, false);
    char *msg = "<Press 'q' or 'c'>";
    ui_win_print_centered(label, msg);
    ui_win_stack(splash, label, 0, true, false);
    wclear(label->id);
    for (int i = 1; i <= SPLASH_FRAMES; i++) {
        char c = getch();
        if (c == 'q' || c == 32 || c == 'c')
            break;
        sprintf(filename, "assets/frames/%d", i);
        f = fopen(filename, "r");
        ui_splash_print(splash, f);
        fclose(f);
    }
    ui_screen_clear();
    nodelay(stdscr, FALSE);
    free(splash);
    free(label);
}

void ui_end_screen_init(win_t *frame) {
    char c;
    FILE *f = fopen("assets/end_screen.txt", "r");
    while ((c = getc(f)) != EOF)
        waddch(frame->id, c);
    wrefresh(frame->id);
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
        mvwaddch(frame->id, qn->node->y + y, qn->node->x + x, '.');
    }
    mvwaddch(frame->id, p->y + y, p->x + x, 'o');
    wattroff(frame->id, A_BOLD);

    wrefresh(frame->id);
}

void ui_startmenu_print(win_t *menu, int highlight) {
    char choices[MENU_ITEMS][20] = {
        "=== INTERACTIVE ===",
        "LEVEL 1",
        "LEVEL 2",
        "LEVEL 3",
        "LEVEL 4",
        "LEVEL 5",
        "======= A_I =======",
        "RECURSIVE",
        "ALWAYS RIGHT",
        "RANDOM",
        "QUIT"
    };
    int y = menu->center.y - (MENU_ITEMS / 2);
    for (int i = 0; i < MENU_ITEMS; ++i) {
        if (highlight == i + 1) {
            wattron(menu->id, A_REVERSE);
            ui_win_print_centered_x(menu, y, choices[i]);
            wattroff(menu->id, A_REVERSE);
        } else {
            ui_win_print_centered_x(menu, y, choices[i]);
            // mvwprintw(menu->id, y, x - (strlen(choices[i]) / 2), "%s", choices[i]);
        }
        ++y;
    }
    wrefresh(menu->id);
}

void ui_startmenu_init(game *g, action *quit) {
    int highlight = 2;
    int choice = 0;
    win_t *startmenu = ui_win_term_info();
    ui_startmenu_print(startmenu, highlight);
    while (1) {
        action c = ui_get_input();
        switch (c) {
        case UP:
            if (highlight == 2)
                highlight = 11;
            else if (highlight == 8)
                highlight -= 2;
            else
                --highlight;
            break;
        case DOWN:
            if (highlight == 11)
                highlight = 2;
            else if (highlight == 6)
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
        if (choice == 2 || choice == 3 || choice == 4 || choice == 5 || choice == 6) {
            g->mode = INTERACTIVE;
            g->level = choice - 1;
            ui_screen_clear();
            return;
        } else if (choice == 8) {
            g->mode = AI;
            g->level = 5;
            ui_screen_clear();
            return;
        } else if (choice == 9) {
            g->mode = AI_RIGHT;
            g->level = 5;
            ui_screen_clear();
            return;
        } else if (choice == 10) {
            g->mode = AI_RANDOM;
            g->level = 5;
            ui_screen_clear();
            return;
        } else if (choice == MENU_ITEMS) {
            *quit = QUIT;
            ui_screen_clear();
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

void ui_layout_free(layout_t *l) {
    free(l->game);
    free(l->legend);
    free(l->map);
    free(l->stats);
    free(l);
}
