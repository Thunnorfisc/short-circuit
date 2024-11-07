#include <stdio.h>
#include "cprocessing.h"
#include "inventorySystem.h"
#include "generalUtils.h"	
#include "worldSystem.h"

CP_Font exo2;
Inventory inventory = { 0 };
char buffer[50] = { 0 };
float centrex, centrey, swordb_y, shieldb_y, emptyb_y, sword2b_y, shield2b_y, button_width, button_height, inv_x, name_y, stat_y, pstat_x, font_size;

typedef struct ps {
	int attack_power;
	int health_points;
	int currency;
} PlayerStats;

PlayerStats ps = {
	.attack_power = 0,
	.health_points = 0 ,
	.currency = 100
};

void Inventory_Init(void) {
	// Initialising ui  
	centrex = WINDOW_WIDTH_HALF;
	centrey = WINDOW_HEIGHT_HALF;
	emptyb_y = WINDOW_HEIGHT_HALF * 0.2f;
	swordb_y = WINDOW_HEIGHT_HALF * 0.5f;
	shieldb_y = WINDOW_HEIGHT_HALF * 0.8f;
	sword2b_y = WINDOW_HEIGHT_HALF * 1.1f;
	shield2b_y = WINDOW_HEIGHT_HALF * 1.4f;
	button_width = WINDOW_WIDTH * 0.3f;
	button_height = WINDOW_HEIGHT * 0.1f;
	inv_x = WINDOW_WIDTH_HALF * 0.5f;
	pstat_x = WINDOW_WIDTH_HALF * 1.5f;
	font_size = WINDOW_HEIGHT_HALF * 0.05f;
	// Font settings
	exo2 = CP_Font_Load(FONT_ASSET_ADDR);
	CP_Font_Set(exo2);
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
	CP_Settings_TextSize(font_size);
}

void Inventory_Update(void) {
	// Press esc to go back to the map
	if (CP_Input_KeyDown(KEY_ESCAPE)) {
		CP_Engine_SetNextGameState(World_Init, World_Update, World_Exit);
	}
    // Clear the background to a grey color
    CP_Graphics_ClearBackground(BACKGROUND_COLOR);
	// Draw the buttons
	CP_Settings_Fill(COLOR_RED);
	CP_Graphics_DrawRect(centrex, shieldb_y, button_width, button_height);
	CP_Graphics_DrawRect(centrex, swordb_y, button_width, button_height);
	CP_Graphics_DrawRect(centrex, emptyb_y, button_width, button_height);
	CP_Graphics_DrawRect(centrex, shield2b_y, button_width, button_height);
	CP_Graphics_DrawRect(centrex, sword2b_y, button_width, button_height);
	CP_Settings_Fill(COLOR_BLACK);
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
	CP_Font_DrawText("Add Sword", centrex, swordb_y);
	CP_Font_DrawText("Add Shield", centrex, shieldb_y);
	CP_Font_DrawText("Add Sword2", centrex, sword2b_y);
	CP_Font_DrawText("Add Shield2", centrex, shield2b_y);
	CP_Font_DrawText("Empty", centrex, emptyb_y);
	// Button actions
	if (IsAreaClicked(centrex, emptyb_y, button_width, button_height, MOUSEX, MOUSEY) && CLICKED) {
		for (int i = 0; i < array_count(inventory.slots); ++i) {
			inventory = Empty_Inventory_Slot(inventory, i);
			inventory = Empty_Inventory_Slot(inventory, i);
			ps.attack_power = 0;
			ps.health_points = 0;
		}
		
	}
	if (IsAreaClicked(centrex, swordb_y, button_width, button_height, CP_Input_GetMouseX(), CP_Input_GetMouseY()) && CP_Input_MouseClicked()) {
		inventory = Add_Sword_To_Inventory(inventory, 0);
		ps.attack_power += inventory.slots->sword.attack;

	}
	if (IsAreaClicked(centrex, shieldb_y, button_width, button_height, CP_Input_GetMouseX(), CP_Input_GetMouseY()) && CP_Input_MouseClicked()) {
		inventory = Add_Shield_To_Inventory(inventory, 1);
		ps.health_points += inventory.slots->shield.hp;
	}
	if (IsAreaClicked(centrex, sword2b_y, button_width, button_height, CP_Input_GetMouseX(), CP_Input_GetMouseY()) && CP_Input_MouseClicked()) {
		inventory = Add_Sword_To_Inventory(inventory, 0);
		ps.attack_power += inventory.slots->sword.attack;

	}
	if (IsAreaClicked(centrex, shield2b_y, button_width, button_height, CP_Input_GetMouseX(), CP_Input_GetMouseY()) && CP_Input_MouseClicked()) {
		inventory = Add_Shield_To_Inventory(inventory, 1);
		ps.health_points += inventory.slots->shield.hp;
	}
	// Display player stats
	CP_Settings_Fill(COLOR_RED);
	sprintf_s(buffer, 50, "Attack: %d", ps.attack_power);
	CP_Font_DrawText(buffer, pstat_x, swordb_y);
	sprintf_s(buffer, 50, "Health: %d", ps.health_points);
	CP_Font_DrawText(buffer, pstat_x, shieldb_y);
	// Display the inventory
	Print_Inventory(inventory);
	
}

void Inventory_Exit(void) {

}

// check if inventory is full, if not full add item to inventory
Inventory Add_Sword_To_Inventory(Inventory inventory, int where) {
	if (where < array_count(inventory.slots)) {
		inventory.slots[where].type = InventoryTYPE_SWORD;
		inventory.slots[where].sword.attack = 10;
	}
	return inventory;
}

Inventory Add_Shield_To_Inventory(Inventory inventory, int where) {
	if (where < array_count(inventory.slots)) {
		inventory.slots[where].type = InventoryTYPE_SHIELD;
		inventory.slots[where].shield.hp = 10;
	}
	return inventory;
}

Inventory Empty_Inventory_Slot(Inventory inventory, int where) {
	if (where < array_count(inventory.slots)) {
		inventory.slots[where].type = InventoryTYPE_EMPTY;
	}
	return inventory;
}
// Run through inventory slots, check if item is in inventory and print the item if it is in inventory
void Print_Inventory(Inventory inventory) {
	for (int i = 0; i < array_count(inventory.slots); ++i) {
		name_y = (i + 0.5f) * 160.0f;
		stat_y = (i + 1) * 160.0f;
		switch (inventory.slots[i].type) {
		case InventoryTYPE_SWORD:
			CP_Font_DrawText("Sword", inv_x, name_y);
			sprintf_s(buffer, 50, "Attack: %d", inventory.slots[i].sword.attack);
			CP_Font_DrawText(buffer, inv_x, stat_y);
			break;
		case InventoryTYPE_SHIELD:
			CP_Font_DrawText("Shield", inv_x, name_y);
			sprintf_s(buffer, 50, "Health: %d", inventory.slots[i].shield.hp);
			CP_Font_DrawText(buffer, inv_x, stat_y);
			break;
		}
	}
}