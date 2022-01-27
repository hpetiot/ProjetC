#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "utf8.h"
#include "structures.h"

static void disp_top_line(Maze maze){
    int i;

    printf("%s", intersections[0][0][0][1]);
    for (i = 0; i < maze.nb_column - 1; i++)
        printf("%s", intersections[maze.blocks[0][i].right_wall][0][1][1]);
        
    printf("%s", intersections[1][0][1][0]);
    printf("\n");
}

static void disp_btwn_line(int y, Maze maze){
    int i;
    int top;
    int bottom;
    int right;
    int left;
    printf("%s", intersections[1][!(y == 0)][0][maze.blocks[y][0].bottom_wall]);
    for (i = 0; i < maze.nb_column - 1; i++){
        top = maze.blocks[y][i].right_wall;
        bottom = maze.blocks[y+1][i].right_wall;
        right = maze.blocks[y][i+1].bottom_wall;
        left = maze.blocks[y][i].bottom_wall;
        printf("%s", intersections[bottom][top][left][right]);
    }
    printf("%s", intersections[maze.blocks[y+1][i].right_wall][1][maze.blocks[y][i].bottom_wall][0]);
    printf("\n");
}

static void disp_bottom_line(Maze maze){
    int i;

    printf("%s", intersections[0][1][0][1]);
    for (i = 0; i < maze.nb_column - 1; i++)
        printf("%s", intersections[0][maze.blocks[maze.nb_line - 1][i].right_wall][1][1]);

    printf("%s", intersections[0][0][1][0]);
    printf("\n");
}

int display_utf8(Maze maze){
    int i;

    disp_top_line(maze);
    for (i = 0; i < maze.nb_line - 1; i++)
        disp_btwn_line(i, maze);
    disp_bottom_line(maze);
    return 1;
}