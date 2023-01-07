#ifndef UTILS_H
#define UTILS_H
/**
 * @file
 * @brief contains struct for error and coordinates.
*/
/**
 * @brief struct defining the position
 * @param x x coordinates
 * @param y y coordinates
*/
typedef struct vec2 {
    int x;
    int y;
} vec2;
/**
 * @brief define the type of error
 * @param MAP_OK if this is 0 there isn't error
 * @param FILE_OPEN the file open correctly
 * @param MALLOC_FAILED the malloc doesn't alloc memory
 * @param UNEXPECTED_EOF unexpected eof
 * @param WRONG_WIDTH the width is wrong
 * @param WRONG_CHARACTER an illegal character was used
 * @param UNEXPECTED_NEW_LINE unexpected new line
 * @param WINDOW_TOO_SMALL window is too small
 * @param NO_COLORS no colors.
*/
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
