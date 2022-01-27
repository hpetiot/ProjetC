#ifndef __BUTTON_H__
#define __BUTTON_H__

#include <MLV/MLV_all.h>

#define BTN_BG_HOVER MLV_COLOR_LIGHT_SEA_GREEN 
#define BTN_BG_HELD MLV_COLOR_PALE_GREEN
#define BTN_BG_BUISY MLV_COLOR_TAN
#define BTN_BG_AVAILABLE MLV_COLOR_GREEN
#define BTN_BG_FORBIDEN MLV_COLOR_GREY

#define BTN_BODER_HOVER MLV_COLOR_YELLOW
#define BTN_BODER_HELD MLV_COLOR_LIGHT_GOLDENROD 
#define BTN_BODER_BUISY MLV_COLOR_DARK_GOLDENROD
#define BTN_BODER_AVAILABLE MLV_COLOR_GOLD
#define BTN_BODER_FORBIDEN MLV_COLOR_ANTIQUE_WHITE

#define BTN_TEXT_HOVER MLV_COLOR_ANTIQUE_WHITE
#define BTN_TEXT_HELD MLV_COLOR_BLACK
#define BTN_TEXT_BUISY MLV_COLOR_GAINSBORO
#define BTN_TEXT_AVAILABLE MLV_COLOR_BLACK
#define BTN_TEXT_FORBIDEN MLV_COLOR_BLACK

#define BTN_HEIGHT 48
#define BTN_WIDTH 175

typedef struct{
	int x; 
	int y;
    MLV_Mouse_button button;
    MLV_Button_state state;
} Mouse;

typedef enum {
	BUISY,
	HELD,
	AVAILABLE,
	HOVER,
	FORBIDEN
}Button_state;

typedef struct{
	int top_left_x;
	int top_left_y;
	int height;
	int width;
} Box;

typedef struct{
	Box box;
	char *name;
	Button_state state;
} Button;

/**
*This function adds a button to the window.
*any number of call to this function must be matched by 1 call to 'free_button_array'
*note: this function uses the "reallocarray" function (cf man 3 malloc), on available on debian10 "buster".
*		@param tl_x an int giving the horizontal coordinate of the top left corner of the button.
*		@param tl_y an int giving the vertical coordinatte of the top left corner of the button.
*		@param height an int giving the height of the button.
*		@param width an int giving the width of the button.
*		@param name a constant character strung that will be displayed in the middle of the button.
*		@param nb_button a pointer on the number of button held in the window managment structure.
*		@param array a pointer on the array of button held in the window managment structure.
*		@return 0 -> alll good; -1 -> memory allocation error.
*/
int add_button(int tl_x, int tl_y, int height, int width, const char* name, int* nb_button, Button** array);
/**
*This function frees the buttons allocated by 'add_button'.
*		@param nb_button the number of buttons in the array.
*		@array a pointer on the array holding the buttons.
*		@return Nothing.
*/
void free_button_array(int nb_button, Button** array);

/**
*This function displays the buttons according to their 'state' field.
*		@param nb_button the number of button in the array.
*		@param array the array holding the buttons.
*		@return Nothing.
*/
void display_all_button(int nb_button, Button* array);

/**
*This function print all button in the array in the console. It is meant for debugging.
*		@param nb_button the number of button in the array.
*		@param array the array holding the buttons.
*		@return nothing.
*/
void print_all_button(int nb_button, Button* array);

/**
*This function updates the state of the button acording to the mouse events.
*	@param mouse a pointer on the structure holding all mouse information.
*	@param array the array holding the buttons.
*	@param nb_button the number of button in the array.
*	@param ev the type of mouse event found.
*	@return nb_button -> no clic happened; [0; nb_button[ -> the designeated member of array was clicked.
*/
int button_update(Mouse *mouse, Button* array, int nb_button, const MLV_Event ev);

#endif