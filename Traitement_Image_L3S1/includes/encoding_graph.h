#ifndef __ENCODING_GRAPH_H__
#define __ENCODING_GRAPH_H__

/* ------------------------------------------------------------------ */
	
	#include <MLV/MLV_all.h>

	#include "quadtree.h"

/* ------------------------------------------------------------------ */

	typedef struct {
		int no;
		int ne;
		int se;
		int so;
	} Leaf_nums;

/* ------------------------------------------------------------------ */

	/**
	* Encode a minimized quadtree (in color)
	* @param t The tree we are encoding
	* @param file The file we are using the encode t
	* @param current_node The number of the node we are encoding
	* @param node_total The number of node so far
	* @return The number of node so far to actualize it (since it's a recursive function)
	*/
	int encoding_graph(Tree *t, FILE *file, int current_node, int node_total);


	/**
	* Encode a minimized quadtree (in black & white)
	* @param t The tree we are encoding
	* @param file The file we are using the encode t
	* @param current_node The number of the node we are encoding
	* @param node_total The number of node so far
	* @return The number of node so far to actualize it (since it's a recursive function)
	*/
	int encoding_graph_bw(Tree *t, FILE *file, int current_node, int node_total);

/* ------------------------------------------------------------------ */

#endif