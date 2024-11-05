/*
File: enemyStructs.h
Description: This will be the file that holds the structs that will be used to generate enemies that
will be used in the game
*/

#pragma once
#include "generalUtils.h"
#include "magicSystem.h"

#define ENEMY_SIZE_SCALING 3

// Data type is EnemyTypes
// 3 different type of normal enemy: Wizard, Spawner, Vulture
typedef enum { E_Wizard = 1, E_Spawner, E_Vulture } EnemyTypes;

typedef struct Enemy {
	EnemyTypes enemy_type;
	int id;
	int attack;
	int weakness;
	int healthbar;

};


//This is the struct that will be used to create the pieces for the magic circuit system
typedef struct E_Mage {

	//This will be used to set the position of the E_Mage
	CP_Vector position;
	//Set Damage here

	
} E_Mage;

/*
Here onwards will be functions used to initialize/get/set the values for the above structs
*/

/*
Function: E_Mage_Initialize
Parameters: CP_Vector v
Usage: This will be used to initialize a new e_mage object
*/
E_Mage E_Mage_Initialize(CP_Vector v); //To be edited to fit the struct

void E_Mage_Initialize_Array(E_Mage e_mage_arr[3], CP_Vector gridLocation[GRID_DIMENSIONS][GRID_DIMENSIONS], int const num_to_generate);