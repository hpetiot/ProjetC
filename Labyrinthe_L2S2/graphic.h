#ifndef __graphic_h__
#define __graphic_h__
#include <MLV/MLV_all.h>
#include "MazeBlock.h"
/* set the size of the wind to be bigg engought*/
int init_graphic(int maze_lines, int maze_cols);
/*to be called between each changes*/
void refresh_graphic(Maze maze, MLV_Color wall_color);

#endif