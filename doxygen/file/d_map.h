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
    EMPTY,   /**< Empty tile*/
    WALL,    /**< Wall tile*/
    COIN,    /**< Coin tile, gets emptied once the player goes on it*/
    UNEVENT, /**< Unforeseen event tile*/
    DRILL,   /**< Drill tile*/
    USER,    /**< The player*/
    END,     /**< Finish tile*/
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

/**
 * @brief Create a map filled with walls
 * 
 * @param height height of the map
 * @param width width of the map
 * @return map* pointer to the newly created map structure
 */
map *map_create(int height, int width);

/**
 * @brief Get a node from the map
 * Given a map and a set of coordinates, the fuctions returs the pointer to the wanted node
 * @param m pointer to the map struct 
 * @param y y point coordinate
 * @param x x point coordinate
 * @return node* pointer to the wanted node
 */
node *map_get_node(map *m, int y, int x);

/**
 * @brief Convert char to respective enum type
 * Given a character, the functions returns the corresponding nodeType unum's value. For 
 * example, given "#"" it will return "WALL"
 * @param c A given character
 * @return nodeType Corresponding node type
 */
nodeType get_character_type(char c);

/**
 * @brief Frees memory used by the map
 * Frees memory used by the map by freing all the nodes, and than the map itself
 * @param m pointer to the map to free
 */
void map_free(map *m);

/**
 * @brief Load map from a give file path
 * The function loads a map from file given via the given path cheking for possible allocation/formatting 
 * errors, writing them into the memory area pointed by error_code
 * @param filename pointer to the path of the file to load the map from
 * @param error_code pointer to the exit status of the function (error type defined by the enum error)
 * @return map* pointer to the newly generated map (NULL if an error occured)
 * 
 * @see error
 */
map *map_load_from_file(char *filename, error *error_code);

/**
 * @brief Load map from a stdin
 * The function loads a map from stdin cheking for possible allocation/formatting errors writing
 *  them into the memory area pointed by error_code
 * @param error pointer to the exit status of the function (error type defined by the enum error)
 * @return map* pointer to the newly generated map (NULL if an error occured)
 */
map *map_load_from_stdin(error *error);

/**
 * @brief Get the visitable nodes adjacent to a given one 
 * Given a set of coordinates and a pointer to the map, the function will return Null in case of errors,
 * or a pointer to an array of up to 4 pointers to the visitable nodes.
 * @param m pointer to the map
 * @param y y node coordinate
 * @param x x node coordinate
 * @param n_nodes pointer to the number of nodes found
 * @return node** pointer to the array of nodes that have been deemed visitable
 */
node **map_get_nearby_nodes(map *m, int y, int x, int *n_nodes);

/**
 * @brief Sets the typr of a node
 * Given the pointer to a node, the function sets its type
 * @param n pointer to the node
 * @param t type of the node
 */
void map_set_node_type(node *n, enum nodeType t);

/**
 * @brief returns true if the coordinates are the same
 * This function returns true if the x and y coordinates are the same, without any regard to the pointers 
 * of the two given nodes
 * @param a pointer to the first node to compare
 * @param b pointer to the second node to compare
 * @return true if x and y of both nodes re the same
 * @return false otherwise
 */
bool map_compare_node(node *a, node *b);

#endif // !MAP_H
