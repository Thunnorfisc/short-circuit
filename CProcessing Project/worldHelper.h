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

void Generate_World(int);

World World_Generate_Dynamic(int);

World World_Load(int);