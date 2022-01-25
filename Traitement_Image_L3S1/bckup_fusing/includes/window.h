#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <MLV/MLV_image.h>

#include "button.h"

#define SIZE_IMAGE 512

#define BCK_GROUND_COLOR = MLV_COLOR_BLACK


#define BTN_TXT_1 "quadtree approximation"
#define BTN_TXT_2 "save b&w binary"
#define BTN_TXT_3 "save rgba bianary"
#define BTN_TXT_4 "minimisation"
#define BTN_TXT_5 "save b&w graf"
#define BTN_TXT_6 "save rgba graf"
#define BTN_TXT_7 "open image"

typedef struct{
	int nb_button;
	int padding_image_area;
	int padding_menu_area;
	int image_tl_x;
	int image_tl_y;
	int size_x;
	int size_y;
	MLV_Image *img;
	char* text_input;
	Button *button_array;
} Win;

void init_window_informations(Win* info);
void place_element_in_window(Win* info);
void display_base_window(Win* info);
int update_event(Win* info, Mouse *mouse);

#endif