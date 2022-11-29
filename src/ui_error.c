#include "../include/ui.h"
#include "../include/ui_error.h"
#include "../include/ui_win.h"
#include <ncurses.h>
#include <stdio.h>
#include <string.h>

void ui_popup_error(error error_code) {
    char **msg = NULL;
    ui_decode_error(error_code, msg);
    win *term = ui_win_term_info();
    mvwprintw(term->id, term->center.y, term->center.x - (strlen(*msg) / 2), "%s", *msg);
    wrefresh(term->id);
    exit(-1);
}

void ui_decode_error(error error_code, char **msg) {
    switch (error_code) {
    case FILE_OPEN:
        *msg = "Errore in lettura della mappa";
        break;
    case MALLOC_FAILED:
        *msg = "Mallac failed";
        break;
    case UNEXPECTED_EOF:
        *msg = "Errore dimensione";
        break;
    case WRONG_WIDTH:
        *msg = "Errore dimensione";
        break;
    case WRONG_CHARACTER:
        *msg = "Carrattere non consentito";
        break;
    case WINDOW_TOO_SMALL:
        *msg = "The Window is too Small";
        break;
    default:
        *msg = "Errore non riconosciuto";
        break;
    }
}
