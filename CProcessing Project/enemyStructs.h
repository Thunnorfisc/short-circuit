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
// Enum for different enemy types
typedef enum EnemyTypes {
	E_Wizard, 
	E_Plant, 
	E_Vulture 
} EnemyTypes;


// Enum for the enemy elemental weaknesses
typedef enum ElementType {
	Element_Fire,
	Element_Grass,
	Element_Water
} ElementType;

// Struct for enemy
typedef struct Enemy {
	EnemyTypes enemy_type;
	int attack;
	ElementType weakness;
	int healthbar;
	ElementType resistance;
	int criticaldmg;
	int is_boss;
	CP_Vector position;
} Enemy;



/*
Here onwards will be functions used to initialize/get/set the values for the above structs
*/


Enemy initializeEnemy(EnemyTypes type, CP_Vector v);


void Enemy_Initialize_Array(Enemy enemies[3], CP_Vector gridLocation[GRID_DIMENSIONS][GRID_DIMENSIONS], int num_to_generate);

