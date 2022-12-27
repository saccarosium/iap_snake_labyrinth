#include "../include/ui.h"
#include "../include/ui_utils.h"
#include "../include/ui_win.h"
#include <ncurses.h>
#include <stdio.h>
#include <string.h>

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

void ui_popup_error(error error_code) {
    ui_win_clear();
    char *msg = ui_decode_error(error_code);
    win_t *term = ui_win_term_info();
    mvwprintw(term->id, term->center.y, term->center.x - (strlen(msg) / 2), "%s", msg);
    wrefresh(term->id);
    getch();
    exit(-1);
}
