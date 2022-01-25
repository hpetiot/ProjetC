#ifndef __LIST_ERRORS_H__
#define __LIST_ERRORS_H__

/* ------------------------------------------------------------------ */
	
	#include "quadtree.h"
	#include "zone.h"

	typedef struct ErrorListElement {
		Tree 							*leaf;
		struct ErrorListElement 		*prev;
		struct ErrorListElement 		*next;
		double 							error;
		Zone							zone;
	} ErrorListElement, *ErrorList;

	typedef struct ErrorList_FirstLast {
		ErrorList 				first;
		ErrorList 				last;
	} ErrorList_FirstLast;

/* ------------------------------------------------------------------ */
	
	/* Initialize an ErrorList_FirstLast (NULL) */
	int initialize_firstlast(ErrorList_FirstLast *firstlast_list);

	/* Allocate a new element for an ErrorListElement */
	int new_elem_error_list(ErrorListElement **new, Tree *leaf, Zone zone);

	/* Free an ErrorListElement */
	void free_error_list(ErrorList *list);

	/* Print an ErrorListElement */
	void print_error_list(ErrorList *list);

	/* Add an element in the first position of the list */
	int add_front_list(ErrorList *list, Tree *leaf, Zone zone);

	/* Add Any Order */
	int add_any_order_list(ErrorList *list, Tree *leaf, Zone zone);

	/* Add an element in the last position of the list  */
	int add_end_list(ErrorList *list, Tree *leaf, Zone zone);

	/* Add an element in an ErrorList */
	int add_elem(ErrorList *list, ErrorList *last, Tree *leaf, Zone zone);

	/* Remove an element from ErrorList.
	   The element we are looking has an error equals to "error" in parameters */
	int remove_elem_errorlist(ErrorList *list, double error);

/* ------------------------------------------------------------------ */

#endif