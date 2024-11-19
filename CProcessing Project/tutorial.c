#include <stdio.h>
#include "cprocessing.h"
#include "tutorial.h"
#include "generalUtils.h"
#include "battleSystem.h"
#include "battleSystemUI.h"

#define TUTORIAL_BOX_WIDTH (WINDOW_WIDTH * 0.25f)
#define TUTORIAL_BOX_HEIGHT (WINDOW_HEIGHT * 0.1f)
#define TUTORIAL_BOX_X (WINDOW_WIDTH * 0.15f)
#define TUTORIAL_BOX_Y (WINDOW_HEIGHT * 0.1f)
#define TUTORIAL_TEXT_SIZE (WINDOW_HEIGHT * 0.025f)

static TutorialState current_state = TUTORIAL_BATTLE_START;

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
        0, // Automatically proceeds when condition met
        Check_Enemy_Hovered
    },
    [TUTORIAL_BATTLE_DRAG_PIECE] = {
        "Click and drag puzzle pieces from below.\n"
        "Elemental pieces (colored) deal extra damage to matching weaknesses!",
        0,
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

    // Draw semi-transparent black box
    CP_Settings_Fill(CP_Color_Create(255, 0, 0, 180));
    CP_Graphics_DrawRect(
        TUTORIAL_BOX_X,
        TUTORIAL_BOX_Y * 1.7f,
        TUTORIAL_BOX_WIDTH,
        TUTORIAL_BOX_HEIGHT * 2.5f
    );

    // Draw tutorial text
    CP_Settings_TextSize(TUTORIAL_TEXT_SIZE);
    CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
    if (tutorial_steps[current_state].message) {
        CP_Font_DrawTextBox(
            tutorial_steps[current_state].message,
            TUTORIAL_BOX_X * 0.25f,
            TUTORIAL_BOX_Y * 0.7f,
            TUTORIAL_BOX_WIDTH - 20
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