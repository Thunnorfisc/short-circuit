/*
File: inventorySystem.c
Author: William Wibisana Dumnanauw (williamwibisana.d)
Sub-Author: Wei Song (weisong.ong@digipen.edu)
Description:
This file contains the define values and declaration of the functions for the inventory system:
 - void Inventory_Init
 - void Inventory_Update (Wei Song)
 - void Inventory_Exit
 - void Handle_Inventory

 * All content © 2024 DigiPen Institute of Technology Singapore, all rights reserved.
*/

#pragma once

#define INVENTORY_SIZE 30
#define COLOR_BLUE CP_Color_Create(0,0,205,255)

void Inventory_Init(void);

void Inventory_Update(void);

void Inventory_Exit(void);

void Handle_Inventory(void);
