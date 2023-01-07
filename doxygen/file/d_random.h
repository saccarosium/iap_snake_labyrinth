#ifndef RANDOM_H
#define RANDOM_H

#include "map.h"
#include "path.h"
/**
 * @file
 * @brief function that generate random moves 
*/
/**
 * @brief generate a random moveset.
 * @param m pointer of the map.
 * @return pointer of the path.
*/
path *random_solve(map *m);

#endif // !RANDOM_H
