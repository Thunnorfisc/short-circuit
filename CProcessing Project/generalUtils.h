#pragma once
#include "cprocessing.h"
#include "magicStructs.h"
#include "enemyStructs.h"
#include "mainMenuSystem.h"

/*
Description: These are the variables that were used repeatedly so they will be stored in the generalUtils.h to be used
int the code for the different system.

NOTE!!! Do not edit these names or values without consulting the team
*/

//File Address for the font
#define FONT_ASSET_ADDR "Assets/Exo2-Regular.ttf"

//Background color that will be used to refresh the screen
#define BACKGROUND_COLOR CP_Color_Create(0, 0, 0, 255)

#define COLOR_BLACK CP_Color_Create(0, 0, 0, 255)

#define COLOR_WHITE(a) CP_Color_Create(255, 255, 255, a)

//Use to get the height of the window
#define WINDOW_HEIGHT CP_System_GetWindowHeight()

//Use to get the width of the window
#define WINDOW_WIDTH CP_System_GetWindowWidth()

//Use to get the half the height of the window
#define WINDOW_HEIGHT_HALF (float)WINDOW_HEIGHT / 2.f

//Use to get the half the width of the window
#define WINDOW_WIDTH_HALF (float)WINDOW_WIDTH / 2.f

//Use to get 1/5 of the height of the window
#define WINDOW_HEIGHT_1_5 (float)WINDOW_HEIGHT * 1/5.f

//Use to get 1/5 of the height of the window
#define WINDOW_WIDTH_1_5 (float)WINDOW_WIDTH * 1/5.f

//Use to get the ratio of the asset display
#define WINDOW_RATIO (float)WINDOW_HEIGHT / 1080.f

#define DEFAULT_ALPHA 255

#define TEXT_SIZE 60.0f

//Used to get the delta time of the program
#define DELTA_TIME CP_System_GetDt()
/*
A_INT = 1,
A_FLOAT = 2,
A_DOUBLE = 3,
A_CP_VECTOR = 4,
A_CIRCUITPIECE = 5,
A_E_MAGE = 6
*/
typedef enum TYPES_OF_ARRAYS
{
	A_INT = 1,
	A_FLOAT = 2,
	A_DOUBLE = 3,
	A_CP_VECTOR = 4,
	A_CIRCUITPIECE = 5,
	A_E_MAGE = 6

}TYPES_OF_ARRAYS;

typedef struct Button {
	CP_Vector position;
	float width;
	float height;
}Button;

//For drawing buttons
/*
@author Lim Yan De (l.yande)
@brief Creates an interactive button with text.
@param text - const char* specifying the button label text
@param x - float specifying the x-coordinate of button center
@param y - float specifying the y-coordinate of button center
@param width - float specifying the button width
@param height - float specifying the button height
@return int - returns 1 if button was clicked, 0 otherwise
*/
int Draw_Button(const char* text, float x, float y, float width, float height);

/*
@author Lim Yan De (l.yande)
@brief Creates an interactive button with both image and text.
@param image - CP_Image specifying the button background image
@param text - const char* specifying the button label text
@param x - float specifying the x-coordinate of button center
@param y - float specifying the y-coordinate of button center
@param width - float specifying the button width
@param height - float specifying the button height
@return int - returns 1 if button was clicked, 0 otherwise
*/
int Draw_Button_With_Image(CP_Image image, const char* text, float x, float y, float width, float height);

/*
Description: These are the functions that were used repeatedly so they will be stored in the generalUtils.h to be used
in the code for the different system.

NOTE!!! Do not edit these names or values without consulting the team
*/

/*
Description: Used to check if the area that is being passed through is the area that is being clicked. This is used in conjuction
How To Use:
This is used in conjuction with an if statement, for example:
if(IsAreaClicked){ ... }
*/
int IsAreaClicked(float area_center_x, float area_center_y, float area_width, float area_height, float click_x, float click_y);

int Exist_In_Array(void* const value_to_check, void* const array, TYPES_OF_ARRAYS type_of_array, int size_of_array);

int Draw_TextBoxAdvanced(const char* text, float textSize, float x, float y,
	float w, float h, float y_scale, CP_Color box_color, CP_Color text_color,
	CP_POSITION_MODE mode);