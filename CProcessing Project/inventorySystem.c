#include <stdio.h>
#include "cprocessing.h"
#include "inventorySystem.h"
#include "generalUtils.h"	
#include "worldSystem.h"

#define array_count(a) sizeof(a)/sizeof(a[0])
#define COLOR_RED CP_Color_Create(255, 125, 125, 255)
#define COLOR_BLACK CP_Color_Create(0, 0, 0, 255)

CP_Font exo2;
CP_Image logo;
float centrex, centrey, sword_y, shield_y, empty_y;
Inventory inventory = { 0 };

void Inventory_Init(void) {
	// Loads "Assets/Exo2-Regular.ttf" into memory and gives back
	// a representation of the font to us (aka a 'handle' to the font).
	exo2 = CP_Font_Load("Assets/Exo2-Regular.ttf");

	// Tells CProcessing to use exo2 for it's future
	// text drawing operations.
	CP_Font_Set(exo2);

	// Tells CProcessing that when drawing text in the future (via CP_Font_DrawText),
	// the position given to it is the center of the text horizontally and vertically.
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);

	// Tells CProcessing that when drawing text in the future (via CP_Font_DrawText),
	// We use size 72 font height.
	CP_Settings_TextSize(72.f);
}

void Inventory_Update(void) {

	if (CP_Input_KeyDown(KEY_ESCAPE)) {
		CP_Engine_SetNextGameState(World_Init, World_Update, World_Exit);
	}

    // clear the background to a grey color
    CP_Graphics_ClearBackground(CP_Color_Create(100, 100, 100, 255));
	centrex = CP_System_GetWindowWidth() / 2.0f;
	centrey = CP_System_GetWindowHeight() / 2.0f;

	// set the Y values for the 2 buttons
	sword_y = centrey - 300.0f;
	shield_y = centrey;
	empty_y = shield_y + 300.0f;
	
	// set the shape color to Red
	CP_Settings_Fill(COLOR_RED);
	// draw the two rectangles
	CP_Graphics_DrawRect(centrex, shield_y, 300.0f, 200.0f);
	CP_Graphics_DrawRect(centrex, sword_y, 300.0f, 200.0f);
	CP_Graphics_DrawRect(centrex, empty_y, 300.0f, 200.0f);

	// sets the text color to Black
	CP_Settings_Fill(COLOR_BLACK);

	// aligns the text to the middle
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);

	// draw the text where the rectangles are
	CP_Font_DrawText("Add Sword", centrex, sword_y);
	CP_Font_DrawText("Add Shield", centrex, shield_y);
	CP_Font_DrawText("Empty", centrex, empty_y);

	if (IsAreaClicked(centrex, empty_y, 300.0f, 200.0f, CP_Input_GetMouseX(), CP_Input_GetMouseY()) && CP_Input_MouseClicked()) {
		inventory = Empty_Inventory_Slot(inventory, 0);
		inventory = Empty_Inventory_Slot(inventory, 1);
	}
	if (IsAreaClicked(centrex, sword_y, 300.0f, 200.0f, CP_Input_GetMouseX(), CP_Input_GetMouseY()) && CP_Input_MouseClicked()) {
		inventory = Add_Sword_To_Inventory(inventory, 0, 10);

	}
	if (IsAreaClicked(centrex, shield_y, 300.0f, 200.0f, CP_Input_GetMouseX(), CP_Input_GetMouseY()) && CP_Input_MouseClicked()) {
		inventory = Add_Shield_To_Inventory(inventory, 1, 20);
	}
	
    for (int i = 0; i < array_count(inventory.slots); ++i) {
		
        switch (inventory.slots[i].type) {
        case InventoryTYPE_EMPTY:
			CP_Font_DrawText("Empty", 300, 60);
            break;

        case InventoryTYPE_SHIELD:
			CP_Font_DrawText("Shield", 300, 180);
			char buffer[50] = { 0 };
			sprintf_s(buffer, 50, "Defence: %d", inventory.slots[i].shield.defense);
			CP_Font_DrawText(buffer, 300, 220);
            break;

        case InventoryTYPE_SWORD:
			CP_Font_DrawText("Sword", 300, 100);
			sprintf_s(buffer, 50, "Attack: %d", inventory.slots[i].sword.attack);
			CP_Font_DrawText(buffer, 300, 140);
            break;
        }
    }
}

void Inventory_Exit(void) {

}

Inventory Add_Sword_To_Inventory(Inventory inventory, int where, int attack) {
	if (where < array_count(inventory.slots)) {
		inventory.slots[where].type = InventoryTYPE_SWORD;
		inventory.slots[where].sword.attack = attack;
	}
	return inventory;
}

Inventory Add_Shield_To_Inventory(Inventory inventory, int where, int defense) {
	if (where < array_count(inventory.slots)) {
		inventory.slots[where].type = InventoryTYPE_SHIELD;
		inventory.slots[where].shield.defense = defense;
	}
	return inventory;
}


Inventory Empty_Inventory_Slot(Inventory inventory, int where) {
	if (where < array_count(inventory.slots)) {
		inventory.slots[where].type = InventoryTYPE_EMPTY;
	}
	return inventory;
}