#pragma once
#include "magicSystemUtil.h"

//Defined values specifically for magic system
#define GRID_DIMENSIONS 5
#define CIRCUIT_CENTER_OFFSET (float)CIRCUIT_PIECE_SIZE/2.f
#define CIRCUIT_UI_LIST_SIZE 4
#define BUFFER 10.f
#define ANGLE_OF_ROTATION 90.f
#define CIRCUIT_L_ASSET_ADDR "Assets/magic_circuit_L.png"

//void Magic_System_Init(void);
//void Magic_System_Update(void);
//void Magic_System_Exit(void);
//void Display_Assets(void); 

void Draw_L_CircuitPiece(CircuitPiece c[], CP_Image circuit_image_l, int N);

void Draw_SelectedCircuitPieces(CircuitPiece selected[GRID_DIMENSIONS][GRID_DIMENSIONS], CP_Image circuit_image_l);

int Circuit_PieceSelected(CircuitPiece* selected, CircuitPiece list_of_circuits[], CP_Vector mouse_position);

int Grid_Cricuit_Drop(CircuitPiece c, CircuitPiece circuit_pos[GRID_DIMENSIONS][GRID_DIMENSIONS], CP_Vector const grid[GRID_DIMENSIONS][GRID_DIMENSIONS], CP_Vector mouse_position);

void Grid_Display(CP_Vector const v[GRID_DIMENSIONS][GRID_DIMENSIONS]);

void Grid_Initialize(CP_Vector v[GRID_DIMENSIONS][GRID_DIMENSIONS]);