#include <stdio.h>

#include <MLV/MLV_all.h>

#include "quadtree.h"
#include "window.h"

int main(void){

	Win info;
	Mouse mouse;
	Tree *t;

	init_window_informations(&info);
	MLV_create_window("test", "test", info.size_x, info.size_y);

	MLV_change_frame_rate(60);

	if (new_node(&t, MLV_COLOR_RED, MLV_COLOR_GREEN, MLV_COLOR_BLUE, MLV_COLOR_WHITE) < 0)
		fprintf(stderr, "mem error\n");

	if (leaf_to_node(t->sub->no, MLV_COLOR_RED, MLV_COLOR_GREEN, MLV_COLOR_BLUE, MLV_COLOR_WHITE) < 0)
		fprintf(stderr, "mem error\n");
	if (leaf_to_node(t->sub->ne, MLV_COLOR_RED, MLV_COLOR_GREEN, MLV_COLOR_BLUE, MLV_COLOR_WHITE) < 0)
		fprintf(stderr, "mem error\n");
	if (leaf_to_node(t->sub->so, MLV_COLOR_RED, MLV_COLOR_GREEN, MLV_COLOR_BLUE, MLV_COLOR_WHITE) < 0)
		fprintf(stderr, "mem error\n");
	if (leaf_to_node(t->sub->se, MLV_COLOR_RED, MLV_COLOR_GREEN, MLV_COLOR_BLUE, MLV_COLOR_WHITE) < 0)
		fprintf(stderr, "mem error\n");
	if (leaf_to_node(t->sub->se->sub->no, MLV_COLOR_RED, MLV_COLOR_GREEN, MLV_COLOR_BLUE, MLV_COLOR_WHITE) < 0)
		fprintf(stderr, "mem error\n");
	print_tree_prefix(t);

	if (!tree_to_image(&(info.img), t))
		fprintf(stderr, "convetion error\n");

	if (info.img == NULL)
		printf("\nwon't work!!\n");

	place_element_in_window(&info);

	while(1){
		update_event(&info, &mouse);
		MLV_clear_window(MLV_COLOR_BLACK);
		display_base_window(&info);
		MLV_update_window();
		MLV_delay_according_to_frame_rate();
	}
printf("there is no prey\n");
	MLV_free_image(info.img);
	free_button_array(info.button_array);
	MLV_free_window();
	return 0;
}