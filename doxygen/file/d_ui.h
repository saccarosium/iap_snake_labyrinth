#ifndef UI_H
#define UI_H

#include "game.h"
#include "map.h"
#include "path.h"
#include "ui_win.h"
#include "utils.h"
#include "queue.h"

#define STRING_LENGHT 23
#define TIMEOUT 120 * 1000
/**
 * @file
 * @brief file contains function for the menu.
*/
/**
 * @brief the function fo the start of the game
*/
void ui_init();
/**
 * @brief the function for the end of the game
*/
void ui_end();
/**
 * @brief rappresent the menù.
 * @param menu pointer of the menù
 * @param highlight value of the option of the menù
*/
void ui_startmenu_init(game *g, action *quit);
/**
 * @brief dealloc memory for the menù
 * @param l pointer of the layout
*/
void ui_layout_free(layout_t *l);
/**
 * @brief menage the game history information
 * @param g pointer of the game
 * @return the pointer of the history of the game.
*/
layout_t *ui_layout_init(game *g);
/**
 * @brief Print map onto the given window 
 * @param win pointer of the windows
 * @param map pointer of the map
 * @param player pointer of the player
*/
void ui_map_print(win_t *win, map *map, queue *player);
/**
 * @brief print leggend of the game moveset
 * @param win pointer of the window
*/
void ui_legend_print(win_t *win);
/**
 * @brief menage the infomation of the level
 * @param frame pointer of the level information
 * @param g pointer od the game.
*/
void ui_stats_print(win_t *win, game *g);
/**
 * @brief function to start the menù
*/
void ui_splash_init();

#endif // !UI_H
