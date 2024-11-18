#pragma once
#include "worldHelper.h"
#include "itemSystem.h"
#include "cprocessing.h"
//#define INVENTORY_SIZE 30

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
