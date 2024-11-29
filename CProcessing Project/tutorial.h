/*All content © 2024 DigiPen Institute of Technology Singapore, all rights reserved.
@file tutorial.h
@author Lim Yan De (l.yande)
@course CSD1401 Software 
@section b
@Project Short Circuit Game
@date 26/11/2024
@brief Header file defining the tutorial system interface and states.
Contains definitions for tutorial states, structures, and function
declarations needed to manage the game's tutorial sequence and
progression tracking.
*/
#pragma once

typedef enum {
    TUTORIAL_BATTLE_START,
    TUTORIAL_BATTLE_HOVER_ENEMY,
    TUTORIAL_BATTLE_DRAG_PIECE,
    TUTORIAL_BATTLE_CAST_SPELL,
} TutorialState;

/*!
@author Lim Yan De (l.yande)
@brief Updates the tutorial state and progression.
@param void
@return void
*/
void Tutorial_Update(void);

/*!
@author Lim Yan De (l.yande)
@brief Draws tutorial UI elements and instructions.
@param void
@return void
*/
void Tutorial_Draw(void);

/*!
@author Lim Yan De (l.yande)
@brief Sets the current tutorial state. If player complete the tutorial,
the tutorial will stop showing.
@param state - TutorialState enum value specifying the new state
@return void
*/
void Tutorial_SetState(TutorialState state);

/*!
@author Lim Yan De (l.yande)
@brief Checks if a specific tutorial state is completed.
@param state - TutorialState to check completion status
@return int - returns 1 if tutorial state is complete
*/
int Tutorial_IsComplete(TutorialState state);