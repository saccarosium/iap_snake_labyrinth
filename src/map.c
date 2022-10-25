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

map* map_load_from_file(char* filename){
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
    char* write_head = read_buffer;
    

    //printf("facendo");
    while ((c = getc(file)) != EOF){
        //putchar(c);
        printf("char: %c ==> %d-%d  (%d)\n", c, currently_used ,write_head, buffer_size);
        *write_head = c;
        write_head++;
        currently_used++;
        if (currently_used == buffer_size){
            buffer_size += sizeof(char) * 32; //aggiungi altri 32 slot
            read_buffer= realloc(read_buffer, buffer_size );
            if (read_buffer == NULL) {
                return NULL;
            }
        }
    }
    printf("currently_used: %d, buffer_size: %d", currently_used, buffer_size);
    fclose(file);
    printf("done");
    for (int i = 0; i < currently_used; i++){
        putchar(*(read_buffer + i));
    }
}

void map_get_nearby_nodes(int x, int y, node *return_nodes){

}

void map_set_node_type(node* n, enum nodeType t){
    n->type = t;
}