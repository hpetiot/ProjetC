#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "MazeBlock.h"

#define __NOT_MAIN__

int init_MazeBlock(int line, int column, MazeBlock* block){
    assert(block != NULL);
    assert(line >= 0);
    assert(column >= 0);

    block->right_wall = true;
    block->bottom_wall = true;

    block->father.line = line;
    block->father.column = column;

    block->rank = 0;
    return 1;
}

int allocate_maze(int nb_line, int nb_column, MazeBlock ***blocks){
    int line;
    int column;

    assert(nb_line > 0);
    assert(nb_column > 0);

    if ((*blocks = (MazeBlock **)malloc(sizeof(MazeBlock*) * nb_line)) == NULL)
        return 0;
    for (line = 0; line < nb_line; line++){
        if (((*blocks)[line] = (MazeBlock*)malloc(sizeof(MazeBlock) * nb_column)) == NULL)
            return 0;
        for (column = 0; column < nb_column; column++)
            init_MazeBlock(line, column, &((*blocks)[line][column]));
    }
    ((*blocks)[nb_line - 1][nb_column - 1]).right_wall = false;
    return 1;
}

int coord_in_maze(int line, int column, Maze maze){
    if (line < 0 || column < 0)
        return 0;
    if (line >= maze.nb_line || column >= maze.nb_column)
        return 0;
    return 1;
}

int wall_status(MazeBlock block){
    int status;

    status = 0;
    if (block.bottom_wall)
        status += 1;

    if (block.right_wall)
        status += 2;
    return status;
}

void print_block(int line, int column, MazeBlock block){
    printf(" === Block (y = %d, x = %d) starts ===\n", line, column);
    printf("right_wall : %d\n", (int)block.right_wall);
    printf("bottom_wall : %d\n", (int)block.bottom_wall);
    printf("coord father (y, x): (%d, %d)\n", block.father.line, block.father.column);
    printf("rank : %d\n", block.rank);
    printf(" === Block (y = %d, x = %d) ends ===\n", line, column);
    return;
}

void print_maze(Maze maze){
    int line;
    int column;

    for (line = 0; line < maze.nb_line; line++){
        for (column = 0; column < maze.nb_column; column++){
            print_block(line, column, maze.blocks[line][column]);
            printf("\n");
        }
    }
    return;
}

#ifndef __NOT_MAIN__

int main(int argc, char **argv){

    int nb_line;
    int nb_column;
    Maze maze;

    if (argc == 3){
        nb_line = atoi(argv[1]);
        nb_column = atoi(argv[2]);
    }
    else{
        nb_line = 3;
        nb_column = 3;
    }

    maze.nb_line = nb_line;
    maze.nb_column = nb_column;
    if (!(allocate_maze(nb_line, nb_column, &(maze.blocks)))){
        fprintf(stderr, "Allocation error\n");
        exit(EXIT_FAILURE);
    }

    print_maze(maze);
    return 0;
}

#endif