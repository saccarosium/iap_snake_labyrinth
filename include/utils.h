#ifndef UTILS_H
#define UTILS_H

typedef struct vec2 {
    int x;
    int y;
} vec2;

typedef enum error {
    // MAP
    MAP_OK = 0,
    FILE_OPEN,
    MALLOC_FAILED,
    UNEXPECTED_EOF,
    WRONG_WIDTH,
    WRONG_CHARACTER,
    UNEXPECTED_NEW_LINE,
    // UI
    WINDOW_TOO_SMALL,
    NO_COLORS
} error;

#endif // !UTILS_H
