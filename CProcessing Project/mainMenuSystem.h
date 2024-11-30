/*
@file mainMenuSystem.h
@author Lim Yan De (l.yande)
@course CSD1401
@section b
@Project Short Circuit Game
@date 26/11/2024
@brief Header file containing declarations for the main menu system functions.
This file provides the interface for initializing, updating, and managing the
main menu, splash screen, pause menu, and related UI functionality for the
Short Circuit game. It declares core menu system functions and screen management
capabilities.

All content © 2024 DigiPen Institute of Technology Singapore, all rights reserved.
*/
#pragma once
/*
@author Lim Yan De (l.yande)
@brief Initializes the main menu system.
This function sets up the menu UI elements, loads necessary assets,
initializes the splash screen, and prepares the menu state machine.
It loads the DigiPen logo, sets text properties, and initializes menu states.
@param void
@return void
*/
void Main_Menu_Init(void);

/*!
@author Lim Yan De (l.yande)
@brief Updates the main menu state and handles user input.
Manages transitions between splash screen and main menu, processes
button interactions, handles menu navigation, and updates the UI
based on current menu state and user interactions.
@param void
@return void
*/
void Main_Menu_Update(void);

/*!
@author Lim Yan De (l.yande)
@brief Clear splash screen image.
@param void
@return void
*/
void Main_Menu_Exit(void);

/*!
@author Lim Yan De (l.yande)
@brief Handles the pause menu functionality.
Controls the display and interaction of the pause menu, including
menu toggling with escape key and processing menu options like
return to main menu and quit game.
@param menu_open - pointer to int controlling menu visibility state
@return void
*/
void Handle_Pause_Menu(int* menu_open);

/*!
@author Lim Yan De (l.yande)
@brief Manages fullscreen toggle functionality.
Handles switching between windowed and fullscreen modes when
the 'F' key is pressed, adjusting window dimensions appropriately.
@param fullscreen - pointer to int tracking fullscreen state
@return void
*/
void Handle_Fullscreen(int* fullscreen);

/*!
@author Lim Yan De (l.yande)
@brief Renders the splash screen.
Displays the DigiPen logo splash screen for 2 seconds and
skip functionality. Manages transition to main menu after timeout
or user input.
@param void
@return void
*/
void Draw_Splash_Screen(void);

/*!
@author Lim Yan De (l.yande)
@brief Renders the main menu interface.
Draws the main menu UI including title, buttons (New Game, Continue,
Credits, Exit), and handles user interactions with these elements.
@param void
@return void
*/
void Draw_Main_Menu(void);

/*!
@author Lim Yan De (l.yande)
@brief Displays copyright information.
@param void
@return void
*/
void Draw_Copyright(void);
