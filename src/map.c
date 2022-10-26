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

nodeType get_character_type(char c) {
    switch (c)
    {
        case ' ':
            return EMPTY;
        case '#':
            return WALL;
        case 10: //LF Line Feed
        case 13: // CR Carriage Return
            return -1;
        case '$':
            return COIN;
        case '!':
            return UNEVENT;
    }
    return -2;
}

map* map_load_from_file(char* filename){
    int map_width = 0, map_height = 0, width_check = 0, tmp_type;

    int c;
    FILE *file;
    file = fopen(filename, "r");
    if (file == NULL) {
        return NULL;
    }

    int buffer_size = 32;
    int currently_used = 0;
    char* read_buffer = malloc(sizeof(char) * buffer_size);
    if (read_buffer == NULL){
        return NULL;
    }

    while ((c = getc(file)) != EOF){
        tmp_type = get_character_type(c);
        if (tmp_type == -2){
            return NULL;
        }
        if(tmp_type != -1) {
            if (!map_height)
                width_check = ++map_width;
            else if (map_width + 1 <= width_check)
                map_width++;
            else {
                return NULL;
            }
        } else if (map_width != 0) {
            if (map_width != width_check) {
                return NULL;
            }
            map_height++;
            map_width = 0;

        }

        if (tmp_type >= 0) {
            *(read_buffer + currently_used) = tmp_type;
            currently_used++;
        }

        if (currently_used == buffer_size){
            buffer_size += 32;
            read_buffer = realloc(read_buffer, buffer_size);
            if (read_buffer == NULL) {
                return NULL;
            }
        }

    }

    fclose(file);

    if (map_width != width_check && map_width != 0){
        free(read_buffer);
        return NULL;
    }
    map_width = width_check;
}

void map_get_nearby_nodes(int x, int y, node *return_nodes){

}

void map_set_node_type(node* n, enum nodeType t){
    n->type = t;
}
