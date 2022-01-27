#ifndef __UNION_FIND_H__
#define __UNION_FIND_H__

#include "MazeBlock.h"

/* find_compress:
Searches recursivly throught the double array 'blocks' representing the labyrinth
to find the ('line', 'column') s father s coordinate whitch will be stored in 'father_ptr'
in case of a successfull find.
1 is returned if somthing was stored in 'father_prt', 0 otherwise;
*/
int find_compress(MazeBlock **blocks, Coordinates *father_ptr, int line, int column);

/* fuse_rank:
This funciton takes the 2 set of coordinates : 'tree_one' and 'tree_two'
fuse the roots of each, setting the father of the lower ranking root as being the higher ranking root
*/
int fuse_rank(MazeBlock **blocks, Coordinates tree_one, Coordinates tree_two);

/* break_random_wall:
pick a random block of the 'maze' and try to break one of its existing wall.
should no wall be available to break, re-roll the randomcoordinates and re-try
returns 1;
*/
int break_random_wall(Maze maze);

#endif