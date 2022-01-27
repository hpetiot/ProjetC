#ifndef __DECODING_H__
#define __DECODING_H__

/* ------------------------------------------------------------------ */
	
	#include <MLV/MLV_all.h>
	#include "bit_buffer.h"
	#include "quadtree.h"

/* ------------------------------------------------------------------ */
	
	/**
	* Allocate a tree with its type == NODE, 
	* and without calculating any of its field (color_error or subtree (color/leafs))
	* @param node The tree we are allocating 
	* @return -1 if we couldn't allocate the tree
			  -2 if we couldn't allocate tree's subtree
			  1 if we allocate the tree without any problem
	*/
	int new_node_decoding(Tree **node);

	/**
	* Allocate a tree with its type == LEAF, 
	* and without calculating any of its field (color_error or subtree (color/leafs))
	* @param node The tree we are allocating 
	* @return -1 if we couldn't allocate the tree
			  -2 if we couldn't allocate tree's subtree
			  1 if we allocate the tree without any problem
	*/
	int new_leaf_decoding(Tree **leaf);

	/**
	* Read an encoded file (.qtc or .qtn) to fill a quadtree
	* @param t The tree we are filling
	* @param file The file we are decoding
	* @param colored_version Whether we decode a tree in color or in B&W (resp. 1 or 0)
	* @return -4 If we couldn't decode a color
			  -3 If we coudn't allocate a leaf
			  -2 If we coudn't allocate a node
			  -1 If we coudn't know wheter next tree will be a node or a leaf (file not correctly writed)
			  0 if we could decode file
	*/
	int decode_tree(Tree **t, FILE *file, int colored_version);
	
/* ------------------------------------------------------------------ */

#endif