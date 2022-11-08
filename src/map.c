#include "../include/map.h"
#include "../include/alloc.h"
#include "../include/utils.h"

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
    case 'o':
    case '_':
        return EMPTY;
    case '#':
        return WALL;
    case '$':
        return COIN;
    case '!':
        return UNEVENT;
    default:
        return -1;
    }
}

void map_free(map *m) {
    free(m->grid);
    free(m);
}

map *map_load_from_file(char *filename, error* error) {
    FILE *f = fopen(filename, "r");
    if (f == NULL) return NULL;

    int width = 0;
    int height = 0;
    char c;

    while(true) {
        c = getc(f);

        if(c == EOF) {
            *error = FILE_OPEN;
            return NULL;
        }

        if(c == '\r' || c == '\n') break;
        width++;
    }

    fseek(f, 0, SEEK_END);

    int size = ftell(f);
    char *buffer = malloc(size);
    if(buffer == NULL) {
        *error = MALLOC_FAILED;
        return NULL;
    }

    fseek(f, 0, SEEK_SET);

    int index = 0;
    int width_check = 0;

    while((c = getc(f)) != EOF) {
        if(c == EOF) {
            *error = UNEXPECTED_EOF;
            free(buffer);
            return NULL;
        }

        if(c == '\r' || c == '\n') {
            if(width_check == width) {
                height++;
                width_check = 0;
            } else {
                *error = WRONG_WIDTH;
                free(buffer);
                return NULL;
            }
        } else {
            buffer[index] = c;
            index++;
            width_check++;
        }
    }

    fclose(f);

    map *m = map_create(height, width);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int character = get_character_type(buffer[i * width + j]);

            if(character == -1) {
                *error = WRONG_CHARACTER;
                map_free(m);
                free(buffer);
                return NULL;
            }

            m->grid[i * width + j].type = character;

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

    free(buffer);
    *error = MAP_OK;
    return m;
}

void map_get_nearby_nodes(int x, int y, node *return_nodes) {
}
