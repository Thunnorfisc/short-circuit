#pragma once
#include "magicSystemUtil.h"

void Draw_UI_CircuitPiece(CircuitPiece c[], CP_Image circuit_image_l, int N);

void Draw_SelectedCircuitPieces(CircuitPiece selected[GRID_DIMENSIONS][GRID_DIMENSIONS]);

void Grid_Display(CP_Vector const v[GRID_DIMENSIONS][GRID_DIMENSIONS]);

void Grid_Initialize(CP_Vector v[GRID_DIMENSIONS][GRID_DIMENSIONS]);