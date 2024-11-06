#include <stdio.h>
#include "cprocessing.h"
#include "mainMenuSystem.h"
#include "generalUtils.h"
#include "worldSystem.h"

//#include "button_newgame.h"
//#include "oldgame.h"
int drawPlayerStatus = 0;

// Structure definitions
typedef struct {
    struct {
        float width;
        float height;
    } window;
    struct {
        float x;
        float y;
    } title;

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
        } button_exit;
    } button;
} UI;

PlayerStats playerStats = {
    .attack_power = 0,
    .health_points = 0 ,
    .currency = 100
};

void Main_Menu_Init()
{
    CP_Font_Load("Assets/Exo2-Regular.ttf"); //text assets
    float textSize = 60.0f; // text size
    CP_Settings_TextSize(textSize); //text size
    CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE); //text alignment
    CP_Settings_RectMode(CP_POSITION_CENTER); //reactangle alignment
    LoadGameState();
}

void Main_Menu_Update()
{
    CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));

    UI ui = {
    .window.width = CP_System_GetWindowWidth(),
    .window.height = CP_System_GetWindowHeight()
    };

    ui.title.x = ui.window.width * 0.5f;
    ui.title.y = ui.window.height * 0.2f;

    ui.button.width = ui.window.width * 0.3f;
    ui.button.height = ui.window.height * 0.1f;
    ui.button.button_newgame.x = ui.window.width * 0.5f;
    ui.button.button_newgame.y = ui.window.height * 0.35f;
    ui.button.button_continue.x = ui.window.width * 0.5f;
    ui.button.button_continue.y = ui.window.height * 0.5f;
    ui.button.button_exit.x = ui.window.width * 0.5f;
    ui.button.button_exit.y = ui.window.height * 0.65f;

    Display_Currency();

    CP_Settings_Fill(CP_Color_Create(20, 200, 200, 255));
    CP_Font_DrawText("Short Circuit", ui.title.x, ui.title.y);

    CP_Settings_Fill(CP_Color_Create(200, 200, 200, 255));
    CP_Graphics_DrawRect(ui.button.button_newgame.x, ui.button.button_newgame.y, ui.button.width, ui.button.height);
    CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
    CP_Font_DrawText("New Game", ui.button.button_newgame.x, ui.button.button_newgame.y);

    CP_Settings_Fill(CP_Color_Create(200, 200, 200, 255));
    CP_Graphics_DrawRect(ui.button.button_continue.x, ui.button.button_continue.y, ui.button.width, ui.button.height);
    CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
    CP_Font_DrawText("button_continue", ui.button.button_continue.x, ui.button.button_continue.y);

    CP_Settings_Fill(CP_Color_Create(200, 200, 200, 255));
    CP_Graphics_DrawRect(ui.button.button_exit.x, ui.button.button_exit.y, ui.button.width, ui.button.height);
    CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
    CP_Font_DrawText("button_exit", ui.button.button_exit.x, ui.button.button_exit.y);

    if (CP_Input_MouseClicked()) {
        float click_x = CP_Input_GetMouseX();
        float click_y = CP_Input_GetMouseY();

        if (IsAreaClicked(ui.button.button_newgame.x, ui.button.button_newgame.y, ui.button.width, ui.button.height, click_x, click_y)) {
            Generate_World(1);
            //Going to the Map System
            CP_Engine_SetNextGameState(World_Init, World_Update, World_Exit);
        }

        /*
        if (IsAreaClicked(ui.button.button_continue.x, ui.button.button_continue.y, ui.button.width, ui.button.height, click_x, click_y)) {
            CP_Engine_SetNextGameState(Game_Init2, Game_Update2, Game_button_exit2);
        }
        */
        if (IsAreaClicked(ui.button.button_exit.x, ui.button.button_exit.y, ui.button.width, ui.button.height, click_x, click_y)) {
            CP_Engine_Terminate();
        }
    }
}

void Main_Menu_Exit()
{

}

void Display_Currency() {
    //Test Value for current currency
    //int currency = 1000;
    int currency = CurrentCurrency();
    CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
    char text[64];
    sprintf_s(text, sizeof(text), "Currency: %d", currency);
    CP_Font_DrawText(text,
        1600.0 * 0.1f,
        800.0 * 0.1f);
}


void Handle_Pause_Menu(int* MenuOpen)
{
    // Toggle menu with escape key
    if (CP_Input_KeyTriggered(KEY_ESCAPE)) {
        *MenuOpen = !(*MenuOpen);
    }

    // Handle pause menu if open
    if (*MenuOpen) {
        CP_Settings_TextSize(50.0f);
        CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));

        // Draw menu
        CP_Font_DrawText("PAUSED", WINDOW_WIDTH * 0.5f, WINDOW_HEIGHT * 0.2f);
        CP_Font_DrawText("Main Menu (Press M)", WINDOW_WIDTH * 0.5f, WINDOW_HEIGHT * 0.4f);
        CP_Font_DrawText("SAVE (Press S)", WINDOW_WIDTH * 0.5f, WINDOW_HEIGHT * 0.5f);
        CP_Font_DrawText("Quit Game (Press Q)", WINDOW_WIDTH * 0.5f, WINDOW_HEIGHT * 0.6f);

        // Main menu option
        if (CP_Input_KeyTriggered(KEY_M)) {
            CP_Engine_SetNextGameStateForced(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
            *MenuOpen = !(*MenuOpen);
        }

        // Save game option
        if (CP_Input_KeyTriggered(KEY_S)) {
            SaveGameState();
        }

        // Quit game option
        if (CP_Input_KeyTriggered(KEY_Q)) {
            CP_Engine_Terminate();
        }
    }
}

void HandlePlayerStats() {
    while (CP_Input_KeyDown(KEY_TAB)) {
        drawPlayerStatus = !drawPlayerStatus;
        if (drawPlayerStatus) {
            CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
            CP_Font_DrawText("Player Status", WINDOW_WIDTH * 0.5f, WINDOW_HEIGHT * 0.3f);

            // Display player stats
            char text[64];
            sprintf_s(text, sizeof(text), "Attack Power: %d", playerStats.attack_power);
            CP_Font_DrawText(text,
                WINDOW_WIDTH * 0.5f,
                WINDOW_HEIGHT * 0.4f);
            sprintf_s(text, sizeof(text), "Health Points: %d", playerStats.health_points);
            CP_Font_DrawText(text,
                WINDOW_WIDTH * 0.5f,
                WINDOW_HEIGHT * 0.5f);
            sprintf_s(text, sizeof(text), "Currency: %d", playerStats.currency);
            CP_Font_DrawText(text,
                WINDOW_WIDTH * 0.5f,
                WINDOW_HEIGHT * 0.6f);
        }
        else return;
    }
}

void Handle_Fullscreen(int* fullscreen) {
    if (CP_Input_KeyTriggered(KEY_F)) {
        *fullscreen = !(*fullscreen);

        if (*fullscreen) {
            CP_System_Fullscreen();
        }
        else {
            CP_System_SetWindowSize(1920, 1080);
        }
    }
}

int CurrentCurrency() {
    return playerStats.currency;
}// to call in mainmenu

void SaveGameState() {
    FILE* file = fopen("save.txt", "wb");

    if (file != NULL) {
        // Write player stats to file
        fwrite(&playerStats.attack_power, sizeof(int), 1, file);
        fwrite(&playerStats.health_points, sizeof(int), 1, file);
        fwrite(&playerStats.currency, sizeof(int), 1, file);

        fclose(file);
    }
}

void LoadGameState() {
    FILE* file = fopen("save.txt", "rb");

    if (file != NULL) {
        // Read player stats from file
        fread(&playerStats.attack_power, sizeof(int), 1, file);
        fread(&playerStats.health_points, sizeof(int), 1, file);
        fread(&playerStats.currency, sizeof(int), 1, file);

        fclose(file);
    }
}