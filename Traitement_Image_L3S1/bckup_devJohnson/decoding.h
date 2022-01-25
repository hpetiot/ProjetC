#ifndef __DECODING_H__
#define __DECODING_H__

/* ------------------------------------------------------------------ */
	
	#include <MLV/MLV_all.h>
	#include "bit_buffer.h"
	#include "quadtree.h"

/* ------------------------------------------------------------------ */
	/* Allocate a node to "node", without calculating its color_error or subtree (color/leafs) */
	int new_node_decoding(Tree **node);

	/* Allocate a leaf to "leaf", without calculating its color_error or subtree (color/leafs) */
	int new_leaf_decoding(Tree **leaf);

	/* Read a color in the bit_buffer, so 8 bit */
	int read_color(Bit_buffer *bit_buffer, FILE *file);

	/* Read file, in order to convert binary to MLV_Color */
	int bin_to_color(MLV_Color *leaf_color, Bit_buffer *bit_buffer, FILE *file);

	/* Read a encoded file (in color) to fill quadtree "t" */
	int decoding(Tree **t, Bit_buffer *bit_buffer, FILE *file);

	/* Init a bit_buffer and read the binary file "file" to fill quadtree "t" */
	int decode_tree(Tree **t, FILE *file, int colored_version);

	/* Read file to see if leaf_color will be black or white */
	int bin_to_bw(MLV_Color *leaf_color, Bit_buffer *bit_buffer, FILE *file);

	/* Read a encoded file (in B&W) to fill quadtree "t" */
	int decoding_bw(Tree **t, Bit_buffer *bit_buffer, FILE *file);
	
/* ------------------------------------------------------------------ */

#endif