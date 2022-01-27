#ifndef __IO_H__
#define __IO_H__

#include "quadtree.h"
#include "list_errors.h"
#include "window.h"

#define BTN_TXT_1 "open image"
#define BTN_TXT_2 "quadtree approximation"
#define BTN_TXT_3 "save rgba bianary"
#define BTN_TXT_4 "save b&w binary"
#define BTN_TXT_5 "minimisation with loss"
#define BTN_TXT_6 "minimisation no loss"
#define BTN_TXT_7 "save rgba graf"
#define BTN_TXT_8 "save b&w graf"
#define BTN_TXT_9 "quit"

typedef enum{
	NOPE,
	GRAPH_BW,
	GRAPH_COLOR,
	QUAD_BW,
	QUAD_COLOR,
	STD_IMAGE
} Verssion;

typedef enum{
	OPEN_IMAGE,
	QUAD_TREE_APPROX,
	SAVE_QUAD_COLOR,
	SAVE_QUAD_BW,
	MINIM_LOSS,
	MINIM_NO_LOSS,
	SAVE_GRAPH_COLOR,
	SAVE_GRAPH_BW,
	QUIT
}Button_fct;

/**
*This function changes the button state to fit the situation where a .qtn was loaded.
*	@param array the array storing all the buttons.
*/
void set_button_state_quadtree_bw(Button *array);
/**
*This function changes the button state to fit the situation where a nothing was loaded.
*	@param array the array storing all the buttons.
*/
void set_button_state_no_image(Button *array);
/**
*This function changes the button state to fit the situation where a standard image was loaded.
*	@param array the array storing all the buttons.
*/
void set_button_state_std_image(Button *array);
/**
*This function changes the button state to fit the situation where a .qtc was loaded.
*	@param array the array storing all the buttons.
*/
void set_button_state_quadtree_color(Button *array);
/**
*This function changes the button state to fit the situation where a .gmn was loaded.
*	@param array the array storing all the buttons.
*/
void set_button_state_graph_bw(Button *array);
/**
*This function changes the button state to fit the situation where a .gmc was loaded.
*	@param array the array storing all the buttons.
*/
void set_button_state_graph_color(Button *array);
/**
*This function changes the button state to fit the situation where a quadtree was minimized without loss.
*	@param array the array storing all the buttons.
*/
void set_was_minimized_no_loss(Button *array);
/**
*This function changes the button state to fit the situation where a quadtree was minimized with loss.
*	@param array the array storing all the buttons.
*/
void set_was_minimized_with_loss(Button *array, Verssion verssion);

/**
*This function links the buttons to the functionalities they represents.
*		@param btn_number an int rorresponding to this button place in the array contained in 'info'.
*		@param info a pointer on all window-relevent inforamtion (including the button array.)
*		@param t the address of the pointer on the root of the tree.
*		@param color_err_list a pointer on the list of color error.
*		@return 
*			0 -> problem loading the tree or image (not fatal)
*			1 -> all good.
*			2 -> user asked to quit.
*/
int link_btn(int btn_number, Win *info, Tree** t, ErrorList_FirstLast *color_err_list, Verssion *verssion);
#endif