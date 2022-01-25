#define _GNU_SOURCE

#include <MLV/MLV_all.h>
#include <stdio.h>
#include <stdlib.h>

#include "button.h"
#include "window.h"

int add_button(int tl_x, int tl_y, int height, int width, const char* name, int* nb_button, Button** array){

	if (NULL == (*array = (Button *)reallocarray(*array, *nb_button + 1, sizeof(Button))))
		return -1;
	
	if (NULL == (((*array)[*nb_button]).name = (char *)malloc(strlen(name) + 1)))
		return -1;

	((*array)[*nb_button]).box.top_left_x = tl_x;
	((*array)[*nb_button]).box.top_left_y = tl_y;
	((*array)[*nb_button]).box.width = width;
	((*array)[*nb_button]).box.height = height;
	((*array)[*nb_button]).state = AVAILABLE;

	strcpy(((*array)[*nb_button]).name, name);

	*nb_button += 1;

	return 0;
}

void free_button_array(int nb_button, Button **array){
	int i;

	for (i = 0; i  < nb_button; i++){
		free((*array)[i].name);
	}
	free(*array);
}

static void dispaly_button(Button *btn_ptr){
	switch(btn_ptr->state){
			case BUISY: MLV_draw_text_box(
										btn_ptr->box.top_left_x,
										btn_ptr->box.top_left_y,
										btn_ptr->box.width,
										btn_ptr->box.height,
										btn_ptr->name,
										0,
										BTN_BODER_BUISY,
										BTN_TEXT_BUISY,
										BTN_BG_BUISY,
										MLV_HORIZONTAL_CENTER,
										MLV_VERTICAL_CENTER,
										MLV_TEXT_CENTER
										); break;
			case HELD: MLV_draw_text_box(
										btn_ptr->box.top_left_x,
										btn_ptr->box.top_left_y,
										btn_ptr->box.width,
										btn_ptr->box.height,
										btn_ptr->name,
										0,
										BTN_BODER_HELD,
										BTN_TEXT_HELD,
										BTN_BG_HELD,
										MLV_HORIZONTAL_CENTER,
										MLV_VERTICAL_CENTER,
										MLV_TEXT_CENTER
										); break;
			case HOVER: MLV_draw_text_box(
										btn_ptr->box.top_left_x,
										btn_ptr->box.top_left_y,
										btn_ptr->box.width,
										btn_ptr->box.height,
										btn_ptr->name,
										0,
										BTN_BODER_HOVER,
										BTN_TEXT_HOVER,
										BTN_BG_HOVER,
										MLV_HORIZONTAL_CENTER,
										MLV_VERTICAL_CENTER,
										MLV_TEXT_CENTER
										); break;
			case AVAILABLE: MLV_draw_text_box(
											btn_ptr->box.top_left_x,
											btn_ptr->box.top_left_y,
											btn_ptr->box.width,
											btn_ptr->box.height,
											btn_ptr->name,
											0,
											BTN_BODER_AVAILABLE,
											BTN_TEXT_AVAILABLE,
											BTN_BG_AVAILABLE,
											MLV_HORIZONTAL_CENTER,
											MLV_VERTICAL_CENTER,
											MLV_TEXT_CENTER
											); break;
		}
}

void display_all_button(int nb_button, Button* array){
	int i;
	Button* btn_ptr = NULL;

	if (! nb_button){
		return;
	}

	for (i = 0; i < nb_button; i++){
		btn_ptr = &(array[i]);
		dispaly_button(btn_ptr);
	}
	return;
}

void print_box(Box *box){
	printf("box: {x= %d, y= %d, height= %d, width= %d}\n", box->top_left_x, box->top_left_y, box->height, box->width);
}

void print_btn_state(Button_state state){
	printf("state:");
		switch(state){
			case BUISY: printf("buisy\n"); break;
			case HELD: printf("held\n"); break;
			case AVAILABLE: printf("available\n"); break;
			case HOVER: printf("hover\n"); break;
		}
}

void print_button(Button *btn){
	printf("\nbutton: {\n");
	print_box(&(btn->box));
	printf("name: \"%s\"\n", btn->name);
	print_btn_state(btn->state);
	printf("}\n");
}

void print_all_button(int nb_button, Button* array){
	int i;
	if (! nb_button){
		printf("no buttons found\n");
		return;
	}

	for (i = 0; i < nb_button; i++){
		print_button(&(array[i]));
	}
	return;
}

int button_on(int mouse_x, int mouse_y, Button* btn){
	if (mouse_x >= btn->box.top_left_x && mouse_x <= (btn->box.top_left_x + btn->box.width))
		if (mouse_y >= btn->box.top_left_y && mouse_y <= (btn->box.top_left_y + btn->box.height))
			return 1;
	return 0;
}

int button_update_clic(Mouse *mouse, Button* array, int nb_button){
	int i;

	if (mouse->state == MLV_RELEASED){
		for(i = 0; i < nb_button; i++){
			if (array[i].state == HELD){
				array[i].state = AVAILABLE;
				if (button_on(mouse->x, mouse->y, &(array[i]))){
					return i;
				}
			}
		}
	}

	if (mouse->state == MLV_PRESSED){
		for (i = 0; i< nb_button; i++){
			if (button_on(mouse->x, mouse->y, &(array[i])))
				if (array[i].state == AVAILABLE || array[i].state == HOVER){
					array[i].state = HELD;
					break;
				}
		}
	}
	return nb_button;
}

void button_update_move(Mouse *mouse, Button* array, int nb_button){
	int i; 

	for (i = 0; i < nb_button; i++){
		if (button_on(mouse->x, mouse->y, &(array[i]))){
			if (array[i].state == AVAILABLE){
				array[i].state = HOVER;
			}
		}
		else{
			if (array[i].state == HOVER)
				array[i].state = AVAILABLE;
		}
	}
}

int button_update(Mouse *mouse, Button* array, int nb_button, const MLV_Event ev){
	int value;
	if (ev == MLV_MOUSE_BUTTON && mouse->button == MLV_BUTTON_LEFT){
		value = button_update_clic(mouse, array, nb_button);
		return value;
	}

	if (ev == MLV_MOUSE_MOTION){
		button_update_move(mouse, array, nb_button);
	}
	return nb_button;
}