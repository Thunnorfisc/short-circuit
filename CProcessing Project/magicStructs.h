/*
File: magicStructs.h
Description: This will be the file that holds the structs that will be used solely for the magic system.
*/

#pragma once
#include "cprocessing.h"

#define GRID_CELL_SIZE Calculate_Cell_Size()

//This is the struct that will be used to create the pieces for the magic circuit system
typedef struct CircuitPiece {
	
	//This will be used to set the position of the piece
	CP_Vector centerPosition;

	//These are the directions that will be set in the struct
	//Directions will be represented by int 0 - 3
	// 0: left, 1: up, 2: right, 3: down 
	int IO_1;
	int IO_2;

	//Rotation of the pipe
	int rot;

	//Size of the CircuitPiece
	int circuitSize;

} CircuitPiece;

/*
Here onwards will be functions used to initialize/get/set the values for the above structs
*/

/*
Function: New_Circui_Piece
Parameters: CP_Image,CP_Vector, int IO_1, int IO_2, int rot
Usage: This will be used to initialize a new circuit piece game object
*/
CircuitPiece New_Circuit_Piece(CP_Vector v, int io_1, int io_2, int rot);