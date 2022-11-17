#include "../include/options.h"

options *options_init() {
    options opt = {
        .keybings = {
            { '*', '*', '*', '*' },
            { 'w', 's', 'a', 'd' },
            { 'n', 's', 'w', 'e' },
            { 'k', 'j', 'h', 'l' },
        },
        .colorscheme = {
             "terminal",
             "gruvbox",
             "codedark",
        },
        .player = {
            'o', 'O', '*', 'V'
        },
    };
    options *handle = &opt;
    return handle;
}
