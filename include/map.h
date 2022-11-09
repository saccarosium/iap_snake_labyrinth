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
    int x;
    int y;
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
map *map_load_from_file(char *filename, error *error_code);
node **map_get_nearby_nodes(map *m, int y, int x, int *n_nodes);
void map_set_node_type(node *n, enum nodeType t);

#endif // !MAP_H
