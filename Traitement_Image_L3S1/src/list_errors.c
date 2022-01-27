#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "list_errors.h"

/* ------------------------------------------------------------------ */

void initialize_firstlast(ErrorList_FirstLast *list) {
	list->first = NULL;
	list->last = NULL;
}

/* ------------------------------------------------------------------ */

void free_error_list(ErrorList *list) {
	ErrorListElement *temp = *list;

	while (temp != NULL) {
		(*list) = (*list)->next;
		free(temp);
		temp = NULL;
		temp = (*list);
	}
}

/* ------------------------------------------------------------------ */

void print_error_list(ErrorList *list) {
	ErrorListElement *temp;

	temp = (*list);

	if ((*list) == NULL) {
		printf("ErrorList is empty\n");
	}

	/* Print the color_error of the element. 
	   Also print the previous and next color_error of the current element. */
	while (temp != NULL) {
		if (temp->prev != NULL) {
			printf("(prev = %f), ", temp->prev->error);
		}

		printf("%f", temp->error);

		if (temp->next != NULL) {
			printf(", (next = %f)", temp->next->error);
		}

		printf("\n");

		temp = temp->next;
	}
}

/* ------------------------------------------------------------------ */
/* Allocate a new element for an ErrorListElement */
static int new_elem_error_list(ErrorListElement **new, Tree *leaf, Zone zone) {
	(*new) = (ErrorListElement*) malloc(sizeof(ErrorListElement));

	if ((*new) == NULL) {
		return -1;
	}

	(*new)->leaf = leaf;
	(*new)->prev = NULL;
	(*new)->next = NULL;
	(*new)->error = leaf->color_error;
	(*new)->zone = zone;

	return 1;
}

/* ------------------------------------------------------------------ */
/* Add an element in the first position of the list */
static int add_front_list(ErrorList *first, Tree *leaf, Zone zone) {
	ErrorListElement *new = NULL;
	
	if (new_elem_error_list(&new, leaf, zone) < 0) {
		return -1;
	}

	new->next = *first;
	*first = new;
	if ((*first)->next != NULL) {
		(*first)->next->prev = (*first);
	}

	return 1;
}

/* ------------------------------------------------------------------ */
/* Add Any Order */
static int add_any_order_list(ErrorList *list, Tree *leaf, Zone zone) {
	ErrorListElement *new = NULL;
	ErrorListElement *temp = *list;
	if (new_elem_error_list(&new, leaf, zone) < 0) {
		return -1;
	}

	/* We add the element backward : we have more chance to add a new
	   element at the end of the list because it's a new leaf, it has more chance to have a small color_error */ 
	while (temp->prev != NULL) {
		if (temp->prev->error >= leaf->color_error) {
			/* Changing next and prev of the new elem we are adding */
			new->next = temp;
			new->prev = temp->prev;

			/* Changing next of the prev elem (prev of the new element) */
			new->prev->next = new;

			/* Changing prev of the next elem (next of the new element) */
			new->next->prev = new;

			return 1;
		}

		temp = temp->prev;
	}

	return 1;
}

/* ------------------------------------------------------------------ */
/* Add an element in the last position of the list  */
static int add_end_list(ErrorList *last, Tree *leaf, Zone zone) {
	ErrorListElement *new = NULL;
	
	if (new_elem_error_list(&new, leaf, zone) < 0) {
		return -1;
	}

	new->prev = (*last);
	(*last)->next = new;
	(*last) = new;

	return 1;
}

/* ------------------------------------------------------------------ */

int add_elem(ErrorList *first, ErrorList *last, Tree *leaf, Zone zone) {
	ErrorListElement *new = NULL;

	/* list empty */
	if (*first == NULL) {
		if (new_elem_error_list(&new, leaf, zone) < 0) {
			return -1;
		}

		*first = new;
		*last = *first;
		/* (*first)->prev = NULL; */
	}

	/* Adding new element at the front of the list */
	else if (leaf->color_error >= (*first)->error) {
		return add_front_list(first, leaf, zone);
	}
	
	/* Adding new element at the end of the list */
	else if (leaf->color_error <= (*last)->error) {
		return add_end_list(last, leaf, zone);
	}

	/* Adding new element in the list (anywhere) */
	else {
		return add_any_order_list(last, leaf, zone);
	}

	return 0;
}


/* ------------------------------------------------------------------ */

int remove_elem_errorlist(ErrorList *list,  double error) {
	ErrorListElement *temp = *list;
	ErrorListElement *temp2;

	if (*list == NULL) {
		return -1;
	}

	/* If the first element is the one we are looking for */
	if (temp->error == error) {
		temp = (*list);
		(*list) = (*list)->next;
		free(temp);
		temp = NULL;

		return 0;
	}
	
	/* In case the first element wasn't the one we were looking for 
	   (extremely rare, but happens somtimes) */
	while (temp != NULL) {
		if (temp->error == error) {
			temp2 = temp;
			temp->prev->next = temp->next;

			/* If temp->next is NULL, it wouldn't work */
			if (temp->next != NULL) {
				temp->next->prev = temp->prev;
			}

			free(temp2);
			temp2 = NULL;

			return 0;
		}
		
		temp = temp->next;
	}

	return -2;
}

/* ------------------------------------------------------------------ */