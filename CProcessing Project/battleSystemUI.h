#pragma once
#include "TEST_playerStruct.h"
#include "enemyStructs.h"
#include "bossStruct.h"
#include "cprocessing.h"

#define UI_COUNT 5
#define HP_COLOR CP_Color_Create(236, 52, 80,255)
#define HEALTH_UI_ADDR "Assets/UI/Health_UI.png"
#define HEALTH_UI_SIZE 256 * WINDOW_RATIO
#define ATTACK_UI_ADDR "Assets/UI/Attack_UI.png"
#define ATTACK_UI_SIZE 256 * WINDOW_RATIO
#define ENEMY_STAT_UI "Assets/UI/Enemy_Stats_UI.png"
#define ENEMY_STAT_UI_SIZE 384 * WINDOW_RATIO

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
void Display_Enemy_Hover(Enemy enemies[ENEMY_COUNT], Enemy const original_enemies[ENEMY_COUNT], CP_Vector mouse_pos, BattleUI ui);

void Display_Boss_Hover(Boss boss, BossPart const original_bp[], CP_Vector mouse_pos, BattleUI ui, int count);

BattleUI UI_Component_Create(CP_Image img, CP_Vector pos, float width, float height);

void UI_Initialize(BattleUI ui[UI_COUNT]);

void Display_UI(BattleUI ui[UI_COUNT], Player player, float original_health);