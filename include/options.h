#ifndef OPTIONS_H
#define OPTIONS_H

typedef struct opt {
    char keybings[4][4];
    char *colorscheme[3];
    char player[4];
} opt;

options *options_init();

#endif // !OPTIONS_H
