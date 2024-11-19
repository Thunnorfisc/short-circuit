#pragma once

typedef enum {
    TUTORIAL_BATTLE_START,
    TUTORIAL_BATTLE_HOVER_ENEMY,
    TUTORIAL_BATTLE_DRAG_PIECE,
    TUTORIAL_BATTLE_CAST_SPELL,
} TutorialState;

// Update tutorial state
void Tutorial_Update(void);

// Draw tutorial UI
void Tutorial_Draw(void);

// Set current tutorial state
void Tutorial_SetState(TutorialState state);

// Check if specific tutorial is complete
int Tutorial_IsComplete(TutorialState state);