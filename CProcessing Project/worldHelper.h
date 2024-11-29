/*
* @author	William Wibisana Dumnanauw (williamwibisana.d)
* @brief	The file contains structs and functions necessary to the world system.
* @note		Related to World System, World Event
* @file		worldHelper.h
* All content © 2024 DigiPen Institute of Technology Singapore, all rights reserved.
*/
#pragma once
#include "worldEvent.h"
#include "itemSystem.h"

#define EVENT_NUMBER 20					// The total number of events

#define EVENT_BOUND_X 10				// The number of bounds in the horizontal direction
#define EVENT_BOUND_Y 5					// The number of bounds in the vertical direction

// Each y-bound start with 1 event
#define MIN_EXTRA_BOUND_EVENTS 0		// The minimum number of extra events per x-bound in the y-bound
#define MAX_EXTRA_BOUND_EVENTS 2		// The maximum number of extra events per x-bound in the y-bound

/*!
* @struct This is a world struct
* @brief This struct is used to keep track of the current world and it's nodes
* @param id				int			The identifier for the current world
* @param is_generated	int			The flag to check whether the world is generated
* @param event_list		EventNode[]	The list of events
*/
typedef struct World {
	int id;
	int is_generated;
	EventNode event_list[EVENT_NUMBER];
} World;

/*!
* @struct This is a world master struct
* @brief This struct is designed to keep track of players's whereabouts
* @param current_world	int		The current world the player is in
* @param current_event  int		The current event node the player is in
* @param currency		int		The amount of currency the player has
*/
typedef struct WorldMaster {
	int current_world;
	int current_event;
	int currency;
} WorldMaster;

/*!
* @attention This is a deprecated function, kept for documentation purposes!
* @brief	 This function generates the world using a preset file
* @param int The ID of the world to be generated
*/
void Generate_World(int);

/*!
* @brief This functions generates the world dynamically, without the use of presets
* @param int  The ID of the world to be generated
*/
World World_Generate_Dynamic(int);

/*!
* @brief This function saves the world into a file
* @param World			-  The current world to be saved
* @param WorldMaster	-  The player information for world and events
* @param Item*			-  The array of items the player have
* @param int			-  The size of the array of items
*/
void World_Save(World world, WorldMaster master, Item* item_list, int item_list_size);

/*!
* @brief This function loads the world into a file
* @param World*			- The pointer to the world to be loaded
* @param WorldMaster	- The player information for world and events to be loaded
* @param Item*			- The array of items the player to be loaded
* @param int*			- The size of the array of items to be loaded
*/
int World_Load(World* world, WorldMaster* master, Item* item_list, int* item_list_size);