#include "../include/options.h"
#include "../include/alloc.h"

void options_set_defaults(options *opt) {
    char arrows[] = { '-', '-', '-', '-' };
    char wasd[] = { 'w', 's', 'a', 'd' };
    char nswe[] = { 'n', 's', 'w', 'e' };
    char vim[] = { 'k', 'j', 'h', 'l' };

    opt->keybings = xmalloc(sizeof(char**) * 4);

    opt->keybings[0] = arrows;
    opt->keybings[1] = wasd;
    opt->keybings[2] = nswe;
    opt->keybings[3] = vim;
    opt->selected_keybings = 0;

    char player[] = { 'o', 'O', '*', 'V' };
    opt->player = xmalloc(sizeof(char*) * 4);
    opt->player = player;
    opt->selected_player = 0;

    char *colorscheme[] = { "terminal", "gruvbox", "vscode" };
    opt->colorscheme = xmalloc(sizeof(char**) * 3);
    opt->colorscheme = colorscheme;
    opt->selected_coloscheme = 0;
}

void options_init() {
    options opt;
}
