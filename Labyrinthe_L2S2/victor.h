#ifndef __VICTOR_H__
#define __VICTOR_H__

#include "MazeBlock.h"
/* victor:
this function takes the maze, 'path' a pointer to pointer to wannabe start of array WITCH IS YET TO BE ALLOCATED
and the coordinates of the entree and exit points as well as the adress of an integer where it will store the lenhght of the shortest path.
it returns 0 & set path to NULL on failure.
1 on success
*/
int victor(Maze maze, Coordinates **path, Coordinates entree, Coordinates exit, int *score);
/* print_victor:
just the path that has been filled and allocated by 'victor' as arguments
as many display fuinciton, returns nothing.
*/
void print_victor(Coordinates *path, int path_size);

#endif