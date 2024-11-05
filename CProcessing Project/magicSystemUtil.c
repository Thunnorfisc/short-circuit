/*
File: magicSystem.c
Author: Jason Teo Jun Hao (jasonjunhao.teo)
Description: This file will contain utilty functions that will be used for the Magic System
*/

#include "magicSystemUtil.h"
#include "magicStructs.h"
#include <math.h>

/*
Function: MouseDownOnPieceFromList
Parameters:
Usage: This will be used to check if the player is currently holding down mouse button 1 on the CircuitPiece object from the original list
of Circuit pieces
*/
int Get_Circuit_Piece_Clicked(CircuitPiece c, CP_Vector *initial_position, int mouse_x, int mouse_y) {
	CP_Vector mouse_vector = CP_Vector_Set((float)mouse_x, (float)mouse_y);
	if (CP_Vector_Distance(c.centerPosition, mouse_vector) < c.circuitSize/2) {
		initial_position = &c.centerPosition;
		return 1;
	}
	return 0;
}