#include <stdio.h>

#include <MLV/MLV_all.h>

#include "quadtree.h"
#include "window.h"

int main(void){

	Win info;
	Mouse mouse;
	Tree *t;
	int last_btn_hit;

	init_window_informations(&info);
	MLV_create_window("test", "test", info.size_x, info.size_y);

	MLV_change_frame_rate(60);

	

	if (!tree_to_image(&(info.img), t))
		fprintf(stderr, "convetion error\n");

	if (info.img == NULL)
		printf("\nwon't work!!\n");

	place_element_in_window(&info);

	while(1){
		last_btn_hit = update_event(&info, &mouse);
		MLV_clear_window(MLV_COLOR_BLACK);
		display_base_window(&info);
		MLV_update_window();
		MLV_delay_according_to_frame_rate();
	}
printf("there is no prey\n");
	MLV_free_image(info.img);
	free_button_array(info.nb_button, &(info.button_array));
	MLV_free_window();
	return 0;
}