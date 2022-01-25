#ifndef __ENCODING_H__
#define __ENCODING_H__

/* ------------------------------------------------------------------ */
	
	#include <MLV/MLV_all.h>
	#include "quadtree.h"

/* ------------------------------------------------------------------ */

	/* Convert an unsigned char to binary, and write it in file */
	void octet_to_bin(unsigned char val, FILE *file);

	/* Convert an MLV_Color (r, g, b, a values) to binary, and write it in file */
	void color_to_bin(MLV_Color color, FILE *file);

	/* Encode a tree to write it in file */
	void encoding(Tree *t, FILE *file);

	/* Convert an MLV_Color (r, g, b, a values) to MLV_COLOR_BLACK (1) or MLV_COLOR_WHITE (0), and write it in file */
	void color_to_bin_bw(MLV_Color color, FILE *file);
	
	/* Encode a tree in black and white, to write it in file */
	void encoding_bw(Tree *t, FILE *file);

/* ------------------------------------------------------------------ */

#endif