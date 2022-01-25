#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "encoding.h"

/* ------------------------------------------------------------------ */

void octet_to_bin(unsigned char val, FILE *file) {
    int index;
	char bit;

    index = 7;

    while (index >= 0) {
		bit = (val | (1u << index)) == val;
		bit == 1 ? fwrite(&bit, 1, 1, file) : fwrite(&bit, 1, 1, file);
        index--;
    }
}

/* ------------------------------------------------------------------ */

void color_to_bin(MLV_Color color, FILE *file) {
	unsigned char r, g, b, a;

	MLV_convert_color_to_rgba(color, &r, &g, &b, &a);

	/* Convert r, g, b and a to bin, and add them in file */
	octet_to_bin(r, file);
	octet_to_bin(g, file);
	octet_to_bin(b, file);
	octet_to_bin(a, file);
}

/* ------------------------------------------------------------------ */

void encoding(Tree *t, FILE *file) {
	char c;

	if (t == NULL) {
		return ;
	}

	/* If 't' is a node, add '0' to file, and encodes all its leaf */
	if (is_node(t)) {
		c = 0;
		fwrite(&c, 1, 1, file);

		encoding(t->sub->no, file);
		encoding(t->sub->ne, file);
		encoding(t->sub->se, file);
		encoding(t->sub->so, file);
	}

	/* If 't' is a leaf, add '1' to file, and convert its color to bin to add it */
	else if (is_leaf(t)) {
		c = 1;
		fwrite(&c, 1, 1, file);
		color_to_bin(t->sub->color, file);
	}
} 

/* ------------------------------------------------------------------ */
/* ------------------------------------------------------------------ */
/* ------------------------------------------------------------------ */

void color_to_bin_bw(MLV_Color color, FILE *file) {
	char c;
	unsigned char r, g, b, a;

	MLV_convert_color_to_rgba(color, &r, &g, &b, &a);
	
	/* Relative luminance formula */
	if (r * 0.2126 + g * 0.7152 + b * 0.722 > 127.5) {
		c = 0;
		fwrite(&c, 1, 1, file);
	}

	else {
		c = 1;
		fwrite(&c, 1, 1, file);
	}
		
}

/* ------------------------------------------------------------------ */

void encoding_bw(Tree *t, FILE *file) {
	char c;

	if (t == NULL) {
		return ;
	}

	/* If 't' is a node, add '0' to file, and encodes all its leaf */
	
	if (is_node(t)) {
		c = 0;
		fwrite(&c, 1, 1, file);

		encoding_bw(t->sub->no, file);
		encoding_bw(t->sub->ne, file);
		encoding_bw(t->sub->se, file);
		encoding_bw(t->sub->so, file);
	}

	/* If 't' is a leaf, add '1' to file, and convert its color to black or white, and add 0 or 1 */
	else if (is_leaf(t)) {
		c = 1;
		fwrite(&c, 1, 1, file);
		color_to_bin_bw(t->sub->color, file);
	}
} 

/* ------------------------------------------------------------------ */



