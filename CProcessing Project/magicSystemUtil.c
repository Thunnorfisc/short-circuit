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

	int allowed_placement = 0;

	for (int row = 1; row <= GRID_DIMENSIONS; ++row) {
		for (int col = 1; col <= GRID_DIMENSIONS; ++col) {

			index_to_use = CP_Vector_Set(col, row);

			if (!CP_Vector_Length(circuit_pos[col - 1][row - 1].centerPosition) && CP_Vector_Distance(mouse_position, grid[col - 1][row - 1]) < GRID_CELL_SIZE_OFFSET) {

				//Check if the current placement is allowed on the board based on the current pieces on the board
				allowed_placement = Check_Placement(index_used, index_to_use, circuit_pos, selectedPiece);

				if (allowed_placement) {
					circuit_pos[col - 1][row - 1] = New_Circuit_Piece(
						CP_Vector_Set(grid[col - 1][row - 1].x, grid[col - 1][row - 1].y),
						selectedPiece.IO_1, selectedPiece.IO_2, selectedPiece.rot
					);

					//Add to array to track the current used row and column
					Add_To_Index_Array(index_used, index_to_use, GRID_DIMENSIONS * GRID_DIMENSIONS);

					circuit_pos[col - 1][row - 1].circuitSize = GRID_CELL_SIZE;

					return 1;
				}
			}
		}
	}
	return 0;
}

/*
Description:
Used in Grid_Circuit_Drop to see if the area can be dropped

Parameters:
CP_Vector index_used[], CP_Vector index_to_use
*/
int Check_Placement(CP_Vector index_used[], CP_Vector index_to_use, CircuitPiece circuit_pos[GRID_DIMENSIONS][GRID_DIMENSIONS], CircuitPiece selectedPiece) {

	/* Check if adjacent and return the start and end of the circuits */
	if (CP_Vector_Length(index_used[0]) == 0) return 1;
	
	else {
		//Check if the new position for placement is right beside horizontally or vertically
		for (int i = 0; CP_Vector_Length(index_used[i]); ++i) { //Checks until the last initialized index
			if (CP_Vector_Distance(index_to_use, index_used[i]) == 1) {

				//Check if the placement is also within the possible IO = 0
				if (circuit_pos[(int)index_used[i].x - 1][(int)index_used[i].y - 1].IO_1 == 0 ||
					circuit_pos[(int)index_used[i].x - 1][(int)index_used[i].y - 1].IO_2 == 0) {
					if ((selectedPiece.IO_1 == 2 || selectedPiece.IO_2 == 2) && index_used[i].y - index_to_use.y == 1) return 1;
				}

				//Check if the placement is also within the possible IO = 1
				if (circuit_pos[(int)index_used[i].x - 1][(int)index_used[i].y - 1].IO_1 == 1 ||
						 circuit_pos[(int)index_used[i].x - 1][(int)index_used[i].y - 1].IO_2 == 1) {
					if ((selectedPiece.IO_1 == 3 || selectedPiece.IO_2 == 3) && index_used[i].x - index_to_use.x == 1) return 1;
				}

				//Check if the placement is also within the possible IO = 2
				if (circuit_pos[(int)index_used[i].x - 1][(int)index_used[i].y - 1].IO_1 == 2 ||
						 circuit_pos[(int)index_used[i].x - 1][(int)index_used[i].y - 1].IO_2 == 2) {
					if ((selectedPiece.IO_1 == 0 || selectedPiece.IO_2 == 0) && index_to_use.y - index_used[i].y == 1) return 1;
				}

				//Check if the placement is also within the possible IO = 3
				if(circuit_pos[(int)index_used[i].x - 1][(int)index_used[i].y - 1].IO_1 == 3 ||
					circuit_pos[(int)index_used[i].x - 1][(int)index_used[i].y - 1].IO_2 == 3){
					if ((selectedPiece.IO_1 == 1 || selectedPiece.IO_2 == 1) && index_to_use.x - index_used[i].x == 1) return 1;
				}
			}
		}
	}
	/* End of check if adjacent */
	return 0;
}

void Add_To_Index_Array(CP_Vector index_list[], CP_Vector vector_to_add, int size) {
	for (int i = 0; i < size; ++i) {

		if (!CP_Vector_Length(index_list[i])) { 
			index_list[i] = vector_to_add; 
			break;
		}
	}
}

float Calculate_Cell_Size() {
	float original_resolution = 1080;
	float original_cell_size = 128;

	return ((float)CP_System_GetWindowHeight() / original_resolution * original_cell_size);
}