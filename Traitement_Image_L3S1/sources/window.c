#include <stddef.h>
#include <stdio.h>

#include <MLV/MLV_all.h>

#include "button.h"
#include "window.h"

void init_window_informations(Win* info){
	info->nb_button = 0;
	info->padding_menu_area = 10;
	info->padding_image_area = 10;
	info->button_array = NULL;
	info->size_x = SIZE_IMAGE + info->padding_menu_area*2 + info->padding_image_area * 2 + BTN_WIDTH;
	info->size_y = SIZE_IMAGE + info->padding_image_area * 2;
	info->img = NULL;
}

void place_element_in_window(Win* info){
	int res = 0;
	int menu_v_align = SIZE_IMAGE + info->padding_image_area*2 + info->padding_menu_area;

	res += add_button(
					menu_v_align,
					(info->padding_menu_area + BTN_HEIGHT)*info->nb_button + info->padding_image_area,
					BTN_HEIGHT,
					BTN_WIDTH,
					"test 1",
					&(info->nb_button),
					&(info->button_array));

	res += add_button(
					menu_v_align,
					(info->padding_menu_area + BTN_HEIGHT)*info->nb_button + info->padding_image_area,
					BTN_HEIGHT,
					BTN_WIDTH,
					"test 2",
					&(info->nb_button),
					&(info->button_array));

	res += add_button(
					menu_v_align,
					(info->padding_menu_area + BTN_HEIGHT)*info->nb_button + info->padding_image_area,
					BTN_HEIGHT,
					BTN_WIDTH,
					"test 3",
					&(info->nb_button),
					&(info->button_array));
}

void update_event(Win* info, Mouse *mouse){
	MLV_Keyboard_button key_sym;
	MLV_Keyboard_modifier key_mod;
	int unicode;
	char *text;
	MLV_Input_box *input_box;
	MLV_Event ev;

	do {
		ev = MLV_get_event(&key_sym, &key_mod, &unicode, &text, &input_box, &(mouse->x), &(mouse->y), &(mouse->button), &(mouse->state));
		button_update(mouse, info->button_array, info->nb_button, ev);
	} while (ev != MLV_NONE);
}

void display_base_window(Win* info){
	display_all_button(info->nb_button, info->button_array);
	MLV_draw_image(info->img, info->padding_image_area, info->padding_image_area);
}

