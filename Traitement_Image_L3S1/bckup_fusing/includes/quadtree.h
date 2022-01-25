#ifndef __QUADTREE_H__
#define __QUADTREE_H__

/* ------------------------------------------------------------------ */

	#include <MLV/MLV_color.h>
	#include <MLV/MLV_image.h>

	#define SIZE_IMAGE 512
	#define NB_SHARES 131072
 
/* ------------------------------------------------------------------ */

	typedef enum {
		LEAF,
		NODE
	} Node_type;

	typedef enum {
		NO,
		NE,
		SO,
		SE
	} Kid_type;

	typedef union {
		struct {
			struct quad* no;
			struct quad* ne;
			struct quad* so;
			struct quad* se;
		};

		MLV_Color color;
	} Sub_tree;

	typedef struct quad{
		Node_type type;
		Sub_tree* sub;
		double color_error;

		int node_num;
		int is_a_copy;
	} Tree;

/* ------------------------------------------------------------------ */
	/* TEMP */
	void nb_node_leaf(Tree *t);
	void print_nb_node_leaf(Tree *t);

	int is_leaf(Tree *t);
	int has_full_leaf(Tree *t);
	int is_node(Tree *t);

	void free_tree(Tree *t);
	void free_all_leaf(Tree *t);

	void replace_node_to_leaf(Tree **node, Tree *leaf);

	void print_tree_prefix(Tree *t);
	void print_node(Tree* t);

	
	int tree_to_image(MLV_Image **img, Tree *t);




	int numbering_nodes_quadtree(Tree *t, int node_total);
	void print_node_num(Tree *t);
	void free_tree_exception(Tree *t, Tree *exception);

/* ------------------------------------------------------------------ */

#endif