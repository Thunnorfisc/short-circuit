/*
File: bossSystem.h
Author: Jason Teo Jun Hao (jasonjunhao.teo)
Description:
This file contains the define values and the decalaration of the runtim functions for the battle system:
 - void Battle_System_Init;
 - void Battle_System_Update;
 - void Battle_System_Exit;
 - void Reset_Initialize;
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
