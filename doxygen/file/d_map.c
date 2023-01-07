#include "../include/map.h"
#include "../include/alloc.h"
#include "../include/utils.h"
#include <string.h>
/**
 * @file 
 * @brief File that contains the funcion to define map elements and get the possible location.
*/


/**
 * @brief Create a map filled with walls
 * @param height height of the map
 * @param width width of the map
 * @return map* pointer to the newly created map structure
 */
map *map_create(int height, int width) {
    map *m = xmalloc(sizeof(map));
    m->height = height;
    m->width = width;
    m->grid = xmalloc(sizeof(node) * height * width);

    for (int i = 0; i < height * width; i++) {
        m->grid[i].type = WALL;
        m->grid[i].cost = 1;
        m->grid[i].parent = NULL;
        m->grid[i].x = i % width;
        m->grid[i].y = i / width;
    }

    return m;
}

/**
 * @brief Get a node from the map
 * Given a map and a set of coordinates, the fuctions returs the pointer to the wanted node
 * @param m pointer to the map struct 
 * @param y y point coordinate
 * @param x x point coordinate
 * @return node* pointer to the wanted node
 */ 
node *map_get_node(map *m, int y, int x) {
    if (x < 0 || x >= m->width)
        return NULL;
    if (y < 0 || y >= m->height)
        return NULL;
    return &m->grid[y * m->width + x];
}
/**
 * @brief copy the node type to a new variable
 * @param n pointer of the node
 * @param t the type of the node
*/
void map_set_node_type(node *n, enum nodeType t) {
    n->type = t;
}
/**
 * @brief Convert char to respective enum type
 * Given a character, the functions returns the corresponding nodeType unum's value. For 
 * example, given "#" it will return "WALL"
 * @param c A given character
 * @return nodeType Corresponding node type
 */ 
nodeType get_character_type(char c) {
    switch (c) {
    case ' ':
        return EMPTY;
    case 'o':
        return USER;
    case '_':
        return END;
    case '#':
        return WALL;
    case '$':
        return COIN;
    case '!':
        return UNEVENT;
    case 'T':
        return DRILL;
    default:
        return -1;
    }
}
/**
 * @brief Frees memory used by the map
 * Frees memory used by the map by freing all the nodes, and than the map itself
 * @param m pointer to the map to free
 */
void map_free(map *m) {
    free(m->grid);
    free(m);
}
/**
 * @brief menage the interaction the player has with the map element
 * @param buffer pointer to the map object.
 * @param height heigth of the map.
 * @param width width of the map.
 * @param error pointer to the exit status of the function (error type defined by the enum error)
 * @return the pointer of the map.
*/
map *load_from_buffer(char *buffer, int height, int width, error *error) {
    map *m = map_create(height, width);
    for (size_t i = 0; i < height; i++) {
        for (size_t j = 0; j < width; j++) {
            int character = get_character_type(buffer[i * width + j]);

            if (character == -1) {
                *error = WRONG_CHARACTER;
                map_free(m);
                free(buffer);
                return NULL;
            }

            m->grid[i * width + j].type = character;
            if (character == COIN) {
                m->grid[i * width + j].cost = 0;
            } else if (character == UNEVENT) {
                m->grid[i * width + j].cost = 100;
            }

            if (buffer[i * width + j] == 'o') {
                m->start.x = j;
                m->start.y = i;
            } else if (buffer[i * width + j] == '_') {
                m->end.x = j;
                m->end.y = i;
            }
        }
    }

    free(buffer);
    *error = MAP_OK;
    return m;
}
/**
 * @brief Load map from a give file path
 * The function loads a map from file given via the given path cheking for possible allocation/formatting 
 * errors, writing them into the memory area pointed by error_code
 * @param filename pointer to the path of the file to load the map from
 * @param error pointer to the exit status of the function (error type defined by the enum error)
 * @return map* pointer to the newly generated map (NULL if an error occured)
 * 
 * @see error
 */ 
map *map_load_from_file(char *filename, error *error) {
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        *error = FILE_OPEN;
        return NULL;
    }

    int width = 0;
    int height = 0;
    char c;

    while (true) {
        c = getc(f);

        if (c == EOF) {
            *error = FILE_OPEN;
            return NULL;
        }

        if (c == '\r' || c == '\n')
            break;
        width++;
    }

    fseek(f, 0, SEEK_END);

    int size = ftell(f);
    char *buffer = malloc(size);
    if (buffer == NULL) {
        *error = MALLOC_FAILED;
        return NULL;
    }

    fseek(f, 0, SEEK_SET);

    int index = 0;
    int width_check = 0;

    while ((c = getc(f)) != EOF) {
        if (c == EOF) {
            *error = UNEXPECTED_EOF;
            free(buffer);
            return NULL;
        }

        if (c == '\r' || c == '\n') {
            if (width_check == width) {
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

    return load_from_buffer(buffer, height, width, error);
}
/**
 * @brief Load map from a stdin
 * The function loads a map from stdin cheking for possible allocation/formatting errors writing
 *  them into the memory area pointed by error_code
 * @param error pointer to the exit status of the function (error type defined by the enum error)
 * @return map* pointer to the newly generated map (NULL if an error occured)
 */
map *map_load_from_stdin(error *error) {
    int width, height;

    scanf(" %d", &width);
    scanf(" %d", &height);

    if (getchar() != '\n') {
        *error = UNEXPECTED_NEW_LINE;
        return NULL;
    }

    char *buffer = malloc(height * width);
    if (buffer == NULL) {
        *error = MALLOC_FAILED;
        return NULL;
    }
    char tmp_char;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width + 1; j++) {
            tmp_char = getchar();
            if (tmp_char == '\n') {
                if (j == width) {
                    break;
                } else {
                    *error = WRONG_WIDTH;
                    return NULL;
                }
            } else {
                buffer[i * width + j] = tmp_char;
            }
        }
    }

    return load_from_buffer(buffer, height, width, error);
}
/**
 * @brief Get the visitable nodes adjacent to a given one 
 * Given a set of coordinates and a pointer to the map, the function will return Null in case of errors,
 * or a pointer to an array of up to 4 pointers to the visitable nodes.
 * @param m pointer to the map
 * @param y y node coordinate
 * @param x x node coordinate
 * @param n_nodes pointer to the number of nodes found
 * @return node** pointer to the array of nodes that have been deemed visitable
 */
node **map_get_nearby_nodes(map *m, int y, int x, int *n_nodes) {
    node **return_nodes = (node **)malloc(sizeof(node *) * 5);
    node **write_head = return_nodes;
    *n_nodes = 0;

    if (x - 1 >= 0 && map_get_node(m, y, x - 1)->type != WALL) {
        *write_head = map_get_node(m, y, x - 1);
        write_head++;
        (*n_nodes)++;
    }

    if (x + 1 < m->width && map_get_node(m, y, x + 1)->type != WALL) {
        *write_head = map_get_node(m, y, x + 1);
        write_head++;
        (*n_nodes)++;
    }

    if (y - 1 >= 0 && map_get_node(m, y - 1, x)->type != WALL) {
        *write_head = map_get_node(m, y - 1, x);
        write_head++;
        (*n_nodes)++;
    }

    if (y + 1 < m->height && map_get_node(m, y + 1, x)->type != WALL) {
        *write_head = map_get_node(m, y + 1, x);
        write_head++;
        (*n_nodes)++;
    }

    return (node **)realloc(return_nodes, sizeof(node *) * *n_nodes);
}
/**
 * @brief returns true if the coordinates are the same
 * This function returns true if the x and y coordinates are the same, without any regard to the pointers 
 * of the two given nodes
 * @param a pointer to the first node to compare
 * @param b pointer to the second node to compare
 * @return true if x and y of both nodes are the same
 * @return false otherwise
 */
bool map_compare_node(node *a, node *b) {
    return a->x == b->x && a->y == b->y;
}
