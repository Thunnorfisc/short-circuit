#pragma once
#include "TEST_playerStruct.h"
#include "enemyStructs.h"
#include "cprocessing.h"

#define UI_COUNT 5
#define HEALTH_UI_ADDR "Assets/UI/Health_UI.png"
#define HEALTH_UI_SIZE 256 * WINDOW_RATIO
#define ATTACK_UI_ADDR "Assets/UI/Attack_UI.png"
#define ATTACK_UI_SIZE 256 * WINDOW_RATIO

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
void Display_Enemy_Hover(Enemy enemies[ENEMY_COUNT], CP_Vector mouse_pos);

BattleUI UI_Component_Create(CP_Image img, CP_Vector pos, float width, float height);

void UI_Initialize(BattleUI ui[UI_COUNT]);

void Display_UI(BattleUI const ui[UI_COUNT], Player player, float original_health);