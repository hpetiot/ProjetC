#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "encoding.h"



/* ------------------------------------------------------------------ */

void write_color(unsigned char color, Bit_buffer *bit_buffer, FILE *file) {
	int i;

	for (i = 0 ; i < 8 ; i++) {
		write_bit_color(bit_buffer, color, file);
	}
}

/* ------------------------------------------------------------------ */

void color_to_bin(MLV_Color color, Bit_buffer *bit_buffer, FILE *file) {
	unsigned char r, g, b, a;

	MLV_convert_color_to_rgba(color, &r, &g, &b, &a);

	/* Convert r, g, b and a to bin, and add them in file */
	write_color(r, bit_buffer, file);
	write_color(g, bit_buffer, file);
	write_color(b, bit_buffer, file);
	write_color(a, bit_buffer, file);
}

/* ------------------------------------------------------------------ */

void encoding(Tree *t, Bit_buffer *bit_buffer, FILE *file) {
	if (t == NULL) {
		return ;
	}

	/* If 't' is a node, add '0' to file, and encodes all its leaf */
	if (is_node(t)) {
		write_bit(bit_buffer, 0, file);

		encoding(t->sub->no, bit_buffer, file);
		encoding(t->sub->ne, bit_buffer, file);
		encoding(t->sub->se, bit_buffer, file);
		encoding(t->sub->so, bit_buffer, file);
	}

	/* If 't' is a leaf, add '1' to file, and convert its color to bin to add it */
	else if (is_leaf(t)) {
		write_bit(bit_buffer, 1, file);

		color_to_bin(t->sub->color, bit_buffer, file);
	}
} 


/* ------------------------------------------------------------------ */

void encode_tree(Tree *t, FILE *file, int colored_version) {
	Bit_buffer bit_buffer;

	init_bit_buffer(&bit_buffer);
	(colored_version) ?  encoding(t, &bit_buffer, file) :
						 encoding_bw(t, &bit_buffer, file);
	padding_last_oct(&bit_buffer, file);
}

/* ------------------------------------------------------------------ */
/* ------------------------------------------------------------------ */
/* ------------------------------------------------------------------ */

void color_to_bin_bw(MLV_Color color, Bit_buffer *bit_buffer, FILE *file) {
	unsigned char r, g, b, a;

	MLV_convert_color_to_rgba(color, &r, &g, &b, &a);
	
	/* Relative luminance formula */
	if (r * 0.2126 + g * 0.7152 + b * 0.722 > 127.5) {
		write_bit(bit_buffer, 0, file);
	}

	else {
		write_bit(bit_buffer, 1, file);
	}
		
}

/* ------------------------------------------------------------------ */

void encoding_bw(Tree *t, Bit_buffer *bit_buffer, FILE *file) {
	if (t == NULL) {
		return ;
	}

	/* If 't' is a node, add '0' to file, and encodes all its leaf */
	
	if (is_node(t)) {
		write_bit(bit_buffer, 0, file);

		encoding_bw(t->sub->no, bit_buffer, file);
		encoding_bw(t->sub->ne, bit_buffer, file);
		encoding_bw(t->sub->se, bit_buffer, file);
		encoding_bw(t->sub->so, bit_buffer, file);
	}

	/* If 't' is a leaf, add '1' to file, and convert its color to black or white, and add 0 or 1 */
	else if (is_leaf(t)) {
		write_bit(bit_buffer, 1, file);

		color_to_bin_bw(t->sub->color, bit_buffer, file);
	}
} 

/* ------------------------------------------------------------------ */



