#ifndef __CREATE_QUADTREE_H__
#define __CREATE_QUADTREE_H__

/* ------------------------------------------------------------------ */

	#include "color.h"
	#include "list_errors.h"
	#include "quadtree.h"
	#include "zone.h"

/* ------------------------------------------------------------------ */
	
	/**
	* Create a quadtree from scratch based on an image
	* @param t The quadtree we'll create
	* @param image The image we'll create the quadtree from
	* @param list_errors All errors value from quadtree's leaf
	* @return -1 if we couldn't create the quadtree
			   1 if the quadtree was created
	*/
	int create_quadtree(Tree **t, MLV_Image *image, ErrorList_FirstLast *list_errors);

/* ------------------------------------------------------------------ */

#endif