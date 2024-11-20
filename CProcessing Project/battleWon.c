#include <stdio.h>
#include "worldSystem.h"
#include "battleLost.h"

#include "battleSystem.h"
#include "magicSystemUtil.h"
#include "enemyStructs.h"
#include "TEST_playerUtil.h"
#include "battleSystemUI.h"
#include "mainMenuSystem.h"

void BattleWon_Initialize(void) {

}

void BattleWon_Update(void) {
	CP_Color backgroundColor = CP_Color_Create(235, 232, 232, 255);
	CP_Graphics_ClearBackground(backgroundColor);

	CP_Settings_Fill(COLOR_BLACK);
	CP_Settings_TextSize(TEXT_SIZE);
	CP_Font_DrawText("You Won! Congratulations!", WINDOW_WIDTH_HALF, WINDOW_HEIGHT_1_5);

	CP_Color returnMainMenuButton = CP_Color_Create(0, 255, 45, 255);
	CP_Settings_Fill(returnMainMenuButton);
	CP_Graphics_DrawRect(WINDOW_WIDTH_HALF, WINDOW_HEIGHT_HALF, WINDOW_WIDTH * 1 / 2.f, WINDOW_HEIGHT * 1 / 8.f);

	CP_Settings_Fill(COLOR_BLACK);
	CP_Font_DrawText("Return to Main Menu", WINDOW_WIDTH_HALF, WINDOW_HEIGHT_HALF);

	if (IsAreaClicked(WINDOW_WIDTH_HALF, WINDOW_HEIGHT_HALF, WINDOW_WIDTH * 1 / 2.f, WINDOW_HEIGHT * 1 / 8.f, CP_Input_GetMouseX(), CP_Input_GetMouseY()) && CP_Input_MouseClicked()) {
		ResetGame();
		CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
	}
}

void BattleWon_Exit(void) {

}