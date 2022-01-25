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

	return 1;
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

	return 1;
}

/* ------------------------------------------------------------------ */

int read_color(Bit_buffer *bit_buffer, FILE *file) {
	int color = 0, i, power;
	
	/* Read 8 bit :
	   Depending on the current_bit value, we add pow(2, current_bit) to color */
	for (i = 0 ; i < 8 ; i++) {
		power = bit_buffer->current_bit;
		color += (read_bit(bit_buffer, file) == 1) ? pow(2, power) : 0;
	}

	return color;
}

/* ------------------------------------------------------------------ */

int bin_to_color(MLV_Color *leaf_color, Bit_buffer *bit_buffer, FILE *file) {
	int r, g, b, a;

	/* Read each value for r, g, b, a in order to create leaf_color */
	if ((r = read_color(bit_buffer, file)) < 0) {
		return -1;
	}
	if ((g = read_color(bit_buffer, file)) < 0) {
		return -2;
	}

	if ((b = read_color(bit_buffer, file)) < 0) {
		return -3;
	}

	if ((a = read_color(bit_buffer, file)) < 0) {
		return -4;
	}

	(*leaf_color) = MLV_convert_rgba_to_color((unsigned char) r,
											  (unsigned char) g,
											  (unsigned char) b,
											  (unsigned char) a);
	return 1;
}

/* ------------------------------------------------------------------ */

int decoding(Tree **t, Bit_buffer *bit_buffer, FILE *file) {
	int c;

	if ((c = read_bit(bit_buffer, file)) < 0) {
		return 0;
	}

	/* If we read a '0', "t" is a node */
	if (c == 0) {
		
		if (new_node_decoding(t) < 0) {
			return -2;
		}

		/* Since "t" is a node, we keep reading the file in order to "create" its leaf */
		return decoding(&(*t)->sub->no, bit_buffer, file) + 
		 	   decoding(&(*t)->sub->ne, bit_buffer, file) + 
		 	   decoding(&(*t)->sub->se, bit_buffer, file) + 
		 	   decoding(&(*t)->sub->so, bit_buffer, file);
	}

	/* If we read a '1', "t" is a leaf */
	else if (c == 1) {
		
		if (new_leaf_decoding(&(*t)) < 0) {
			return -3;
		}

		/* We read file in order to "create" leaf's color */
		if (bin_to_color(&(*t)->sub->color, bit_buffer, file) < 0) {
			return -4;
		}

		return 0;
	}


	return 0;
}

/* ------------------------------------------------------------------ */

int decode_tree(Tree **t, FILE *file, int colored_version) {
	int res; 

	Bit_buffer bit_buffer;

	init_bit_buffer(&bit_buffer);
	bit_buffer.c = fgetc(file);

	res = (colored_version) ?  decoding(t, &bit_buffer, file) :
						 	   decoding_bw(t, &bit_buffer, file);
	padding_last_oct(&bit_buffer, file);

	return res;
}


/* ------------------------------------------------------------------ */
/* ------------------------------------------------------------------ */
/* ------------------------------------------------------------------ */

int bin_to_bw(MLV_Color *leaf_color, Bit_buffer *bit_buffer, FILE *file) {
	char c;

	/* File ended but missing color */
	if ((c = read_bit(bit_buffer, file)) < 0) {
		return 1;
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

int decoding_bw(Tree **t, Bit_buffer *bit_buffer, FILE *file) {
	char c;

	if ((c = read_bit(bit_buffer, file)) < 0) {
		return 0;
	}

	/* If we read a '0', "t" is a node */
	if (c == 0) {
		if (new_node_decoding(t) < 0) {
			return -2;
		}

		return decoding_bw(&(*t)->sub->no, bit_buffer, file) + 
		 	   decoding_bw(&(*t)->sub->ne, bit_buffer, file) + 
		 	   decoding_bw(&(*t)->sub->se, bit_buffer, file) + 
		 	   decoding_bw(&(*t)->sub->so, bit_buffer, file);
	}

	/* If we read a '1', "t" is a leaf */
	else if (c == 1) {
		if (new_leaf_decoding(t) < 0) {
			return -3;
		}

		if (bin_to_bw(&(*t)->sub->color, bit_buffer, file) < 0) {
			return -4;
		}

		return 0;
	}

	return 0;
}

/* ------------------------------------------------------------------ */