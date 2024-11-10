#include "creditScreen.h"
#include "cprocessing.h"
#include "mainMenuSystem.h"

// Position ratios for UI elements
#define UI_CENTER_X         0.5f    // Centered horizontally

// Define positions for credits text
#define CREDITS_TITLE_Y         0.1f
#define CREDITS_START_Y         0.2f
#define CREDITS_LINE_SPACE      0.05f
#define CREDITS_HALF_SPACE      0.025f    
#define CREDITS_DOUBLE_SPACE    0.1f      

void Credits_Init(void) {
    CP_Settings_RectMode(CP_POSITION_CENTER);
    CP_Font_Load("Assets/Exo2-Regular.ttf");
    CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_TOP);
}

void Credits_Update(void) {
    // Clear background
    CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));

    float windowWidth = (float)CP_System_GetWindowWidth();
    float windowHeight = (float)CP_System_GetWindowHeight();
    float currentY = windowHeight * CREDITS_START_Y;

    CP_Settings_Save();

    // Draw title
    CP_Settings_TextSize(50.0f);
    CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
    CP_Font_DrawText("CREDITS", windowWidth * UI_CENTER_X, windowHeight * CREDITS_TITLE_Y);

    // Draw credits content
    CP_Settings_TextSize(30.0f);

    // President
    CP_Font_DrawText("President", windowWidth * UI_CENTER_X, currentY);
    currentY += windowHeight * CREDITS_LINE_SPACE;
    CP_Settings_TextSize(25.0f);
    CP_Font_DrawText("Claude Comair", windowWidth * UI_CENTER_X, currentY);
    currentY += windowHeight * CREDITS_DOUBLE_SPACE;

    // Team Members
    CP_Settings_TextSize(30.0f);
    CP_Font_DrawText("Team Members", windowWidth * UI_CENTER_X, currentY);
    currentY += windowHeight * CREDITS_LINE_SPACE;
    CP_Settings_TextSize(25.0f);
    CP_Font_DrawText("Jason - Lead Programmer", windowWidth * UI_CENTER_X, currentY);
    currentY += windowHeight * CREDITS_HALF_SPACE;
    CP_Font_DrawText("William", windowWidth * UI_CENTER_X, currentY);
    currentY += windowHeight * CREDITS_HALF_SPACE;
    CP_Font_DrawText("Yande", windowWidth * UI_CENTER_X, currentY);
    currentY += windowHeight * CREDITS_HALF_SPACE;
    CP_Font_DrawText("Kelly", windowWidth * UI_CENTER_X, currentY);
    currentY += windowHeight * CREDITS_HALF_SPACE;
    CP_Font_DrawText("Wei Song", windowWidth * UI_CENTER_X, currentY);
    currentY += windowHeight * CREDITS_DOUBLE_SPACE;

    // Advisors
    CP_Settings_TextSize(30.0f);
    CP_Font_DrawText("Instructors", windowWidth * UI_CENTER_X, currentY);
    currentY += windowHeight * CREDITS_LINE_SPACE;
    CP_Settings_TextSize(25.0f);
    CP_Font_DrawText("Professor Ding Xiang", windowWidth * UI_CENTER_X, currentY);
    currentY += windowHeight * CREDITS_HALF_SPACE;
    CP_Font_DrawText("Professor Gerald Wong", windowWidth * UI_CENTER_X, currentY);
    currentY += windowHeight * CREDITS_HALF_SPACE;
    CP_Font_DrawText("Professor Soroor", windowWidth * UI_CENTER_X, currentY);
    currentY += windowHeight * CREDITS_DOUBLE_SPACE;

    // Special Thanks
    CP_Settings_TextSize(30.0f);
    CP_Font_DrawText("Special Thanks", windowWidth * UI_CENTER_X, currentY);
    currentY += windowHeight * CREDITS_LINE_SPACE;
    CP_Settings_TextSize(25.0f);
    CP_Font_DrawText("DigiPen Institute of Technology Singapore", windowWidth * UI_CENTER_X, currentY);

    // Draw return instruction
    currentY = windowHeight * 0.9f;
    CP_Settings_TextSize(20.0f);
    CP_Font_DrawText("Press ESC to return to Main Menu", windowWidth * UI_CENTER_X, currentY);

    CP_Settings_Restore();

    if (CP_Input_KeyTriggered(KEY_ESCAPE)) {
        CP_Engine_SetNextGameStateForced(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
    }
}

void Credits_Exit(void) {
}