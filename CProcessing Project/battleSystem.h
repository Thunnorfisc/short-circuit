/*!
@file battleSystem.h
@author JASON (jasonjunhao.teo)
@course CSD1401
@section B
@brief
This battleSystem.h file serves as the header for the implementation of the battle system for our game.
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

//Various Checks
extern int Piece_Placed;
extern int Spell_Cast;

void Battle_System_Init(void);

void Battle_System_Update(void);

void Battle_System_Exit(void);

void Reset_Initialize(int* boss_initialize);
