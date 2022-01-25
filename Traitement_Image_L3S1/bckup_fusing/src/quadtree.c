#include <MLV/MLV_color.h>
#include <MLV/MLV_image.h>
#include <stdio.h>
#include <stdlib.h>

#include "quadtree.h"

int nb_node = 0;
int nb_leaf = 0;
int same_node = 0;


/* ------------------------------------------------------------------ */
/* TEMP */
void nb_node_leaf(Tree *t) {
	if (t->type == NODE) {
		nb_node++;

		/* NE */
		if (t->sub->ne == t->sub->no) {
			same_node++;
		}

		/* SO */
		if (t->sub->so == t->sub->no) {
			same_node++;
		}

		else if (t->sub->so == t->sub->ne) {
			same_node++;
		}

		/* SE */
		if (t->sub->se == t->sub->no) {
			same_node++;
		}

		else if (t->sub->se == t->sub->ne) {
			same_node++;
		}

		else if (t->sub->se == t->sub->so) {
			same_node++;
		}

		nb_node_leaf(t->sub->no);

		if (t->sub->ne != t->sub->no) {
			nb_node_leaf(t->sub->ne);
		}

		if (t->sub->se != t->sub->no && t->sub->se != t->sub->ne) {
			nb_node_leaf(t->sub->se);
		}
		
		if (t->sub->so != t->sub->no && t->sub->so != t->sub->ne && t->sub->so != t->sub->se) {
			nb_node_leaf(t->sub->so);
		}
		
	}

	if (t->type == LEAF) {
		nb_leaf++;
	}
}

/* ------------------------------------------------------------------ */
/* TEMP */
void print_nb_node_leaf(Tree *t) {
	nb_node = 0;
	nb_leaf = 0;

	printf("Printf Nb Node Leaf :\n");
	nb_node_leaf(t);

	printf("Nb Node différents = %d // Leaf = %d\n", nb_node, nb_leaf);
	printf("Same nodes (%d)\n\n", same_node);
}

/* ------------------------------------------------------------------ */

int is_leaf(Tree *t) {
	return t->type == LEAF;
}

/* ------------------------------------------------------------------ */

int has_full_leaf(Tree *t) {
	return is_leaf(t->sub->no) && 
		   is_leaf(t->sub->ne) &&
		   is_leaf(t->sub->se) &&
		   is_leaf(t->sub->so);
}

/* ------------------------------------------------------------------ */

int is_node(Tree *t) {
	return t->type == NODE;
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

/* ------------------------------------------------------------------ */

void fill_image(MLV_Image *img, Tree *t){
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

int numbering_nodes_quadtree(Tree *t, int node_total) {
	t->node_num = node_total;

	if (is_node(t)) {
		node_total = numbering_nodes_quadtree(t->sub->no, node_total + 1);
		node_total = numbering_nodes_quadtree(t->sub->ne, node_total + 1);
		node_total = numbering_nodes_quadtree(t->sub->se, node_total + 1);
		node_total = numbering_nodes_quadtree(t->sub->so, node_total + 1);
	}

	return node_total;
}

/* ------------------------------------------------------------------ */

void print_node_num(Tree *t) {
	printf("%d\n", t->node_num);

	if (is_node(t)) {
		print_node_num(t->sub->no);
		print_node_num(t->sub->ne);
		print_node_num(t->sub->se);
		print_node_num(t->sub->so);
	}
}

/* ------------------------------------------------------------------ */

void free_tree_exception(Tree *t, Tree *exception) {
	Tree *no, *ne, *so, *se;

	if (t == exception) {
		return ;
	}

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