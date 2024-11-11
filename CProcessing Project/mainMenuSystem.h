#pragma once

// Structure definitions
typedef struct {
    int attack_power;
    int health_points;
    int currency;
} PlayerStats;

/*
PlayerStats playerStats = {
    .attack_power = 0,
    .health_points = 0 ,
    .currency = 100
};*/

extern PlayerStats playerStats;

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
void Draw_Splash_Screen(void);
void Draw_Main_Menu(void);
void Draw_Copyright();