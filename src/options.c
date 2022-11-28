#include "../include/options.h"

opt *options_init() {
    opt options = {
        .keybings =
            {
                {'w', 's', 'a', 'd'},
                {'k', 'j', 'h', 'l'},
                {'n', 's', 'w', 'e'},
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
