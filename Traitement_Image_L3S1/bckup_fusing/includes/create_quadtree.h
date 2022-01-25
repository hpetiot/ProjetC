#ifndef __CREATE_QUADTREE_H__
#define __CREATE_QUADTREE_H__

/* ------------------------------------------------------------------ */

	#include "color.h"
	#include "list_errors.h"
	#include "quadtree.h"
	#include "zone.h"

/* ------------------------------------------------------------------ */
		
	/* 
	Change a leaf into a node :
		- First change its type
		- Then calculates each of its leafs' color
		- Allocate each of its leafs
		- Finally, remove the leaf we turned into a node of the list "list_errors" (it's not a leaf anymore we won't subdivise it anymore)

	Return < 0 if there was an allocation problem in one of the leaf, otherwise 0 there wasn't any problem 
	*/
	int leaf_to_node(Tree **leaf,const MLV_Image *image, Zone zone, ErrorList_FirstLast *list_errors);

	/* 
	Allocate leaf in the parameters.

   	If its color_error (that we'll calculate in the function) is equal to 0.0, we don't add the new leaf
   	in list_errors since the color is probably very close to the reality (or already the real color)

   	Return < 0 if there was an allocation problem, or if we couldn't add the leaf in list_errors (allocation problem)
   	*/
	int new_leaf(Tree **leaf, const MLV_Image *image, Zone zone, MLV_Color color, ErrorList_FirstLast *list_errors);

	/* 
	Take the first leaf of list_errors and subdivise it.
	If list_errors is empty, we calculate the average color of all the pixels in image, and create a new leaf in the tree 't'.
	*/
	int image_to_quadtree(Tree **t, MLV_Image *image, ErrorList_FirstLast *list_errors);

	/* 
	Create the quadtree "t" from scratch based on "image".
   	The process will stop until we have did "NB_SHARES" shares in the quadtree (cf. quadtree.h).
   	Also display the quadtree every power of 2 (1 share, 2 shares, 4 shares, 8, 16 ect.), and pause the screen for 500ms 
   	*/
	int create_quadtree(Tree **t, MLV_Image *image, ErrorList_FirstLast *list_errors);

/* ------------------------------------------------------------------ */

#endif