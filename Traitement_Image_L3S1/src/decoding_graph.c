#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "decoding.h"
#include "decoding_graph.h"

/* ------------------------------------------------------------------ */
/* Allocate NE if it needs to (if it's not the same as NO) */
static int allocate_ne(Tree **t, int no_num, int ne_num, int *res, FILE *file, int colored_version) {
	/* NE */
	if (ne_num == no_num) {
		(*t)->sub->ne = (*t)->sub->no;
	}
	
	else {
		if (new_leaf_decoding(&(*t)->sub->ne) < 0) {
			return 0;
		}

		*res += (colored_version == 1) ? decoding_graph(&(*t)->sub->ne, file) :
							 			 decoding_graph_bw(&(*t)->sub->ne, file);
	}

	return 1;
}

/* ------------------------------------------------------------------ */
/* Allocate SE if it needs to (if it's not the same as NO or NE) */
static int allocate_se(Tree **t, int no_num, int ne_num, int se_num, int *res, FILE *file, int colored_version) {
	/* SE */
	if (se_num == no_num) {
		(*t)->sub->se = (*t)->sub->no;
	}

	else if (se_num == ne_num) {
		(*t)->sub->se = (*t)->sub->ne;
	}

	else {
		if (new_leaf_decoding(&(*t)->sub->se) < 0) {
			return 0;
		}

		*res += (colored_version == 1) ? decoding_graph(&(*t)->sub->se, file) :
							 			 decoding_graph_bw(&(*t)->sub->se, file);
	}

	return 1;
}


/* ------------------------------------------------------------------ */
/* Allocate SO if it needs to (if it's not the same as NO, NE or SE) */
static int allocate_so(Tree **t, int no_num, int ne_num, int se_num, int so_num, int *res, FILE *file, int colored_version) {
	if (so_num == no_num) {
		(*t)->sub->so = (*t)->sub->no;
	}

	else if (so_num == ne_num) {
		(*t)->sub->so = (*t)->sub->ne;
	}

	else if (so_num == se_num) {
		(*t)->sub->so = (*t)->sub->se;
	}

	else {
		if (new_leaf_decoding(&(*t)->sub->so) < 0) {
			return 0;
		}

		*res += (colored_version == 1) ? decoding_graph(&(*t)->sub->so, file) :
							 			 decoding_graph_bw(&(*t)->sub->so, file);
	}

	return 1;
}

/* ------------------------------------------------------------------ */
/* Allocate each of t's leaf if they need to */
static int allocate_leafs(Tree **t, int no_num, int ne_num, int se_num, int so_num, int *res, FILE *file, int colored_version) {
	/* For each leaf, we check if the current leaf isn't the same as the leafs we already allocate : 
	   in that case, we just point this leaf to the one he is the same as. 
	If the leaf isn't the same as the leaf we already allocate, we allocate a new leaf for it */

	/* NO : don't need to check anything, it's the first leaf */
	if (new_leaf_decoding(&(*t)->sub->no) < 0) {
		return 0;
	}

	*res += (colored_version == 1) ? decoding_graph(&(*t)->sub->no, file) :
						 			 decoding_graph_bw(&(*t)->sub->no, file);

	if (!allocate_ne(t, no_num, ne_num, res, file, colored_version)) {
		return 0;
	}

	if (!allocate_se(t, no_num, ne_num, se_num, res, file, colored_version)) {
		return 0;
	}

	if (!allocate_so(t, no_num, ne_num, se_num, so_num, res, file, colored_version)) {
		return 0;
	}
	
	return 1;
}

/* ------------------------------------------------------------------ */
/* Returns 1 if c is a digit (0 to 9), otherwise 0 */
static int is_digit(int c) {
	return c > 47 && c < 58;
}

/* ------------------------------------------------------------------ */
/* Returns 1 if val is an octet (0 to 255), otherwise 0 */
static int is_octet(int val) {
	return val >= 0 && val <= 255;
}

/* ------------------------------------------------------------------ */
/* Read file content to fill leaf_color */
static int bin_to_color_graph(MLV_Color *leaf_color, FILE *file) {
	int r, g, b, a;

	fscanf(file, "%d %d %d %d", &r, &g, &b, &a);

	/* If r, g, b, a isn't an octet (< 0 or > 255), the file isn't correctly writed */
	if (!is_octet(r) || !is_octet(g) || !is_octet(b) || !is_octet(a)) {
		return 0;
	}

	(*leaf_color) = MLV_convert_rgba_to_color((unsigned char) r,
											  (unsigned char) g,
											  (unsigned char) b,
											  (unsigned char) a);
	return 1;
}

/* ------------------------------------------------------------------ */

int decoding_graph(Tree **t, FILE *file) {
	char node[20];
	int num1, num2, num3, num4, res = 0; /* Each num corresponds to the number of the int we read on each line */

	/* Get first line's number */
	fscanf(file, "%s", node);

	/* First, we check what's the last char of the first string of the line to determine
	   if the line describe a NODE or a LEAF */
	/* If it's a digit, the line is a node */
	if (is_digit(node[strlen(node) - 1])) {
		if (new_node_decoding(t) < 0) {
			return -1;
		}

		/* Get all leafs number */
		fscanf(file, "%d %d %d %d\n", &num1, &num2, &num3, &num4);

		/* Allocate t's leafs */
		if (!allocate_leafs(t, num1, num2, num3, num4, &res, file, 1)) {
			return -2;
		}
		
		return res;
	}

	/* If it's the letter 'f', the line is a leaf */
	else if (node[strlen(node) - 1] == 'f') {
		if (new_leaf_decoding(t) < 0) {
			return -2;
		}

		/* We read file in order to "create" leaf's color */
		if (!bin_to_color_graph(&(*t)->sub->color, file)) {
			return -3;
		}

		return 0;
	}

	/* Not a digit, nor 'f' : the file isn't correctly writed */
	else {
		return -4;
	}

	free(node);

	return 0;
}

/* ------------------------------------------------------------------ */

int decoding_graph_bw(Tree **t, FILE *file) {
	int c;
	int nb_num = 0;
	int node, num1, num2, num3, num4, res = 0;

	do {
		switch(nb_num++) {
			case 0: fscanf(file, "%d", &node); break;
			case 1: fscanf(file, "%d", &num1); break;
			case 2: fscanf(file, "%d", &num2); break;
			case 3: fscanf(file, "%d", &num3); break;
			case 4: fscanf(file, "%d", &num4); break;
			default: return -1; /* More than 5 numbers on 1 single line */
		}

		c = fgetc(file);

	} while (c != '\n');


	/* 5 int on the line : it's a node and its leafs */
	if (nb_num == 5) {
		if (new_node_decoding(t) < 0) {
			return -1;
		}

		/* Allocate t's leafs */
		if (!allocate_leafs(t, num1, num2, num3, num4, &res, file, 0)) {
			return -2;
		}
		
		return res;
	}

	/* 2 int on the line : it's a leaf and its color */
	else if (nb_num == 2) {
		if (new_leaf_decoding(t) < 0) {
			return -2;
		}

		(*t)->sub->color = (num1 == 1) ? MLV_COLOR_BLACK : MLV_COLOR_WHITE;

		return 0;
	}

	/* Not 2 nor 5 int on the line, the file wasn't correctly writed */
	else {
		return -1;
	}

	return 0;
}

/* ------------------------------------------------------------------ */
