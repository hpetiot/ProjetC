#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <MLV/MLV_image.h>

#include "button.h"

#define SIZE_IMAGE 512

#define BCK_GROUND_COLOR = MLV_COLOR_BLACK

typedef struct{
	int nb_button;
	int padding_image_area;
	int padding_menu_area;
	int image_tl_x;
	int image_tl_y;
	int size_x;
	int size_y;
	MLV_Image *img;
	Button *button_array;
} Win;

void init_window_informations(Win* info);
void place_element_in_window(Win* info);
void display_base_window(Win* info);
int update_event(Win* info, Mouse *mouse);

#endif