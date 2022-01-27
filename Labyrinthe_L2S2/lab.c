#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <MLV/MLV_all.h>


#include "ascii.h"
#include "graphic.h"
#include "MazeBlock.h"
#include "victor.h"
#include "union_find.h"
#include "utf8.h"
#include "parseur.h"

#define DEFAULT_ENTREE 0
#define DEFAULT_SIZE 10
#define PASSIVE_WAIT 100
#define TXT 0
#define UTF8 1
#define GRAPH 2
#define NONE 3
#define COLOR MLV_COLOR_GREY

void global_display(int type, Maze maze){
	switch(type){
		case TXT: 
			disp_ascii(maze);
			break;
		case UTF8: 
			display_utf8(maze);
			break;
		case GRAPH: 
			refresh_graphic(maze, COLOR);
			break;
		case NONE:
			break;
	}
}

int main(int argc, char **argv){
	int *option;
	unsigned int seed;
	int res;

	int path_size;
	Maze maze;

	Coordinates entree;
	Coordinates f_entree;
	Coordinates f_exit;
	Coordinates exit_pt;
	Coordinates *path;

	if ((res = parseur(argc, argv, &option, &seed)) == -2){

		fprintf(stderr, "ERROR : could not allocate option managment table\n");
		exit(EXIT_FAILURE);
	}

	if (res == -1)
		return 0;

	if ((maze.nb_line = option[SIZE_LINE]) < 0){
		printf("Wrong/Corrupted/No value for maze number of line, switching to default\n");
		maze.nb_line = DEFAULT_SIZE;
	}
	if ((maze.nb_column = option[SIZE_COLS]) < 0){
		printf("Wrong/Corrupted/No value for maze number of columns, switching to default\n");
		maze.nb_column = DEFAULT_SIZE;
	}

	if ((entree.line = option[ENTREE_LINE]) < 0 || entree.line >= maze.nb_line){
		printf("Wrong/Corrupted/No value for entree point\'s line coordinate, switching to default\n");
		entree.line = DEFAULT_ENTREE;
	}
	if ((entree.column = option[ENTREE_COLUMN]) < 0 || entree.column >= maze.nb_column){
		printf("Wrong/Corrupted/No value for entree point\'s column coordinate, switching to default\n");
		entree.column = DEFAULT_ENTREE;
	}

	if ((exit_pt.line = option[EXIT_LINE]) < 0 || exit_pt.line >= maze.nb_line){
		printf("Wrong/Corrupted/No value for exit point\'s line coordinate, switching to default\n");
		exit_pt.line = maze.nb_line -1;
	}
	if ((exit_pt.column = option[EXIT_COLUMN]) < 0 || exit_pt.column >= maze.nb_column){
		printf("Wrong/Corrupted/No value for exit point\'s column coordinate, switching to default\n");
		exit_pt.column = maze.nb_column -1;
	}

	if (res == 1){
		printf("Wrong/Corrupted/No value for seed, switching to default\n");
		seed = time(NULL);
	}

	if (!allocate_maze(maze.nb_line, maze.nb_column, &(maze.blocks))){
		fprintf(stderr, "ERROR : could not allocate maze\n");
		exit(EXIT_FAILURE);
	}

	if (option[MODE] == GRAPH)
		init_graphic(maze.nb_line, maze.nb_column);

	srand(seed);

	do{
        break_random_wall(maze);
        find_compress(maze.blocks, &f_entree, entree.line, entree.column);
        find_compress(maze.blocks, &f_exit, exit_pt.line, exit_pt.column);
        if (option[WAIT] != 0){
        	if (option[WAIT] == -1){
        		if (option[MODE] == GRAPH)
        			MLV_wait_keyboard(NULL, NULL, NULL);
        		else
        			scanf("%*1c");
        	}
	        else
	        	usleep(option[WAIT] * 1000);
	        global_display(option[MODE], maze);
    	}
    }while((f_entree.line != f_exit.line) || (f_entree.column != f_exit.column));

    global_display(option[MODE], maze);
    printf("finished generation\n");
    if (option[WIN]){
    	if (victor(maze, &path, entree, exit_pt, &path_size))
    		print_victor(path, path_size);
    	else
    		fprintf(stderr, "Could not allocate table to contain the path from entree point to exit\n");
    }

    if (option[MODE] == GRAPH){
    	while(getchar() == EOF){
	        usleep(PASSIVE_WAIT);
    	}
		MLV_free_window();
    }
    return 0;
}

