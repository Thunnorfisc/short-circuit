/*
* @author	William Wibisana Dumnanauw (williamwibisana.d)
* @brief	The file contains the world scene and get set functions related to world and player
* @file		worldSystem.h
* All content © 2024 DigiPen Institute of Technology Singapore, all rights reserved.
*/
#pragma once
#include "worldHelper.h"
#include "itemSystem.h"
#include "cprocessing.h"
//#define INVENTORY_SIZE 30

// Scene Fucntions
void World_Init(void);
void World_Update(void);
void World_Exit(void);


void Generate_World(int);

void World_Reset();

World World_Generate_Dynamic(int);

void World_UpdateInventory(Item item);

void World_UpdateCurrency(int amt);

int World_GetCurrency();

void World_PlayerUI();

int World_GetBoss();

CP_Image World_GetCurrencyImage();

void World_SetLoadFlag();

void ResetGame();