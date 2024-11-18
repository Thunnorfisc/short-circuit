#include "battleSystemUI.h"
#include "generalUtils.h"

/*
Function   : Display_Enemy_Hover
Description: Used to display the Enemy Stats by hovering over the Enemy
Parameters : Enemy enemies[ENEMY_COUNT], CP_Vector mouse_pos
Return	   : void
*/
void Display_Enemy_Hover(Enemy enemies[ENEMY_COUNT], Enemy const original_enemies[ENEMY_COUNT], CP_Vector mouse_pos, BattleUI ui) {
	float text_size = TEXT_SIZE * WINDOW_RATIO;
	float hp_width = ui.width - BUFFER * 4 * WINDOW_RATIO;
	float hp_height = BUFFER * 3 * WINDOW_RATIO;

	for (int i = 0; i < ENEMY_COUNT; ++i) {
		if (CP_Vector_Distance(enemies[i].position, mouse_pos) <= GRID_CELL_SIZE / 2.0f) {
			CP_Image_Draw(ui.img, ui.pos.x, ui.pos.y, ui.width, ui.height, DEFAULT_ALPHA/2);

			//Display Name of the enemy
			CP_Settings_Fill(CP_Color_Create(0, 0, 0, DEFAULT_ALPHA));
			CP_Settings_TextSize(text_size);
			CP_Font_DrawText(enemies[i].name, ui.pos.x, (ui.pos.y - ui.height/2.f) + text_size/2.f + 3* BUFFER * WINDOW_RATIO);

			//Display Health of Enemy
			CP_Settings_Fill(HP_COLOR);
			CP_Settings_RectMode(CP_POSITION_CORNER);
			CP_Graphics_DrawRect(ui.pos.x - ui.width / 2.f + BUFFER * 2 * WINDOW_RATIO, ui.pos.y, hp_width * enemies[i].healthbar/original_enemies[i].healthbar, hp_height);
			CP_Settings_RectMode(CP_POSITION_CENTER);
			//draw enemy data
			break;
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
		CP_Vector_Set(HEALTH_UI_SIZE / 2, (int)WINDOW_HEIGHT - HEALTH_UI_SIZE / 2.f),
		HEALTH_UI_SIZE,
		HEALTH_UI_SIZE
	);

	//1: Attack UI
	ui[1] = UI_Component_Create(
		CP_Image_Load(ATTACK_UI_ADDR),
		CP_Vector_Set((int)WINDOW_WIDTH - ATTACK_UI_SIZE / 2, (int)WINDOW_HEIGHT - ATTACK_UI_SIZE / 2.f),
		ATTACK_UI_SIZE,
		ATTACK_UI_SIZE
	);

	//2: Circuit UI
	
	//3: Button to switch circuit types
	
	//4: Hover Stats UI
	float hover_x = WINDOW_WIDTH - (WINDOW_WIDTH - (WINDOW_WIDTH_HALF + GRID_CELL_SIZE * 2.5f)) / 2.f;
	float hover_y = GRID_CELL_SIZE_OFFSET * 4 + ENEMY_STAT_UI_SIZE / 2.f;
	ui[4] = UI_Component_Create(
		CP_Image_Load(ENEMY_STAT_UI),
		CP_Vector_Set(hover_x, hover_y),
		ENEMY_STAT_UI_SIZE,
		ENEMY_STAT_UI_SIZE
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
	float text_size = TEXT_SIZE * WINDOW_RATIO;

	//Calculate and display player health
	CP_Settings_Fill(HP_COLOR);
	CP_Settings_NoStroke();
	CP_Graphics_DrawRect(ui[0].pos.x - ui[0].width * 0.11f, ui[0].pos.y + ui[0].height * 0.08f + height * ((original_health - player.health) / original_health), width, height * (player.health / original_health));

	//Display the attack text
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, DEFAULT_ALPHA));
	CP_Settings_TextSize(text_size);
	CP_Font_DrawText("Cast", ui[1].pos.x + text_size / 1.5f , ui[1].pos.y + text_size / 2.f);
	
	for (int i = 0; i < UI_COUNT - 1; ++i) {
		if (ui[i].width == 0) break;
		CP_Image_Draw(ui[i].img, ui[i].pos.x, ui[i].pos.y, ui[i].width, ui[i].height, DEFAULT_ALPHA);
	}
}