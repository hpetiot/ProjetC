#ifndef __QUADTREE_H__
#define __QUADTREE_H__

#include <MLV/MLV_color.h>

typedef enum {
LEAF,
NODE
} Node_type;


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
	Sub_tree* sub;
	Node_type type;
	double color_error;
} Tree;


void print_tree_prefix(Tree *t);
void print_node(Tree* t);
int new_leaf(Tree **t, MLV_Color color);
int new_node(Tree **t, MLV_Color color_no, MLV_Color color_ne, MLV_Color color_so, MLV_Color color_se);
int leaf_to_node(Tree *leaf, MLV_Color color_no, MLV_Color color_ne, MLV_Color color_so, MLV_Color color_se);
void free_tree(Tree *t);
int tree_to_image(MLV_Image **img, Tree *t);

#endif