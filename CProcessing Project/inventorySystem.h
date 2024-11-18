#pragma once

#define INVENTORY_SIZE 30
#define COLOR_RED CP_Color_Create(255, 125, 125, 255)
#define MOUSEX CP_Input_GetMouseX()
#define MOUSEY CP_Input_GetMouseY()
#define CLICKED CP_Input_MouseClicked()


void Inventory_Init(void);

void Inventory_Update(void);

void Inventory_Exit(void);

