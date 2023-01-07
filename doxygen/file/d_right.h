#ifndef RIGHT_H
#define RIGHT_H

#include "map.h"
#include "path.h"
/**
 * @file
 * @brief contains function to generate a moveset always with wall on right.
*/
/**
 * @brief the function calculate the path for have always a wall at right
 * @param m pointer of the map.
 * @return the path for have alwyas wall at right.
*/
path *right_solve(map* m);

#endif // !RIGHT_H
