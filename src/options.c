#include "../include/options.h"

opt *options_init() {
    opt opt = {
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
    opt *handle = &opt;
    return handle;
}
