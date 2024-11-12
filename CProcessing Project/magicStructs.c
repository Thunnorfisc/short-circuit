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
CircuitPiece New_Circuit_Piece(CP_Vector v,CP_Image piece_image, int io_1, int io_2, int rot, int size, CircuitType type) {
	CircuitPiece new_piece;
	new_piece.type = type;
	new_piece.image = piece_image;
	new_piece.position = v;
	new_piece.circuit_size = size;
	new_piece.IO_1 = io_1;
	new_piece.IO_2 = io_2;
	new_piece.rot = rot;
	return new_piece;
}

void Set_Circuit_Element(CircuitPiece* circuit_piece, CircuitElement element, CP_Image elemental_image) {
	circuit_piece->element = element;
	circuit_piece->image = elemental_image;
}