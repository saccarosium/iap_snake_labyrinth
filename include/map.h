#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include <stdlib.h>
#include "path.h"
#include "utils.h"

typedef enum nodeType {
    EMPTY,
    WALL,
    COIN,
    UNEVENT,
    USER,
    END,
} nodeType;

typedef struct node {
    enum nodeType type;
} node;

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
map *map_load_from_file(char *filename, error *error);
void map_get_nearby_nodes(int x, int y, node *return_nodes);
void map_set_node_type(node *n, enum nodeType t);

#endif // !MAP_H
