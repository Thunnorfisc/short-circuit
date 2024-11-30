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

#include <stdio.h>
#include "cprocessing.h"
#include "inventorySystem.h"
#include "generalUtils.h"	
#include "worldSystem.h"
#include "TEST_playerUtil.h"
#include "itemSystem.h"

// Declaration of variables 
// Text variables
CP_Font exo2;
float imgSize = 128;
char buffer[50] = { 0 };

// Player variables
Item item_list[INVENTORY_SIZE];
Player player_inv;
int current_inventory_size;

// UI Variables
float centrex, centrey, name_y, stat_y, font_size, pstat_x, pstat_y, health_y, mana_y, defence_y, fire_y, water_y, grass_y, attack_y,rect_x, rect_y, text_x, num_x, rect_width,
image_x, iname_x, image_y, image_width, image_height, init_image_y, idesc_x, item_x, itype_x, item_y_increment;

// Array that corresponds to the item type (its written as an enum)
const char* Type_Of_Items[] = { "Health Points","Mana","Attack","Defense","Fire Critical Damage","Water Critical Damage","Grass Critical Damage" };

void Inventory_Init(void) {
	// Load player stats from the temp file
	PlayerStats_ReadFile(&player_inv);

	// Font settings
	font_size = (float)(WINDOW_HEIGHT / 24);
	exo2 = CP_Font_Load(FONT_ASSET_ADDR);
	CP_Font_Set(exo2);
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_LEFT, CP_TEXT_ALIGN_V_MIDDLE);
	CP_Settings_TextSize(font_size);

	// Initialising ui variables
	centrex = WINDOW_WIDTH_HALF;
	centrey = WINDOW_HEIGHT_HALF;
	pstat_x = centrex * 1.2f;
	pstat_y = centrey * 0.10f;
	health_y = centrey * 0.17f;
	mana_y = centrey * 0.24f;
	defence_y = centrey * 0.31f;
	fire_y = centrey * 0.38f;
	water_y = centrey * 0.45f;
	grass_y = centrey * 0.52f;
	attack_y = centrey * 0.59f;
	rect_x = centrex * 1.18f;
	rect_y = centrey * 0.06f;
	num_x = centrex * 1.6f;
	rect_width = centrex*0.7f;
	image_x = WINDOW_WIDTH / 64.0f;
	iname_x = WINDOW_WIDTH / 30.0f;
	idesc_x = centrex * 0.45f;
	item_x = centrex * 0.01f;
	image_width = WINDOW_HEIGHT / 24.0f;
	image_height = image_width;
	init_image_y = WINDOW_HEIGHT / 10.0f;
	item_y_increment = WINDOW_WIDTH / 32.0f;
}

void Inventory_Update(void) {
	// Press esc to go back to the map
	if (CP_Input_KeyDown(KEY_ESCAPE)) {
		CP_Engine_SetNextGameState(World_Init, World_Update, World_Exit);
	}

    // Clear the background
    CP_Graphics_ClearBackground(BACKGROUND_COLOR);

	// Display player stats
	CP_Settings_Fill(COLOR_BLUE);
	CP_Settings_RectMode(CP_POSITION_CORNER);
	CP_Graphics_DrawRect(rect_x,rect_y,rect_width,attack_y);
	CP_Settings_Fill(COLOR_WHITE(255));
	CP_Font_DrawText("Player Stats:", pstat_x, pstat_y);
	CP_Font_DrawText("Health:", pstat_x, health_y);
	CP_Font_DrawText("Defence:", pstat_x, defence_y);
	CP_Font_DrawText("Mana:", pstat_x, mana_y);
	CP_Font_DrawText("Attack:", pstat_x, attack_y);
	CP_Font_DrawText("Fire Critial Damage:", pstat_x, fire_y);
	CP_Font_DrawText("Water Critial Damage:", pstat_x, water_y);
	CP_Font_DrawText("Grass Critial Damage:", pstat_x, grass_y);

	// Displays the player stats loaded from the temp file
	sprintf_s(buffer, 50, "%.2f", player_inv.health);
	CP_Font_DrawText(buffer, num_x, health_y);
	sprintf_s(buffer, 50, "%.2lf", player_inv.defense);
	CP_Font_DrawText(buffer, num_x, defence_y);
	sprintf_s(buffer, 50, "%d", player_inv.s_mana);
	CP_Font_DrawText(buffer, num_x, mana_y);
	sprintf_s(buffer, 50, "%.2lf", player_inv.fire_crit);
	CP_Font_DrawText(buffer, num_x, fire_y);
	sprintf_s(buffer, 50, "%.2lf", player_inv.water_crit);
	CP_Font_DrawText(buffer, num_x, water_y);
	sprintf_s(buffer, 50, "%.2lf", player_inv.grass_crit);
	CP_Font_DrawText(buffer, num_x, grass_y);
	sprintf_s(buffer, 50, "%d", player_inv.attack);
	CP_Font_DrawText(buffer, num_x, attack_y);
	
	// Display Items by using a for loop that goes through the inventory and gets all of the images, names and stats of all the items within it
	CP_Font_DrawText("Items:", item_x, rect_y);
	for (int i = 0; i < current_inventory_size; ++i) {
		CP_Image_Draw(item_list[i].image, image_x, init_image_y + (i * (item_y_increment)), image_width, image_height, 255);
		CP_Font_DrawText(item_list[i].name, iname_x, init_image_y + (i * (item_y_increment)));
		sprintf_s(buffer, 50, "+%.2lf %s", item_list[i].modifier, Type_Of_Items[(int)item_list[i].type]);
		CP_Font_DrawText(buffer, idesc_x, init_image_y + (i * (item_y_increment)));
	}
}

void Inventory_Exit(void) {
	
}

// Go to inventory screen
void Handle_Inventory(void) {
	if (CP_Input_KeyTriggered(KEY_TAB)) {
		CP_Engine_SetNextGameStateForced(Inventory_Init, Inventory_Update, Inventory_Exit);
	}
}
