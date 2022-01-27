#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#include "union_find.h"

#define __NOT_MAIN__

/* find_compress:
Searches recursivly throught the double array 'blocks' representing the labyrinth
to find the ('line', 'column') s father s coordinate whitch will be stored in 'father_ptr'
in case of a successfull find.
1 is returned if somthing was stored in 'father_prt', 0 otherwise;
*/
int find_compress(MazeBlock **blocks, Coordinates *father_ptr, int line, int column){
    int *f_line;
    int *f_column;

    f_line = &(blocks[line][column].father.line);
    f_column = &(blocks[line][column].father.column);

    if(*f_line == line && *f_column == column){ /*orphelin*/
        father_ptr->line = line;
        father_ptr->column = column;
        return 0;
    }

    if (find_compress(blocks, father_ptr, *f_line, *f_column)){
        *f_line = father_ptr->line;
        *f_column = father_ptr->column;
    }
    return 1;
}

/* fuse_rank:
This funciton takes the 2 set of coordinates : 'tree_one' and 'tree_two'
fuse the roots of each, setting the father of the lower ranking root as being the higher ranking root
*/
int fuse_rank(MazeBlock **blocks, Coordinates tree_one, Coordinates tree_two){
    int *rank_one;
    int *rank_two;
    Coordinates *f_one;
    Coordinates *f_two;

    f_one = &(blocks[tree_one.line][tree_one.column].father);
    f_two = &(blocks[tree_two.line][tree_two.column].father);

    find_compress(blocks, f_one, tree_one.line, tree_one.column);
    find_compress(blocks, f_two, tree_two.line, tree_two.column);

    rank_one = &(blocks[f_one->line][f_one->column].rank);
    rank_two = &(blocks[f_two->line][f_two->column].rank);

    if (*rank_one == *rank_two){
        *rank_one = *rank_one + 1;
        blocks[f_two->line][f_two->column].father = *f_one;
    }
    else if (*rank_one < *rank_two){
        blocks[f_one->line][f_one->column].father = *f_two;
    }
    else if (*rank_one > *rank_two){
        blocks[f_two->line][f_two->column].father = *f_one;   
    }
    return 1;
}

/* break_random_wall:
pick a random block of the 'maze' and try to break one of its existing wall.
should no wall be available to break, re-roll the randomcoordinates and re-try
returns 1;
*/
int break_random_wall(Maze maze){
    int rand_line;
    int rand_column;
    int rand_wall;
    int walls;
    bool not_right_most;
    bool not_bottom_most;
    Coordinates tree_one;
    Coordinates tree_two;

    do {
        rand_line = rand() % maze.nb_line;
        rand_column = rand() % maze.nb_column;

        if (rand_line == maze.nb_line-1 && rand_column == maze.nb_column-1)
            continue;

        tree_one.line = rand_line;
        tree_one.column = rand_column;


        walls = wall_status(maze.blocks[rand_line][rand_column]);

        if(walls == NO_WALL)
            continue;

        not_right_most = (rand_column + 1) != maze.nb_column;
        not_bottom_most = (rand_line + 1) != maze.nb_line;

        if (walls == BOTTOM_WALL && not_bottom_most){
            maze.blocks[rand_line][rand_column].bottom_wall = false;
            tree_two.line = rand_line + 1;
            tree_two.column = rand_column;
            break;
        }
        else if (walls == RIGHT_WALL && not_right_most){
            maze.blocks[rand_line][rand_column].right_wall = false;
            tree_two.line = rand_line;
            tree_two.column = rand_column + 1;
            break;
        }
        else if  (walls == BOTH_WALL){
            rand_wall = rand() % 2;

            if (rand_wall && not_right_most){
                maze.blocks[rand_line][rand_column].right_wall = false;
                tree_two.line = rand_line;
                tree_two.column = rand_column+ 1;
                break;
            }
            else if (not_bottom_most){
                maze.blocks[rand_line][rand_column].bottom_wall = false;
                tree_two.line = rand_line + 1;
                tree_two.column = rand_column;
                break;
            }
        }
    } while (true);
    fuse_rank(maze.blocks, tree_one, tree_two);
    return 1;
}

#ifndef __NOT_MAIN__

int main(int argc, char **argv){

    Maze maze;

    Coordinates f_entree;
    Coordinates f_exit;
    srand(time(NULL));
    maze.nb_line = 7;
    maze.nb_column = 10;

    if (allocate_maze(maze.nb_line, maze.nb_column, &(maze.blocks)) == 0)
        exit(EXIT_FAILURE);
    do{
        break_random_wall(maze);
        find_compress(maze.blocks, &f_entree, 0, 0);
        find_compress(maze.blocks, &f_exit, maze.nb_line-1, maze.nb_column-1);
    }while((f_entree.line != f_exit.line) || (f_entree.column != f_exit.column));
    init_graphic(maze.nb_line, maze.nb_column);
    refresh_graphic(maze, MLV_COLOR_SEASHELL);
    sleep(5000000);
    return 0;
}
#endif