#ifndef BACKTRACKING_H
#define BACKTRACKING_H

#include "map.h"
#include "path.h"
/**
 * @file
 * @brief this file contains the function for optimized way.
*/
/**
 * @brief fuction to resolve the shortest way.
 * @param m pointer of the map.
 * @return return the pointer of the path of the shortest way.
*/
path *backtracking_solve(map *m);

#endif // !BACKTRACKING_H
