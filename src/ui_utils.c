#include "../include/ui.h"
#include "../include/ui_win.h"
#include "../include/ui_utils.h"
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @file
 * @brief contains the function for manage the error.
*/
/**
 * @brief function that control if the player do something wrong or the map have some error
 * @param error_code type of the error
 * @return the string rapresentation of the error
*/
char* ui_decode_error(error error_code) {
    char *msg;
    switch (error_code) {
    case FILE_OPEN:
        msg = "Errore in lettura della mappa";
        return msg;
    case MALLOC_FAILED:
        msg = "Mallac failed";
        return msg;
    case UNEXPECTED_EOF:
        msg = "Errore dimensione";
        return msg;
    case WRONG_WIDTH:
        msg = "Errore dimensione";
        return msg;
    case WRONG_CHARACTER:
        msg = "Carrattere non consentito";
        return msg;
    case WINDOW_TOO_SMALL:
        msg = "Finestra troppo piccola";
        return msg;
    case NO_COLORS:
        msg = "Terminal non supporta i colori";
        return msg;
    default:
        msg = "Errore non riconosciuto";
        return msg;
    }
}

/**
 * @brief the function generate a pop-up with the error.
 * @param error_code type of the error
*/
void ui_popup_error(error error_code) {
    ui_screen_clear();
    char *msg = ui_decode_error(error_code);
    win_t *term = ui_win_term_info();
    ui_win_print_centered(term, msg);
    wrefresh(term->id);
    free(term);
    getch();
    exit(EXIT_FAILURE);
}

/**
 * @brief convert a keybind in an action
 * @return the type of the action
*/
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
