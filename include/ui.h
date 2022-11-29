#ifndef UI_H
#define UI_H

#include "map.h"
#include "path.h"
#include "utils.h"
#include "game.h"

void ui_init();
void ui_popup_error(error error_code);
void ui_decode_error(error error_code, char **msg);
void ui_startmenu_init(game *g, action *quit);
void ui_init_layout(game *g);
action ui_get_input();

#endif // !UI_H
