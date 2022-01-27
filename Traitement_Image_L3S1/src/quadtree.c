#include <MLV/MLV_color.h>
#include <MLV/MLV_image.h>
#include <stdio.h>
#include <stdlib.h>

#include "quadtree.h"

/* ------------------------------------------------------------------ */

int is_leaf(Tree *t) {
	return t->type == LEAF;
}

/* ------------------------------------------------------------------ */

int is_node(Tree *t) {
	return t->type == NODE;
}

/* ------------------------------------------------------------------ */

int has_full_leaf(Tree *t) {
	if (is_node(t)) {
		return is_leaf(t->sub->no) && 
			   is_leaf(t->sub->ne) &&
			   is_leaf(t->sub->se) &&
			   is_leaf(t->sub->so);
	}

	return 0;
}

/* ------------------------------------------------------------------ */

void print_tree_prefix(Tree *t){
	print_node(t);
	if (t->type == NODE) {
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

/* ------------------------------------------------------------------ */

void print_node(Tree* t){
	unsigned char r, g, b, a;
	printf("Node {\n");
	printf("type = %s\n", t->type == LEAF? "leaf":"node");
	printf("color_error = %f\n", t->color_error);

	if (is_leaf(t)) {
		MLV_convert_color_to_rgba(t->sub->color, &r, &g, &b, &a);
		printf("color = (%d, %d, %d, %d)\n", r, g, b, a);
	}
}

/* ------------------------------------------------------------------ */

void free_tree(Tree *t) {
	Tree *no, *ne, *so, *se;
	if (t->type == NODE) {
		no = t->sub->no;
		ne = t->sub->ne;
		so = t->sub->so;
		se = t->sub->se;

		free_tree(t->sub->no);
		free(t->sub->no);
		t->sub->no = NULL;

		/* Before freeing each leaf, we check if the leaf we are going to free
		   isn't the same as the leafs we already freed */
		if (ne != no) {
			free_tree(t->sub->ne);
			free(t->sub->ne);
			t->sub->no = NULL;
		}

		if (so != no && so != ne) {
			free_tree(t->sub->so);
			free(t->sub->so);
			t->sub->so = NULL;
		}

		if (se != no && se != ne && se != so) {
			free_tree(t->sub->se);
			free(t->sub->se);
			t->sub->se = NULL;
		}

		free(t->sub);
		t->sub = NULL;
	}

	if (t->type == LEAF) {
		free(t->sub);
		t->sub = NULL;
	}
} 	

/* ------------------------------------------------------------------ */

void free_all_leaf(Tree *t) {
	free(t->sub->no->sub);
	t->sub->no->sub = NULL;

	free(t->sub->ne->sub);
	t->sub->ne->sub = NULL;

	free(t->sub->so->sub);
	t->sub->so->sub = NULL;

	free(t->sub->se->sub);
	t->sub->se->sub = NULL;

	free(t->sub->no);
	free(t->sub->ne);
	free(t->sub->so);
	free(t->sub->se);
}

/* ------------------------------------------------------------------ */

void replace_node_to_leaf(Tree **node, Tree *leaf) {
	(*node)->type = LEAF;
	(*node)->sub->color = leaf->sub->color;
	(*node)->color_error = leaf->color_error;
}

/* ------------------------------------------------------------------ */

void paint_sub_image(MLV_Image *img, MLV_Color color, int start_x, int start_y, int size){
	int i;
	int j;

	for (i = 0; i < size; i++){
		for (j = 0; j < size; j++){
			MLV_set_pixel_on_image(start_x + i, start_y + j, color, img);
		}
	}
}

/* ------------------------------------------------------------------ */

static void fill_sub_image(MLV_Image *img, Tree *t, int start_x, int start_y, int size){
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

/* ------------------------------------------------------------------ */

static void fill_image(MLV_Image *img, Tree *t){
	fill_sub_image(img, t, 0, 0, SIZE_IMAGE);
}

/* ------------------------------------------------------------------ */

int tree_to_image(MLV_Image **img, Tree *t){
	if (NULL == (*img = MLV_create_image(SIZE_IMAGE, SIZE_IMAGE))){
		return 0;
	}

	fill_image(*img, t);

	return 1;
}

/* ------------------------------------------------------------------ */
