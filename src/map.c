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

int get_character_type(char c) {
    switch (c)
    {
    case ' ':
        return 1;
    case '#':
        return 1;
    case 10: //LF Line Feed
        return 2;
    case 13: // CR Carriage Return
        return 2;
    case '$':
        return 1;
    case '!':
        return 1; 
    default:
        return 0;
    }
}

map* map_load_from_file(char* filename){
    int map_width = 0, map_length = 0, width_check = 0, tmp_type;

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
        if (!tmp_type){
            return NULL;
        }
        if(tmp_type != 2) {
            if (!map_length)
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
            map_length++;
            map_width = 0;

        }

        *(read_buffer + currently_used) = c;
        currently_used++;
        if (currently_used == buffer_size){
            buffer_size += sizeof(char) * 32;
            read_buffer= realloc(read_buffer, buffer_size );
            if (read_buffer == NULL) {
                return NULL;
            }
        }
    }
    
    fclose(file);

    if (map_width != width_check && map_width != 0){
        return NULL;
    }

}

void map_get_nearby_nodes(int x, int y, node *return_nodes){

}

void map_set_node_type(node* n, enum nodeType t){
    n->type = t;
}
