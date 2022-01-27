#ifndef __MINIMISATION_H__
#define __MINIMISATION_H__

/* ------------------------------------------------------------------ */

	#include "color.h"
	#include "quadtree.h" 
	#include "zone.h"

	#define DIST_MAX 7.5
	#define ERROR_MAX 100.0

/* ------------------------------------------------------------------ */

	/**
	* Minimize a tree without loss : 
	* if a node with a heigh of 1 still have all of its leaf with the same color, 
	* we replace the leaf with one of its leaf.
	* @param t The tree we are minimizing
	*/	   
	void minimize_without_loss(Tree **t);

	/**
	* Minimize a tree with loss : 
	* minimize a quadtree using both minimize_loss_remove_small_errors and
	* minimize_loss_fuse_identical_subtree functions.
	* @param t The tree we are minimizing
	* @param image The image the tree is created from
	* @param zone The zone we are minimizing
	*/	   
	void minimize_loss(Tree **t, const MLV_Image *image, Zone zone);

/* ------------------------------------------------------------------ */

#endif