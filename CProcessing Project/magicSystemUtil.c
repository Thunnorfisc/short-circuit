/*
File: magicSystemUtil.c
Author: Jason Teo Jun Hao (jasonjunhao.teo)
Description: This file will contain definition of the utilty functions that will be used for the Magic System:
int Get_Circuit_Piece_Clicked
int Get_Size_Of_Selected
int Circuit_Piece_Selected
int Grid_Circuit_Drop
int Check_Placement
int Is_Closed_Circuit
float Calculate_Cell_Size
void Set_Elemental_Circuits
void Add_To_Index_Array
*/

#include "magicSystemUtil.h"
#include "generalUtils.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
Function   : Get_Circuit_Piece_Clicked
Description: This will be used to check if the player is currently holding down mouse button 1 on the CircuitPiece object from the original list
			 of Circuit pieces
Parameters : CircuitPiece c, CP_Vector *initial_position, CP_Vector mouse_position
Return	   : int (true/false)
*/
int Get_Circuit_Piece_Clicked(CircuitPiece c, CP_Vector *initial_position, CP_Vector mouse_position) {
	if (CP_Vector_Distance(c.position, mouse_position) < (float)c.circuit_size/2.0f) {
		initial_position = &c.position;
		return 1;
	}
	return 0;
}

/*
Function   : Get_Size_Of_Selected
Description: Check for the array length of the selectedCircuit array
Parameters : CircuitPiece const selected_pieces[GRID_DIMENSIONS][GRID_DIMENSIONS]
Return	   : int (total count of pieces in selected_pieces)
*/
int Get_Size_Of_Selected(CircuitPiece const selected_pieces[GRID_DIMENSIONS][GRID_DIMENSIONS]) {
	int count = 0;

	for (int row = 0; row < GRID_DIMENSIONS; ++row) {
		for (int col = 0; col < GRID_DIMENSIONS; ++col) {
			//Check by using the size to see if there is a circuit in the current address
			if (selected_pieces[row][col].circuit_size) count++;
		}
	}

	return count;
}

/*
Function   : Circuit_Piece_Selected
Description: Used to find out where the mouse is when the UI for the CircuitPiece is selected and find out which piece was selected.
			 Returns 1 when it finds that a piece was selected
Parameters : CircuitPiece* selected, CircuitPiece list_of_circuits[], CP_Vector mouse_position, int* total_s_pieces
Return	   : int (true/false)
*/
int Circuit_Piece_Selected(CircuitPiece* selected, CircuitPiece list_of_circuits[], CP_Vector mouse_position, int* total_s_pieces) {
	for (int i = 0; i < CIRCUIT_UI_LIST_SIZE; ++i) {
		if (CP_Vector_Distance(mouse_position, list_of_circuits[i].position) < GRID_CELL_SIZE_OFFSET) {
			if (*total_s_pieces == 0 && list_of_circuits[i].type == S_Type) {
				return 0;
			}

			*selected = list_of_circuits[i];

			return 1;
		}
	}
	return 0;
}

/*
Function   : Grid_Circuit_Drop
Description: Used to check where the piece was dropped when the mouse is released by checking the coordinates of the mouse and the
			 index of the grid (Checking each position of the cells & mouse position
			 Should not allow for replacement of an existing piece

Parameters : CircuitPiece c, CircuitPiece circuit_pos[GRID_DIMENSIONS][GRID_DIMENSIONS]
			 CP_Vector const grid[GRID_DIMENSIONS][GRID_DIMENSIONS], CP_Vector mouse_position

Return	   : int (true/false)
*/
int Grid_Circuit_Drop(CircuitPiece circuit_pos[GRID_DIMENSIONS][GRID_DIMENSIONS], CP_Vector const grid[GRID_DIMENSIONS][GRID_DIMENSIONS],
	CircuitPiece selected_piece, CP_Vector index_used[GRID_DIMENSIONS * GRID_DIMENSIONS], CP_Vector mouse_position) {

	int test_size = Get_Size_Of_Selected(circuit_pos);

	CP_Vector index_to_use;

	int allowed_placement = 0;

	for (int row = 1; row <= GRID_DIMENSIONS; ++row) {
		for (int col = 1; col <= GRID_DIMENSIONS; ++col) {

			index_to_use = CP_Vector_Set((float)col, (float)row);

			if (!CP_Vector_Length(circuit_pos[col - 1][row - 1].position) && CP_Vector_Distance(mouse_position, grid[col - 1][row - 1]) < GRID_CELL_SIZE_OFFSET) {

				//Check if the current placement is allowed on the board based on the current pieces on the board
				allowed_placement = Check_Placement(index_used, index_to_use, circuit_pos, selected_piece);

				if (allowed_placement) {
					circuit_pos[col - 1][row - 1] = New_Circuit_Piece(
						CP_Vector_Set(grid[col - 1][row - 1].x, grid[col - 1][row - 1].y),
						selected_piece.image,
						selected_piece.IO_1, selected_piece.IO_2, selected_piece.rot,selected_piece.circuit_size,selected_piece.type
					);
					Set_Circuit_Element(&(circuit_pos[col - 1][row - 1]), selected_piece.element, selected_piece.image);
					//Add to array to track the current used row and column
					Add_To_Index_Array(index_used, index_to_use, GRID_DIMENSIONS * GRID_DIMENSIONS);

					circuit_pos[col - 1][row - 1].circuit_size = GRID_CELL_SIZE;

					return 1;
				}
			}
		}
	}
	return 0;
}

/*
Function   : Check_Placement
Description: Used in Grid_Circuit_Drop to see if the area can be dropped
Parameters : CP_Vector index_used[], CP_Vector index_to_use
Return	   : int (true/false)
*/
int Check_Placement(CP_Vector index_used[], CP_Vector index_to_use, CircuitPiece circuit_pos[GRID_DIMENSIONS][GRID_DIMENSIONS], CircuitPiece selected_piece) {

	/* Check if adjacent and return the start and end of the circuits */
	if (CP_Vector_Length(index_used[0]) == 0) return 1;
	
	else {
		//Check if the new position for placement is right beside horizontally or vertically
		for (int i = 0; CP_Vector_Length(index_used[i]); ++i) { //Checks until the last initialized index
			if (CP_Vector_Distance(index_to_use, index_used[i]) == 1) {

				//Check if the placement is also within the possible IO = 0
				if (circuit_pos[(int)index_used[i].x - 1][(int)index_used[i].y - 1].IO_1 == 0 ||
					circuit_pos[(int)index_used[i].x - 1][(int)index_used[i].y - 1].IO_2 == 0) {
					if ((selected_piece.IO_1 == 2 || selected_piece.IO_2 == 2) && index_used[i].y - index_to_use.y == 1) return 1;
				}

				//Check if the placement is also within the possible IO = 1
				if (circuit_pos[(int)index_used[i].x - 1][(int)index_used[i].y - 1].IO_1 == 1 ||
						 circuit_pos[(int)index_used[i].x - 1][(int)index_used[i].y - 1].IO_2 == 1) {
					if ((selected_piece.IO_1 == 3 || selected_piece.IO_2 == 3) && index_used[i].x - index_to_use.x == 1) return 1;
				}

				//Check if the placement is also within the possible IO = 2
				if (circuit_pos[(int)index_used[i].x - 1][(int)index_used[i].y - 1].IO_1 == 2 ||
						 circuit_pos[(int)index_used[i].x - 1][(int)index_used[i].y - 1].IO_2 == 2) {
					if ((selected_piece.IO_1 == 0 || selected_piece.IO_2 == 0) && index_to_use.y - index_used[i].y == 1) return 1;
				}

				//Check if the placement is also within the possible IO = 3
				if(circuit_pos[(int)index_used[i].x - 1][(int)index_used[i].y - 1].IO_1 == 3 ||
					circuit_pos[(int)index_used[i].x - 1][(int)index_used[i].y - 1].IO_2 == 3){
					if ((selected_piece.IO_1 == 1 || selected_piece.IO_2 == 1) && index_to_use.x - index_used[i].x == 1) return 1;
				}
			}
		}
	}
	/* End of check if adjacent */
	return 0;
}


/*
Function   : Is_Closed_Circuit
Description: Checks the array of struct CircuitPieces and see if the pieces are connected and has completed a loop
Parameters : CP_Vector index_used[], CircuitPiece circuit_pos[GRID_DIMENSIONS][GRID_DIMENSIONS]
Return	   : int (true,false)
*/
int Is_Closed_Circuit(CP_Vector index_used[], CircuitPiece circuit_pos[GRID_DIMENSIONS][GRID_DIMENSIONS]) {

	int count = 0;
	while (CP_Vector_Length(index_used[count])) {
		count++;
	}

	if (count == 0) return 0;
	int k;
	CircuitPiece to_check;

	int count_connected = 0;

	//Check by clockwise, if the length of the another piece is 1 in terms of the array index, then it is connected.
	//If the number of connected pieces is = to the total count of circuits then its a closed circuit? TRUE
	for (int i = 0; i < count; ++i) {
		k = i < count ? i : 0;
		for (int j = 0; j < count; ++j) {
			if (CP_Vector_Distance(index_used[i], index_used[k]) == 1) {
				to_check = circuit_pos[(int)index_used[k].x - 1][(int)index_used[k].y - 1];
				//Check if the placement is also within the possible IO = 0
				if (circuit_pos[(int)index_used[i].x - 1][(int)index_used[i].y - 1].IO_1 == 0 ||
					circuit_pos[(int)index_used[i].x - 1][(int)index_used[i].y - 1].IO_2 == 0) {
					if ((to_check.IO_1 == 2 || to_check.IO_2 == 2) && index_used[i].y - index_used[k].y == 1) count_connected++;
				}

				//Check if the placement is also within the possible IO = 1
				if (circuit_pos[(int)index_used[i].x - 1][(int)index_used[i].y - 1].IO_1 == 1 ||
					circuit_pos[(int)index_used[i].x - 1][(int)index_used[i].y - 1].IO_2 == 1) {
					if ((to_check.IO_1 == 3 || to_check.IO_2 == 3) && index_used[i].x - index_used[k].x == 1) count_connected++;
				}

				//Check if the placement is also within the possible IO = 2
				if (circuit_pos[(int)index_used[i].x - 1][(int)index_used[i].y - 1].IO_1 == 2 ||
					circuit_pos[(int)index_used[i].x - 1][(int)index_used[i].y - 1].IO_2 == 2) {
					if ((to_check.IO_1 == 0 || to_check.IO_2 == 0) && index_used[k].y - index_used[i].y == 1) count_connected++;
				}

				//Check if the placement is also within the possible IO = 3
				if (circuit_pos[(int)index_used[i].x - 1][(int)index_used[i].y - 1].IO_1 == 3 ||
					circuit_pos[(int)index_used[i].x - 1][(int)index_used[i].y - 1].IO_2 == 3) {
					if ((to_check.IO_1 == 1 || to_check.IO_2 == 1) && index_used[k].x - index_used[i].x == 1) count_connected++;
				}
			}
			k = k >= count - 1 ? 0 : k + 1;
		}
	}
	return count_connected/2 == count;
}

/*
Function   : Calculate_Cell_Size()
Description: Caclulates the size of the cells which will scale with the window size
Parameters : void
Return	   : float (new size of the cell)
*/
float Calculate_Cell_Size() {
	float original_cell_size = 128.f;
	return (WINDOW_RATIO * original_cell_size);
}

/*
Function   : Set_Elemental_Circuit
Description: Loops through the CircuitPiece Array that is used to display the UI and changes the elements for a randomised 3 pieces
Parameters : CircuitPiece pieces_ui[NUM_OF_L_PIECE], CP_Image elemental_image_list[3]
Return	   : void
*/
void Set_Elemental_Circuits(CircuitPiece pieces_ui[NUM_OF_L_PIECE], CP_Image elemental_image_list[4]) {
	srand((unsigned int)time(NULL));
	int random_index, random_element;
	int random_index_arr[4];

	//Choosing which circuit piece to change the element
	for (int i = 0; i < 4;) {
		random_index = CP_Random_RangeInt(0, NUM_OF_L_PIECE - 1);
		if (!Exist_In_Array(&random_index, random_index_arr, A_INT, NUM_OF_L_PIECE)) {
			random_index_arr[i] = random_index;
			++i;
		}
	}

	ElementType elements[] = { Element_Grass,Element_Water,Element_Fire};
	int random_element_arr[3];

	for (int i = 0; i < NUM_OF_L_PIECE;) {
		random_element = CP_Random_RangeInt(0, 2);
		if (i < 3) {
			if (!Exist_In_Array(&random_element, random_element_arr, A_INT, 3)) {
				Set_Circuit_Element(&(pieces_ui[random_index_arr[i]]), elements[random_element], elemental_image_list[random_element]);
				random_element_arr[i] = random_element;
				++i;
			}
		}
		else {
			pieces_ui[random_index_arr[i]].type = Element_None;
			pieces_ui[random_index_arr[i]].image = elemental_image_list[i];
			++i;
		}
	}
}

/*
Function   : Add_To_Index_Array
Description: Used in Grid_Circuit_Drop to add to the array of indexes that are currently being used
Parameters : P_Vector index_list[], CP_Vector vector_to_add, int size
Return	   : void
*/
void Add_To_Index_Array(CP_Vector index_list[], CP_Vector vector_to_add, int size) {
	for (int i = 0; i < size; ++i) {

		if (!CP_Vector_Length(index_list[i])) {
			index_list[i] = vector_to_add;
			break;
		}
	}
}
