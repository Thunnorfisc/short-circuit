/*
File: magicSystem.h
Author: Jason Teo Jun Hao (jasonjunhao.teo)
Description:
This file will contain declaration of the display and initialize functions that will be used for the Magic System:
void Draw_UI_CircuitPiece
void Draw_SelectedCircuitPieces
void Grid_Display
void Grid_Initialize
*/

#pragma once
#include "magicSystemUtil.h"

/*
Function   : Draw_UI_CircuitPiece
Description: Used to display the UI of Circuit Pieces the player will click and drag from.
Parameters : CircuitPiece list_of_circuit_pieces[], int size_of_array
Return	   : void
*/
void Draw_UI_CircuitPiece(CircuitPiece c[], CP_Image circuit_image_l, int N, int s_count);

/*
Function   : Draw_SelectedCircuitPieces
Description: Used to display the Circuit pieces the payer chose to drop into the grid
Parameters : CircuitPiece selected[GRID_DIMENSIONS][GRID_DIMENSIONS], CP_Image circuit_image_l
Return	   : void
*/
void Draw_SelectedCircuitPieces(CircuitPiece selected[GRID_DIMENSIONS][GRID_DIMENSIONS]);

/*
Function   : Grid_Display
Description: Used to display the grid that the circuit pieces can be dropped into.
			 This function calls the function Grid_Display
Parameters : CP_Vector const grid[GRID_DIMENSIONS][GRID_DIMENSIONS]
Return	   : void
*/
void Grid_Display(CP_Vector const v[GRID_DIMENSIONS][GRID_DIMENSIONS]);

/*
Function   : Grid_Initialize
Description: Used to initialize the list of vectors that will be used to generate the
			 grid.
Parameters : CP_Vector grid[GRID_DIMENSIONS][GRID_DIMENSIONS]
Return	   : void
*/
void Grid_Initialize(CP_Vector v[GRID_DIMENSIONS][GRID_DIMENSIONS]);