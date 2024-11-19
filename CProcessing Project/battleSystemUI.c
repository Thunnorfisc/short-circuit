#include "battleSystemUI.h"
#include "generalUtils.h"
/*
Function   : Display_Enemy_Hover
Description: Used to display the Enemy Stats by hovering over the Enemy
Parameters : Enemy enemies[ENEMY_COUNT], CP_Vector mouse_pos
Return	   : void
*/
void Display_Enemy_Hover(Enemy enemies[ENEMY_COUNT], CP_Image const weakness[3], Enemy const original_enemies[ENEMY_COUNT], CP_Vector mouse_pos, BattleUI ui) {
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

			for (int j = 0; j < ENEMY_COUNT; ++j) {
				if (enemies[i].enemy_type == original_enemies[j].enemy_type) {
					//Display Health of Enemy Stats
					CP_Settings_Fill(HP_COLOR);
					CP_Settings_RectMode(CP_POSITION_CORNER);
					// hard code adjust healthbar go slightly above
					CP_Graphics_DrawRect(ui.pos.x - ui.width / 2.f + BUFFER * 2 * WINDOW_RATIO, ui.pos.y - 30.0f, hp_width * enemies[i].healthbar / original_enemies[j].healthbar, hp_height);
					break;
				}
			}
			CP_Settings_RectMode(CP_POSITION_CENTER);

			//draw enemy data
			float y_pos_elements = ui.pos.y + ui.height / 2 - WEAKNESS_UI_SIZE/2.f - BUFFER * WINDOW_RATIO;

			if (enemies[i].weakness != 0) {
				CP_Image_Draw(weakness[enemies[i].weakness - 1], ui.pos.x - WEAKNESS_UI_SIZE / 2.f, y_pos_elements, WEAKNESS_UI_SIZE, WEAKNESS_UI_SIZE, DEFAULT_ALPHA);
				// Hard coded - need to be changed
				CP_Image crit_weakness_img;
				crit_weakness_img = CP_Image_Load(CRIT_WEAKNESS);
				CP_Image_Draw(crit_weakness_img, ui.pos.x - WEAKNESS_UI_SIZE - 0.25f / 2.f, y_pos_elements - 20.f, WEAKNESS_UI_SIZE * 0.5f, WEAKNESS_UI_SIZE * 0.5f, DEFAULT_ALPHA);
			}
			
			// Draw weakness text
			CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
			CP_Settings_TextSize(text_size - 22.f);
			CP_Font_DrawText("Weakness", ui.pos.x - WEAKNESS_UI_SIZE / 2.f, y_pos_elements - 60.f);

			// Draw resistance text
			CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
			CP_Settings_TextSize(text_size - 22.f);
			CP_Font_DrawText("Resistance", ui.pos.x + WEAKNESS_UI_SIZE / 2.f, y_pos_elements - 60.f);

			if (enemies[i].resistance != 0) {
				CP_Image_Draw(weakness[enemies[i].resistance - 1], ui.pos.x + WEAKNESS_UI_SIZE/2.f, y_pos_elements, WEAKNESS_UI_SIZE, WEAKNESS_UI_SIZE, DEFAULT_ALPHA);
			}
			break;
		}
	}
}

void Display_Boss_Hover(Boss boss, CP_Image const weakness[3], BossPart const original_bp[], CP_Vector mouse_pos, BattleUI ui, int count) {
	float text_size = TEXT_SIZE * WINDOW_RATIO;
	float hp_width = ui.width - BUFFER * 4 * WINDOW_RATIO;
	float hp_height = BUFFER * 3 * WINDOW_RATIO;

	for (int i = 0; i < boss.num_of_bp; ++i) {
		if (CP_Vector_Distance(boss.parts[i].pos, mouse_pos) <= GRID_CELL_SIZE / 2.0f) {
			CP_Image_Draw(ui.img, ui.pos.x, ui.pos.y, ui.width, ui.height, DEFAULT_ALPHA / 2);

			//Display Name of the enemy
			CP_Settings_Fill(CP_Color_Create(0, 0, 0, DEFAULT_ALPHA));
			CP_Settings_TextSize(text_size);
			CP_Font_DrawText(boss.boss_name, ui.pos.x, (ui.pos.y - ui.height / 2.f) + text_size / 2.f + 3 * BUFFER * WINDOW_RATIO);

			//Display Health of Enemy
			CP_Settings_Fill(HP_COLOR);
			CP_Settings_RectMode(CP_POSITION_CORNER);
			// hard code adjust healthbar go slightly above
			CP_Graphics_DrawRect(ui.pos.x - ui.width / 2.f + BUFFER * 2.f * WINDOW_RATIO, ui.pos.y - 30.0f, hp_width * boss.parts[i].healthbar / original_bp[boss.parts[i].id].healthbar, hp_height);
			CP_Settings_RectMode(CP_POSITION_CENTER);
			
			//Draw Boss Weakness
			float y_pos_elements = ui.pos.y + ui.height / 2 - WEAKNESS_UI_SIZE/2.f - BUFFER * WINDOW_RATIO;
			if (boss.parts[i].weakness != 0){
				CP_Image_Draw(weakness[boss.parts[i].weakness - 1], ui.pos.x - WEAKNESS_UI_SIZE / 2.f, y_pos_elements, WEAKNESS_UI_SIZE, WEAKNESS_UI_SIZE, DEFAULT_ALPHA);
				
				// Hard coded - need to be changed
				CP_Image crit_weakness_img;
				crit_weakness_img = CP_Image_Load(CRIT_WEAKNESS);
				CP_Image_Draw(crit_weakness_img, ui.pos.x - WEAKNESS_UI_SIZE - 0.25f / 2.f, y_pos_elements - 20.f, WEAKNESS_UI_SIZE * 0.5f, WEAKNESS_UI_SIZE * 0.5f, DEFAULT_ALPHA);

				// Draw weakness text
				CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
				CP_Settings_TextSize(text_size - 22.f);
				CP_Font_DrawText("Weakness", ui.pos.x - WEAKNESS_UI_SIZE / 2.f, y_pos_elements - 60.f);
			};

			//Draw Boss Resistance
			if (boss.parts[i].resistance != 0) {
				// Draw resistance text
				CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
				CP_Settings_TextSize(text_size - 22.f);
				CP_Font_DrawText("Resistance", ui.pos.x + WEAKNESS_UI_SIZE / 2.f, y_pos_elements - 60.f);
				CP_Image_Draw(weakness[boss.parts[i].resistance - 1], ui.pos.x + WEAKNESS_UI_SIZE/2.f, y_pos_elements, WEAKNESS_UI_SIZE, WEAKNESS_UI_SIZE, DEFAULT_ALPHA);
			}
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

	float circuit_x = CIRCUIT_UI_X;
	float circuit_y = CIRCUIT_UI_Y;
	//2: Circuit UI
	ui[2] = UI_Component_Create(
		CP_Image_Load(CIRCUIT_UI),
		CP_Vector_Set(circuit_x, circuit_y),
		CIRCUIT_UI_SIZE,
		Calculate_Cell_Size()
	);

	//3: Hover Stats UI
	float hover_x = WINDOW_WIDTH - (WINDOW_WIDTH - (WINDOW_WIDTH_HALF + GRID_CELL_SIZE * 2.5f)) / 2.f;
	float hover_y = GRID_CELL_SIZE_OFFSET * 4 + ENEMY_STAT_UI_SIZE / 2.f;
	ui[3] = UI_Component_Create(
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
void Display_UI(BattleUI ui[UI_COUNT], Player player, float original_health, int s_count) {
	//Default Health Size
	float width = ui[0].width * 0.78f;
	float height = (ui[0].height * 0.81f) * (player.health / original_health);
	float text_size = TEXT_SIZE * WINDOW_RATIO;

	//Calculate and display player health
	CP_Settings_Fill(HP_COLOR);
	CP_Settings_NoStroke();
	CP_Graphics_DrawRect(ui[0].pos.x - ui[0].width * 0.11f, WINDOW_HEIGHT - (height / 2.f), width, height);

	//Display the attack text
	CP_Settings_Fill(COLOR_WHITE(255));
	CP_Settings_TextSize(text_size);
	CP_Font_DrawText("Cast", ui[1].pos.x + text_size / 1.5f , ui[1].pos.y + text_size / 2.f);
	
	//Display the BG and Text for Circuit UI
	CP_Settings_Fill(COLOR_WHITE(124));
	CP_Graphics_DrawRect(ui[2].pos.x, ui[2].pos.y, ui[2].width, ui[2].height);

	// To display count of straight pipes
	char s_count_str[40];
	sprintf_s(s_count_str,sizeof(s_count_str),"(Vertical/Horizontal): %d Left",s_count);
	CP_Settings_Fill(COLOR_WHITE(255));
	// Hardcode first
	int straight_text_y_pos = ui[2].pos.y - 50;
	int straight_text_x_pos = ui[2].pos.x - 100;
	CP_Settings_TextSize(text_size - 25);
	CP_Font_DrawText(s_count_str, straight_text_x_pos + ui[2].width/2 + BUFFER * 3 * WINDOW_RATIO, straight_text_y_pos);

	for (int i = 0; i < UI_COUNT - 1; ++i) {
		if (ui[i].width == 0) break;
		CP_Image_Draw(ui[i].img, ui[i].pos.x, ui[i].pos.y, ui[i].width, ui[i].height, DEFAULT_ALPHA);
	}
}