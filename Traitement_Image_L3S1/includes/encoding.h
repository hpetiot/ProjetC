#ifndef __ENCODING_H__
#define __ENCODING_H__

/* ------------------------------------------------------------------ */
	
	#include <MLV/MLV_all.h>
	#include "bit_buffer.h"
	#include "quadtree.h"

/* ------------------------------------------------------------------ */
	
	/**
	* Encode a (not minimized) quadtree in file
	* @param t The quadtree we are encoding
	* @param file The file we are using to encode t
	* @param colored_version Whether we encode a tree in color or in B&W (resp. 1 or 0)
	*/
	void encode_tree(Tree *t, FILE *file, int colored_version);

/* ------------------------------------------------------------------ */

#endif