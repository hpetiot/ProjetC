#include <MLV/MLV_image.h>
#include <MLV/MLV_input_box>
#include <stdio.h>

#include "button.h"
#include "io.h"
#include "window.h"

int get_compatible_file_name(Win *info){
	int top_left_X = SIZE_IMAGE + info->padding_image_area*2 + info->padding_menu_area;
	int top_left_Y = (SIZE_IMAGE + info->padding_image_area*2) - (20 + 70);
	int sufix_result;


	MLV_wait_input_box(
			top_left_X,
			top_left_Y,
			top_left_X + BTN_WIDTH,
			top_left_Y + 20,
			BTN_BG_BUISY,
			BTN_BORDER_BUISY,
			MLV_COLOR_BLACK,
			"input image path",
			&(info->text_input)
		);
	sufix_result= check_txt_input(info->text_input)
	while (0 == suffix_result){
		MLV_wait_input_box(
			top_left_X,
			top_left_Y,
			top_left_X + BTN_WIDTH,
			top_left_Y + 20,
			BTN_BG_BUISY,
			BTN_BORDER_BUISY,
			MLV_COLOR_BLACK,
			"not compatible, retry",
			&(info->text_input)
		);
		sufix_result = check_txt_input(info->text_input);
	}
	return sufix_result;
}

int manage_image_input(Win *info, Tree **t){
	int image_type;
	image_type = get_compatible_file_name(info);
	

	switch(image_type){
		case 1:info->img = MLV_load_image(info->text_input); break;
		case 2:
		case 3:
		case 4:
		case 5:
		default: fprintf("unexpected error: image sufix passed screening but still unknown/unexpected stuff");
	}
	

}

int link_btn(int btn_number, Win info, Tree** t){
	MLV_clear_window(MLV_COLOR_BLACK);
	display_base_window(&info);

	MLV_update_window();	

	switch(btn_number){
		case 0: printf("pushed: %s\n", BTN_TXT_1);break; //"quadtree approximation"
		case 1: printf("pushed: %s\n", BTN_TXT_2);break; // "save b&w binary"
		case 2: printf("pushed: %s\n", BTN_TXT_3);break; // "save rgba bianary"
		case 3: printf("pushed: %s\n", BTN_TXT_4);break; // "minimisation"
		case 4: printf("pushed: %s\n", BTN_TXT_5);break; // "save b&w graf"
		case 5: printf("pushed: %s\n", BTN_TXT_6);break; // "save rgba graf" 
		case 6: printf("pushed: %s\n", BTN_TXT_7);break; // "open image"
		default: break;
	}
	return 0;
}

/*
	This function check the sufix of the given file name to indicate if the program should try to open it (and how) or discard it.
		Params:
			file_name -> a pointer on the first character composing the file name;
		Returns:
			0 -> Not accepted;
			1 -> Accepted, is a generic image and should be opened as such.
			2 -> Accepted, is a b&w quatree
			3 -> Accepted, is a color quadtree
			4 -> Accepted, is a b&w graph
			5 -> Accepted, is a color graph
*/
int check_txt_input(char* file_name){
	int position_point = strlen(file_name) - 1;
	char *sufix
	while(position_point > 0 && file_name[posisiton_point] != "."){
		position_point --;
	}
	sufix = file_name[position_point];
	if (strcmp(sufix, "jpeg") == 0)
		return 1;
	if (strcmp(sufix, "ico") == 0)
		return 1
	if (strcmp(sufix, "cur") == 0)
		return 1
	if (strcmp(sufix, "bmp") == 0)
		return 1
	if (strcmp(sufix, "pnm") == 0)
		return 1
	if (strcmp(sufix, "xpm") == 0)
		return 1
	if (strcmp(sufix, "lbm") == 0)
		return 1
	if (strcmp(sufix, "pcx") == 0)
		return 1
	if (strcmp(sufix, "gif") == 0)
		return 1
	if (strcmp(sufix, "tga") == 0)
		return 1
	if (strcmp(sufix, "tiff") == 0)
		return 1
	if (strcmp(sufix, "xv") == 0)
		return 1
	if (strcmp(sufix, "png") == 0)
		return 1;

	if (strcmp(sufix, "qtn") == 0)
		return 2;
	if (strcmp(sufix, "qtc") == 0)
		return 3;
	if (strcmp(sufix, "gmn") == 0)
		return 4;
	if (strcmp(sufix, "gmc") == 0)
		return 5;
	return 0;
}

