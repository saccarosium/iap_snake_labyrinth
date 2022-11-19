#include "../include/options.h"

opt *options_init() {
    opt options = {
        .keybings =
            {
                {'*', '*', '*', '*'},
                {'w', 's', 'a', 'd'},
                {'n', 's', 'w', 'e'},
                {'k', 'j', 'h', 'l'},
            },
        .colorscheme =
            {
                "terminal",
                "gruvbox",
                "codedark",
            },
        .player = {'o', 'O', '*', 'V'},
    };
    opt *handle = &options;
    return handle;
}
