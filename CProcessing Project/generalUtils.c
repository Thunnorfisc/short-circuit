#include <math.h>
#include <stdio.h>
#include <float.h>
#include "generalUtils.h"

/*
Description: These are the variables that were used repeatedly so they will be stored in the generalUtils.h to be used
int the code for the different system.

NOTE!!! Do not edit these names or values without consulting the team
*/

int IsAreaClicked(float area_center_x, float area_center_y, float area_width, float area_height, float click_x, float click_y)
{
	float half_width = area_width / 2;
	float half_height = area_height / 2;

	// If click x is larger than area_center_x - half_width and smaller than area_center_x + half_width
	if (click_x >= (area_center_x - half_width) && \
		click_x <= (area_center_x + half_width) && \
		click_y >= (area_center_y - half_height) && \
		click_y <= (area_center_y + half_height)) {
		return 1;
	}
	else
		return 0;
}

int IsCircleClicked(float circle_center_x, float circle_center_y, float diameter, float click_x, float click_y)
{
	float radius = diameter / 2;
	// Find the distance between the click and the center of the circle
	float distance = sqrtf((click_x - circle_center_x) * (click_x - circle_center_x) +
		(click_y - circle_center_y) * (click_y - circle_center_y));
	if (distance <= radius)
		return 1;
	else
		return 0;
}

int AreCirclesIntersecting(float c1_x, float c1_y, float r1, float c2_x, float c2_y, float r2)
{
	double dx = c1_x - c2_x;
	double dy = c1_y - c2_y;
	double distance_squared = dx * dx + dy * dy;

	double radii_sum = r1 + r2;

	// Check for intersection
	if (distance_squared <= radii_sum * radii_sum)
		return 1;

	return 0;
}

int Exist_In_Array(void* const value_to_check,void* const array, TYPES_OF_ARRAYS type_of_array, int size_of_array) {
	switch (type_of_array)
	{
	case(1):
	{
		//Write code to check if variables exist in int array
		int* array_casted = (int*)array;
		int* value_to_check_casted = (int*)value_to_check;
		for (int i = 0; i < size_of_array; ++i) {
			if (*value_to_check_casted == array_casted[i])
			{
				return 1;
			}
		}
		return 0;
		break;
	}
	case(2): 
	{
		//Write code to check if variables exist in float array
		float* array_casted = (float*)array;
		return 0;
		break;
	}
	case(3):
	{
		//Write code to check if variables exist in double array
		double* array_casted = (double*)array;
		return 0;
		break;
	}
	case(4):	
	{
		//Write code to check if variables exist in CP_Vector array
		CP_Vector* array_casted = (CP_Vector*)array;
		CP_Vector* value_to_check_casted = (CP_Vector*)value_to_check;
		for (int i = 0; i < size_of_array; ++i) {
			printf("existing x:%f existing y:%f\n", value_to_check_casted->x, array_casted[i].x);
			if (value_to_check_casted->x == array_casted[i].x && value_to_check_casted->y == array_casted[i].y)
			{
				return 1;
			}
		}
		return 0;
		break;
	}
	case(5):	
	{
		//Write code to check if variables exist is CircuitPiece array
		CircuitPiece* array_casted = (CircuitPiece*)array;
		return 0;
		break;
	}
	case(6):
	{
		// Might need to write code to check if variables exist in enemy array in the future? 12/11/2024
		return 0;
		break;
	}
	default:
		return 0;
		break;
	}
	return 0;
}

//this function is used to draw a button - yande
int Draw_Button(const char* text, float x, float y, float width, float height)
{	
	CP_Settings_Save();

	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);

	CP_Settings_Fill(CP_Color_Create(200, 200, 200, 255));
	CP_Graphics_DrawRect(x, y, width, height);
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Font_DrawText(text, x, y);

	CP_Settings_Restore();

	// Check for click
	float click_x = CP_Input_GetMouseX();
	float click_y = CP_Input_GetMouseY();

	if (IsAreaClicked(x, y, width, height, click_x, click_y) && CP_Input_MouseClicked()) {
		CP_Graphics_DrawRect(x, y, width - 10, height - 10);
		return 1;
	}
	return 0;
}

int Draw_Button_With_Image(CP_Image image, const char* text, float x, float y, float width, float height) {
	CP_Settings_Save();

	CP_Settings_ImageMode(CP_POSITION_CENTER);
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);

	// Draw image
	CP_Image_DrawAdvanced(image, x, y, width, height, 255, 0.0f);

	// Draw text
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Font_DrawText(text, x, y);

	CP_Settings_Restore();

	// Check for click
	float click_x = CP_Input_GetMouseX();
	float click_y = CP_Input_GetMouseY();

	if (IsAreaClicked(x, y, width, height, click_x, click_y) && CP_Input_MouseClicked()) {
		CP_Image_DrawAdvanced(image, x, y, width-10, height-10, 255, 0.0f);
		return 1;
	}
	return 0;
}
