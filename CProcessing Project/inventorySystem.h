#pragma once

#define INVENTORY_SIZE 30
#define COLOR_BLUE CP_Color_Create(0,0,205,255)

void Inventory_Init(void);

void Inventory_Update(void);

void Inventory_Exit(void);

void Handle_Inventory(void);
