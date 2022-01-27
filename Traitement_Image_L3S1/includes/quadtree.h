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
	} Tree;

/* ------------------------------------------------------------------ */

	/**
	* Check if "t" is a leaf
	* @param t The tree we are looking at
	* @return 1 if "t" is a leaf
	*		  0 otherwise
	*/
	int is_leaf(Tree *t);

	/**
	* Check if "t" is a node
	* @param t The tree we are looking at
	* @return 1 if "t" is a node
	*		  0 otherwise
	*/
	int is_node(Tree *t);

	/**
	* Check if "t" is a node, and if NO, NE, SE and SO are leaf
	* @param t The tree we are looking at
	* @return 1 if "t" is a node with only leafs
	*		  0 otherwise
	*/
	int has_full_leaf(Tree *t);

	/**
	* Print a tree in prefix order
	* @param t The tree we'll print
	*/
	void print_tree_prefix(Tree *t);

	/**
	* Print a node
	* @param t The node we'll print
	*/
	void print_node(Tree* t);

	/**
	* Free a tree
	* @param t The tree we'll free
	*/
	void free_tree(Tree *t);

	/**
	* Free all t's leaf
	* @param t The tree we'll free
	*/
	void free_all_leaf(Tree *t);

	/**
	* Replace a node with a leaf
	* @param node The node we replace
	* @param leaf The leaf we take the fields from
	*/
	void replace_node_to_leaf(Tree **node, Tree *leaf);

	/**
	* Fill an image with a subtree
	* @param img The image we'll fill
	* @param t The tree we use to fill the image
	* @return 1 if we can fill the image
			  0 otherwise
	*/
	int tree_to_image(MLV_Image **img, Tree *t);

/* ------------------------------------------------------------------ */

#endif