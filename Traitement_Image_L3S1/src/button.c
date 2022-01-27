#define _GNU_SOURCE

#include <MLV/MLV_all.h>
#include <stdio.h>
#include <stdlib.h>

#include "button.h"
#include "window.h"

/*
This function adds a button to the window.
any number of call to this function must be matched by 1 call to 'free_button_array'
note: this function uses the "reallocarray" function (cf man 3 malloc), on available on debian10 "buster".
	Params:
		tl_x -> an int giving the horizontal coordinate of the top left corner of the button.
		tl_y -> an int giving the vertical coordinatte of the top left corner of the button.
		height -> an int giving the height of the button.
		width -> an int giving the width of the button.
		name -> a constant character strung that will be displayed in the middle of the button.
		nb_button -> a pointer on the number of button held in the window managment structure.
		array -> a pointer on the array of button held in the window managment structure.
	Returns:
		0 -> alll good
		-1 -> memory allocation error.
*/
int add_button(int tl_x, int tl_y, int height, int width, const char* name, int* nb_button, Button** array){

	if (NULL == (*array = (Button *)realloc(*array, (*nb_button + 1) * sizeof(Button))))
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

/*
This function frees the buttons allocated by 'add_button'.
	Params:
		nb_button -> the number of buttons in the array.
		array -> a pointer on the array holding the buttons.
	Returns:
		Nothing.
*/
void free_button_array(int nb_button, Button **array){
	int i;

	for (i = 0; i  < nb_button; i++){
		free((*array)[i].name);
	}
	free(*array);
}

/*
This function displays 1 button according to its 'state' field.
	Param:
		btn_ptr -> a pointer on the structure holding all button-relevent information.
	Return:
		Nothing.
*/
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
			case FORBIDEN: MLV_draw_text_box(
											btn_ptr->box.top_left_x,
											btn_ptr->box.top_left_y,
											btn_ptr->box.width,
											btn_ptr->box.height,
											btn_ptr->name,
											0,
											BTN_BODER_FORBIDEN,
											BTN_TEXT_FORBIDEN,
											BTN_BG_FORBIDEN,
											MLV_HORIZONTAL_CENTER,
											MLV_VERTICAL_CENTER,
											MLV_TEXT_CENTER
											); break;
		}
}

/*
This function displays the buttons according to their 'state' field.
	Params:
		nb_button -> the number of button in the array.
		array -> the array holding the buttons.
	Returns:
		Nothing.
*/
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

/*
This function prints all inforamtion about the 'box' of the button.
	Params:
		box -> a pointer on the structure holding the position and size of the button.
	Returns
		nothing.
*/
static void print_box(Box *box){
	printf("box: {x= %d, y= %d, height= %d, width= %d}\n", box->top_left_x, box->top_left_y, box->height, box->width);
}

/*
This function prints the state of the button.
	Param:
		state -> enumeration member indicationg a state of button.
	Returns:
		nothing.
*/
static void print_btn_state(Button_state state){
	printf("state:");
		switch(state){
			case BUISY: printf("buisy\n"); break;
			case HELD: printf("held\n"); break;
			case AVAILABLE: printf("available\n"); break;
			case HOVER: printf("hover\n"); break;
			case FORBIDEN: printf("forbiden\n"); break;
		}
}

void print_button(Button *btn){
	printf("\nbutton: {\n");
	print_box(&(btn->box));
	printf("name: \"%s\"\n", btn->name);
	print_btn_state(btn->state);
	printf("}\n");
}

/*
This function print all button in the array in the console. It is meant for debugging.
	Params:
		nb_button -> the number of button in the array.
		array -> the array holding the buttons.
	Returns:
		nothing.
*/
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

/*
This function checks if the coordinates of the mose pointer place on a given button.
	Params:
		mouse_x -> the horizontal coordinate of the button.
		mouse_y -> the vertical coordinate of the button.
		btn -> a pointer on the structure holding all button-relevent information.
	Returns:
		0 -> the mouse pointer is not on the give button.
		1 -> the mouse pointer is on the given button.
*/
int button_on(int mouse_x, int mouse_y, Button* btn){
	if (mouse_x >= btn->box.top_left_x && mouse_x <= (btn->box.top_left_x + btn->box.width))
		if (mouse_y >= btn->box.top_left_y && mouse_y <= (btn->box.top_left_y + btn->box.height))
			return 1;
	return 0;
}

/*
This function checks if a  button has been pressed or realeased and updates its state accordingly.
	Params:
		mouse -> a pointer on the structure holding all mouse-relevent information.
		array -> the array containing all buttons.
		nb_button -> the number of button contained in the array.
	Returns:
		nb_button -> nothing was clicked.
		[0; nb_button[ -> the index of the click button in 'array'.
*/
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

	else if (mouse->state == MLV_PRESSED){
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

/*
This function checks if the mous is simply hovering above a button and changes said button's state accordingly.
	Params:
		mouse -> a pointer on the structure holding all mouse-relevent information.
		array -> the array containing all buttons.
		nb_button -> the number of button contained in the array.
	Returns:
		Nothing.
*/
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

/*
This function updates the state of the button acording to the mouse events.
	Params:
		mouse -> a pointer on the structure holding all mouse information.
		array -> the array holding the buttons.
		nb_button -> the number of button in the array.
		ev -> the type of mouse event found.
	Returns:
		nb_button -> no clic happened.
		[0; nb_button[ -> the designeated member of array was clicked.
*/
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