#pragma once
#include "worldEvent.h"
#include "cprocessing.h"

#define EVENT_NUMBER 20

typedef struct World {
	int id;
	int is_generated;
	EventNode event_list[EVENT_NUMBER];
} World;

typedef struct WorldMaster {
	int current_world;
	int current_event;
} GameMaster;

void World_Init(void);

void World_Update(void);

void World_Exit(void);

void Generate_World(int);

World World_Generate_Dynamic(int);

World Read_World(int);

CP_Color Event_Type_Colour(EventType);