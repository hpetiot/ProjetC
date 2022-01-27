#ifndef __MAZEBLOCK_H__
#define __MAZEBLOCK_H__

#include <stdbool.h>

typedef struct {
    int line;
    int column;
} Coordinates;

typedef struct {
    bool right_wall, bottom_wall;
    Coordinates father;
    int rank;
} MazeBlock;

typedef struct {
	int nb_line;
	int nb_column;
	MazeBlock **blocks;
} Maze;

typedef enum {
	NO_WALL = 0,
	BOTTOM_WALL = 1,
	RIGHT_WALL = 2,
	BOTH_WALL = 3
} status;


/*	allocate_maze:
Allocate enought memory to contain 'nb_line' * 'nb_column' blocks as an array of array
and uses function "init_mazeblock" to initialise each of them*
returns 1 on success, 0 on allocation failure
*/
int allocate_maze(int nb_line, int nb_column, MazeBlock ***blocks);

/* coord_in_maze:
returns 0 if the block of coordinates ('line', 'column') does not belong to the maze
returns 1 otherwise
*/
int coord_in_maze(int line, int column, Maze maze);

/* wall_status:
returns 1, 2, 3, or 0 respectivly if the 'block' has its bottom, right, both or no wall at all
*/
int wall_status(MazeBlock block);

/*print_maze:
print information about each block composing the maze
using function "print_block"
*/
void print_maze(Maze maze);

/*print_block:
print every information contained by 'block'
as well as its coordinates ('line', 'column')
*/
void print_block(int line, int column, MazeBlock block);

#endif