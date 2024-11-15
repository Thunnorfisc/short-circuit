/*
File: magicStruct.h
Author: Jason Teo Jun Hao (jasonjunhao.teo)
Description:
This file will contain declaration of the "get, set" functions that will be used for the struct CircuitPiece
and the struct CircuitPiece and enums for the CircuitType and CircuitElement in Magic System:

CircuitPiece New_Circuit_Piece
void Set_Circuit_Element
*/

#pragma once
#include "cprocessing.h"

#define GRID_CELL_SIZE Calculate_Cell_Size()

/*
enum       : CircuitType
Description: This is the enum that will be used to set type in CircuitPiece
Parameters :
- L_Type : 0;
- S_Type : 1;
*/
typedef enum CircuitType{
	L_Type,
	S_Type

} CircuitType;

/*
enum       : ElementType
Description: This is the enum that will be used to set elements in CircuitPiece
Parameters : 
- Grass : 0;
- Water : 1;
- Fire  : 2;
- None  : -1;
*/
// Enum for the enemy elemental weaknesses
typedef enum ElementType {
	Element_Grass,
	Element_Water,
	Element_Fire,
	Element_None,
} ElementType;

/*
Struct     : CircuitPiece
Description: This is the struct that will be used to create CircuitPiece objects
Parameters : CP_Vector position, CP_Image image, CircuitType type, 
			 int IO_1, int IO_2, int rot, int circuit_size, CircuitElement element
*/
typedef struct CircuitPiece {
	
	//This will be used to set the position of the piece
	CP_Vector position;

	//This will be the image that the Circuit Piece will use
	CP_Image image;

	CircuitType type;

	//These are the directions that will be set in the struct
	//Directions will be represented by int 0 - 3
	// 0: left, 1: up, 2: right, 3: down 
	int IO_1;
	int IO_2;

	//Rotation of the pipe
	int rot;

	//Size of the CircuitPiece
	float circuit_size;

	//Element of the CircuitPiece
	ElementType element;

} CircuitPiece;

/*
Here onwards will be functions used to initialize/get/set the values for the above structs
*/

/*
Function   : New_Circuit_Piece
Description: This will be used to initialize a new circuit piece game object
Parameters : CP_Vector v,CP_Image piece_image, int io_1, int io_2, int rot, int size, CircuitType type
Return	   : CircuitPiece new_circuit_piece
*/
CircuitPiece New_Circuit_Piece(CP_Vector position, CP_Image image, int io_1, int io_2, int rot, float size, CircuitType type);

/*
Function   : Set_Circuit_Element
Description: This will be used to change the element of the Circuit Object
Parameters : CircuitPiece* circuit_piece, CircuitElement element, CP_Image elemental_image
Return	   : void
*/
void Set_Circuit_Element(CircuitPiece* circuit_piece, ElementType element, CP_Image elemental_image);