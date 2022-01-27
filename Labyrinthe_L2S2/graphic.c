#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include "graphic.h"

#define __NOT_MAIN__
#define SQUARE 50

int init_graphic(int maze_lines, int maze_cols){
    int size_y;
    int size_x;
    char *win_name;
    char *ico_name;

    if (maze_lines <= 0 || maze_cols <= 0){
        printf("ERROR : maze width (here %d) and heigh (here %d) should not be lower than 1\n", maze_cols, maze_lines);
        return 0;
    }

    size_y = (maze_lines * SQUARE) + 20;
    size_x = (maze_cols * SQUARE) + 20;

    win_name = "projet: Lab";
    ico_name = "projet";
    MLV_create_window(win_name, ico_name, size_x, size_y);
    return 1;
}

void refresh_graphic(Maze maze, MLV_Color wall_color){
    int x;
    int y;

    /*MLV_clear_window(MLV_COLOR_BLACK);*/

    for (y = 0; y < maze.nb_line; y++){
        for (x = 0; x < maze.nb_column; x++){
            if ((maze.blocks[y][x]).right_wall)
                MLV_draw_line((x+1) * SQUARE + 10, y * SQUARE +10, (x+1) * SQUARE + 10, (y + 1) * SQUARE + 10, wall_color);
            if ((maze.blocks[y][x]).bottom_wall)
                MLV_draw_line(x * SQUARE + 10, (y+1) * SQUARE + 10, (x + 1) * SQUARE  +10, (y+1) * SQUARE + 10, wall_color);
        }
    }
    MLV_draw_line(10, SQUARE + 10, 10, SQUARE * maze.nb_line + 10, wall_color);
    MLV_draw_line(10, 10, (maze.nb_column * SQUARE) + 10, 10, wall_color);
    MLV_actualise_window();
}

#ifndef __NOT_MAIN__

int main(int argc, char **argv){
    int size_y;
    int size_x;

    MazeBlock **maze;

    size_y = 15;
    size_x = 15;

    if (!init_maze(15, 15, &maze)){
        printf("\nallocation problem.\n");
        exit(EXIT_FAILURE);
    }

    if (init_graphic(size_x, size_y)){
        refresh_graphic(size_x ,size_y, maze, MLV_COLOR_SEASHELL);
        sleep(10);   
        MLV_free_window();
    }
    return 0;
}

#endif