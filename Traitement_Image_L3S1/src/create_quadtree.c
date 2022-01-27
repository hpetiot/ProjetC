#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "create_quadtree.h"


/* ------------------------------------------------------------------ */
/* 
	Allocate leaf in the parameters.

   	If its color_error (that we'll calculate in the function) is equal to 0.0, we don't add the new leaf
   	in list_errors since the color is probably very close to the reality (or already the real color)

   	Return < 0 if there was an allocation problem, or if we couldn't add the leaf in list_errors (allocation problem)
*/

static int new_leaf(Tree **leaf, const MLV_Image *image, Zone zone, MLV_Color color, ErrorList_FirstLast *list_errors) {
	if ((*leaf = (Tree*) malloc(sizeof(Tree))) == NULL) {
		return -1;
	}

	if (((*leaf)->sub = (Sub_tree*) malloc(sizeof(Sub_tree))) == NULL) {
		return -2;
	}

	(*leaf)->type = LEAF;
	(*leaf)->sub->color = color;
	(*leaf)->color_error = zone_color_error((*leaf)->sub->color, image, zone);

	/* If color_error is equal to 0, the leaf displays the real color,
	   we don't want to subdivise the zone anymore : we won't even see the difference */
	if ((*leaf)->color_error == 0.0) {
		return 0;
	}

	/* If color_error is still to high, we want to subdivise it later. So we add it to list_errors */
	if (add_elem(&(list_errors->first), &(list_errors->last), *leaf, zone) < 0) {
		return -3;
	}
	
	return 0;
}

/* ------------------------------------------------------------------ */

/* 
	Change a leaf into a node :
		- First change its type
		- Then calculates each of its leafs' color
		- Allocate each of its leafs
		- Finally, remove the leaf we turned into a node of the list "list_errors" (it's not a leaf anymore we won't subdivise it anymore)

	Return < 0 if there was an allocation problem in one of the leaf, otherwise 0 there wasn't any problem 
*/
static int leaf_to_node(Tree **leaf, const MLV_Image *image, Zone zone, ErrorList_FirstLast *list_errors) {
	int res = 0;
	MLV_Color no_color, ne_color, so_color, se_color;

	if ((*leaf)->type == NODE) {
		remove_elem_errorlist(&list_errors->first, (*leaf)->color_error);
		return 0;
	}

	(*leaf)->type = NODE;

	/* First, getting each leaf's color */
	get_zones_average_color(image, zone, &no_color, &ne_color, &so_color, &se_color);

	/* Then create them */
	res += new_leaf(&((*leaf)->sub->no), image, no_zone(zone), no_color, list_errors);
	res += new_leaf(&((*leaf)->sub->ne), image, ne_zone(zone), ne_color, list_errors);
	res += new_leaf(&((*leaf)->sub->se), image, se_zone(zone), se_color, list_errors);
	res += new_leaf(&((*leaf)->sub->so), image, so_zone(zone), so_color, list_errors);
	
	/* Removing leaf from the errorlist, since it's not a leaf anymore we won't subdivise it anymore */
	remove_elem_errorlist(&list_errors->first, (*leaf)->color_error);

	return res;
}

/* ------------------------------------------------------------------ */
/* 
	Take the first leaf of list_errors and subdivise it.
	If list_errors is empty, we calculate the average color of all the pixels in image, and create a new leaf in the tree 't'.
*/
static int image_to_quadtree(Tree **t, MLV_Image *image, ErrorList_FirstLast *list_errors) {
	/* If "t" is empty */
	if (*t == NULL) {
		if (new_leaf(t, 
					 image,
					 return_zone(0, 0, SIZE_IMAGE, SIZE_IMAGE), 
					 zone_average_color(image, 
					 					return_zone(0, 0, SIZE_IMAGE, SIZE_IMAGE)), 
					 list_errors) < 0) {
			return -1;
		}

		return 0;
	}

	/* We turn the leaf with the biggest color_error into a node : it means it's the one further from the reality.
	   The leaf we are looking for will always be the first element of list_errors,
	   therefore we don't have to look every leaf of the tree, which would be very long in a enormous tree */
	if (leaf_to_node(&(list_errors->first->leaf), image, list_errors->first->zone, list_errors) < 0) {
		return -1;
	}

	return 0;
}

/* ------------------------------------------------------------------ */

int create_quadtree(Tree **t, MLV_Image *image, ErrorList_FirstLast *list_errors) {
	int shares = 0, power = 0;
	MLV_Image *quadtree_img;

	printf("Creating quadtree... \n");

	/* We won't stop until we have "NB_SHARES" shares in the quadtree */
	while (shares < NB_SHARES) {
		if (image_to_quadtree(t, image, list_errors) < 0) {
			return -1;
		} 	

		/* If shares == a power of 2, we display the tree on the screen */
		if (pow(2, power) == ++shares) {
			if (!tree_to_image(&quadtree_img, *t)) {
	    		fprintf(stderr, "convention error\n");
			}

			printf("2^%-2d / %-6d %s\n", power, shares, (shares == 1) ? "partage " : "partages");
			MLV_draw_image(quadtree_img, 0, 0);
			MLV_actualise_window();
			power++; 
			MLV_wait_milliseconds(0);
			MLV_free_image(quadtree_img);
		}

		/* If we don't have any error left in list_eror to subdivise */ 
		if (list_errors->first == NULL) {
			break;
		}
	}

	if (shares != NB_SHARES) {
		printf("Final: %-6d %s\n\n", shares, (shares == 1) ? "partage " : "partages");
	}

	return 1;
}

/* ------------------------------------------------------------------ */
