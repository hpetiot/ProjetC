#ifndef __BUTTON_H__
#define __BUTTON_H__

#include <MLV/MLV_all.h>

#define BTN_BG_HOVER MLV_COLOR_LIGHT_SEA_GREEN 
#define BTN_BG_HELD MLV_COLOR_PALE_GREEN
#define BTN_BG_BUISY MLV_COLOR_TAN
#define BTN_BG_AVAILABLE MLV_COLOR_GREEN

#define BTN_BODER_HOVER MLV_COLOR_YELLOW
#define BTN_BODER_HELD MLV_COLOR_LIGHT_GOLDENROD 
#define BTN_BODER_BUISY MLV_COLOR_DARK_GOLDENROD
#define BTN_BODER_AVAILABLE MLV_COLOR_GOLD

#define BTN_TEXT_HOVER MLV_COLOR_ANTIQUE_WHITE
#define BTN_TEXT_HELD MLV_COLOR_BLACK
#define BTN_TEXT_BUISY MLV_COLOR_GAINSBORO
#define BTN_TEXT_AVAILABLE MLV_COLOR_BLACK

#define BTN_HEIGHT 50
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
	HOVER
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

int add_button(int tl_x, int tl_y, int height, int width, const char* name, int* nb_button, Button** array);
void display_all_button(int nb_button, Button* array);
void print_all_button(int nb_button, Button* array);
void free_button_array(int nb_button, Button** array);
int button_update(Mouse *mouse, Button* array, int nb_button, const MLV_Event ev);

#endif