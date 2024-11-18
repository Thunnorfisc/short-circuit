#include <stdio.h>
#include "cprocessing.h"
#include "inventorySystem.h"
#include "generalUtils.h"	
#include "worldSystem.h"
#include "TEST_playerUtil.h"
#include "itemSystem.h"



CP_Font exo2;
char buffer[50] = { 0 };
float centrex, centrey, inv_x, name_y, stat_y, font_size, pstat_x, pstat_y, health_y, mana_y, defence_y, fire_y, water_y, grass_y, attack_y;
Player player;

void Inventory_Init(void) {
	// Initialising ui  
	centrex = WINDOW_WIDTH_HALF;
	centrey = WINDOW_HEIGHT_HALF;
	inv_x = WINDOW_WIDTH_HALF * 0.5f;
	pstat_x = WINDOW_WIDTH_HALF * 1.5f;
	pstat_y = WINDOW_HEIGHT_HALF * 0.1f;
	health_y = WINDOW_HEIGHT_HALF * 0.14f;
	defence_y = WINDOW_HEIGHT_HALF * 0.18f;
	fire_y = WINDOW_HEIGHT_HALF * 0.22f;
	water_y = WINDOW_HEIGHT_HALF * 0.26f;
	grass_y = WINDOW_HEIGHT_HALF * 0.30f;
	attack_y = WINDOW_HEIGHT_HALF * 0.34f;
	mana_y = WINDOW_HEIGHT_HALF * 0.38f;
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
    // Clear the background
    CP_Graphics_ClearBackground(BACKGROUND_COLOR);

	// Display player stats
	CP_Settings_Fill(COLOR_RED);
	CP_Font_DrawText("Player Stats:", pstat_x, pstat_y);
	sprintf_s(buffer, 50, "Health: %2lf", player.health);
	CP_Font_DrawText(buffer, pstat_x, health_y);
	sprintf_s(buffer, 50, "Defense: %lf", player.defense);
	CP_Font_DrawText(buffer, pstat_x, defence_y);
	sprintf_s(buffer, 50, "Mana: %d", player.s_mana);
	CP_Font_DrawText(buffer, pstat_x, mana_y);
	sprintf_s(buffer, 50, "Fire Critial Damage: %2lf", player.fire_crit);
	CP_Font_DrawText(buffer, pstat_x, fire_y);
	sprintf_s(buffer, 50, "Water Critial Damage: %2lf", player.water_crit);
	CP_Font_DrawText(buffer, pstat_x, water_y);
	sprintf_s(buffer, 50, "Grass Critial Damage: %2lf", player.grass_crit);
	CP_Font_DrawText(buffer, pstat_x, grass_y);
	sprintf_s(buffer, 50, "Attack: %d", player.attack);
	CP_Font_DrawText(buffer, pstat_x, attack_y);
}

void Inventory_Exit(void) {

}
