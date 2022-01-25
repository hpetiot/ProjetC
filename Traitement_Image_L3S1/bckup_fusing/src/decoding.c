#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "decoding.h"

/* ------------------------------------------------------------------ */

int new_node_decoding(Tree **node) {
	if ((*node = (Tree*) malloc(sizeof(Tree))) == NULL) {
		return -1;
	}

	if (((*node)->sub = (Sub_tree*) malloc(sizeof(Sub_tree))) == NULL) {
		return -2;
	}

	(*node)->type = NODE;

	return 0;
}

/* ------------------------------------------------------------------ */

int new_leaf_decoding(Tree **leaf) {
	if ((*leaf = (Tree*) malloc(sizeof(Tree))) == NULL) {
		return -1;
	}

	if (((*leaf)->sub = (Sub_tree*) malloc(sizeof(Sub_tree))) == NULL) {
		return -2;
	}

	(*leaf)->type = LEAF;

	return 0;
}

/* ------------------------------------------------------------------ */

int bin_to_octet(FILE *file) {
	char bin[8], c;
	int i, res = 0;

	/* First, we get 8 char from file */
	for (i = 7 ; i >= 0 ; i--) {
		if (fread(&c, 1, 1, file) == 0) {
			return -1;
		}

		if (c == EOF) {
			return -2;
		}

		bin[i] = c;
	}

	/* Then, we convert these 8 char to an int/unsigned char (octet) */
	for (i = 0 ; i < 8 ; i++) {
		res += (bin[i] == '1') ? pow(2, i) : 0;
	}

	return res;
}

/* ------------------------------------------------------------------ */

int bin_to_color(MLV_Color *leaf_color, FILE *file) {
	int r, g, b, a;

	/* Read each value for r, g, b, a in order to create leaf_color */
	if ((r = bin_to_octet(file)) < 0) {
		return -1;
	}
	if ((g = bin_to_octet(file)) < 0) {
		return -2;
	}

	if ((b = bin_to_octet(file)) < 0) {
		return -3;
	}

	if ((a = bin_to_octet(file)) < 0) {
		return -4;
	}

	(*leaf_color) = MLV_convert_rgba_to_color((unsigned char) r,
											  (unsigned char) g,
											  (unsigned char) b,
											  (unsigned char) a);
	return 1;
}

/* ------------------------------------------------------------------ */

int decoding(Tree **t, FILE *file) {
	char c;

	if (fread(&c, 1, 1, file) == 0) {
		return -1;
	}

	if (c == EOF) {
		return 0;
	}

	/* If we read a '0', "t" is a node */
	if (c == 0) {
		if (new_node_decoding(t) < 0) {
			return -2;
		}

		/* Since "t" is a node, we keep reading the file in order to "create" its leaf */
		return decoding(&(*t)->sub->no, file) + 
		 	   decoding(&(*t)->sub->ne, file) + 
		 	   decoding(&(*t)->sub->se, file) + 
		 	   decoding(&(*t)->sub->so, file);
	}

	/* If we read a '1', "t" is a leaf */
	else if (c == 1) {
		if (new_leaf_decoding(&(*t)) < 0) {
			return -3;
		}

		/* We read file in order to "create" leaf's color */
		if (bin_to_color(&(*t)->sub->color, file) < 0) {
			return -4;
		}

		return 0;
	}

	return 0;
}

/* ------------------------------------------------------------------ */
/* ------------------------------------------------------------------ */
/* ------------------------------------------------------------------ */

int bin_to_bw(MLV_Color *leaf_color, FILE *file) {
	char c;

	if (fread(&c, 1, 1, file) == 0) {
		return -1;
	}

	/* Missing color */
	if (c == EOF) {
		return -2;
	}

	/* If we read a '1', leaf_color is black */
	else if (c == 1) {
		(*leaf_color) = MLV_COLOR_BLACK;
	}

	/* If we read a '0', leaf_color is white */
	else if (c == 0) {
		(*leaf_color) = MLV_COLOR_WHITE;
	}

	return 1;
}

/* ------------------------------------------------------------------ */

int decoding_bw(Tree **t, FILE *file) {
	char c;

	if (fread(&c, 1, 1, file) == 0) {
		return -1;
	}

	if (c == EOF) {
		return 0;
	}

	/* If we read a '0', "t" is a node */
	if (c == 0) {
		if (new_node_decoding(t) < 0) {
			return -2;
		}

		return decoding_bw(&(*t)->sub->no, file) + 
		 	   decoding_bw(&(*t)->sub->ne, file) + 
		 	   decoding_bw(&(*t)->sub->se, file) + 
		 	   decoding_bw(&(*t)->sub->so, file);
	}

	/* If we read a '1', "t" is a leaf */
	else if (c == 1) {
		if (new_leaf_decoding(t) < 0) {
			return -3;
		}

		if (bin_to_bw(&(*t)->sub->color, file) < 0) {
			return -4;
		}

		return 0;
	}

	return 0;
}

/* ------------------------------------------------------------------ */