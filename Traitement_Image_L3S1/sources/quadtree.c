#include <MLV/MLV_color.h>
#include <MLV/MLV_image.h>
#include <stdio.h>
#include <stdlib.h>


#include "quadtree.h"
#include "window.h"

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

void paint_sub_image(MLV_Image *img, MLV_Color color, int start_x, int start_y, int size){
	int i;
	int j;

	for (i = 0; i < size; i++){
		for (j = 0; j < size; j++){
			MLV_set_pixel_on_image (start_x + i, start_y + j, color, img);
		}
	}
}

void fill_sub_image(MLV_Image *img, Tree *t, int start_x, int start_y, int size){
	int sub_size;

	if (t->type == NODE){
		sub_size = size / 2;
		fill_sub_image(img, t->sub->no, start_x, start_y, sub_size);
		fill_sub_image(img, t->sub->ne, start_x + sub_size, start_y, sub_size);
		fill_sub_image(img, t->sub->so, start_x, start_y + sub_size, sub_size);
		fill_sub_image(img, t->sub->se, start_x + sub_size, start_y + sub_size, sub_size);
	}
	else {
		paint_sub_image(img, t->sub->color, start_x, start_y, size);
	}
}

void fill_image(MLV_Image *img, Tree *t){
	fill_sub_image(img, t, 0, 0, SIZE_IMAGE);
}

int tree_to_image(MLV_Image **img, Tree *t){
	if (NULL == (*img = MLV_create_image(SIZE_IMAGE, SIZE_IMAGE))){
		return 0;
	}
	fill_image(*img, t);

	return 1;
}