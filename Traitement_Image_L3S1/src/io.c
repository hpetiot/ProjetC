#include <MLV/MLV_image.h>
#include <MLV/MLV_input_box.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "button.h"
#include "create_quadtree.h"
#include "decoding_graph.h"
#include "decoding.h"
#include "encoding_graph.h"
#include "encoding.h"
#include "io.h"
#include "list_errors.h"
#include "minimisation.h"
#include "window.h"

/*
This function take the paht given by the user and attempts to detect the file's name within.
	Params:
		path -> the path to analyse.
		name -> a pointer on a pointer to a character. On succes, it will point to the 1st character composing the file's name.
	Returns:
		0 -> failed.
		1 -> worked.
*/
static int isolate_file_name_from_path(char *path, char **name){
	int i = strlen(path);

	while (i >= 0){
		if (path[i] == '/'){
			*name = &(path[i+1]);
			return 1;
		}
		i--;
	}
	return 0;
}

/*
This function creates the name of the file that will be saved.
note: this function's return has been malloc'ed!!
	Params:
		path -> a pointer on the path to the file used as a base to create the new one.
		save_type -> the type file we want to create.
	Returns:
		the name of the new file complete with appropriate extention.
*/
char *create_encoded_name(char *path, Button_fct save_type){
	int name_len;
	char *name_prefix = "./img/";
	char *new_name;
	char *old_name;

	if (! isolate_file_name_from_path(path, &old_name))
		old_name = path;

	name_len = strlen(old_name) + strlen(name_prefix) + 5;

	if (NULL != (new_name = (char *)malloc(sizeof(char) * name_len))){
		strcpy(new_name, name_prefix);
		strcat(new_name, old_name);
		switch(save_type){
			case GRAPH_BW: strcat(new_name, ".gmn"); break;
			case GRAPH_COLOR: strcat(new_name, ".gmc"); break;
			case QUAD_BW: strcat(new_name, ".qtn"); break;
			case QUAD_COLOR: strcat(new_name, ".qtc"); break;
			default: fprintf(stderr, "Strange error: should not be able to reach this funciton without wanting to use the above solutions (create_encoded_name)\n");break;
		}
	}
	return new_name;
}

/*
This function sets the button state according to what was the type of immage loaded.
	Params:
		verssion -> the type of image loaded.
		array -> the array of button present in the window.
	Returns:
		nothing.
*/
void update_button_state(Verssion verssion, Button *array){
	switch(verssion){
		case GRAPH_BW: set_button_state_graph_bw(array); break;
		case GRAPH_COLOR: set_button_state_graph_color(array); break;
		case QUAD_BW: set_button_state_quadtree_bw(array); break;
		case QUAD_COLOR: set_button_state_quadtree_color(array); break;
		case STD_IMAGE: set_button_state_std_image(array); break;
		default: break;
	}
}

/*
In the few next functions:
	Params:
		array -> the array containing all button on the window.
		verssion -> (not always there) the type of image we opened.
*/

/*
	This function set the button state suitable for actions possible after loading a standart type image (png, jpeg...)
*/
void set_button_state_std_image(Button *array){
	array[OPEN_IMAGE].state = AVAILABLE;
	array[QUAD_TREE_APPROX].state = AVAILABLE;
	array[SAVE_QUAD_COLOR].state = FORBIDEN;
	array[SAVE_QUAD_BW].state = FORBIDEN;
	array[MINIM_LOSS].state = FORBIDEN;
	array[MINIM_NO_LOSS].state = FORBIDEN;
	array[SAVE_GRAPH_COLOR].state = FORBIDEN;
	array[SAVE_GRAPH_BW].state = FORBIDEN;
}
/*
	This function set the button state suitable for actions possible after failing to load an image.
*/
void set_button_state_no_image(Button *array){
	array[OPEN_IMAGE].state = AVAILABLE;
	array[QUAD_TREE_APPROX].state = FORBIDEN;
	array[SAVE_QUAD_COLOR].state = FORBIDEN;
	array[SAVE_QUAD_BW].state = FORBIDEN;
	array[MINIM_LOSS].state = FORBIDEN;
	array[MINIM_NO_LOSS].state = FORBIDEN;
	array[SAVE_GRAPH_COLOR].state = FORBIDEN;
	array[SAVE_GRAPH_BW].state = FORBIDEN;
}
/*

	This function set the button state suitable for actions possible after loading a black and white quadtree (.qtn).
*/
void set_button_state_quadtree_bw(Button *array){
	int i;

	for (i = 0; i <= QUIT; i++){
		array[i].state = AVAILABLE;
	}
	array[SAVE_GRAPH_BW].state = FORBIDEN;
	array[SAVE_GRAPH_COLOR].state = FORBIDEN;
	array[SAVE_QUAD_COLOR].state = FORBIDEN;
}

/*
	This function set the button state suitable for actions possible after loading a color quadtree (.qtc).
*/
void set_button_state_quadtree_color(Button *array){
	int i;

	for (i = 0; i <= QUIT; i++){
		array[i].state = AVAILABLE;
	}
	array[SAVE_GRAPH_BW].state = FORBIDEN;
	array[SAVE_GRAPH_COLOR].state = FORBIDEN;
}
/*
	This function set the button state suitable for actions possible after loading a black and white graph (.gmn).
*/
void set_button_state_graph_bw(Button *array){
	int i;
	
	for (i = 0; i <= QUIT; i++){
		array[i].state = AVAILABLE;
	}
	array[SAVE_QUAD_BW].state = FORBIDEN;
	array[SAVE_QUAD_COLOR].state = FORBIDEN;
	array[SAVE_GRAPH_COLOR].state = FORBIDEN;
	array[MINIM_LOSS].state = FORBIDEN;
	array[MINIM_NO_LOSS].state = FORBIDEN;
}

/*
	This function sets the button state suitable for actions possible after loading a color graph (.gmc).
*/
void set_button_state_graph_color(Button *array){
	int i;
	
	for (i = 0; i <= QUIT; i++){
		array[i].state = AVAILABLE;
	}
	array[SAVE_QUAD_BW].state = FORBIDEN;
	array[SAVE_QUAD_COLOR].state = FORBIDEN;
	array[MINIM_LOSS].state = FORBIDEN;
	array[MINIM_NO_LOSS].state = FORBIDEN;
}

/*
	This function sets the button state suitable for a actions possible after minimising a tree with loss.
*/
void set_was_minimized_with_loss(Button *array, Verssion verssion){
	if (verssion == QUAD_COLOR)
		array[SAVE_GRAPH_COLOR].state = AVAILABLE;
	array[SAVE_QUAD_BW].state = FORBIDEN;
	array[SAVE_QUAD_COLOR].state = FORBIDEN;
	array[MINIM_LOSS].state = FORBIDEN;
	array[MINIM_NO_LOSS].state = FORBIDEN;
	array[SAVE_GRAPH_BW].state = AVAILABLE;
}

/*
	This function sets the button state suitable for a actions possible after minimising a tree without loss.
*/
void set_was_minimized_no_loss(Button *array){
	array[QUAD_TREE_APPROX].state = FORBIDEN;
	array[SAVE_QUAD_BW].state = FORBIDEN;
	array[SAVE_QUAD_COLOR].state = FORBIDEN;
	array[MINIM_LOSS].state = AVAILABLE;
	array[MINIM_NO_LOSS].state = FORBIDEN;
	array[SAVE_GRAPH_BW].state = FORBIDEN;
	array[SAVE_GRAPH_COLOR].state = FORBIDEN;
}

/*
	This function check the sufix of the given file name to indicate if the program should try to open it (and how) or discard it.
		Params:
			file_name -> a pointer on the first character composing the file name;
		Returns:
			0 -> Not accepted;
			other: the correspinding enumarated value
*/
Verssion check_txt_input(char* file_name){
	int position_point = strlen(file_name) - 1;
	char *sufix;

	while(position_point > 0 && file_name[position_point] != '.'){
		position_point --;
	}
	sufix = &(file_name[position_point+1]);

	if (strcmp(sufix, "jpeg") == 0)
		return STD_IMAGE;
	if (strcmp(sufix, "ico") == 0)
		return STD_IMAGE;
	if (strcmp(sufix, "cur") == 0)
		return STD_IMAGE;
	if (strcmp(sufix, "bmp") == 0)
		return STD_IMAGE;
	if (strcmp(sufix, "pnm") == 0)
		return STD_IMAGE;
	if (strcmp(sufix, "xpm") == 0)
		return STD_IMAGE;
	if (strcmp(sufix, "lbm") == 0)
		return STD_IMAGE;
	if (strcmp(sufix, "pcx") == 0)
		return STD_IMAGE;
	if (strcmp(sufix, "gif") == 0)
		return STD_IMAGE;
	if (strcmp(sufix, "tga") == 0)
		return STD_IMAGE;
	if (strcmp(sufix, "tiff") == 0)
		return STD_IMAGE;
	if (strcmp(sufix, "xv") == 0)
		return STD_IMAGE;
	if (strcmp(sufix, "png") == 0)
		return STD_IMAGE;

	if (strcmp(sufix, "qtn") == 0)
		return QUAD_BW;
	if (strcmp(sufix, "qtc") == 0){
		return QUAD_COLOR;
	}
	if (strcmp(sufix, "gmn") == 0)
		return GRAPH_BW;
	if (strcmp(sufix, "gmc") == 0)
		return GRAPH_COLOR;
	return 0;
}

/*
This function prompts a writing field for the user add ask for a coorect extention. It INSITS on getting a  correct extention.
	Params:
		info -> a pointer on the structure containing all the inforamtion about the window.
	Returns:
		sufix_result -> a member of the 'Verssion' enumeration corresponding to the type of file the given suffix represents.
*/
Verssion get_compatible_file_name(Win *info){
	
	Verssion sufix_result;

	if (info->text_input != NULL){
		free(info->text_input);
	}

	MLV_wait_input_box(
			info->padding_image_area,
			info->padding_image_area+ 30,
			info->padding_image_area + SIZE_IMAGE,
			info->padding_image_area + 60,
			BTN_BG_FORBIDEN,
			MLV_COLOR_ANTIQUE_WHITE,
			MLV_COLOR_BLACK,
			"input image path :  ",
			&(info->text_input)
		);
	sufix_result= check_txt_input(info->text_input);

	while (sufix_result == 0){
		if (info->text_input != NULL){
			free(info->text_input);
		}
		MLV_wait_input_box(
			info->padding_image_area,
			info->padding_image_area+30,
			info->padding_image_area + SIZE_IMAGE,
			info->padding_image_area + 60,
			BTN_BG_FORBIDEN,
			BTN_BODER_FORBIDEN,
			MLV_COLOR_BLACK,
			"not compatible, retry :  ",
			&(info->text_input)
		);
		sufix_result = check_txt_input(info->text_input);

	}
	return sufix_result;
}

/*
This function creates a quadtree based on the file path the user gave.
	Params:
		tree -> a pointer on the pointer to the root of the future tree.
		info -> all information about the window (including the path given by the user).
		verssion -> the type of file that was given.
	Returns:
		1 -> success
		0 -> an error occured.
*/
int file_decode(Tree **tree, Win *info, Verssion verssion){
	FILE *file;
	int ret_value = 1;
	if (NULL == (file = fopen(info->text_input, "rb"))){
		fprintf(stderr, "Error could not open file '%s'", info->text_input);
		return 0;
	}
	printf("decoding ...\n");
	switch (verssion){
		case GRAPH_BW: ret_value = decoding_graph_bw(tree, file); break;
		case GRAPH_COLOR: ret_value = decoding_graph(tree, file); break;
		case QUAD_BW: ret_value = decode_tree(tree, file, 0); break;
		case QUAD_COLOR: ret_value = decode_tree(tree, file, 1); break;
		default: break;
	}
	printf("done.\n");
	fclose(file);

	if (ret_value < 0)
		return 0;
	return 1;
}

/*
This function asks the user for an image path 
and attemps to decode it into a tree or simply displays it according to its type.
	Params:
		info -> a pointer on the structure holding all window information.
		t -> a pointer on the root of the tree.
		verssion -> a pointer on the storage of the type of image that was passed
	Returns:
		0 -> error (strange)
		1 -> succes, an image was loaded.
		2 -> nothing to load.
*/
int manage_image_input(Win *info, Tree *t, Verssion *verssion){

	*verssion = get_compatible_file_name(info);
	
	if (*verssion == 0){
		fprintf(stderr, "Strange Error: Couldn't get input type but it seems to be valid.\n");
		return 0;
	}
	if (*verssion == STD_IMAGE){
		info->img = MLV_load_image(info->text_input);
		if (info->img == NULL){
			fprintf(stderr, "Couldn't find image to load.\n");
			return 2;
		}
		update_button_state(*verssion, info->button_array);
		return 1;
	}
	else{
		if (file_decode(&t, info, *verssion)){

			if (! tree_to_image(&(info->img), t))
				return 0;
			update_button_state(*verssion, info->button_array);
			return 1;
		}

	}
	return 0;
}

/*
This function handles the writing of the demanded save.
	Params:
		save_type -> the type of file we are writing.
		t -> a pointer on the root of the tree.
		current_file_name -> the name of the file that was used to generate the tree.
	Returns:
		1 -> success.
		0 -> failure.
*/
int manage_saves(int save_type, Tree *t, char *current_file_name){
	FILE *file = NULL;
	char *encoded_name;
	Verssion style;

	if (save_type == SAVE_QUAD_BW)
		style = QUAD_BW;
	else if (save_type == SAVE_QUAD_COLOR)
		style = QUAD_COLOR;
	else if (save_type == SAVE_GRAPH_COLOR)
		style = GRAPH_COLOR;
	else if (save_type == SAVE_GRAPH_BW)
		style = GRAPH_BW;

	encoded_name = create_encoded_name(current_file_name, style);

	if (NULL == (file = fopen(encoded_name, "w+"))){
		fprintf(stderr, "couldn't open new file to save data.\n");
		return 0;
	}
	printf("encodeing ...\n");
	switch(style){
		case GRAPH_BW: encoding_graph_bw(t, file, 0, 0); break;
		case GRAPH_COLOR: encoding_graph(t, file, 0, 0); break;
		case QUAD_BW: encode_tree(t, file, 0); break;
		case QUAD_COLOR: encode_tree(t, file, 1); break;
		default :{
			fclose(file);
			fprintf(stderr, "Strange occurance (function name: manage_saves)");
			return 0;
		};
	}
	printf("done\n");
	fclose(file);
	free(encoded_name);
	return 1;
}

/*
This function links the buttons to the functionalities they represents.
	Params:
		btn_number -> an int rorresponding to this button place in the array contained in 'info'.
		info -> a pointer on all window-relevent inforamtion (including the button array.)
		t -> the address of the pointer on the root of the tree.
		color_err_list -> a pointer on the list of color error.
	Returns:
		0 -> problem loading the tree or image (not fatal)
		1 -> all good.
		2 -> user asked to quit.

*/
int link_btn(int btn_number, Win *info, Tree** t, ErrorList_FirstLast *color_err_list, Verssion *verssion){
	int res;
	MLV_clear_window(MLV_COLOR_BLACK);
	display_base_window(info);

	MLV_update_window();	

	switch(btn_number){
		case OPEN_IMAGE: {
			res = manage_image_input(info, *t, verssion);
			if (res != 1){
				return 0;
			}
			break;
		}
		case QUAD_TREE_APPROX:{
			if (*t != NULL){
				printf("earasing existing stuff\n");
				free_tree(*t);
				*t = NULL;
			}
			if (!create_quadtree(t, info->img, color_err_list)) {
				fprintf(stderr, "Error in image_to_quadtree\n");
				return 0;
			}
			update_button_state(QUAD_COLOR, info->button_array);
			*verssion = QUAD_COLOR;
			tree_to_image(&(info->img), *t);
		} break;
		case MINIM_LOSS:{
			minimize_loss(t, info->img, return_zone(0, 0, SIZE_IMAGE, SIZE_IMAGE));
			set_was_minimized_with_loss(info->button_array, *verssion);
			tree_to_image(&(info->img), *t);

		} break;
		case MINIM_NO_LOSS:{
			minimize_without_loss(t);
			set_was_minimized_no_loss(info->button_array);
			tree_to_image(&(info->img), *t);
		} break;
		case QUIT: return 2; break;
		default:{
			if (btn_number == SAVE_QUAD_BW 
				|| btn_number == SAVE_QUAD_COLOR
				|| btn_number == SAVE_GRAPH_COLOR
				|| btn_number == SAVE_GRAPH_BW){
				manage_saves(btn_number, *t, info->text_input);
			}
		} break;
	}
	return 1;
}