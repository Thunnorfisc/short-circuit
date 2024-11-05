#pragma once

void Main_Menu_Init(void);
void Main_Menu_Update(void);
void Main_Menu_Exit(void);
void Display_Currency(void);

void Handle_Pause_Menu(int* menu_open); 

void Handle_Fullscreen(int* fullscreen);

//DEBUG CODE
void HandlePlayerStats(void);

void SaveGameState(void);

void LoadGameState(void);