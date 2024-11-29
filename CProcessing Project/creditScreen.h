/*All content © 2024 DigiPen Institute of Technology Singapore, all rights reserved.
@file creditScreen.h
@author Lim Yan De (l.yande)
@course CSD1401
@section b
@Project Short Circuit Game
@date 26/11/2024
@brief Header file for the credits screen system. Defines structures and
functions needed to display and manage the game's credits sequence.
Includes definitions for credit categories, display parameters, and
the interface for credit screen initialization and management.
*/
#pragma once

/*
@author Lim Yan De (l.yande)
@brief Initializes the credits screen.
Sets up the display parameters and loads required assets for
the credits sequence.
@param void
@return void
*/
void Credits_Init(void);

/*
@author Lim Yan De (l.yande)
@brief Updates the credits screen display.
@param void
@return void
*/
void Credits_Update(void);

/*
@author Lim Yan De (l.yande)
@brief NULL
@param void
@return void
*/
void Credits_Exit(void);

// Define maximum number of names per category
#define MAX_NAMES_PER_CATEGORY  10

// Structure to hold a credit category
typedef struct {
    const char* category;
    const char* names[MAX_NAMES_PER_CATEGORY];
    int nameCount;
} CreditCategory;

/*
@author Lim Yan De (l.yande)
@brief Prints a credit category with associated names.
@param category - pointer to CreditCategory containing category info
@param windowWidth - float specifying the window width for positioning
@param currentY - pointer to float tracking vertical position
@return void
*/
void PrintCredit(const CreditCategory* category, float windowWidth, float* currentY);