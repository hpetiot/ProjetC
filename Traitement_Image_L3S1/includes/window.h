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
	char* text_input;
	Button *button_array;
} Win;
/**
*This function initialise all variales needed for future handling of window informations
*	@param info a pointer on the structue holding all the information.
*	@return Nothing.
*/
void init_window_informations(Win* info);

/**
*This function places all buttons in the window and intialises them their base apearence.
*It allocates memory on the 'button_array' field and updates 'nb_button' accordingly.
*	@param info a pointer on the structure holding all window information.
*	@return
*		0: Memory allocation error.
*		1: All good.
*/
int place_element_in_window(Win* info);

/**
*This function displays all elements in the window.
*	@param info a pointer on the structure holding all window-relevent infromation.	
*	@return Nothing.
*/
void display_base_window(Win* info);

/**
*This function goes throught the liste of recent events and updated the window  buttons accordingly  using 'button_update' (button.c).
*	@param info a pointer on the structure holding all window information.
*	@param mouse -> a pointer on a structure to store all mouse relvent informations.
*	@return
*		info.nb_button -> no event affecting the window buttons found.
*		[0; nb_button[ -> the numbre in the button_array field of info corresponding to the affected button.
*/
int update_event(Win* info, Mouse *mouse);

#endif