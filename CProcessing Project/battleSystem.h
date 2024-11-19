#pragma once
#include "generalUtils.h"
#include "enemyStructs.h"

#define E_MAGE_ASSET_ADDR "Assets/e_mage.png"

// Enemy asset addresses
#define E_WIZARD_ASSET_ADDR "Assets/e_mage.png"
#define E_PLANT_ASSET_ADDR "Assets/e_plant.png"
#define E_VULTURE_ASSET_ADDR "Assets/e_vulture.png"

void Battle_System_Init(void);

void Battle_System_Update(void);

void Battle_System_Exit(void);

void Reset_Initialize(int* boss_initialize);