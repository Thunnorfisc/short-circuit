#pragma once
#include "TEST_playerStruct.h"
#include "stdio.h"

/*
Function   : PlayerStats_Calculate
Description: Takes in the inventory of the player and copies the current player stats to calculate the stats for battle
Parameters : Item inventory[], Player player
Return	   : void
*/
void PlayerStats_Calculate(Item inventory[], Player player);

/*
Function   : PlayerStats_Create_Temp
Description: Takes the calculated player stats and writes to a temp file that will be read in battle system to calculate damage
Parameters : Player modified_player
Return	   : int (if the function successfully ran)
*/
int PlayerStats_Create_Temp(Player modified_player);

/*
Function   : PlayerStats_ReadFile
Description: Takes the calculated player stats in a temp file and set the player in battle system to be used for damage calculation
Parameters : Player modified_player
Return	   : int (if the function successfully ran)
*/
int PlayerStats_ReadFile(Player* player);