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
	Tree *tree = NULL;
	Verssion verssion;
	int last_btn_hit;

	init_window_informations(&info);
	MLV_create_window("test", "test", info.size_x, info.size_y);

	MLV_change_frame_rate(60);

	initialize_firstlast(&list_firstlast);

	if (place_element_in_window(&info) == 0){
		fprintf(stderr, "error while creating buttons, quitting.\n");
		MLV_free_window();
		return 0;
	}
	set_button_state_no_image(info.button_array);
	display_base_window(&info);

	while(1){

		last_btn_hit = update_event(&info, &mouse);

		if (info.nb_button != last_btn_hit){
			(info.button_array[last_btn_hit]).state = BUISY;
		
		
			if (link_btn(last_btn_hit, &info, &tree, &list_firstlast, &verssion) == 2)
				break;

			if ((info.button_array[last_btn_hit]).state != FORBIDEN)
				(info.button_array[last_btn_hit]).state = AVAILABLE;
		}
		MLV_clear_window(MLV_COLOR_BLACK);
		display_base_window(&info);

		MLV_update_window();
		MLV_delay_according_to_frame_rate();
	}

	if(info.img != NULL)
		MLV_free_image(info.img);
	if (info.text_input != NULL)
		free(info.text_input);

	if (tree != NULL)
		free_tree(tree);

	free_button_array(info.nb_button, &(info.button_array));

	MLV_free_window();
	return 0;
}