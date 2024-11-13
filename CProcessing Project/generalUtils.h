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

//Use to get the height of the window
#define WINDOW_HEIGHT CP_System_GetWindowHeight()

//Use to get the width of the window
#define WINDOW_WIDTH CP_System_GetWindowWidth()

//Use to get the half the height of the window
#define WINDOW_HEIGHT_HALF (float)WINDOW_HEIGHT / 2.f

//Use to get the half the width of the window
#define WINDOW_WIDTH_HALF (float)WINDOW_WIDTH / 2.f

//Use to get the ratio of the asset display
#define WINDOW_RATIO (float)WINDOW_HEIGHT / 1080.f

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

//Used to draw buttons
int Draw_Button(const char* text, float x, float y, float width, float height);

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

int Exist_In_Array(void* value_to_check, void* array, TYPES_OF_ARRAYS type_of_array, int size_of_array);