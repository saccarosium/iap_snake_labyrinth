#ifndef UI_ERROR_H
#define UI_ERROR_H

#include "path.h"
#include "utils.h"
/**
 * @file
 * @brief contains the function for menage the error.
*/
/**
 * @brief function that control if the player do something wrong or the map have some error
 * @param error_code type of the error.
 * @return the indormation about the error.
*/
char *ui_decode_error(error error_code);
/**
 * @brief the function generate a pop-up with the error.
 * @param error_code type of the error
*/
void ui_popup_error(error error_code);
/**
 * @brief convert a keybind in a node type.
 * @return the node type of a movement.
*/
action ui_get_input();

#endif // !UI_ERROR_H
