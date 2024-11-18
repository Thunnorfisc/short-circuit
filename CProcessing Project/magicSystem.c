#include <stdio.h>
#include "generalUtils.h"

/*
Description:
Used to display the UI of Circuit Pieces the player will click and drag from.

Parameters:
CircuitPiece list_of_circuit_pieces[], int size_of_array
*/
void Draw_L_CircuitPiece(CircuitPiece c[], CP_Image circuit_image_l, int N) {
	for (int i = 0; i < N; ++i) {
		CP_Image_DrawAdvanced(
			circuit_image_l, c[i].centerPosition.x, c[i].centerPosition.y,
			(float)c[i].circuitSize, (float)c[i].circuitSize, 255, (float)c[i].rot * 90.0f);
	}
	
}

/*
Description:
Used to display the Circuit pieces the payer chose to drop into the grid

Parameters:
CircuitPiece selected[GRID_DIMENSIONS][GRID_DIMENSIONS], CP_Image circuit_image_l
*/
void Draw_SelectedCircuitPieces(CircuitPiece selected[GRID_DIMENSIONS][GRID_DIMENSIONS], CP_Image circuit_image_l) {
	for (int row = 0; row < GRID_DIMENSIONS; ++row) {
		for (int col = 0; col < GRID_DIMENSIONS; ++col) {
			if (selected[row][col].circuitSize > 0) {
				CP_Image_DrawAdvanced(
					circuit_image_l, selected[row][col].centerPosition.x, selected[row][col].centerPosition.y,
					(float)selected[row][col].circuitSize, (float)selected[row][col].circuitSize, 255, (float)selected[row][col].rot * 90.0f);
			}
		}
	}
}

/*
Description:
Used to display the grid that the circuit pieces can be dropped into.
This function calls the function Grid_Display

Parameters:
CP_Vector const array_of_vectors_for_grid[], int size_of_array
*/
void Grid_Display(CP_Vector const grid[GRID_DIMENSIONS][GRID_DIMENSIONS]) {
	for (int row = 0; row < GRID_DIMENSIONS; ++row) {
		for (int col = 0; col < GRID_DIMENSIONS; ++col) {
			CP_Graphics_DrawRect(grid[row][col].x, grid[row][col].y, GRID_CELL_SIZE, GRID_CELL_SIZE);
		}
	}
}

/*
Description:
Used to initialize the list of vectors that will be used to generate the
grid.

Parameters:
CP_Vector const array_of_vectors_for_grid[], int size_of_the_grid
*/
void Grid_Initialize(CP_Vector grid[GRID_DIMENSIONS][GRID_DIMENSIONS]) {
	//Calculate the buffer for spawn of grids
	int total_size_of_grid = GRID_DIMENSIONS * GRID_CELL_SIZE;

	//Calculating the left-most buffer
	float left_buffer = (float)(WINDOW_WIDTH - total_size_of_grid) / 2.f + GRID_CELL_SIZE_OFFSET;
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

