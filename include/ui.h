#ifndef UI_H
#define UI_H

#include "game.h"
#include "map.h"
#include "path.h"
#include "ui_win.h"
#include "utils.h"
#include "queue.h"

void ui_init();
void ui_end();
void ui_startmenu_init(game *g, action *quit);
layout_t *ui_init_layout(game *g);
action ui_get_input();
void ui_map_print(win_t *frame, map *map, queue *player);
void ui_legend_print(win_t *frame);
void ui_stats_print(win_t *frame, game *g);
void ui_splash_init();

#endif // !UI_H
