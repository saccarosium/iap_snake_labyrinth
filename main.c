// 893189 894579 894360 896954
#include <stdio.h>
#include "./include/path.h"
#include "./include/astar.h"
#include "./include/utils.h"

void check_err(error error_code) {
    char *msg;
    switch(error_code) {
    case MALLOC_FAILED:
        msg = "Mallac failed";
        break;
    case UNEXPECTED_EOF:
        msg = "Errore dimensione";
        break;
    case WRONG_WIDTH:
        msg = "Errore dimensione";
        break;
    case WRONG_CHARACTER:
        msg = "Carrattere non consentito";
        break;
    default:
        msg = "Errore non riconosciuto";
        break;
    }
    printf("%s\n", msg);
    exit(-1);
}

int main() {
    error err = MAP_OK;
    map *m = map_load_from_stdin(&err);
    if (err != MAP_OK) {
        check_err(err);
    }

    path *p = astar_solve(m);
    printf("%s\n", path_string(p));

    return 0;
}
