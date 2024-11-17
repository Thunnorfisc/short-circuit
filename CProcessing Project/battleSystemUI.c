#include "battleSystemUI.h"
#include "generalUtils.h"

/*
Function   : Display_Enemy_Hover
Description: Used to display the Enemy Stats by hovering over the Enemy
Parameters : Enemy enemies[ENEMY_COUNT], CP_Vector mouse_pos
Return	   : void
*/
void Display_Enemy_Hover(Enemy enemies[ENEMY_COUNT], CP_Vector mouse_pos) {
	for (int i = 0; i < ENEMY_COUNT; ++i) {
		if (CP_Vector_Distance(enemies[i].position, mouse_pos) <= GRID_CELL_SIZE / 2.f) {

		}
	}
}

/*
Function   : UI_Component_Create
Description: Initialize each UI Components
Parameters : CP_Image img, CP_Vector pos, float width, float height
Return	   : BattleUI
*/
BattleUI UI_Component_Create(CP_Image img, CP_Vector pos, float width, float height){
	BattleUI new_battle_ui = { 0 };
	new_battle_ui.img = img;
	new_battle_ui.pos = pos;
	new_battle_ui.width = width;
	new_battle_ui.height = height;

	return new_battle_ui;
}

/*
Function   : UI_Initialize
Description: Initialize all UI Components
Parameters : BattleUI ui[UI_COUNT]
Return	   : void
*/
void UI_Initialize(BattleUI ui[UI_COUNT]) {
	//0: Health UI
	ui[0] = UI_Component_Create(
		CP_Image_Load(HEALTH_UI_ADDR),
		CP_Vector_Set(HEALTH_UI_SIZE / 2, (int)WINDOW_HEIGHT - HEALTH_UI_SIZE / 2),
		HEALTH_UI_SIZE,
		HEALTH_UI_SIZE
	);
	//1: Attack UI
	ui[1] = UI_Component_Create(
		CP_Image_Load(ATTACK_UI_ADDR),
		CP_Vector_Set((int)WINDOW_WIDTH - ATTACK_UI_SIZE / 2, (int)WINDOW_HEIGHT - ATTACK_UI_SIZE / 2),
		ATTACK_UI_SIZE,
		ATTACK_UI_SIZE
	);
}

/*
Function   : Display_UI
Description: Display all UI Components
Parameters : BattleUI const ui[UI_COUNT], Player player, float original_health
Return	   : void
*/
void Display_UI(BattleUI const ui[UI_COUNT], Player player, float original_health) {
	//Default Health Size
	float width = ui[0].width * 0.78f;
	float height = ui[0].height * 0.81f;

	//Calculate and display player health
	CP_Settings_Fill(CP_Color_Create(236, 52, 80, DEFAULT_ALPHA));
	CP_Settings_NoStroke();
	CP_Graphics_DrawRect(ui[0].pos.x - ui[0].width * 0.11f, ui[0].pos.y + ui[0].height * 0.08f, width, height * (player.health / original_health));

	for (int i = 0; i < UI_COUNT; ++i) {
		if (ui[i].width == 0) break;
		CP_Image_Draw(ui[i].img, ui[i].pos.x, ui[i].pos.y, ui[i].width, ui[i].height, DEFAULT_ALPHA);
	}
}