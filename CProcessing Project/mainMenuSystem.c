/*All content © 2024 DigiPen Institute of Technology Singapore, all rights reserved.
@file mainMenuSystem.c
@author Lim Yan De (l.yande)
@course CSD1401
@section b
@Project Short Circuit Game
@date 26/11/2024
@brief This file implements the main menu system and pause menu functionality for
the Short Circuit game. It handles the splash screen, main menu interface,
pause menu controls, and transitions between different game states. The file
manages UI elements like buttons, logo display, copyright information, and
screen transitions while providing fullscreen toggle capability.
*/
#include <stdio.h>
#include "cprocessing.h"
#include "mainMenuSystem.h"
#include "generalUtils.h"
#include "worldSystem.h"
#include "creditScreen.h"

// Position ratios for UI elements
#define UI_CENTER_X         0.5f    // Centered horizontally
#define UI_CENTER_Y         0.5f    // Centered vertically
#define FONT_SIZE_LARGE     0.05f
#define FONT_SIZE_TINY      0.02f

// Vertical position ratios for main menu UI
#define UI_TITLE_Y         0.2f
#define UI_LOGO_Y          0.5f
#define UI_COPYRIGHT_Y     0.95f
#define UI_NEWGAME_Y       0.35f
#define UI_CREDITS_Y       0.65f
#define UI_EXIT_Y          0.80f

// Size ratios for main menu UI
#define UI_BUTTON_WIDTH    0.3f
#define UI_BUTTON_HEIGHT   0.1f
#define UI_LOGO_WIDTH      0.6f
#define UI_LOGO_HEIGHT     0.6f

// Position ratios for pause menu UI 
#define PAUSE_TITLE_Y     0.2f
#define PAUSE_MAINMENU_Y  0.4f
#define PAUSE_SAVE_Y      0.5f
#define PAUSE_QUIT_Y      0.6f
#define PAUSE_BUTTON_W    0.3f
#define PAUSE_BUTTON_H    0.1f

int isFullscreen = 0;

// Structure definitions for UI elements
typedef struct {
    struct {
        float width;
        float height;
    } window;
    struct {
		float x;
		float y;
    } copyright;
    struct {
        float x;
        float y;
    } title;
    struct {
        float x;
        float y;
		float width;
		float height;
    } logo;

    struct {
        float width;
        float height;
        struct {
            float x;
            float y;
        } button_newgame;
        struct {
            float x;
            float y;
        } button_continue;
		struct {
			float x;
			float y;
		} button_credits;
        struct {
            float x;
            float y;
        } button_exit;
    } button;
} UI;

// Setup for menu states
typedef enum {
    SPLASH_SCREEN,
    MAIN_MENU
} MenuState;

CP_Image logo;
MenuState currentMenuState = SPLASH_SCREEN;
float splashStartTime = 0;

void Main_Menu_Init(void)
{
    logo = CP_Image_Load("Assets/DigiPen_Singapore_WEB_RED.png");
    CP_Settings_ImageMode(CP_POSITION_CENTER);

    if (currentMenuState != MAIN_MENU) {
        splashStartTime = CP_System_GetSeconds();
        currentMenuState = SPLASH_SCREEN;
    }

    // Set text properties
    CP_Font_Load("Assets/Exo2-Regular.ttf");
    float windowHeight = (float)CP_System_GetWindowHeight();
    CP_Settings_TextSize(windowHeight * FONT_SIZE_LARGE); 
    CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
    
    CP_Settings_RectMode(CP_POSITION_CENTER);
}

void Main_Menu_Update(void)
{
    Handle_Fullscreen(&isFullscreen);
    switch (currentMenuState) {
    case SPLASH_SCREEN:
        Draw_Splash_Screen();
        break;

    case MAIN_MENU:
        Draw_Main_Menu();
        break;
    }
}

void Main_Menu_Exit(void)
{
    CP_Image_Free(&logo);
}

// Handles the pause menu when pressing ESC while in game
void Handle_Pause_Menu(int* MenuOpen)
{
    // Toggle menu with escape key
    if (CP_Input_KeyTriggered(KEY_ESCAPE)) {
        *MenuOpen = !(*MenuOpen);
    }

    // Handle pause menu if open
    if (*MenuOpen) {
        // Set text colour for the title
        CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));

        // Draw "PAUSED" title
        CP_Font_DrawText("PAUSED",
            WINDOW_WIDTH * UI_CENTER_X,
            WINDOW_HEIGHT * PAUSE_TITLE_Y);

        // Draw buttons
        if (Draw_Button("Main Menu",
            WINDOW_WIDTH * UI_CENTER_X,
            WINDOW_HEIGHT * PAUSE_MAINMENU_Y,
            WINDOW_WIDTH * PAUSE_BUTTON_W,
            WINDOW_HEIGHT * PAUSE_BUTTON_H)) {
            World_Reset();
            currentMenuState = MAIN_MENU;  // Set menu state
            CP_Engine_SetNextGameStateForced(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
            *MenuOpen = !*MenuOpen;
        }      
        if (Draw_Button("Quit Game",
            WINDOW_WIDTH * UI_CENTER_X,
            WINDOW_HEIGHT * PAUSE_QUIT_Y,
            WINDOW_WIDTH * PAUSE_BUTTON_W,
            WINDOW_HEIGHT * PAUSE_BUTTON_H)) {

            CP_Engine_Terminate();
        }
    }
}

// Handles fullscreen toggle
void Handle_Fullscreen(int* fullscreen) {
    if (CP_Input_KeyTriggered(KEY_F)) {
        *fullscreen = !(*fullscreen);

        if (*fullscreen) {
            CP_System_Fullscreen();
        }
        else {
            CP_System_SetWindowSize(1280, 720);
        }
    }
}

// Draws the splash screen
void Draw_Splash_Screen()
{
    CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
    UI ui = {
            .logo.x = CP_System_GetWindowWidth() * UI_CENTER_X,
            .logo.y = CP_System_GetWindowHeight() * UI_LOGO_Y,
            .logo.width = CP_System_GetWindowWidth() * UI_LOGO_WIDTH,
            .logo.height = CP_System_GetWindowHeight() * UI_LOGO_HEIGHT
    };

    // Draw Logo
    CP_Image_DrawAdvanced(logo,
        ui.logo.x,
        ui.logo.y,
        ui.logo.width,
        ui.logo.height,
        255,
        0.0f);

    // Check if 2 seconds have passed
    if (CP_System_GetSeconds() - splashStartTime >= 2.0f) {
        currentMenuState = MAIN_MENU;
    }

    // Allow skipping with Escape key
    if (CP_Input_KeyTriggered(KEY_ESCAPE)) {
        currentMenuState = MAIN_MENU;
    }
}

//Draws the main menu
void Draw_Main_Menu()
{
    CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));

    UI ui = {
        .window = {
            .width = (float)CP_System_GetWindowWidth(),
            .height = (float)CP_System_GetWindowHeight()
        },
        .title = {
            .x = (float)CP_System_GetWindowWidth() * UI_CENTER_X,
            .y = (float)CP_System_GetWindowHeight() * UI_TITLE_Y
        },
    };

    ui.button.width = ui.window.width * UI_BUTTON_WIDTH;
    ui.button.height = ui.window.height * UI_BUTTON_HEIGHT;

    ui.button.button_newgame.x = ui.window.width * UI_CENTER_X;
    ui.button.button_newgame.y = ui.window.height * UI_NEWGAME_Y;
    ui.button.button_continue.x = ui.window.width * UI_CENTER_X;
    ui.button.button_continue.y = ui.window.height * UI_CENTER_Y;
	ui.button.button_credits.x = ui.window.width * UI_CENTER_X;
	ui.button.button_credits.y = ui.window.height * UI_CREDITS_Y;
    ui.button.button_exit.x = ui.window.width * UI_CENTER_X;
    ui.button.button_exit.y = ui.window.height * UI_EXIT_Y;

    CP_Settings_Fill(CP_Color_Create(20, 200, 200, 255));
    CP_Font_DrawText("Short Circuit", ui.title.x, ui.title.y);

    if (Draw_Button("New Game", ui.button.button_newgame.x, ui.button.button_newgame.y, ui.button.width, ui.button.height)) {
        CP_Engine_SetNextGameState(World_Init, World_Update, World_Exit);
    }

    if (Draw_Button("Load Game", ui.button.button_continue.x, ui.button.button_continue.y, ui.button.width, ui.button.height)) {
        World_SetLoadFlag();
        CP_Engine_SetNextGameState(World_Init, World_Update, World_Exit);
    }

    if (Draw_Button("Credits", ui.button.button_credits.x, ui.button.button_credits.y, ui.button.width, ui.button.height)) {
		CP_Engine_SetNextGameState(Credits_Init, Credits_Update, Credits_Exit);
	}

    if (Draw_Button("Quit Game", ui.button.button_exit.x, ui.button.button_exit.y, ui.button.width, ui.button.height)) {
        CP_Engine_Terminate();
    }
    Draw_Copyright();
}

//Prints the copyright text
void Draw_Copyright(){
    CP_Settings_Fill(COLOR_WHITE(255));
    UI ui = {
        .copyright.x = CP_System_GetWindowWidth() * UI_CENTER_X,
        .copyright.y = CP_System_GetWindowHeight() * UI_COPYRIGHT_Y
    };

    CP_Settings_Save();
    float windowHeight = (float)CP_System_GetWindowHeight();
    CP_Settings_TextSize(windowHeight * FONT_SIZE_TINY);
    CP_Font_DrawText("All content (c) 2024 DigiPen Institute of Technology Singapore, all rights reserved.", ui.copyright.x, ui.copyright.y);
    CP_Settings_Restore();
}