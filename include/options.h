#ifndef OPTIONS_H
#define OPTIONS_H

typedef struct options {
    char keybings[4][4];
    char *colorscheme[3];
    char player[4];
} options;

options *options_init();

#endif // !OPTIONS_H
