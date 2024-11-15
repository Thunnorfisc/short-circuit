#pragma once
#include "worldEvent.h"

#define EVENT_NUMBER 20

#define EVENT_BOUND_X 10
#define EVENT_BOUND_Y 5

#define MIN_EXTRA_BOUND_EVENTS 0
#define MAX_EXTRA_BOUND_EVENTS 1

typedef struct World {
	int id;
	int is_generated;
	EventNode event_list[EVENT_NUMBER];
} World;

typedef struct WorldMaster {
	int current_world;
	int current_event;
} WorldMaster;

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

void Generate_World(int);

World World_Generate_Dynamic(int);

World World_Load(int);