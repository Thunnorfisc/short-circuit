/*
File: enemyStructs.h
Description: This will be the file that holds the structs that will be used to generate enemies that
will be used in the game
*/

#pragma once
#include "generalUtils.h"
#include "magicSystem.h"
#include "TEST_playerStruct.h"
#include <stdio.h>

//Total number of different enemy types
#define ENEMY_COUNT 3

// Data type is EnemyTypes
// Enum for different enemy types
typedef enum EnemyTypes {
	E_Wizard, 
	E_Plant, 
	E_Vulture 
} EnemyTypes;

// Struct for enemy
typedef struct Enemy {
	int attack;
	int initiative;
	float healthbar;
	float resist_multiplier;
	CP_Vector position;
	EnemyTypes enemy_type;
	ElementType weakness;
	ElementType resistance;
	
	
} Enemy;

/*
Here onwards will be functions used to initialize/get/set the values for the above structs
*/

Enemy Enemy_Arr_Initialize(EnemyTypes type, CP_Vector v);

void Enemy_Initialize_Array(Enemy enemies[ENEMY_COUNT], CP_Vector gridLocation[GRID_DIMENSIONS][GRID_DIMENSIONS], int num_to_generate, int do_randomise_enemy);

/*
Function   : Check_Enemy_Hit
Description: Used to check which enemy was attacked
Parameters : Enemy enemy_arr[3], CP_Vector index_used[], CircuitPiece selected_pieces[GRID_DIMENSIONS][GRID_DIMENSIONS], Player player
Return	   : void
*/
void Check_Enemy_Hit(Enemy enemy_arr[3], CP_Vector index_used[], CircuitPiece selected_pieces[GRID_DIMENSIONS][GRID_DIMENSIONS], Player player);

/*
Function   : Enemy_Calculate_Damage
Description: Used to calculate the amount of damage that is dealt to the enemy
Parameters : Enemy* enemy, Player const player, CircuitPiece piece_that_hit, int number_of_pipes, int num_of_enemies_hit
Return	   : void
*/
void Enemy_Calculate_Damage(Enemy* enemy, Player const player, CircuitPiece piece_that_hit, int number_of_pipes, int num_of_enemies_hit);

/*
Function   : Enemy_Damage_Player
Description: Used to calculate the amount of damage the enemy will do
Parameters : Enemy enemy, Player* player
Return	   : void
*/
void Enemy_Damage_Player(Enemy enemy[ENEMY_COUNT], Player* player);