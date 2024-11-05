#include <stdio.h>
#include "cprocessing.h"
#include "inventorySystem.h"
#include "generalUtils.h"	
#include "worldSystem.h"

CP_Font exo2;
CP_Image logo;
Inventory inventory = { 0 };
char buffer[50] = { 0 };
float centrex, centrey, swordb_y, shieldb_y, emptyb_y, button_width, button_height, inv_x;

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

	// Initialising variables
	centrex = WINDOW_WIDTH_HALF;
	centrey = WINDOW_HEIGHT_HALF;
	emptyb_y = WINDOW_HEIGHT_HALF * 0.5;
	swordb_y = WINDOW_HEIGHT_HALF;
	shieldb_y = WINDOW_HEIGHT_HALF * 1.5;
	button_width = WINDOW_WIDTH * 0.3;
	button_height = WINDOW_HEIGHT * 0.1;
	inv_x = WINDOW_WIDTH_HALF * 0.5;

}

void Inventory_Update(void) {

	if (CP_Input_KeyDown(KEY_ESCAPE)) {
		CP_Engine_SetNextGameState(World_Init, World_Update, World_Exit);
	}

    // clear the background to a grey color
    CP_Graphics_ClearBackground(COLOR_GREY);
	// set the shape color to Red
	CP_Settings_Fill(COLOR_RED);
	// draw the two rectangles
	CP_Graphics_DrawRect(centrex, shieldb_y, button_width, button_height);
	CP_Graphics_DrawRect(centrex, swordb_y, button_width, button_height);
	CP_Graphics_DrawRect(centrex, emptyb_y, button_width, button_height);
	// sets the text color to Black
	CP_Settings_Fill(COLOR_BLACK);
	// aligns the text to the middle
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
	// draw the text where the buttons are
	CP_Font_DrawText("Add Sword", centrex, swordb_y);
	CP_Font_DrawText("Add Shield", centrex, shieldb_y);
	CP_Font_DrawText("Empty", centrex, emptyb_y);

	// functions to call when buttons are pressed
	if (IsAreaClicked(centrex, emptyb_y, button_width, button_height, CP_Input_GetMouseX(), CP_Input_GetMouseY()) && CP_Input_MouseClicked()) {
		inventory = Empty_Inventory_Slot(inventory, 0);
		inventory = Empty_Inventory_Slot(inventory, 1);
	}
	if (IsAreaClicked(centrex, swordb_y, button_width, button_height, CP_Input_GetMouseX(), CP_Input_GetMouseY()) && CP_Input_MouseClicked()) {
		inventory = Add_Sword_To_Inventory(inventory, 0, 10);

	}
	if (IsAreaClicked(centrex, shieldb_y, button_width, button_height, CP_Input_GetMouseX(), CP_Input_GetMouseY()) && CP_Input_MouseClicked()) {
		inventory = Add_Shield_To_Inventory(inventory, 1, 20);
	}
	
	// display the inventory
    for (int i = 0; i < array_count(inventory.slots); ++i) {
        switch (inventory.slots[i].type) {
        case InventoryTYPE_EMPTY:
			CP_Font_DrawText("Empty", inv_x, 80);
            break;
		case InventoryTYPE_SWORD:
			CP_Font_DrawText("Sword", inv_x, 160);
			sprintf_s(buffer, 50, "Attack: %d", inventory.slots[i].sword.attack);
			CP_Font_DrawText(buffer, inv_x, 240);
			break;
        case InventoryTYPE_SHIELD:
			CP_Font_DrawText("Shield", inv_x, 320);
			sprintf_s(buffer, 50, "Defence: %d", inventory.slots[i].shield.defense);
			CP_Font_DrawText(buffer, inv_x, 400);
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