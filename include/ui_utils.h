#ifndef UI_ERROR_H
#define UI_ERROR_H

#include "path.h"
#include "utils.h"

char *ui_decode_error(error error_code);
void ui_popup_error(error error_code);
action ui_get_input();

#endif // !UI_ERROR_H
