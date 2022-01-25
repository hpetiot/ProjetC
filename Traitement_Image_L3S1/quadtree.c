#include <MLV/MLV_color.h>
#include <stdio.h>
#include <stdlib.h>


#include "quadtree.h"

void print_tree_prefix(Tree *t){
	print_node(t);
	if (t->type == NODE){
		printf("no :\n");
		print_tree_prefix(t->sub->no);
		printf("ne :\n");
		print_tree_prefix(t->sub->ne);
		printf("so :\n");
		print_tree_prefix(t->sub->so);
		printf("se :\n");
		print_tree_prefix(t->sub->se);
	}
}

void print_node(Tree* t){

	printf("Node {\n");
	printf("type = %s\n", t->type == LEAF? "leaf":"node");
	printf("color_error = %f\n", t->color_error);
	if (t->type == LEAF){
		
		printf("color = %s\n", MLV_convert_color_to_string(t->sub->color));
	}
	printf("}\n");
}

int new_leaf(Tree **t, MLV_Color color){

	if (NULL == (*t = (Tree*)malloc(sizeof(Tree)))){
		return -1;
	}

	if (NULL == ((*t)->sub = (Sub_tree*)malloc(sizeof(Sub_tree)))){
		return -2;
	}

	(*t)->type = LEAF;
	(*t)->color_error = 0.0;
	(*t)->sub->color = color;

	return 0;
}

/*
Returns:
	[-1 ; -8] -> Memory allocation error while allocating a leaf.
	-9 -> Memory allocation error while allocating space for 'Tree'.
	-10 -> Memory allocation error while allocating space for 'Sub_tree'.
*/
int new_node(Tree **t, MLV_Color color_no, MLV_Color color_ne, MLV_Color color_so, MLV_Color color_se){
	int res = 0;

	if (NULL == (*t = (Tree*)malloc(sizeof(Tree)))){
		return -9;
	}

	if (NULL == ((*t)->sub = (Sub_tree*)malloc(sizeof(Sub_tree)))){
		return -10;
	}

	(*t)->type = NODE;
	(*t)->color_error = 0.0;

	res += new_leaf(&((*t)->sub->no), color_no);
	res += new_leaf(&((*t)->sub->ne), color_ne);
	res += new_leaf(&((*t)->sub->se), color_se);
	res += new_leaf(&((*t)->sub->so), color_so);

	return res;
}

int leaf_to_node(Tree *leaf, MLV_Color color_no, MLV_Color color_ne, MLV_Color color_so, MLV_Color color_se){
	int res = 0;
	leaf->type = NODE;

	res += new_leaf(&(leaf->sub->no), color_no);
	res += new_leaf(&(leaf->sub->ne), color_ne);
	res += new_leaf(&(leaf->sub->se), color_se);
	res += new_leaf(&(leaf->sub->so), color_so);

	return res;
}

void free_tree(Tree *t){
	if(t->type == NODE){
		free_tree(t->sub->no);
		free_tree(t->sub->ne);
		free_tree(t->sub->so);
		free_tree(t->sub->se);
	}
	free(t->sub);
	free(t);
	t = NULL;
}

int main(void){
	Tree *quad;
	int res;

	res = new_node(
		&quad,
		MLV_COLOR_BLUE,
		MLV_COLOR_BLUE,
		MLV_COLOR_BLUE,
		MLV_COLOR_BLUE
		);
	if(res < 0)
		fprintf(stderr, "MEM ERROR\n");

	res = leaf_to_node(
		quad->sub->no,
		MLV_COLOR_RED,
		MLV_COLOR_GREEN,
		MLV_COLOR_RED,
		MLV_COLOR_RED
		);
	if(res < 0)
		fprintf(stderr, "MEM ERROR\n");


	printf("errcode = %d", res);
	print_tree_prefix(quad);

	free_tree(quad);

	return 0;
}