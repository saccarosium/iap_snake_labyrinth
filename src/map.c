#include "../include/map.h"
#include "../include/alloc.h"

map *map_create(int height, int width) {
    map *m = xmalloc(sizeof(map));
    m->height = height;
    m->width = width;
    m->grid = xmalloc(sizeof(node) * height * width);

    for (int i = 0; i < height * width; i++) {
        m->grid[i].type = WALL;
    }

    return m;
}

node *map_get_node(map *m, int y, int x) {
    return &m->grid[y * m->width + x];
}

void map_set_node_type(node *n, enum nodeType t) {
    n->type = t;
}

nodeType get_character_type(char c) {
    switch (c) {
    case ' ':
        return EMPTY;
    case '#':
        return WALL;
    case '$':
        return COIN;
    case '!':
        return UNEVENT;
    default:
        return EMPTY;
    }
}

map *map_load_from_file(char *filename) {
    FILE *f = fopen(filename, "r");
    if (f == NULL) return NULL;

    int width = 0;
    int height = 0;
    char c;

    while(true) {
        c = getc(f);
        if(c == EOF) return NULL;
        if(c == '\r' || c == '\n') break;
        width++;
    }

    fseek(f, 0, SEEK_END);

    int size = ftell(f);
    char *buffer = malloc(size);
    if(buffer == NULL) return NULL;

    fseek(f, 0, SEEK_SET);

    int index = 0;
    int width_check = 0;

    while((c = getc(f)) != EOF) {
        if(c == EOF) {
            free(buffer);
            return NULL;
        }

        if(c == '\r' || c == '\n') {
            if(width_check == width) {
                height++;
                width_check = 0;
            } else {
                free(buffer);
                return NULL;
            }
        } else {
            buffer[index] = c;
            index++;
            width_check++;
        }
    }

    map *m = map_create(height, width);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            m->grid[i * width + j].type = get_character_type(buffer[i * width + j]);

            if(buffer[i * width + j] == 'o') {
                m->start.x = j;
                m->start.y = i;
            }

            if(buffer[i * width + j] == '_') {
                m->end.x = j;
                m->end.y = i;
            }
        }
    }

    return m;
}

void map_get_nearby_nodes(int x, int y, node *return_nodes) {
}
