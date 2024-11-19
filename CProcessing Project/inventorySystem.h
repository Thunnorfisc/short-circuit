#pragma once

#define INVENTORY_SIZE 30
#define COLOR_RED CP_Color_Create(255, 125, 125, 255)
#define COLOR_GREEN CP_Color_Create(102,146,61,255)
#define COLOR_BLUE CP_Color_Create(0,0,205,255)
#define COLOR_MANA CP_Color_Create(0,191,255,255)
#define MOUSEX CP_Input_GetMouseX()
#define MOUSEY CP_Input_GetMouseY()
#define CLICKED CP_Input_MouseClicked()


void Inventory_Init(void);

void Inventory_Update(void);

void Inventory_Exit(void);

void Handle_Inventory(void);
