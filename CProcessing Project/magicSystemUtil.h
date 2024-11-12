/*
File: magicSystem.h
Author: Jason Teo Jun Hao (jasonjunhao.teo)
Description: This file will contain utilty functions that will be used for the Magic System
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
Description:
This will be used to check if the player is currently holding down mouse button 1 on the CircuitPiece object from the original list
of Circuit pieces

Parameters:
CircuitPiece c, CP_Vector* initial_position, int mouseX, int mouseY

Return:
int that will represent true or false
*/
int Get_Circuit_Piece_Clicked(CircuitPiece c, CP_Vector* initial_position, int mouseX, int mouseY);

/*
Description:
Check for the array length of the selectedCircuit array

Parameters:
CircuitPiece selectedPieces[]

Return:
int: the size of the given array
*/
int Get_Size_Of_Selected(CircuitPiece const selectedPieces[GRID_DIMENSIONS][GRID_DIMENSIONS]);

int Circuit_Piece_Selected(CircuitPiece* selected, CircuitPiece list_of_circuits[], CP_Vector mouse_position, int* total_s_pieces);

int Grid_Circuit_Drop(CircuitPiece circuit_pos[GRID_DIMENSIONS][GRID_DIMENSIONS], CP_Vector const grid[GRID_DIMENSIONS][GRID_DIMENSIONS],
	CircuitPiece selected_piece, CP_Vector index_used[GRID_DIMENSIONS * GRID_DIMENSIONS], CP_Vector mouse_position);
/*
Function: Available_Circuit_Positions

Parameters: CircuitPiece *piece, CircuitPiece selectedPieces[], CP_Vector grid[GRID_DIMENSIONS][GRID_DIMENSIONS]

Usage: This will be used to check if the player is currently holding down mouse button 1 on the CircuitPiece object from the original list
of Circuit pieces
*/

void Add_To_Index_Array(CP_Vector index_list[], CP_Vector vector_to_add, int size);

int Check_Placement(CP_Vector index_used[], CP_Vector index_to_use, CircuitPiece circuit_pos[GRID_DIMENSIONS][GRID_DIMENSIONS], CircuitPiece selectedPiece);

float Calculate_Cell_Size(void);

void Set_Elemental_Circuits(CircuitPiece pieces_ui[NUM_OF_L_PIECE], CP_Image elemental_image_list[3]);