#ifndef MAP_H
#define MAP_H

#include "path.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @file
 * @brief File containing all most of the functions used with the map.
 *
 * Here are contained all the functions to load a map from a file ora from the standard input, functions to retrive data from all the nodes or compare them, and a function to free the memory once it isn't usefull anymore.
 */

/**
 * enum specifying every possible type of node
 */
typedef enum nodeType {
    EMPTY,
    WALL,
    COIN,
    UNEVENT,
    DRILL,
    USER,
    END,
} nodeType;

/**
 * @brief Struct defining the position, cost and type of node
 *
 * This strcut is used to define every node of the map
 * @param x position of the node into the x axis
 * @param y position of the node into the y axis
 * @param type the "content" of the node defined by nodeType
 * @param cost needed cost to move through the node
 * @param parent parent of the node
 *
 * @see map
 * @see nodeType
 */
typedef struct node {
    int x;
    int y;
    enum nodeType type;

    // A* data
    int cost;
    struct node *parent;
} node;

/**
 * @brief Struct defining the map dimentions, its contents andthe strating and finishing position
 *
 * This struct is used to define the structure of the map and its contents via a
 * flattened matrix containing all of the nodes
 * @param height Height of the matrix/gamefield
 * @param width Width of the matrix/gamefield
 * @param grid flattened matrix containing all of the nodes
 * @param start starting point of the map
 * @param end finishing point of the map
 */
typedef struct map {
    int height;
    int width;
    node *grid;
    vec2 start;
    vec2 end;
} map;

map *map_create(int height, int width);
node *map_get_node(map *m, int y, int x);
nodeType get_character_type(char c);
void map_free(map *m);
map *map_load_from_file(char *filename, error *error_code);
map *map_load_from_stdin(error *error);
node **map_get_nearby_nodes(map *m, int y, int x, int *n_nodes);
void map_set_node_type(node *n, enum nodeType t);
bool map_compare_node(node *a, node *b);

#endif // !MAP_H
