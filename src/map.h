#ifndef MAP_H
#define MAP_H

#include <stdlib.h>
#include <stdio.h>

enum nodeType{
    EMPTY,
    WALL,
    COIN,
};

typedef struct node {
    enum nodeType type;
} node;

typedef struct map {
    int height;
    int width;
    node *grid;
} map;

map *map_create(int height, int width);
node *map_get_node(map* m, int y, int x);
map* map_load_from_file(char* filename);
void map_get_nearby_nodes(int x, int y, node *return_nodes);
void map_set_node_type(node* n, enum nodeType t);

#endif // !MAP_H
