#ifndef UI_ERROR_H
#define UI_ERROR_H

#include "utils.h"

char *ui_decode_error(error error_code);
void ui_popup_error(error error_code);

#endif // !UI_ERROR_H
