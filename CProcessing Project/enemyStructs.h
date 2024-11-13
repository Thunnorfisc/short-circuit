/*
File: enemyStructs.h
Description: This will be the file that holds the structs that will be used to generate enemies that
will be used in the game
*/

#pragma once
#include "generalUtils.h"
#include "magicSystem.h"
#include <stdio.h>

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
Struct     : BossPart
Description: This is the struct that will be used to create BossPart objects and used to create Boss Objects
Parameters :
int initiative : The "Speed" of the Boss Part to attack the player
int healthbar  : The health bar of the Boss Part
CP_Image image : Image of the Boss Part
CP_Vector pos  : Position of the Boss Part
ElementType weakness   : Weakness of the Boss Part
ElementType resistance : Resistance of the Boss Part
*/
typedef struct BossPart {
	int initiative;
	int healthbar;
	CP_Image image;
	CP_Vector pos;
	ElementType weakness;
	ElementType resistance;
}BossPart;

/*
Struct     : Boss
Description: This is the struct that will be used to create Boss objects
Parameters :
int boss_id      : The ID of the boss to read from JSON File
int enrage_time  : The number of turns until the Boss goes into enrage
char* boss_name  : Name of the boss to display
BossPart parts[] : Array of the BossParts

*/
typedef struct Boss {
	int boss_id;
	int enrage_time;
	char* boss_name;
	BossPart parts[];
}Boss;


/*
Here onwards will be functions used to initialize/get/set the values for the above structs
*/


Enemy initializeEnemy(EnemyTypes type, CP_Vector v);


void Enemy_Initialize_Array(Enemy enemies[3], CP_Vector gridLocation[GRID_DIMENSIONS][GRID_DIMENSIONS], int num_to_generate);

int Check_Enemy_Hit(Enemy enemy_attacked[3], Enemy enemy_arr[3], CP_Vector index_used[], CircuitPiece selected_pieces[GRID_DIMENSIONS][GRID_DIMENSIONS]);


/*
Function   : BossParts_Initialize
Description: Used to initialize the bodypart array in the Boss Struct
Parameters : BossPart bp[], int initiative, int healthbar, CP_Image image, CP_Vector pos, ElementType weakness, ElementType resistance, int number_of_parts
Return	   : void
*/
void BossParts_Initialize(BossPart bp[], int initiative, int healthbar, CP_Image image, CP_Vector pos, ElementType weakness, ElementType resistance, int number_of_parts);

/*
Function   : Boss_Initialize
Description: Used to initialize the boss struct
Parameters : BossPart bp[], int initiative, int healthbar, CP_Image image, CP_Vector pos, ElementType weakness, ElementType resistance, int number_of_parts
Return	   : int (true/false on if the boss was properly initialized)
*/
int Boss_Initialize(Boss* boss, FILE* const boss_file, int boss_id);
