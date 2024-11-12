#include "creditScreen.h"
#include "cprocessing.h"
#include "mainMenuSystem.h"
#include "creditScreen.h"

#define UI_CENTER_X         0.5f    // Centered horizontally

// Define positions for credits text
#define CREDITS_TITLE_Y         0.1f
#define CREDITS_START_Y         0.2f
#define CREDITS_LINE_SPACE      0.045f
#define CREDITS_HALF_SPACE      0.025f

void Credits_Init(void) {}

void Credits_Update(void) {
    // Define credit categories and their members
    CreditCategory credits[] = {
        {
            .category = "President",
            .names = {"Claude Comair"},
            .nameCount = 1
        },
        {
            .category = "Team Members",
            .names = {
                "Jason - Lead Programmer",
                "William",
                "Yande",
                "Kelly",
                "Wei Song"
            },
            .nameCount = 5
        },
        {
            .category = "Instructors",
            .names = {
                "Professor Ding Xiang",
                "Professor Gerald Wong",
                "Professor Soroor"
            },
            .nameCount = 3
        },
        {
            .category = "Special Thanks",
            .names = {"DigiPen Institute of Technology Singapore"},
            .nameCount = 1
        }
    };

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

    // Print all credit categories
    for (int i = 0; i < sizeof(credits) / sizeof(credits[0]); i++) {
        PrintCredit(&credits[i], windowWidth, &currentY);
    }

    // Draw return instruction
    CP_Settings_TextSize(20.0f);
    CP_Font_DrawText("Press ESC to return to Main Menu",
        windowWidth * UI_CENTER_X,
        windowHeight * 0.9f);

    CP_Settings_Restore();

    if (CP_Input_KeyTriggered(KEY_ESCAPE)) {
        CP_Engine_SetNextGameStateForced(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
    }
}

void Credits_Exit(void) {}

void PrintCredit(const CreditCategory* category, float windowWidth, float* currentY) {
    float windowHeight = (float)CP_System_GetWindowHeight();

    // Print category name
    CP_Settings_TextSize(30.0f);
    CP_Font_DrawText(category->category, windowWidth * UI_CENTER_X, *currentY);
    *currentY += windowHeight * CREDITS_LINE_SPACE;

    // Print all names in category
    CP_Settings_TextSize(25.0f);
    for (int i = 0; i < category->nameCount; i++) {
        CP_Font_DrawText(category->names[i], windowWidth * UI_CENTER_X, *currentY);
        *currentY += windowHeight * CREDITS_HALF_SPACE;
    }

    // Add space between end of names and start of next category
    *currentY += windowHeight * CREDITS_LINE_SPACE;
}