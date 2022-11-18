#ifndef OPTIONS_H
#define OPTIONS_H

typedef struct opt {
    char keybings[4][4];
    char *colorscheme[3];
    char player[4];
} opt;

typedef struct saved_opt {
    char *keybings;
    char *colorscheme;
    char player;
} saved_opt;

opt *options_init();

#endif // !OPTIONS_H
