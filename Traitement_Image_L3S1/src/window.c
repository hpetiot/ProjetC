#include <stddef.h>
#include <stdio.h>

#include <MLV/MLV_all.h>

#include "button.h"
#include "io.h"
#include "window.h"

/*
This function initialise all variales needed for future handling of window informations
	Params:
		info -> a pointer on the structue holding all the information.
	Returns
		Nothing.
*/
void init_window_informations(Win* info){
	info->nb_button = 0;
	info->padding_menu_area = 10;
	info->padding_image_area = 10;
	info->button_array = NULL;
	info->size_x = SIZE_IMAGE + info->padding_menu_area*2 + info->padding_image_area * 2 + BTN_WIDTH;
	info->size_y = SIZE_IMAGE + info->padding_image_area * 2;
	info->img = NULL;
	info->text_input = NULL;
}

/*
This function places all buttons in the window and intialises them their base apearence.
It allocates memory on the 'button_array' field and updates 'nb_button' accordingly.
	Params:
		info -> a pointer on the structure holding all window information.
	Returns:
		0 -> Memory allocation error.
		1 -> All good.
*/
int place_element_in_window(Win* info){
	int res = 0;
	int menu_v_align = SIZE_IMAGE + info->padding_image_area*2 + info->padding_menu_area;

	res += add_button(
					menu_v_align,
					(info->padding_menu_area + BTN_HEIGHT)*info->nb_button + info->padding_image_area,
					BTN_HEIGHT,
					BTN_WIDTH,
					BTN_TXT_1,
					&(info->nb_button),
					&(info->button_array));

	res += add_button(
					menu_v_align,
					(info->padding_menu_area + BTN_HEIGHT)*info->nb_button + info->padding_image_area,
					BTN_HEIGHT,
					BTN_WIDTH,
					BTN_TXT_2,
					&(info->nb_button),
					&(info->button_array));

	res += add_button(
					menu_v_align,
					(info->padding_menu_area + BTN_HEIGHT)*info->nb_button + info->padding_image_area,
					BTN_HEIGHT,
					BTN_WIDTH,
					BTN_TXT_3,
					&(info->nb_button),
					&(info->button_array));

	res += add_button(
					menu_v_align,
					(info->padding_menu_area + BTN_HEIGHT)*info->nb_button + info->padding_image_area,
					BTN_HEIGHT,
					BTN_WIDTH,
					BTN_TXT_4,
					&(info->nb_button),
					&(info->button_array));

	res += add_button(
					menu_v_align,
					(info->padding_menu_area + BTN_HEIGHT)*info->nb_button + info->padding_image_area,
					BTN_HEIGHT,
					BTN_WIDTH,
					BTN_TXT_5,
					&(info->nb_button),
					&(info->button_array));

	res += add_button(
					menu_v_align,
					(info->padding_menu_area + BTN_HEIGHT)*info->nb_button + info->padding_image_area,
					BTN_HEIGHT,
					BTN_WIDTH,
					BTN_TXT_6,
					&(info->nb_button),
					&(info->button_array));
	res += add_button(
					menu_v_align,
					(info->padding_menu_area + BTN_HEIGHT)*info->nb_button + info->padding_image_area,
					BTN_HEIGHT,
					BTN_WIDTH,
					BTN_TXT_7,
					&(info->nb_button),
					&(info->button_array));
	res += add_button(
					menu_v_align,
					(info->padding_menu_area + BTN_HEIGHT)*info->nb_button + info->padding_image_area,
					BTN_HEIGHT,
					BTN_WIDTH,
					BTN_TXT_8,
					&(info->nb_button),
					&(info->button_array));
	res += add_button(
					menu_v_align,
					(info->padding_menu_area + BTN_HEIGHT)*info->nb_button + info->padding_image_area,
					BTN_HEIGHT,
					BTN_WIDTH,
					BTN_TXT_9,
					&(info->nb_button),
					&(info->button_array));
	if (res < 0)
		return 0;
	return 1;
}

/*
This function goes throught the liste of recent events and updated the window  buttons accordingly  using 'button_update' (button.c).
	Params:
		info -> a pointer on the structure holding all window information.
		mouse -> a pointer on a structure to store all mouse relvent informations.
	Returns:
		info.nb_button -> no event affecting the window buttons found.
		[0; nb_button[ -> the numbre in the button_array field of info corresponding to the affected button.
*/
int update_event(Win* info, Mouse *mouse){
	int value;
	int return_value =info->nb_button;
	MLV_Keyboard_button key_sym;
	MLV_Keyboard_modifier key_mod;
	int unicode;
	char *text;
	MLV_Input_box *input_box;
	MLV_Event ev;

	do {
		ev = MLV_get_event(&key_sym, &key_mod, &unicode, &text, &input_box, &(mouse->x), &(mouse->y), &(mouse->button), &(mouse->state));
		value = button_update(mouse, info->button_array, info->nb_button, ev);
		if (value != info->nb_button){
			return_value = value;
		}
	} while (ev != MLV_NONE);

	return return_value;
}

/*
This function displays all elements in the window.
	Paramas:
		info -> a pointer on the structure holding all window-relevent infromation.
	Returns:
		Nothing.
*/
void display_base_window(Win* info){
	display_all_button(info->nb_button, info->button_array);

	if(info->img != NULL){
		MLV_draw_image(info->img, info->padding_image_area, info->padding_image_area);
	}
}

