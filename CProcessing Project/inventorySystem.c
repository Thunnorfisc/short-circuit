#include <stdio.h>
#include "cprocessing.h"
#include "inventorySystem.h"
#include "generalUtils.h"	
#include "worldSystem.h"
#include "TEST_playerUtil.h"
#include "itemSystem.h"



CP_Font exo2;
char buffer[50] = { 0 };
Item item_list[INVENTORY_SIZE];
Player player;
int current_inventory_size;
float centrex, centrey, name_y, stat_y, font_size, pstat_x, pstat_y, health_y, mana_y, defence_y, fire_y, water_y, grass_y, attack_y,rect_x, rect_y, text_x, num_x, rect_width, image_x, iname_x, image_y, image_width, image_height, init_image_y;


void Inventory_Init(void) {
	// Font settings
	font_size = (float)(WINDOW_HEIGHT / 24);
	exo2 = CP_Font_Load(FONT_ASSET_ADDR);
	CP_Font_Set(exo2);
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_LEFT, CP_TEXT_ALIGN_V_MIDDLE);
	CP_Settings_TextSize(font_size);
	// Initialising ui  
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
	image_width = WINDOW_HEIGHT / 24.0f;
	image_height = image_width;
	init_image_y = WINDOW_HEIGHT / 10.0f;
}

void Inventory_Update(void) {
	// Press esc to go back to the map
	if (CP_Input_KeyDown(KEY_ESCAPE)) {
		CP_Engine_SetNextGameState(World_Init, World_Update, World_Exit);
	}
    // Clear the background
    CP_Graphics_ClearBackground(BACKGROUND_COLOR);
	CP_Settings_Fill(COLOR_BLUE);
	CP_Settings_RectMode(CP_POSITION_CORNER);
	CP_Graphics_DrawRect(rect_x,rect_y,rect_width,attack_y);
	// Display player stats
	CP_Settings_Fill(COLOR_WHITE);
	CP_Font_DrawText("Player Stats:", pstat_x, pstat_y);
	CP_Font_DrawText("Health:", pstat_x, health_y);
	CP_Font_DrawText("Defence:", pstat_x, defence_y);
	CP_Font_DrawText("Mana:", pstat_x, mana_y);
	CP_Font_DrawText("Attack:", pstat_x, attack_y);
	CP_Font_DrawText("Fire Critial Damage:", pstat_x, fire_y);
	CP_Font_DrawText("Water Critial Damage:", pstat_x, water_y);
	CP_Font_DrawText("Grass Critial Damage:", pstat_x, grass_y);

	sprintf_s(buffer, 50, "%.3f", player.health);
	CP_Font_DrawText(buffer, num_x, health_y);
	sprintf_s(buffer, 50, "%.3lf", player.defense);
	CP_Font_DrawText(buffer, num_x, defence_y);
	sprintf_s(buffer, 50, "%d", player.s_mana);
	CP_Font_DrawText(buffer, num_x, mana_y);
	sprintf_s(buffer, 50, "%.3lf", player.fire_crit);
	CP_Font_DrawText(buffer, num_x, fire_y);
	sprintf_s(buffer, 50, "%.3lf", player.water_crit);
	CP_Font_DrawText(buffer, num_x, water_y);
	sprintf_s(buffer, 50, "%.3lf", player.grass_crit);
	CP_Font_DrawText(buffer, num_x, grass_y);
	sprintf_s(buffer, 50, "%d", player.attack);
	CP_Font_DrawText(buffer, num_x, attack_y);
	CP_Font_DrawText("Items:", 0, rect_y);

	float imgSize = 128;
	for (int i = 0; i < current_inventory_size; ++i) {
		CP_Image_Draw(item_list[i].image, image_x, init_image_y + (i * (WINDOW_WIDTH / 32.0f)), image_width, image_height, 255);
		CP_Font_DrawText(item_list[i].name, iname_x, init_image_y + (i * (WINDOW_WIDTH / 32.0f)));
	}
}

void Inventory_Exit(void) {

}
