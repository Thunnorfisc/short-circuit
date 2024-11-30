/*
File: magicSystem.c
Author: Jason Teo Jun Hao (jasonjunhao.teo)
Description:
This file will contain definition of the display and initialize functions that will be used for the Magic System:
void Draw_UI_CircuitPiece
void Draw_SelectedCircuitPieces
void Grid_Display
void Grid_Initialize

* All content © 2024 DigiPen Institute of Technology Singapore, all rights reserved.
*/

#include <stdio.h>
#include "generalUtils.h"

/*
Function   : Draw_UI_CircuitPiece
Description: Used to display the UI of Circuit Pieces the player will click and drag from.
Parameters : CircuitPiece list_of_circuit_pieces[], int size_of_array
Return	   : void
*/
void Draw_UI_CircuitPiece(CircuitPiece c[], CP_Image circuit_image_l, int N, int s_count) {
	for (int i = 0; i < N; ++i) {
		int alpha = 255;
		if (i >= 4 && s_count <= 0) alpha = 128;
		CP_Image_DrawAdvanced(
			c[i].image, c[i].position.x, c[i].position.y,
			(float)c[i].circuit_size, (float)c[i].circuit_size, alpha, (float)c[i].rot * 90.0f);
	}
	
}

/*
Function   : Draw_SelectedCircuitPieces
Description: Used to display the Circuit pieces the payer chose to drop into the grid
Parameters : CircuitPiece selected[GRID_DIMENSIONS][GRID_DIMENSIONS], CP_Image circuit_image_l
Return	   : void
*/
void Draw_SelectedCircuitPieces(CircuitPiece selected[GRID_DIMENSIONS][GRID_DIMENSIONS]) {
	for (int row = 0; row < GRID_DIMENSIONS; ++row) {
		for (int col = 0; col < GRID_DIMENSIONS; ++col) {
			if (selected[row][col].circuit_size > 0) {
				CP_Image_DrawAdvanced(
					selected[row][col].image, selected[row][col].position.x, selected[row][col].position.y,
					(float)selected[row][col].circuit_size, (float)selected[row][col].circuit_size, 255, (float)selected[row][col].rot * 90.0f);
			}
		}
	}
}

/*
Function   : Grid_Display
Description: Used to display the grid that the circuit pieces can be dropped into.
			 This function calls the function Grid_Display
Parameters : CP_Vector const grid[GRID_DIMENSIONS][GRID_DIMENSIONS]
Return	   : void
*/
void Grid_Display(CP_Vector const grid[GRID_DIMENSIONS][GRID_DIMENSIONS]) {
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, DEFAULT_ALPHA / 2));
	CP_Settings_Stroke(COLOR_BLACK);
	for (int row = 0; row < GRID_DIMENSIONS; ++row) {
		for (int col = 0; col < GRID_DIMENSIONS; ++col) {
			CP_Graphics_DrawRect(grid[row][col].x, grid[row][col].y, GRID_CELL_SIZE, GRID_CELL_SIZE);
		}
	}
}

/*
Function   : Grid_Initialize
Description: Used to initialize the list of vectors that will be used to generate the
			 grid.
Parameters : CP_Vector grid[GRID_DIMENSIONS][GRID_DIMENSIONS]
Return	   : void
*/
void Grid_Initialize(CP_Vector grid[GRID_DIMENSIONS][GRID_DIMENSIONS]) {
	//Calculate the buffer for spawn of grids
	float total_size_of_grid = (float)GRID_DIMENSIONS * GRID_CELL_SIZE;

	//Calculating the left-most buffer
	float left_buffer = ((float)WINDOW_WIDTH - total_size_of_grid) / 2.f + GRID_CELL_SIZE_OFFSET;
	//Calculating the top buffer
	float top_buffer = (float)GRID_CELL_SIZE + GRID_CELL_SIZE_OFFSET;

	//This will make all the vectors for the grid
	for (int row = 0 ; row < GRID_DIMENSIONS; ++row) {
		for (int col = 0; col < GRID_DIMENSIONS; ++col) {
			grid[row][col] = CP_Vector_Set(
				left_buffer + GRID_CELL_SIZE * col,
				top_buffer + GRID_CELL_SIZE * row);
		}
	}
	return;
}

