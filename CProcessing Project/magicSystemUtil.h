/*
File: magicSystemUtil.h
Author: Jason Teo Jun Hao (jasonjunhao.teo)
Description: 
This file will contain declaration of the utilty functions that will be used for the Magic System:
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

#pragma once
#include "cprocessing.h"
#include "magicStructs.h"

//Defined values specifically for magic system
#define GRID_DIMENSIONS 5
#define GRID_CELL_SIZE_OFFSET (float)GRID_CELL_SIZE/2.f
#define NUM_OF_L_PIECE 4
#define NUM_OF_S_PIECE 2
#define CIRCUIT_UI_LIST_SIZE NUM_OF_L_PIECE + NUM_OF_S_PIECE
#define BUFFER 10.f
#define ANGLE_OF_ROTATION 90.f
#define CIRCUIT_L_ASSET_ADDR "Assets/magic_circuit_L.png"
#define CIRCUIT_S_ASSET_ADDR "Assets/magic_circuit_S.png"
#define CIRCUIT_LG_ASSET_ADDR "Assets/magic_circuit_L_G.png"
#define CIRCUIT_LW_ASSET_ADDR "Assets/magic_circuit_L_W.png"
#define CIRCUIT_LF_ASSET_ADDR "Assets/magic_circuit_L_F.png"

/*
Function   : Get_Circuit_Piece_Clicked
Description: This will be used to check if the player is currently holding down mouse button 1 on the CircuitPiece object from the original list
			 of Circuit pieces
Parameters : CircuitPiece c, CP_Vector *initial_position, CP_Vector mouse_position
Return	   : int (true/false)
*/
int Get_Circuit_Piece_Clicked(CircuitPiece c, CP_Vector* initial_position, CP_Vector mouse_position);

/*
Function   : Get_Size_Of_Selected
Description: Check for the array length of the selectedCircuit array
Parameters : CircuitPiece const selected_pieces[GRID_DIMENSIONS][GRID_DIMENSIONS]
Return	   : int (total count of pieces in selected_pieces)
*/
int Get_Size_Of_Selected(CircuitPiece const selectedPieces[GRID_DIMENSIONS][GRID_DIMENSIONS]);

/*
Function   : Circuit_Piece_Selected
Description: Used to find out where the mouse is when the UI for the CircuitPiece is selected and find out which piece was selected.
			 Returns 1 when it finds that a piece was selected
Parameters : CircuitPiece* selected, CircuitPiece list_of_circuits[], CP_Vector mouse_position, int* total_s_pieces
Return	   : int (true/false)
*/
int Circuit_Piece_Selected(CircuitPiece* selected, CircuitPiece list_of_circuits[], CP_Vector mouse_position, int* total_s_pieces);

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
	CircuitPiece selected_piece, CP_Vector index_used[GRID_DIMENSIONS * GRID_DIMENSIONS], CP_Vector mouse_position);

/*
Function   : Check_Placement
Description: Used in Grid_Circuit_Drop to see if the area can be dropped
Parameters : CP_Vector index_used[], CP_Vector index_to_use
Return	   : int (true/false)
*/
int Check_Placement(CP_Vector index_used[], CP_Vector index_to_use, CircuitPiece circuit_pos[GRID_DIMENSIONS][GRID_DIMENSIONS], CircuitPiece selectedPiece);

/*
Function   :Is_Closed_Circuit
Description:Checks the array of struct CircuitPieces and see if the pieces are connected and has completed a loop
Parameters :CP_Vector index_used[], CircuitPiece circuit_pos[GRID_DIMENSIONS][GRID_DIMENSIONS]
Return	   :int (true,false)
*/
int Is_Closed_Circuit(CP_Vector index_used[], CircuitPiece circuit_pos[GRID_DIMENSIONS][GRID_DIMENSIONS]);

/*
Function   : Calculate_Cell_Size()
Description: Caclulates the size of the cells which will scale with the window size
Parameters : void
Return	   : float (new size of the cell)
*/
float Calculate_Cell_Size(void);

/*
Function   : Set_Elemental_Circuit
Description: Loops through the CircuitPiece Array that is used to display the UI and changes the elements for a randomised 3 pieces
Parameters : CircuitPiece pieces_ui[NUM_OF_L_PIECE], CP_Image elemental_image_list[3]
Return	   : void
*/
void Set_Elemental_Circuits(CircuitPiece pieces_ui[NUM_OF_L_PIECE], CP_Image elemental_image_list[3]);

/*
Function   : Add_To_Index_Array
Description: Used in Grid_Circuit_Drop to add to the array of indexes that are currently being used
Parameters : P_Vector index_list[], CP_Vector vector_to_add, int size
Return	   : void
*/
void Add_To_Index_Array(CP_Vector index_list[], CP_Vector vector_to_add, int size);