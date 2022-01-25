#ifndef __ENCODING_H__
#define __ENCODING_H__

/* ------------------------------------------------------------------ */
	
	#include <MLV/MLV_all.h>
	#include "bit_buffer.h"
	#include "quadtree.h"

/* ------------------------------------------------------------------ */
	
	/* Write color in the file in byte */
	void write_color(unsigned char color, Bit_buffer *bit_buffer, FILE *file);

	/* Convert an MLV_Color (r, g, b, a values) to binary, and write it in file */
	void color_to_bin(MLV_Color color, Bit_buffer *bit_buffer, FILE *file);

	/* (colored_version) Encode a tree to write it in file */
	void encoding(Tree *t, Bit_buffer *bit_buffer, FILE *file);

	/* Init a bit_buffer and write quadtree "t" in file in bytes */
	void encode_tree(Tree *t, FILE *file, int colored_version);

	/* Convert an MLV_Color (r, g, b, a values) to MLV_COLOR_BLACK (1) or MLV_COLOR_WHITE (0), and write it in file */
	void color_to_bin_bw(MLV_Color color, Bit_buffer *bit_buffer, FILE *file);
	
	/* (B&W version) Encode a tree in black and white, to write it in file */
	void encoding_bw(Tree *t, Bit_buffer *bit_buffer, FILE *file);

/* ------------------------------------------------------------------ */

#endif