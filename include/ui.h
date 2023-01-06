#ifndef UI_H
#define UI_H

#include "game.h"
#include "map.h"
#include "path.h"
#include "ui_win.h"
#include "utils.h"
#include "queue.h"

#define STRING_LENGHT 23
#define TIMEOUT 120 * 1000

void ui_init();
void ui_end();
void ui_startmenu_init(action *quit, game_mode *mode, int *level);
void ui_layout_free(layout_t *l);
layout_t *ui_layout_init(game *g);
void ui_map_print(win_t *win, map *map, queue *player);
void ui_legend_print(win_t *win);
void ui_stats_print(win_t *win, game *g);
void ui_splash_init();

#endif // !UI_H
