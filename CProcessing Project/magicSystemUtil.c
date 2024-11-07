/*
File: magicSystem.c
Author: Jason Teo Jun Hao (jasonjunhao.teo)
Description: This file will contain utilty functions that will be used for the Magic System
*/

#include "magicSystemUtil.h"
#include "generalUtils.h"
#include <math.h>
#include <stdio.h>
/*
Description:
This will be used to check if the player is currently holding down mouse button 1 on the CircuitPiece object from the original list
of Circuit pieces

Parameters:
CircuitPiece* selected, CircuitPiece list_of_circuits[], CP_Vector mouse_position
*/
int Get_Circuit_Piece_Clicked(CircuitPiece c, CP_Vector *initial_position, int mouse_x, int mouse_y) {
	CP_Vector mouse_vector = CP_Vector_Set((float)mouse_x, (float)mouse_y);
	if (CP_Vector_Distance(c.centerPosition, mouse_vector) < c.circuitSize/2) {
		initial_position = &c.centerPosition;
		return 1;
	}
	return 0;
}

/*
Description:
Check for the array length of the selectedCircuit array

Parameters:
CircuitPiece selectedPieces[]
*/
int Get_Size_Of_Selected(CircuitPiece const selectedPieces[GRID_DIMENSIONS][GRID_DIMENSIONS]) {
	int count = 0;

	for (int row = 0; row < GRID_DIMENSIONS; ++row) {
		for (int col = 0; col < GRID_DIMENSIONS; ++col) {
			//Check by using the size to see if there is a circuit in the current address
			if (selectedPieces[row][col].circuitSize) count++;
		}
	}

	return count;
}

/*
Description:
Used to find out where the mouse is when the UI for the CircuitPiece is selected and find out which piece was selected.
Returns 1 when it finds that a piece was selected

Parameters:
CircuitPiece* selected, CircuitPiece list_of_circuits[], CP_Vector mouse_position
*/
int Circuit_PieceSelected(CircuitPiece* selected, CircuitPiece list_of_circuits[], CP_Vector mouse_position) {
	for (int i = 0; i < CIRCUIT_UI_LIST_SIZE; ++i) {
		if (CP_Vector_Distance(mouse_position, list_of_circuits[i].centerPosition) < GRID_CELL_SIZE_OFFSET) {
			*selected = list_of_circuits[i];

			return 1;
		}
	}
	return 0;
}

/*
Description:
Used to check where the piece was dropped when the mouse is released by checking the coordinates of the mouse and the
index of the grid (Checking each position of the cells & mouse position
Should not allow for replacement of an existing piece

Parameters:
CircuitPiece c, CircuitPiece circuit_pos[GRID_DIMENSIONS][GRID_DIMENSIONS]
CP_Vector const grid[GRID_DIMENSIONS][GRID_DIMENSIONS], CP_Vector mouse_position
*/
int Grid_Cricuit_Drop(CircuitPiece circuit_pos[GRID_DIMENSIONS][GRID_DIMENSIONS], CP_Vector const grid[GRID_DIMENSIONS][GRID_DIMENSIONS],
	CircuitPiece selectedPiece, CP_Vector index_used[GRID_DIMENSIONS * GRID_DIMENSIONS], CP_Vector mouse_position) {

	int test_size = Get_Size_Of_Selected(circuit_pos);

	CP_Vector index_to_use;

	for (int row = 1; row <= GRID_DIMENSIONS; ++row) {
		for (int col = 1; col <= GRID_DIMENSIONS; ++col) {

			index_to_use = CP_Vector_Set(row, col);

			if (!CP_Vector_Length(circuit_pos[row - 1][col - 1].centerPosition) && CP_Vector_Distance(mouse_position, grid[row - 1][col - 1]) < GRID_CELL_SIZE_OFFSET) {

				circuit_pos[row - 1][col - 1] = New_Circuit_Piece(
					CP_Vector_Set(grid[row - 1][col - 1].x, grid[row - 1][col - 1].y),
					selectedPiece.IO_1, selectedPiece.IO_2, selectedPiece.rot
				);
				Add_To_Index_Array(index_used, index_to_use, GRID_DIMENSIONS * GRID_DIMENSIONS);
				circuit_pos[row - 1][col - 1].circuitSize = GRID_CELL_SIZE;

				return 1;
			}

		}
	}
	return 0;
}

/*
Description:
Used in Grid_Circuit_Drop to see if the area can be dropped

Parameters:
CircuitPiece c, CircuitPiece circuit_pos[GRID_DIMENSIONS][GRID_DIMENSIONS]
CP_Vector const grid[GRID_DIMENSIONS][GRID_DIMENSIONS], CP_Vector mouse_position
*/
int Available_Circuit_Positions(CircuitPiece* piece, CircuitPiece selectedPieces[], CP_Vector grid[GRID_DIMENSIONS][GRID_DIMENSIONS], CP_Vector mouse_position) {

	//Check if the selectedPiece array is empty
	if (selectedPieces[0].circuitSize == 0) return 1;

	//Check if the position of the drop is right beside horizontally/vertically to the exisiting pieces
	//for (int i = 0; i < ) {

	//}
}

void Add_To_Index_Array(CP_Vector index_list[], CP_Vector vector_to_add, int size) {
	for (int i = 0; i < size; ++i) {

		if (!CP_Vector_Length(index_list[i])) { 
			index_list[i] = vector_to_add; 
			break;
		}
	}
}