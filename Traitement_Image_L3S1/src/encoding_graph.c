#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "encoding_graph.h"

/* ------------------------------------------------------------------ */
/* Write MLV_Color (r, g, b, a) values in file */
static void color_to_oct(MLV_Color color, FILE *file) {
	unsigned char r, g, b, a;

	MLV_convert_color_to_rgba(color, &r, &g, &b, &a);
	fprintf(file, " %d %d %d %d\n", (int) r, (int) g, (int) b, (int) a);
}

/* ------------------------------------------------------------------ */
/* Convert MLV_Color (r, g, b, a) in black and white, and write its color
	   in file (0 = white, 1 = black */
static void color_to_bw(MLV_Color color, FILE *file) {
	unsigned char r, g, b, a;

	MLV_convert_color_to_rgba(color, &r, &g, &b, &a);
	
	/* Relative luminance formula */
	(r * 0.2126 + g * 0.7152 + b * 0.722 > 127.5) ? fprintf(file, " 0\n") :
													fprintf(file, " 1\n");
}

/* ------------------------------------------------------------------ */
/* Check if NE is the same as NO */
static void ne_identical_leaf(Tree *t, int node_total, int *new_node, Leaf_nums *leaf_nums, FILE *file) {
	if (t->sub->ne == t->sub->no) {
		fprintf(file, "%d ", leaf_nums->no);
	}

	else {
		*new_node += 1;
		leaf_nums->ne = node_total + *new_node;
		fprintf(file, "%d ", leaf_nums->ne);
	}
}

/* ------------------------------------------------------------------ */
/* Check if SE is the same as NO and NE */
static void se_identical_leaf(Tree *t, int node_total, int *new_node, Leaf_nums *leaf_nums, FILE *file) {
	if (t->sub->se == t->sub->no) {
		fprintf(file, "%d ", leaf_nums->no);
	}

	else if (t->sub->se == t->sub->ne) {
		fprintf(file, "%d ", leaf_nums->ne);
	}

	else {
		*new_node += 1;
		leaf_nums->se = node_total + *new_node;
		fprintf(file, "%d ", leaf_nums->se);
	}
}

/* ------------------------------------------------------------------ */
/* Check if SO is the same as NO, NE and SE */
static void so_identical_leaf(Tree *t, int node_total, int *new_node, Leaf_nums *leaf_nums, FILE *file) {
	if (t->sub->so == t->sub->no) {
		fprintf(file, "%d\n", leaf_nums->no);
	}

	else if (t->sub->so == t->sub->ne) {
		fprintf(file, "%d\n", leaf_nums->ne);
	}

	else if (t->sub->so == t->sub->se) {
		fprintf(file, "%d\n", leaf_nums->se);
	}

	else {
		*new_node += 1;
		leaf_nums->so = node_total + *new_node;
		fprintf(file, "%d\n", leaf_nums->so);
	}
}


/* ------------------------------------------------------------------ */
/* Check if t's leaf are identical : 
	   if they are, we write the same node number in the file 
	   if they aren't, we increment new_node, and write the node number */
static void identical_leafs(Tree *t, int node_total, int *new_node, Leaf_nums *leaf_nums, FILE *file) {
	/* For each leaf (except NO), we check if they point to the same quadtree as another leaf. 
	   If a leaf is the same as another leaf, its leaf_num will be the same as this leaf.
	   If the leaf isn't the same as the other leaf, we increment its leaf_num (compared to the
	   previous leaf). */

	/* NO : first, so we don't need to check anything */
	*new_node += 1;
	fprintf(file, " %d ", node_total + *new_node);
	leaf_nums->no = node_total + *new_node;

	ne_identical_leaf(&(*t), node_total, new_node, leaf_nums, file);
	se_identical_leaf(&(*t), node_total, new_node, leaf_nums, file);
	so_identical_leaf(&(*t), node_total, new_node, leaf_nums, file);
}

/* ------------------------------------------------------------------ */
/* Encode each of t's leafs if they need to : identical leafs don't need to be encoded 2 times
	   "colored_version" parameter is to indicate if we use decoding_graph in color or in B&W */
static void encoding_leafs(Tree *t, FILE *file, int current_node, Leaf_nums leaf_nums, int *node_total, int colored_version) {
	/* For each leaf, we check if they are the same as the one we already encoded.
	   If they are the same, we don't need to encode it.
	   Otherwise, we need to encode it */

	*node_total = (colored_version == 1) ? encoding_graph(t->sub->no, file, leaf_nums.no, *node_total) :
										   encoding_graph_bw(t->sub->no, file, leaf_nums.no, *node_total);

	/* NE */
	if (t->sub->ne != t->sub->no) {
		*node_total = (colored_version == 1) ? encoding_graph(t->sub->ne, file, leaf_nums.ne, *node_total) :
											   encoding_graph_bw(t->sub->ne, file, leaf_nums.ne, *node_total);
	}

	/* SE */
	if (t->sub->se != t->sub->no && t->sub->se != t->sub->ne) {
		*node_total = (colored_version == 1) ? encoding_graph(t->sub->se, file, leaf_nums.se, *node_total) :
											   encoding_graph_bw(t->sub->se, file, leaf_nums.se, *node_total);
	}

	/* SO */
	if (t->sub->so != t->sub->no && t->sub->so != t->sub->ne && t->sub->so != t->sub->se) {
		*node_total = (colored_version == 1) ? encoding_graph(t->sub->so, file, leaf_nums.so, *node_total) : 
											   encoding_graph_bw(t->sub->so, file, leaf_nums.so, *node_total);
	}
}

/* ------------------------------------------------------------------ */

int encoding_graph(Tree *t, FILE *file, int current_node, int node_total) {
	int new_node = 0;
	Leaf_nums leaf_nums;

	if (t == NULL) {
		return 0;
	}

	/* Write current node number in file */
	fprintf(file, "%d", current_node);
	
	/* Then, we check if t is a node or a leaf */
	/* If it's a node, we'll write each of its leaf number, which will be node_total + new_node (new_node = number of node we'll create for this node) */
	if (is_node(t)) {
		identical_leafs(t, node_total, &new_node, &leaf_nums, file);
		node_total += new_node;

		encoding_leafs(t, file, current_node, leaf_nums, &node_total, 1);
	}

	else if (is_leaf(t)) {
		fputc('f', file);
		color_to_oct(t->sub->color, file);
	}

	return node_total;
}



/* ------------------------------------------------------------------ */

/* NB : No commmentaries in this function : cf. encoding_graph, same functionning */
int encoding_graph_bw(Tree *t, FILE *file, int current_node, int node_total) {
	int new_node = 0;
	Leaf_nums leaf_nums;

	if (t == NULL) {
		return 0;
	}

	fprintf(file, "%d", current_node);
	
	if (is_node(t)) {
		identical_leafs(t, node_total, &new_node, &leaf_nums, file);
		node_total += new_node;

		encoding_leafs(t, file, current_node, leaf_nums, &node_total, 0);
	}

	else if (is_leaf(t)) {
		color_to_bw(t->sub->color, file);
	}

	return node_total;
}

/* ------------------------------------------------------------------ */

