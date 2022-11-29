#ifndef UI_ERROR_H
#define UI_ERROR_H

#include "utils.h"

void ui_popup_error(error error_code);
void ui_decode_error(error error_code, char **msg);

#endif // !UI_ERROR_H
