#ifndef ASTAR_H
#define ASTAR_H

#include "map.h"
#include "path.h"
/**
 * @file 
 * @brief contain function to manage coin and unevent.
*/

/**
 * @brief manage the point of the coin and unevent.
 * @param m pointer to the map.
 * @return return the pointer of the path.
*/
path *astar_solve(map *m);

#endif // !ASTAR_H
