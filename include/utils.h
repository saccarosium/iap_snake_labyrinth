#ifndef UTILS_H
#define UTILS_H

typedef struct vec2 {
    int x;
    int y;
} vec2;

typedef enum error {
    MAP_OK = 0,
    // UI
    WINDOW_TOO_SMALL,
    // MAP
    FILE_OPEN,
    MALLOC_FAILED,
    UNEXPECTED_EOF,
    WRONG_WIDTH,
    WRONG_CHARACTER,
} error;

#endif // !UTILS_H
