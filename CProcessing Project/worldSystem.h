#pragma once
#include "worldEvent.h"
#include "cprocessing.h"

#define EVENT_NUMBER 20

typedef struct World {
	int id;
	EventNode event_list[EVENT_NUMBER];
} World;

typedef struct GameMaster {
	int seed;
	int current_world;
	int current_event;
} GameMaster;

void World_Init(void);

void World_Update(void);

void World_Exit(void);

void Generate_World(int);

World Read_World(int);

CP_Color Event_Type_Colour(EventType);