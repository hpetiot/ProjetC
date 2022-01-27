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
	
	/**
	* Initialize an ErrorList_FirstLast (NULL).
	* @param list The ErrorList_FirstLast we are initializing
	*/
	void initialize_firstlast(ErrorList_FirstLast *list);

	/**
	* Free an ErrorListElement.
	* @param list The list we are freeing
	*/
	void free_error_list(ErrorList *list);

	/**
	* Print an ErrorListElement.
	* @param list The list we are printing
	*/
	void print_error_list(ErrorList *list);

	/**
	* Add an element in an ErrorList.
	* @param list The list we are adding the element in
	* @param last Pointer of last element of list
	* @param leaf The leaf and its error we are adding
	* @param zone Leaf's zone in the image it's coming from
	* @return 1 we add leaf's and its error in list
	*		  0 otherwise (malloc pb)
	*/
	int add_elem(ErrorList *list, ErrorList *last, Tree *leaf, Zone zone);

	/**
	* Remove an element from ErrorList by looking at its error value.
	* @param list explication
	* @return -2 if we couldn't find the error value 
			  -1 if list is empty
			  0 if we removed an element
	*/
	int remove_elem_errorlist(ErrorList *list, double error);

/* ------------------------------------------------------------------ */

#endif