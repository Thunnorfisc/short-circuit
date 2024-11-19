#pragma once
#include "TEST_playerStruct.h"
#include "enemyStructs.h"
#include "bossStruct.h"
#include "cprocessing.h"

#define UI_COUNT 4
#define HP_COLOR CP_Color_Create(236, 52, 80,255)

#define HEALTH_UI_ADDR "Assets/UI/Health_UI.png"
#define HEALTH_UI_SIZE 256 * WINDOW_RATIO

#define ATTACK_UI_ADDR "Assets/UI/Attack_UI.png"
#define ATTACK_UI_SIZE 256 * WINDOW_RATIO

#define ENEMY_STAT_UI "Assets/UI/Enemy_Stats_UI.png"
#define ENEMY_STAT_UI_SIZE 384 * WINDOW_RATIO

#define CIRCUIT_UI "Assets/UI/Circuit_UI.png"
#define CIRCUIT_UI_SIZE 896 * WINDOW_RATIO

#define GRASS_UI "Assets/UI/Icon_Grass_Weakness.png"
#define FIRE_UI "Assets/UI/Icon_Fire_Weakness.png"
#define WATER_UI "Assets/UI/Icon_Water_Weakness.png"
#define WEAKNESS_UI_SIZE 128 * WINDOW_RATIO

#define CIRCUIT_UI_Y (float)WINDOW_HEIGHT - Calculate_Cell_Size() - BUFFER;
#define CIRCUIT_UI_X WINDOW_WIDTH_HALF;

typedef struct BattleUI {
	CP_Vector pos;
	CP_Image img;
	float width, height;
}BattleUI;

/*
Function   : Display_Enemy_Hover
Description: Used to display the Enemy Stats by hovering over the Enemy
Parameters : Enemy enemies[ENEMY_COUNT], CP_Vector mouse_pos
Return	   : void
*/
void Display_Enemy_Hover(Enemy enemies[ENEMY_COUNT], CP_Image const weakness[3], Enemy const original_enemies[ENEMY_COUNT], CP_Vector mouse_pos, BattleUI ui);

void Display_Boss_Hover(Boss boss, CP_Image const weakness[3], BossPart const original_bp[], CP_Vector mouse_pos, BattleUI ui, int count);

BattleUI UI_Component_Create(CP_Image img, CP_Vector pos, float width, float height);

void UI_Initialize(BattleUI ui[UI_COUNT]);

void Display_UI(BattleUI ui[UI_COUNT], Player player, float original_health, int s_count);