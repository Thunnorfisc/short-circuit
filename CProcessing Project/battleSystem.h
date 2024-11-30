/*
File: bossSystem.h
Author: Jason Teo Jun Hao (jasonjunhao.teo)
Sub-Author: KELLY CHIANG KAR YAN (chiang.k)
Description:
This file contains the define values and the declaration of the runtime functions for the battle system:
 - void Battle_System_Init;
 - void Battle_System_Update; (Kelly)
 - void Battle_System_Exit;
 - void Reset_Initialize;

 * All content © 2024 DigiPen Institute of Technology Singapore, all rights reserved.
*/

#pragma once
#include "generalUtils.h"
#include "enemyStructs.h"
#include "worldSystem.h"
#include "itemSystem.h"

#define E_MAGE_ASSET_ADDR "Assets/e_mage.png"

// Enemy asset addresses
#define E_WIZARD_ASSET_ADDR "Assets/e_mage.png"
#define E_PLANT_ASSET_ADDR "Assets/e_plant.png"
#define E_VULTURE_ASSET_ADDR "Assets/e_vulture.png"

// Flags that are used for the tutorial
extern int Piece_Placed;
extern int Spell_Cast;

void Battle_System_Init(void);

void Battle_System_Update(void);

void Battle_System_Exit(void);

/*
Function   : Reset_Initialize (Deprecated)
Description: Used to reset the flags to allow the program to re-initialize the player and bosses
Parameters : int* boss_initialize
Return	   : void
*/
void Reset_Initialize(int* boss_initialize);
