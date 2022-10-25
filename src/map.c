#include "map.h"
#include "alloc.h"

map *map_create(int height, int width) {
    map *m = xmalloc(sizeof(map));
    m->height = height;
    m->width = width;
    m->grid = xmalloc(sizeof(node) * height * width);

    for(int i = 0; i < height * width; i++) {
        m->grid[i].type = WALL;
    }

    return m;
}

node *map_get_node(map* m, int y, int x) {
    return &m->grid[y * m->width + x];
}
