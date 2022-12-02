#ifndef UI_H
#define UI_H

#include "map.h"
#include "path.h"
#include "utils.h"
#include "game.h"
#include "ui_win.h"

void ui_init();
void ui_startmenu_init(game *g, action *quit);
layout *ui_init_layout(game *g);
action ui_get_input();

#endif // !UI_H
