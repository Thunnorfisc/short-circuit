/*
File: magicStruct.c
Author: Jason Teo Jun Hao (jasonjunhao.teo)
Description:
This file will contain definition of the "get, set" functions that will be used for the struct CircuitPiece in Magic System:
CircuitPiece New_Circuit_Piece
void Set_Circuit_Element
*/

#include "magicStructs.h"

/*
Function   : New_Circuit_Piece
Description: This will be used to initialize a new circuit piece game object
Parameters : CP_Vector v,CP_Image piece_image, int io_1, int io_2, int rot, int size, CircuitType type
Return	   : CircuitPiece new_circuit_piece
*/
CircuitPiece New_Circuit_Piece(CP_Vector v,CP_Image piece_image, int io_1, int io_2, int rot, int size, CircuitType type) {
	CircuitPiece new_piece = { 0 };
	new_piece.type = type;
	new_piece.image = piece_image;
	new_piece.position = v;
	new_piece.circuit_size = size;
	new_piece.IO_1 = io_1;
	new_piece.IO_2 = io_2;
	new_piece.rot = rot;
	return new_piece;
}

/*
Function   : Set_Circuit_Element
Description: This will be used to change the element of the Circuit Object
Parameters : CircuitPiece* circuit_piece, CircuitElement element, CP_Image elemental_image
Return	   : void
*/
void Set_Circuit_Element(CircuitPiece* circuit_piece, CircuitElement element, CP_Image elemental_image) {
	circuit_piece->element = element;
	circuit_piece->image = elemental_image;
}