/*
* @author	Main Author:	William Wibisana Dumnanauw (williamwibisana.d)
* @author   Sub-Author: KELLY CHIANG KAR YAN (chiang.k)
*			Sub-Author Contributions:
*					- GameReset Function
* @brief	The file contains the world scene and get set functions related to world and player
* @file		worldSystem.h
* All content © 2024 DigiPen Institute of Technology Singapore, all rights reserved.
*/
#pragma once
#include "worldHelper.h"
#include "itemSystem.h"
#include "cprocessing.h"
//#define INVENTORY_SIZE 30

/* ======== SCENE FUNCTIONS ======== */
void World_Init(void);
void World_Update(void);
void World_Exit(void);

/* ======== OTHER FUNCTIONS ======== */

// Display the player's UI, including their inventory and currency at the top of the screen
void World_PlayerUI();

/* ===== Setter/Updater Functions ===== */
void World_UpdateInventory(Item item);	// Update inventory with new item
void World_UpdateCurrency(int amt);		// Update currency by new amount
void World_SetLoadFlag();				// Turn on load flag to load world from save file

/* ===== Getter Functions ===== */
int World_GetCurrency();				// Get the current currency
int World_GetBoss();					// Get the ID of the current boss
CP_Image World_GetCurrencyImage();		// Get the sprite of currency, used if needed to display currency

/* ===== Resetting Functions ===== */
void World_Reset();						// Reset the world and variables
void ResetGame();						// Reset the run and all variables, calls World_Reset