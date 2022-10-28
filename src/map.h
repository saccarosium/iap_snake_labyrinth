#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include <stdlib.h>

typedef enum nodeType {
    EMPTY,
    WALL,
    COIN,
    UNEVENT,
} nodeType;

typedef enum direction {
    UP,
    DOWN,
    LEFT,
    RIGHT,
} direction;

typedef struct node {
    enum nodeType type;
} node;

typedef struct map {
    int height;
    int width;
    node *grid;
} map;

map *map_create(int height, int width);
node *map_get_node(map *m, int y, int x);
nodeType get_character_type(char c);
map *map_load_from_file(char *filename);
void map_get_nearby_nodes(int x, int y, node *return_nodes);
void map_set_node_type(node *n, enum nodeType t);

#endif // !MAP_H
