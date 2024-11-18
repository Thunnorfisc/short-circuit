#pragma once
#include "cprocessing.h"
#include "bossStruct.h"
#include <stdio.h>
#include <stdlib.h>
#include "magicSystemUtil.h"
#include "TEST_playerStruct.h"
/*
Function   : BossParts_Initialize
Description: Used to initialize the bodypart array in the Boss Struct
Parameters : BossPart bp[], int initiative, int healthbar, CP_Image image, CP_Vector pos, ElementType weakness, ElementType resistance, int number_of_parts
Return	   : void
*/
void BossParts_Initialize(BossPart bp[], int initiative, float healthbar, CP_Image image, CP_Vector pos, ElementType weakness, ElementType resistance, int number_of_parts);

/*
Function   : Boss_Initialize
Description: Used to initialize the boss struct
Parameters : BossPart bp[], int initiative, int healthbar, CP_Image image, CP_Vector pos, ElementType weakness, ElementType resistance, int number_of_parts
Return	   : int (true/false on if the boss was properly initialized)
*/
int Boss_Initialize(Boss* boss, int boss_id, CP_Vector grid_location[GRID_DIMENSIONS][GRID_DIMENSIONS]);

/*
Function   : Check_Enemy_Hit
Description: Used to check which enemy was attacked
Parameters : Enemy enemy_arr[3], CP_Vector index_used[], CircuitPiece selected_pieces[GRID_DIMENSIONS][GRID_DIMENSIONS], Player player
Return	   : void
*/
void Check_Boss_Hit(BossPart bp[GRID_DIMENSIONS* GRID_DIMENSIONS], CP_Vector index_used[], CircuitPiece selected_pieces[GRID_DIMENSIONS][GRID_DIMENSIONS], Player player, int bp_count);

/*
Function   : Enemy_Calculate_Damage
Description: Used to calculate the amount of damage that is dealt to the enemy
Parameters : Enemy* enemy, Player const player, CircuitPiece piece_that_hit, int number_of_pipes, int num_of_enemies_hit
Return	   : void
*/
void Boss_Calculate_Damage(BossPart* bp, Player const player, CircuitPiece piece_that_hit, int number_of_pipes, int num_of_enemies_hit);

void Boss_Randomise_Position(BossPart bp[GRID_DIMENSIONS * GRID_DIMENSIONS], CP_Vector gridLocation[GRID_DIMENSIONS][GRID_DIMENSIONS], int bp_count);

void Gatekeeper_Mechanics(Player* player, Boss const boss, int* enrage);