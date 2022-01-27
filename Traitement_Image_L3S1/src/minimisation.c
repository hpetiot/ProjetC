#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "minimisation.h"

/* ------------------------------------------------------------------ */

void minimize_without_loss(Tree **t) {
	MLV_Color color;
	double error;

	if ((*t)->type == NODE) {
		minimize_without_loss(&(*t)->sub->no);
	  	minimize_without_loss(&(*t)->sub->ne);
		minimize_without_loss(&(*t)->sub->so);
		minimize_without_loss(&(*t)->sub->se);

		/* We check if 't' node has 4 leafs (height == 1). If he does, check if they all have the same color 
		   If they do, we replace the node with one of its leaf, and free all its leaf */
		if (has_full_leaf((*t))) {
			if (kids_same_color((*t))) {
				(*t)->type = LEAF;
				color = (*t)->sub->no->sub->color;
				error = (*t)->sub->no->color_error;
				
				free_all_leaf((*t));

				(*t)->sub->color = color;
				(*t)->color_error = error;
			}
		}
	}
}

/* ------------------------------------------------------------------ */
/* Remove all node's leaf when a node's color error has a small value (<= ERROR_MAX) */
static void minimize_loss_remove_small_errors(Tree **t, const MLV_Image *image, Zone zone) {
	if (is_node(*t)) {
		minimize_loss_remove_small_errors(&(*t)->sub->no, image, no_zone(zone));
	  	minimize_loss_remove_small_errors(&(*t)->sub->ne, image, ne_zone(zone));
		minimize_loss_remove_small_errors(&(*t)->sub->so, image, so_zone(zone));
		minimize_loss_remove_small_errors(&(*t)->sub->se, image, se_zone(zone));

		if (has_full_leaf((*t))) {
			/* If tree's color error is small (<= ERROR_MAX), we remove its leaf */
			if ((*t)->color_error <= ERROR_MAX) {
				free_all_leaf((*t));

				(*t)->type = LEAF;
				(*t)->sub->color = zone_average_color(image, zone);
			}
		}
	}
}

/* ------------------------------------------------------------------ */
/* Return the distance between the Quadtree */
static double compare_distance(Tree *t1, Tree *t2) {
	double dist = 0;

	/* t1 = LEAF / t2 = LEAF */
	if (is_leaf(t1) && is_leaf(t2)) {
		dist = color_distance(t1->sub->color, t2->sub->color);
	}

	/* t1 = LEAF / t2 = NODE */
	else if (is_leaf(t1) && is_node(t2)) {
		dist += (compare_distance(t1, t2->sub->no) +
		 		 compare_distance(t1, t2->sub->ne) +
		 		 compare_distance(t1, t2->sub->so) +
				 compare_distance(t1, t2->sub->se)) / 4;
	}

	/* t1 = NODE / t2 = LEAF */
	else if (is_node(t1) && is_leaf(t2)) {
		dist += (compare_distance(t1->sub->no, t2) +
		 		 compare_distance(t1->sub->ne, t2) +
		 		 compare_distance(t1->sub->so, t2) +
				 compare_distance(t1->sub->se, t2)) / 4;
	}

	/* t1 = NODE / t2 = NODE */
	else if (is_node(t1) && is_node(t2)) {
		dist += (compare_distance(t1->sub->no, t2->sub->no) +
		 		 compare_distance(t1->sub->ne, t2->sub->ne) +
		 		 compare_distance(t1->sub->so, t2->sub->so) +
				 compare_distance(t1->sub->se, t2->sub->se)) / 4;
	}

	return dist;
}

/* ------------------------------------------------------------------ */
/* Compare 2 subtree by first comparing their average color, then their distance between each other.
	   If they are close enough (dist <= DIST_MAX), we make t2 points at t1, and free the old t2 we don't need anymore */ 
static void compare_subtree(Tree **parent, Tree **t1, Tree **t2, Kid_type type1, Kid_type type2) {
	/* If t1 and t2 have a close average color, we check if they also have a small distance between each other/
	   If they do, we change parent leafs : we point both t1 and t2 at the same subtree, and we free the one we don't need anymore */
	if (close_color((*t1)->sub->color, (*t2)->sub->color)) {
		if (compare_distance((*t1), (*t2)) <= DIST_MAX) {
			/* temp = (*t2); */
			free_tree((*t2));
			free((*t2));
			if (type1 == NO && type2 == NE) {
				(*parent)->sub->ne = (*parent)->sub->no;
			}

			else if (type1 == NO && type2 == SE) {
				(*parent)->sub->se = (*parent)->sub->no;
			}

			else if (type1 == NO && type2 == SO) {
				(*parent)->sub->so = (*parent)->sub->no;
			}

			else if (type1 == NE && type2 == SE) {
				(*parent)->sub->se = (*parent)->sub->ne;
			}

			else if (type1 == NE && type2 == SO) {
				(*parent)->sub->so = (*parent)->sub->ne;
			}

			else if (type1 == SE && type2 == SO) {
				(*parent)->sub->so = (*parent)->sub->se;
			}
		}
	}
}

/* ------------------------------------------------------------------ */
/* In this minimize function, for each node, we check if its leafs are close enough (distance <= DIST_MAX) 
	   If they are, we make t2 points at t1, and free the old t2 we don't need anymore */ 
static void minimize_loss_fuse_identical_subtree(Tree **t) {
	/* If "t" is a node, we compare all its leafs with each other 
	   in order to check if they have a small distance between each other */
	if ((*t)->type == NODE) {
		/* Comparing NO with other leafs */
		compare_subtree(t, &(*t)->sub->no, &(*t)->sub->ne, NO, NE);
		compare_subtree(t, &(*t)->sub->no, &(*t)->sub->se, NO, SE);
		compare_subtree(t, &(*t)->sub->no, &(*t)->sub->so, NO, SO);

		/* Comparing NE with other leafs 
		   However, first we check if NE != NO : if we didn't, we would do the same thing as above. 
		   Also, if NO == NE == SE == SO, freeing the leaf we don't need anymore would trigger an error */
		if ((*t)->sub->ne != (*t)->sub->no) {
			compare_subtree(t, &(*t)->sub->ne, &(*t)->sub->se, NE, SE);
			compare_subtree(t, &(*t)->sub->ne, &(*t)->sub->so, NE, SO);
		}
		
		/* Comparing SE and SO leafs
		   Same as NE, we first check if SE != NO and SE != NE */
		if ((*t)->sub->se != (*t)->sub->no && (*t)->sub->se != (*t)->sub->so) {
			compare_subtree(t, &(*t)->sub->se, &(*t)->sub->so, SE, SO);
		}


		/* Minimizing t's leafs */
		minimize_loss_fuse_identical_subtree(&(*t)->sub->no);

		/* Before minimizing other leafs, we check if a leaf isn't the same as the other leaf we have minimize so far : 
		   if the leaf is the same as a previous leaf we already minimize, we don't need to minimize it */
		if ((*t)->sub->ne != (*t)->sub->no) {
			minimize_loss_fuse_identical_subtree(&(*t)->sub->ne);
		}

		if ((*t)->sub->se != (*t)->sub->no && (*t)->sub->se != (*t)->sub->ne) {
			minimize_loss_fuse_identical_subtree(&(*t)->sub->se);
		}

		if ((*t)->sub->so != (*t)->sub->no && (*t)->sub->so != (*t)->sub->ne && (*t)->sub->so != (*t)->sub->se) {
			minimize_loss_fuse_identical_subtree(&(*t)->sub->so);
		}
	}
}

/* ------------------------------------------------------------------ */

void minimize_loss(Tree **t, const MLV_Image *image, Zone zone) {
	printf("Minimisation (with loss) Step 1 : Removing small errors from quadtree... ");
	minimize_loss_remove_small_errors(t, image, zone);
	printf("Done.\n");

	printf("Minimisation (with loss) Step 2 : Fusing identical subtrees... ");
	minimize_loss_fuse_identical_subtree(t);
	printf("Done.\n");
}

/* ------------------------------------------------------------------ */
