#ifndef __DECODING_H__
#define __DECODING_H__

/* ------------------------------------------------------------------ */
	
	#include <MLV/MLV_all.h>
	#include "quadtree.h"

/* ------------------------------------------------------------------ */
	/* Allocate a node to "node", without calculating its color_error or subtree (color/leafs) */
	int new_node_decoding(Tree **node);

	/* Allocate a leaf to "leaf", without calculating its color_error or subtree (color/leafs) */
	int new_leaf_decoding(Tree **leaf);

	/* Read 8 char from file, and convert those to binary, and to unsigned char (octet) */
	int bin_to_octet(FILE *file);

	/* Read file, in order to convert binary to MLV_Color */
	int bin_to_color(MLV_Color *leaf_color, FILE *file);

	/* Decodes a file to create a tree */
	int decoding(Tree **t, FILE *file);

	/* Read file to see if leaf_color will be black or white */
	int bin_to_bw(MLV_Color *leaf_color, FILE *file);

	/* Decodes a file writed in black and white format to create a tree */
	int decoding_bw(Tree **t, FILE *file);
	
/* ------------------------------------------------------------------ */

#endif