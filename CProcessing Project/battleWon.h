/*!
@file battleWon.h
@author KELLY CHIANG KAR YAN (chiang.k)
@course CSD1401
@section B
@brief
This battleWon.h file serves as the header for the BattleWon module, providing declarations and dependencies needed for its functionality
*/

#pragma once
#include "TEST_playerStruct.h"
#include "enemyStructs.h"
#include "bossStruct.h"
#include "cprocessing.h"

void BattleWon_Initialize(void);
void BattleWon_Update(void);
void BattleWon_Exit(void);