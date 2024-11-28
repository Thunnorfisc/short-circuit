/*!
@file battleLost.h
@author KELLY CHIANG KAR YAN (chiang.k)
@course CSD1401
@section B
@brief
This battleLost.h file serves as the header for the BattleLost module, providing declarations and dependencies needed for its functionality
*/

#pragma once
#include "TEST_playerStruct.h"
#include "enemyStructs.h"
#include "bossStruct.h"
#include "cprocessing.h"

void BattleLost_Initialize(void);
void BattleLost_Update(void);
void BattleLost_Exit(void);