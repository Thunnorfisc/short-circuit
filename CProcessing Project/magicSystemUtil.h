/*
File: magicSystem.h
Author: Jason Teo Jun Hao (jasonjunhao.teo)
Description: This file will contain utilty functions that will be used for the Magic System
*/

#pragma once
#include "cprocessing.h"
#include "magicStructs.h"

/*
Function: MouseDownOnPieceFromList
Parameters: 
Usage: This will be used to check if the player is currently holding down mouse button 1 on the CircuitPiece object from the original list
of Circuit pieces
*/
int Get_Circuit_Piece_Clicked(CircuitPiece c, CP_Vector* initial_position, int mouseX, int mouseY);
