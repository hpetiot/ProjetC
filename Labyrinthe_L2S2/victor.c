#include <stdio.h>
#include <stdlib.h>
#include "MazeBlock.h"
#include "victor.h"

static void reset_rank(Maze maze){
	int total_blocks;
	int line;
	int column;

	total_blocks = maze.nb_line * maze.nb_column;
	for (line = 0; line < maze.nb_line; line++){
		for (column = 0; column < maze.nb_column; column++){
			maze.blocks[line][column].rank = total_blocks;
		}
	}
}
static int get_path(Maze maze, int score, Coordinates **path, Coordinates current){

	if (NULL == (*path = (Coordinates*)malloc(sizeof(Coordinates) * (score + 1))))
		return 0;
	(*path)[score].line = current.line;
	(*path)[score].column = current.column;
	score --;
	while (score >= -1){
		
		if(current.line - 1 >= 0 
			&& maze.blocks[current.line-1][current.column].rank == score
			&& !maze.blocks[current.line-1][current.column].bottom_wall){
			current.line --;
		}
		else if (current.column - 1 >= 0
			&& maze.blocks[current.line][current.column - 1].rank == score
			&& !maze.blocks[current.line][current.column - 1].right_wall){
			current.column --;
		}
		else if (current.column + 1 < maze.nb_column
			&& maze.blocks[current.line][current.column + 1].rank == score
			&& !maze.blocks[current.line][current.column].right_wall){
			current.column ++;
		}
		else if (current.line + 1 < maze.nb_line
			&& maze.blocks[current.line + 1][current.column].rank == score
			&& !maze.blocks[current.line][current.column].bottom_wall){
			current.line ++;
		}
		(*path)[score].line = current.line;
		(*path)[score].column = current.column;
		score --;
	}
	return 1;
}

int search_path(Maze maze, int* score, int depth, int line, int column, 
	Coordinates *entree, Coordinates *exit, bool* exist)
{	int walls;

	walls = 0;
	if ((line == exit->line) && (column == exit->column)){ /*si sur la case de sortie*/
		if (depth  <= *score){ /* si la profondeur est plus petite que le score*/
			if (!(*exist))
				*exist = true;
			*score = depth;
			maze.blocks[line][column].rank = depth;
			return 0;
		}
		return 0;
	}
	if (maze.blocks[line][column].rank == -1)
		return 1;
	if (depth >= maze.blocks[line][column].rank) /* si la profondeur est égale ou superieur à la derniere profondeur enregistrée ici*/
		return 0;

	maze.blocks[line][column].rank = depth;

	if (depth == *score) /* la profondeur est égale au meilleur score*/
		return 0;

	depth ++;

	if (line  + 1 < maze.nb_line
		&& !maze.blocks[line][column].bottom_wall
		&& maze.blocks[line + 1][column].rank != -1)
		walls += search_path(maze, score, depth, line + 1, column, entree, exit, exist);
	else
		walls ++;

	if (column + 1 < maze.nb_column
		&& !maze.blocks[line][column].right_wall
		&& maze.blocks[line][column + 1].rank != -1)
		walls += search_path(maze, score, depth, line, column + 1, entree, exit, exist);
	else
		walls ++;

	if (column - 1 >= 0
		&& !maze.blocks[line][column - 1].right_wall
		&& maze.blocks[line][column -1].rank != -1)
		walls += search_path(maze, score, depth, line, column - 1, entree, exit, exist);
	else
		walls ++;

	if (line - 1 >= 0
		&& !maze.blocks[line - 1][column].bottom_wall
		&& maze.blocks[line - 1][column].rank != -1)
		walls += search_path(maze, score, depth, line - 1, column, entree, exit, exist);
	else
		walls ++;

	if (walls >= 3
		&& (entree->line != line || entree->column != column)){
		maze.blocks[line][column].rank = -1;
		return 1;
	}
	return 0;
}

int victor(Maze maze, Coordinates **path, Coordinates entree, Coordinates exit, int *score){
	bool exist;

	*score = maze.nb_line * maze.nb_column;
	exist = false;
	reset_rank(maze);
	search_path(maze, score, 0, entree.line, entree.column, &entree, &exit, &exist);
	if(exist)
		return get_path(maze, *score, path, exit);

	else{
		path = NULL;
		return 0;
	}
}

void print_victor(Coordinates *path, int path_size){
	int i;

	for (i = 0; i <= path_size; i++){
		printf("%d : (%d; %d)\n", i, path[i].line, path[i].column);
	}
	return;
}
