#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "ascii.h"

#define __NOT_MAIN__

void disp_ascii(Maze maze){
    int y;
    int x;

    for (x = 0; x < maze.nb_column; x++)
        printf("+--");
    printf("+\n");
    for (y = 0; y < maze.nb_line; y++){
        if (y == 0)
            printf("   ");
        else
            printf("|  ");
        for (x = 0; x < maze.nb_column; x++){
            if ((maze.blocks[y][x]).right_wall)
                printf("|");
            else
                printf(" ");
            printf("  ");
        }
        printf("\n");
        for (x = 0; x < maze.nb_column; x++){
            printf("+");
            if ((maze.blocks[y][x]).bottom_wall)
                printf("--");
            else
                printf("  ");
        }
        printf("+\n");
    }
}

#ifndef __NOT_MAIN__

int main(int argc, char **argv){
    int size_y;
    int size_x;

    MazeBlock **maze;

    size_y = 15;
    size_x = 15;
    init_maze(size_x, size_y, &maze);
    aff_ascii(size_x, size_y, maze);
    if (!init_maze(15, 15, &maze)){
        printf("\nallocation problem.\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}

#endif