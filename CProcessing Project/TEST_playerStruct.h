#pragma once
#define NAME_LENGTH 30 + 1 // Plus 1 for null terminator

/*
int health; health will be used to calculate how much damage the player can take

int mana; mana will be used to calculate how many straight pipes can be used

int attack; attack will be used as a base damage in damage calculation along with the crits

double defense; defense will be used to calculate how much damage will be mitigated from the player when taking damage

The following variables will be used in the calculation of damage when an enemy is weak to any of the elements
double fire_crit;
double water_crit;
double grass_crit;
*/
typedef struct Player {
	//health will be used to calculate how much damage the player can take
	int health;

	//mana will be used to calculate how many straight pipes can be used
	int mana;

	//attack will be used as a base damage in damage calculation along with the crits
	int attack;

	//defense will be used to calculate how much damage will be mitigated from the player when taking damage
	double defense;

	//The following variables will be used in the calculation of damage when an enemy is weak to any of the elements
	double fire_crit;
	double water_crit;
	double grass_crit;

} Player;