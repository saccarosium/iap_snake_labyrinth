#ifndef MAP_H
#define MAP_H

enum type {
    EMPTY,
    WALL,
    COIN,
};

typedef struct node {
    enum type type;
} node;

typedef struct map {
    int height;
    int width;
    node *grid;
} map;

map *map_create(int height, int width);
node *map_get_node(map* m, int y, int x);

#endif // !MAP_H
