#include <stdio.h>
#include "cprocessing.h"
#include "tutorial.h"
#include "generalUtils.h"
#include "battleSystem.h"
#include "battleSystemUI.h"

#define TUTORIAL_BOX_WIDTH     (WINDOW_WIDTH * 0.25f)
#define TUTORIAL_BOX_HEIGHT    (WINDOW_HEIGHT * 0.1f)
#define TUTORIAL_BOX_X         (WINDOW_WIDTH * 0.15f)
#define TUTORIAL_BOX_Y         (WINDOW_HEIGHT * 0.1f)
#define TUTORIAL_TEXT_SIZE     (WINDOW_HEIGHT * 0.025f)

#define TUTORIAL_BOX_Y_MULT    1.7f
#define TUTORIAL_BOX_H_MULT    2.5f
#define TUTORIAL_TEXT_X_MULT   0.25f
#define TUTORIAL_TEXT_Y_MULT   0.7f
#define TUTORIAL_TEXT_PADDING  20

typedef enum {
    RED_BOX_R = 255,
    RED_BOX_G = 0,
    RED_BOX_B = 0,
    RED_BOX_ALPHA = 180,

    TEXT_R = 255,
    TEXT_G = 255,
    TEXT_B = 255,
    TEXT_ALPHA = 255
} TutorialColors;

static TutorialState current_state = TUTORIAL_BATTLE_START;
static int showing_tutorial = 1;

typedef struct {
    const char* message;
    int requires_click;
    int (*completion_check)(void);
} TutorialStep;

// Completion check functions
static int Check_Enemy_Hovered(void) {
    if (Enemy_Hovered == 1) return 1;
    return 0;
}

static int Check_Piece_Placed(void) {
    if (Piece_Placed == 1) return 1;
    return 0;
}

static int Check_Spell_Cast(void) {
    if (Spell_Cast == 1) return 1;
    return 0;
}

// Tutorial steps configuration
static const TutorialStep tutorial_steps[] = {
    // Battle tutorials
    [TUTORIAL_BATTLE_START] = {
        "Welcome to battle! Let's learn how to defeat enemies.\n"
        "Click to proceed.",
        1, // Requires click to continue
        NULL
    },
    [TUTORIAL_BATTLE_HOVER_ENEMY] = {
        "Hover over enemies to see their health, weaknesses, and resistances.\n"
        "Red bar shows health\n"
        "Left icon shows weakness\n"
        "Right icon (with red overlay) shows resistance\n"
        "Click on the enemy to proceed.",
        0, 
        Check_Enemy_Hovered
    },
    [TUTORIAL_BATTLE_DRAG_PIECE] = {
        "Click and drag puzzle pieces from below.\n"
        "Elemental pieces (colored) deal extra damage to matching weaknesses!",
        0, // Automatically proceeds when condition met
        Check_Piece_Placed
    },
    [TUTORIAL_BATTLE_CAST_SPELL] = {
        "Create a complete loop using \n"
        "puzzle pieces to deal damage to the enemy\n"
        "Click 'Cast' to end turn\n"
        "Defeat the enemy to earn currency.",
        0,
        Check_Spell_Cast
    },
};

void Tutorial_Update(void) {
    if (!showing_tutorial) return;

    // Handle click to continue if required
    if (tutorial_steps[current_state].requires_click) {
        if (CP_Input_MouseClicked()) {
            Tutorial_SetState(current_state + 1);
        }
    }
    // Otherwise check completion condition
    else if (tutorial_steps[current_state].completion_check &&
        tutorial_steps[current_state].completion_check()) {
        Tutorial_SetState(current_state + 1);
    }
}

void Tutorial_Draw(void) {
    if (!showing_tutorial) return;

    // Draw semi-transparent red box
    CP_Settings_Fill(CP_Color_Create(RED_BOX_R, RED_BOX_G, RED_BOX_B, RED_BOX_ALPHA));
    CP_Graphics_DrawRect(
        TUTORIAL_BOX_X,
        TUTORIAL_BOX_Y * TUTORIAL_BOX_Y_MULT,
        TUTORIAL_BOX_WIDTH,
        TUTORIAL_BOX_HEIGHT * TUTORIAL_BOX_H_MULT
    );

    // Draw tutorial text
    CP_Settings_TextSize(TUTORIAL_TEXT_SIZE);
    CP_Settings_Fill(CP_Color_Create(TEXT_R, TEXT_G, TEXT_B, TEXT_ALPHA));
    if (tutorial_steps[current_state].message) {
        CP_Font_DrawTextBox(
            tutorial_steps[current_state].message,
            TUTORIAL_BOX_X * TUTORIAL_TEXT_X_MULT,
            TUTORIAL_BOX_Y * TUTORIAL_TEXT_Y_MULT,
            TUTORIAL_BOX_WIDTH - TUTORIAL_TEXT_PADDING
        );
    }
}

void Tutorial_SetState(TutorialState state) {
    current_state = state;

    // End tutorial after last step
    if (state == TUTORIAL_BATTLE_CAST_SPELL + 1) {
        showing_tutorial = 0;
    }
}

int Tutorial_IsComplete(TutorialState state) {
    return !showing_tutorial;
}