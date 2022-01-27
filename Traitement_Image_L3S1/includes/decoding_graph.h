#ifndef __DECODING_GRAPH_H__
#define __DECODING_GRAPH_H__

/* ------------------------------------------------------------------ */
	
	#include <MLV/MLV_all.h>

	#include "decoding.h"
	#include "quadtree.h"

/* ------------------------------------------------------------------ */
		
	/**
	* Read an encoded colored graph file (.gmc) to fill a quadtree
	* @param t The tree we are filling
	* @param file The file we are decoding
	* @return -4 if the last character of the first string from the file wasn't correctly writed (not a digit, nor 'f')
			  -3 if a color wasn't correctly writed (r, g, b or a < 0 or > 255)
			  -2 if a leaf couldn't be allocated
			  -1 if a node couldn't be allocated
			  0 if it worked
	*/
	int decoding_graph(Tree **t, FILE *file);

	/**
	* Read an encoded B&W graph file (.gmn) to fill a quadtree
	* @param t The tree we are filling
	* @param file The file we are decoding
	* @return -4 if the last character of the first string from the file wasn't correctly writed (not a digit, nor 'f')
			  -3 if a color wasn't correctly writed (r, g, b or a < 0 or > 255)
			  -2 if a leaf couldn't be allocated
			  -1 if a node couldn't be allocated
			  0 if it worked
	*/
	int decoding_graph_bw(Tree **t, FILE *file);

/* ------------------------------------------------------------------ */

#endif