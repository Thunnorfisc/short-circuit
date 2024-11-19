#pragma once

#include "cprocessing.h"
#include "magicStructs.h"
#include "magicSystemUtil.h"

#define BOSS_DATA_ADDR "Assets/Enemy_Files/Bosses_Data.txt"
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
	int id;
	int initiative;
	float healthbar;
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
int num_of_bp	 : The number of body parts
char* boss_name  : Name of the boss to display
BossPart parts[] : Array of the BossParts

*/
typedef struct Boss {
	int boss_id;
	int enrage_time;
	int num_of_bp;
	float attack;
	char boss_name[100];
	BossPart parts[GRID_DIMENSIONS*GRID_DIMENSIONS];
}Boss;

