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
    case 10: // LF Line Feed
    case 13: // CR Carriage Return
        return -1;
    case '$':
        return COIN;
    case '!':
        return UNEVENT;
    default:
        return -2;
    }
}

map *map_load_from_file(char *filename, int *error_code) {
    *error_code = 0;
    int map_width = 0, map_height = 0, width_check = 0, tmp_type, c;

    
    char *read_buffer;
    int buffer_size = 32;
    int currently_used = 0;
    
    FILE *file;
    file = fopen(filename, "r");
    if (file == NULL) {
        *error_code = -1;
    } else {
        read_buffer = malloc(sizeof(char) * buffer_size);
        if (read_buffer == NULL) {
            *error_code = -2;
        } else {
            while ((c = getc(file)) != EOF) {
                tmp_type = get_character_type(c);
                if (tmp_type == -2) {
                    *error_code = -3;
                    break;
                }

                if (tmp_type != -1) {
                    if (!map_height)
                        width_check = ++map_width;
                    else if (map_width + 1 <= width_check)
                        map_width++;
                    else {
                        *error_code = -4;
                        break;
                    }
                } else if (map_width != 0) {
                    if (map_width != width_check) {
                        *error_code = -4;
                        break;
                    }
                    map_height++;
                    map_width = 0;
                }

                if (tmp_type >= 0) {
                    read_buffer[currently_used] = tmp_type;
                    currently_used += sizeof(char);
                }

                if (currently_used == buffer_size) {
                    buffer_size += sizeof(char) * 32;
                    read_buffer = realloc(read_buffer, buffer_size);
                    if (read_buffer == NULL) {
                        *error_code = -5;
                        break;
                    }
                }
            }

            fclose(file);

            if (*error_code == 0) {
                if (map_width != width_check && map_width != 0) {
                    *error_code = -6;
                } else {
                    map_width = width_check;
                    map_height++;

                    map *m = map_create(map_height, width_check);

                    for (int i = 0; i < map_height; i++) {
                        for (int j = 0; j < map_width; j++) {
                            m->grid[i * map_width + j].type =
                                read_buffer[i * map_width + j];
                        }
                    }
                    return m;
                }
            }
        }
    }
    switch (*error_code) {
    case -1:
        break;
    case -2:
    case -5:
        fclose(file);
        break;
    case -3:
    case -4:
    case -6:
        fclose(file);
        free(read_buffer);
        break;
    default:
        break;
    }
}

void map_get_nearby_nodes(int x, int y, node *return_nodes) {
}
