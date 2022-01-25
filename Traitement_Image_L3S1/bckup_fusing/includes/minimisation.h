#ifndef __MINIMISATION_H__
#define __MINIMISATION_H__

/* ------------------------------------------------------------------ */

	#include "color.h"
	#include "quadtree.h" 
	#include "zone.h"

	#define DIST_MAX 7.5
	#define ERROR_MAX 100.0

/* ------------------------------------------------------------------ */
	/* In this minimize function, if a node with a heigh of 1 have all of its leaf with the same color, 
	   we replace the leaf with one of its leaf */
	void minimize_without_loss(Tree **t);

	/* Minimize a quadtree using both 
	   minimize_loss_remove_small_errors and minimize_loss_fuse_identical_subtree functions */
	void minimize_loss(Tree **t, const MLV_Image *image, Zone zone);

	/* Remove all node's leaf when a node's color error has a small value (<= ERROR_MAX) */
	void minimize_loss_remove_small_errors(Tree **t, const MLV_Image *image, Zone zone);

	/* In this minimize function, for each node, we check if its leafs are close enough (distance <= DIST_MAX) 
	   If they are, we make t2 points at t1, and free the old t2 we don't need anymore */ 
	void minimize_loss_fuse_identical_subtree(Tree **t);

	/* Compare 2 subtree by first comparing their average color, then their distance between each other.
	   If they are close enough (dist <= DIST_MAX), we make t2 points at t1, and free the old t2 we don't need anymore */ 
	void compare_subtree(Tree **parent, Tree **t1, Tree **t2, Kid_type type1, Kid_type type2);

	/* Return the distance between the Quadtree */
	double compare_distance(Tree *t1, Tree *t2);

/* ------------------------------------------------------------------ */

#endif