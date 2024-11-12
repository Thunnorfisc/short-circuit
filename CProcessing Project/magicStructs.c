/*
File: magicStructs.c
Description: This will be the file that holds the structs that will be used solely for the magic system.
*/

#include "magicStructs.h"

/*
Here onwards will be functions used to initialize/get/set the values for the above structs
*/

/*
Function: New_Circuit_Piece
Parameters: CP_Image,CP_Vector, int IO_1, int IO_2, int rot
Usage: This will be used to initialize a new circuit piece game object
*/
CircuitPiece New_Circuit_Piece(CP_Vector v, int io_1, int io_2, int rot) {
	CircuitPiece newPiece;
	newPiece.centerPosition = v;
	newPiece.circuitSize = GRID_CELL_SIZE;
	newPiece.IO_1 = io_1;
	newPiece.IO_2 = io_2;
	newPiece.rot = rot;
	return newPiece;
}