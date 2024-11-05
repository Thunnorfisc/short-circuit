#include <stdio.h>
#include "generalUtils.h"
#include "magicSystem.h"

////Image of the circuit pieces
//CP_Image circuit_image_l;
//
////List of all the circuit pieces the player can use
//CircuitPiece circuit_list_l[CIRCUIT_UI_LIST_SIZE];
//CircuitPiece circuit_pieces_s[2];
//
////Circuit Piece Selected
//CircuitPiece circuit_selected_list[GRID_DIMENSIONS][GRID_DIMENSIONS] = { 0 };
//CircuitPiece circuit_piece_selected = { 0 };
//int selected_circuit_piece = 0;
//
////mouse vector that will be updated when mouse down is detected
//CP_Vector mouse_position = { 0 };
//
////TEST VALUES
////Grids that will be used to test if the circuits can be displayed
//CP_Vector grid_squares[GRID_DIMENSIONS][GRID_DIMENSIONS];

//void Magic_System_Init(void)
//{
//	//Loading the image for the Magic Circuit's L Piece
//	circuit_image_l = CP_Image_Load("Assets/magic_circuit_L.png");
//
//	/*------------Calculating the buffer for the display location of the UI---------- */
//	float circuit_ui_buffer_top = (float)(GRID_DIMENSIONS * CIRCUIT_PIECE_SIZE + CIRCUIT_CENTER_OFFSET * 4);
//	float circuit_ui_buffer_left = (float)(WINDOW_WIDTH - (CIRCUIT_PIECE_SIZE * CIRCUIT_UI_LIST_SIZE + BUFFER * (CIRCUIT_UI_LIST_SIZE - 1))) / 2.f;
//
//	//This loop will initialize the ciruits to be displayed on the UI for selection
//	for (int i = 0, j = i + 1; i < 4; ++i, j = j < 3 ? j + 1 : 0) {
//		circuit_list_l[i] = New_Circuit_Piece(
//			CP_Vector_Set(circuit_ui_buffer_left + (float)CIRCUIT_PIECE_SIZE/2.f + CIRCUIT_PIECE_SIZE * i + BUFFER * i, circuit_ui_buffer_top)
//			, i, j, i);
//		circuit_list_l[i].circuitSize = CIRCUIT_PIECE_SIZE;
//	}
//	/*-------------------------------------------------------------------------------- */
//
//	//Setting Modes for display
//	CP_Settings_ImageMode(CP_POSITION_CENTER);
//	CP_Settings_RectMode(CP_POSITION_CENTER);
//
//	//TEST (initialize the grids for testing)
//	Grid_Initialize(grid_squares);
//}
//
//void Magic_System_Update(void)
//{
//	CP_Graphics_ClearBackground(BACKGROUND_COLOR);
//
//	/* --------------- This Section will be to check for the functions that can run when mouse is interacted -------------*/
//	if (CP_Input_MouseDown(MOUSE_BUTTON_1)) {
//		mouse_position = CP_Vector_Set(CP_Input_GetMouseX(), CP_Input_GetMouseY());
//
//		//Function to check which circuit piece is selected
//		if(!selected_circuit_piece)
//		selected_circuit_piece = Circuit_PieceSelected(&circuit_piece_selected,circuit_list_l);
//
//		//Check if the mouse is at the area of the circuits
//		TEST_checkMouseGrid(grid_squares);
//	}
//	else if(CP_Input_MouseReleased(MOUSE_BUTTON_1)){
//		if (selected_circuit_piece) {
//			Grid_Cricuit_Drop(circuit_piece_selected, circuit_selected_list, grid_squares);
//			selected_circuit_piece = 0;
//		}
//	}
//	/* --------------------------------------------------------------------------------------------------------------------*/
//	//Display all the assets
//	Display_Assets();
//
//	if (selected_circuit_piece) {
//		CP_Image_DrawAdvanced(
//			circuit_image_l, mouse_position.x, mouse_position.y,
//			(float)circuit_piece_selected.circuitSize, (float)circuit_piece_selected.circuitSize, 255, (float)circuit_piece_selected.rot * ANGLE_OF_ROTATION);
//	}
//}
//
//void Magic_System_Exit()
//{
//	CP_Image_Free(&circuit_image_l);
//}

//void Display_Assets() 
//{
//	//Display Grid to Drag and Drop into
//	Grid_Display(grid_squares);
//	Draw_L_CircuitPiece(circuit_list_l, CIRCUIT_UI_LIST_SIZE);
//	Draw_SelectedCircuitPieces(circuit_selected_list);
//}

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

int Circuit_PieceSelected(CircuitPiece* selected, CircuitPiece list_of_circuits[], CP_Vector mouse_position) {
	for (int i = 0; i < CIRCUIT_UI_LIST_SIZE; ++i) {
		if (CP_Vector_Distance(mouse_position, list_of_circuits[i].centerPosition) < CIRCUIT_CENTER_OFFSET) {
			*selected = list_of_circuits[i];

			return 1;
		}
	}
	return 0;
}

int Grid_Cricuit_Drop(CircuitPiece c, CircuitPiece circuit_pos[GRID_DIMENSIONS][GRID_DIMENSIONS], CP_Vector const grid[GRID_DIMENSIONS][GRID_DIMENSIONS], CP_Vector mouse_position) {
	for (int row = 0; row < GRID_DIMENSIONS; ++row) {
		for (int col = 0; col < GRID_DIMENSIONS; ++col) {
			if (CP_Vector_Distance(mouse_position, grid[row][col]) < CIRCUIT_CENTER_OFFSET) {
				//printf("Row: %d, Col: %d, Vector(%f,%f)\n\n",row,col, grid[row][col].x, grid[row][col].y);
				circuit_pos[row][col] = New_Circuit_Piece(
					CP_Vector_Set(grid[row][col].x, grid[row][col].y),
					c.IO_1, c.IO_2, c.rot
				);
				circuit_pos[row][col].circuitSize = CIRCUIT_PIECE_SIZE;
				return 1;
			}
		}
	}
	return 0;
}
//TEST FUNCTIONS

/*
Description:
Used to Check where the mouse clicked in the grid

Parameters:
CP_Vector mouse_pos, CP_Vector grid[][];
*/
//void TEST_checkMouseGrid(CP_Vector grid[GRID_DIMENSIONS][GRID_DIMENSIONS]) {
//	for (int row = 0; row < GRID_DIMENSIONS; ++row) {
//		for (int col = 0; col < GRID_DIMENSIONS; ++col) {
//			if (CP_Vector_Distance(mouse_position, grid[row][col]) < CIRCUIT_CENTER_OFFSET) {
//				//printf("Row: %d, Col: %d, Vector(%f,%f)\n\n",row,col, grid[row][col].x, grid[row][col].y);
//
//			}
//		}
//	}
//}

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
			CP_Graphics_DrawRect(grid[row][col].x, grid[row][col].y, CIRCUIT_PIECE_SIZE, CIRCUIT_PIECE_SIZE);
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
	int total_size_of_grid = GRID_DIMENSIONS * CIRCUIT_PIECE_SIZE;

	//Calculating the left-most buffer
	float left_buffer = (float)(WINDOW_WIDTH - total_size_of_grid) / 2.f + CIRCUIT_CENTER_OFFSET;
	//Calculating the top buffer
	float top_buffer = (float)CIRCUIT_PIECE_SIZE + CIRCUIT_CENTER_OFFSET;

	//This will make all the vectors for the grid
	for (int row = 0 ; row < GRID_DIMENSIONS; ++row) {
		for (int col = 0; col < GRID_DIMENSIONS; ++col) {
			grid[row][col] = CP_Vector_Set(
				left_buffer + CIRCUIT_PIECE_SIZE * col,
				top_buffer + CIRCUIT_PIECE_SIZE * row);
			
		}
	}

	return;
}