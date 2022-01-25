#include <stdio.h>

#include <MLV/MLV_all.h>

#include "create_quadtree.h"
#include "io.h"
#include "list_errors.h"
#include "quadtree.h"
#include "window.h"

int main(void){

	Win info;
	Mouse mouse;
	ErrorList_FirstLast list_firstlast;
	MLV_Image *image_tree;
	Tree *tree = NULL;
	int last_btn_hit;

	init_window_informations(&info);
	MLV_create_window("test", "test", info.size_x, info.size_y);

	MLV_change_frame_rate(60);

	info.img = MLV_load_image("./img/panda.png");
	initialize_firstlast(&list_firstlast);

	place_element_in_window(&info);
	display_base_window(&info);

	if (!create_quadtree(&tree, info.img, &list_firstlast)) {
		fprintf(stderr, "Error in image_to_quadtree\n");
		exit(EXIT_FAILURE);
	}

	if (!tree_to_image(&(info.img), tree)) {
		fprintf(stderr, "convention error\n");
		exit(EXIT_FAILURE);
	}

	if (info.img == NULL)
		printf("\nwon't work!!\n");

	while(1){

		last_btn_hit = update_event(&info, &mouse);

		(info.button_array[last_btn_hit]).state = BUISY;
		
		link_btn(last_btn_hit, info, &tree);
		(info.button_array[last_btn_hit]).state = AVAILABLE;

		MLV_clear_window(MLV_COLOR_BLACK);
		display_base_window(&info);

		MLV_update_window();
		MLV_delay_according_to_frame_rate();
	}
	MLV_free_image(info.img);
	free_button_array(info.nb_button, &(info.button_array));
	MLV_free_window();
	return 0;
}