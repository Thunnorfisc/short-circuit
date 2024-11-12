#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "worldSystem.h"
#include "linkedlist.h"
#include "generalUtils.h"
#include "inventorySystem.h"
#include "battleSystem.h"

#define MIN_EXTRA_BOUND_EVENTS 0
#define MAX_EXTRA_BOUND_EVENTS 1

#define EVENT_BOUND_X 10
#define EVENT_BOUND_Y 5

#define OFFSET_X WINDOW_WIDTH/EVENT_BOUND_X
#define OFFSET_Y WINDOW_HEIGHT/EVENT_BOUND_Y

#define NODE_RECT_WIDTH (WINDOW_WIDTH / EVENT_NUMBER / 1.2f)
#define NODE_RECT_HEIGHT (WINDOW_HEIGHT / EVENT_NUMBER / 1.2f)

/* ============= WORLD VARIABLES ============= */
World world;
int next_id = 0;
int world_id = 1;
int player_node = 0;

//File Addresses
const char* map_addr = "Assets/Event_Chains/Preset/map-1.txt";
const char* event_type_addr = "Assets/Event_Chains/event-types.txt";
const char* world_addr = "Assets/Event_Chains/Generated/world-1.txt";

//Variables for Pause Menu
int fullscreen = 0;
int menu_open = 0;

/* ============= PRIVATE FUNCTIONS DECLARATIONS ============= */

/*  
	This functions gets a random non-special event type 
	and helps to decrement the number in event type map.
*/
EventType World_GetRandom_EventType(EventTypeMap* type_map);

/*
	Find the nodes closest to it in the direction specified.
	Returns the node ID.
	If no node is found, return 0.
	Direction is based on the y bounds
	--- Direction values ---
	0 = equal
	1 = above
	2 = below
*/
int World_FindNextBoundNodes(int* event_matrix, int y, int x, int direction);

void World_SwitchScene(EventType type);

/* ============= GAME SCENE FUNCTIONS ============= */
void World_Init(void)
{
	if (!world.is_generated) world = World_Generate_Dynamic(world_id);
	CP_Settings_RectMode(CP_POSITION_CENTER);
}

void World_Update(void)
{
	// Handle pause menu
	Handle_Pause_Menu(&menu_open);

	// Handle fullscreen toggle
	Handle_Fullscreen(&fullscreen);

	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_Stroke(CP_Color_Create(255, 255, 255, 255));

	if (!menu_open) {
		// Render Nodes
		for (int i = 0; i < EVENT_NUMBER; ++i) {
			CP_Settings_Fill(Event_Type_Colour(world.event_list[i].type));
			world.event_list[i].location.x = world.event_list[i].bound.x * (((WINDOW_WIDTH - OFFSET_X) - ((EVENT_BOUND_X - 1))) / EVENT_BOUND_X);
			world.event_list[i].location.y = world.event_list[i].bound.y * (((WINDOW_HEIGHT - OFFSET_Y) - ((EVENT_BOUND_Y - 1))) / EVENT_BOUND_Y);
			CP_Graphics_DrawRect(world.event_list[i].location.x, world.event_list[i].location.y,
				NODE_RECT_WIDTH, NODE_RECT_HEIGHT);
			for (int j = 0; j < world.event_list[i].next_nodes.length; ++j) {
				next_id = List_GetAtIndex(world.event_list[i].next_nodes, j);
				if (next_id <= -1) break;
				CP_Graphics_DrawLine(world.event_list[i].location.x + NODE_RECT_WIDTH / 2,
					world.event_list[i].location.y,
					world.event_list[next_id - 1].location.x - NODE_RECT_WIDTH / 2,
					world.event_list[next_id - 1].location.y);
			}
		}

		// Render player
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
		CP_Graphics_DrawRect(world.event_list[player_node].location.x,
			world.event_list[player_node].location.y,
			WINDOW_WIDTH / NODE_RECT_WIDTH, WINDOW_HEIGHT / NODE_RECT_HEIGHT);

		// Update Player
		if (CP_Input_MouseClicked()) {
			for (int i = 0; i < EVENT_NUMBER; ++i) {
				if (IsAreaClicked(world.event_list[i].location.x, world.event_list[i].location.y,
					NODE_RECT_WIDTH, NODE_RECT_HEIGHT, CP_Input_GetMouseX(), CP_Input_GetMouseY()))
				{
					for (int j = 0; j < world.event_list[player_node].next_nodes.length; ++j) {
						if (List_GetAtIndex(world.event_list[player_node].next_nodes, j) == i + 1) {
							player_node = i;
							// Go to battle system
							World_SwitchScene(world.event_list[i].type);
						}
					}
				}
			}
		}

		//Go to inventory system
		if (CP_Input_KeyDown(KEY_TAB)) {
			CP_Engine_SetNextGameState(Inventory_Init, Inventory_Update, Inventory_Exit);
		}
	}
}

void World_Exit(void)
{

}

/* ============= WORLD FUNCTIONS ============= */
World World_Generate_Dynamic(int world_number) {
	srand((unsigned int)time(NULL));
	World world;
	world.id = world_number;
	world.is_generated = 0;
	EventNode event = { 0 };
	EventTypeMap type_map[NON_SPECIAL_TYPE_END - 1];
	unsigned int total_events = EVENT_NUMBER;
	int bound_event_arr[EVENT_BOUND_Y][EVENT_BOUND_X] = { 0 };
	int event_linkage[EVENT_NUMBER] = { 0 }; // Bool Array to check whether the event has at least one linkage from the back
	int event_y = 0;
	unsigned int avg_events_per_bound = 0;
	unsigned int extra_events = 0;
	int special_bound = 0;

	// Event Type Map File
	FILE* type_file;
	if (fopen_s(&type_file, event_type_addr, "r") != 0) {
		printf("Failed to open events type file\n");
		return world;
	};

	/* Update the event type map with the one in the file */
	for (int i = 0; i < NON_SPECIAL_TYPE_END - 1; ++i) {
		fscanf_s(type_file, "%d,%d", &type_map[i].type, &type_map[i].number);
		printf_s("Type: %d,Number: %d\n", type_map[i].type, type_map[i].number);
	};

	// Set up the one event node per x bound, randomized y bound
	for (event.bound.x  = 1; event.bound.x <= EVENT_BOUND_X; ++event.bound.x) {
		event.id = (int)event.bound.x;
		event_y = rand() % (EVENT_BOUND_Y + 1 - 1) + 1;
		event.bound.y = (float)event_y;
		bound_event_arr[event_y - 1][event.id - 1] = event.id;
		if (event.bound.x == EVENT_BOUND_X && ++special_bound) event.type = BOSS_BATTLE;
		else if (event.bound.x == (int)(EVENT_BOUND_X / 2) && ++special_bound) event.type = MIDBOSS_BATTLE;
		else if (event.bound.x == 1 && ++special_bound) event.type = STARTING_NODE;
		else event.type = World_GetRandom_EventType(type_map);
		printf_s("ID: %d, Type: %d, [%d,%d]\n", event.id, event.type, (int)event.bound.x, (int)event.bound.y);
		total_events--;
		world.event_list[event.id - 1] = event;
	}

	avg_events_per_bound = (unsigned int)((EVENT_NUMBER - special_bound) / (EVENT_BOUND_X - special_bound)) - 1;
	printf("\nAVERAGE: %ud\n", avg_events_per_bound);
	// More events for regular bounds
	for (int bound = 1; bound <= EVENT_BOUND_X; ++bound) {
		if (bound == EVENT_BOUND_X || bound == (int)(EVENT_BOUND_X / 2) || bound == 1) continue;
		extra_events = avg_events_per_bound + CP_Random_RangeInt(MIN_EXTRA_BOUND_EVENTS, MAX_EXTRA_BOUND_EVENTS);
		extra_events = extra_events > total_events ? total_events : extra_events;
		extra_events = ((bound == EVENT_BOUND_X - 1) && (total_events > extra_events)) ? total_events : extra_events;
		for (unsigned int j = 0; j < extra_events; ++j) {
			++event.id;
			event.bound.x = (float)bound;
			event_y = CP_Random_RangeInt(1, EVENT_BOUND_Y);
			while (bound_event_arr[event_y - 1][bound - 1] != 0) {
				printf_s("bound and event_y is same\n");
				event_y = CP_Random_RangeInt(1, EVENT_BOUND_Y);
			}
			event.bound.y = (float)event_y;
			event.type = World_GetRandom_EventType(type_map);
			bound_event_arr[event_y - 1][bound - 1] = event.id;
			printf_s("ID: %d, Type: %d, [%d,%d]\n", event.id, event.type, (int)event.bound.x, (int)event.bound.y);
			total_events--;
			world.event_list[event.id - 1] = event;
		}
	}
	// Linkage
	// Search for the closest node next x-bound and connect to it
	// Meanwhile check for backmarking to see if the node has
	// previous connections
	for (int i = 0, x = (int)world.event_list[i].bound.x, y = (int)world.event_list[i].bound.y - 1; 
		i < EVENT_NUMBER;
		++i, x = (int)world.event_list[i].bound.x, y = (int)world.event_list[i].bound.y) {
		int adjancent_bound = 0;
		if (x == EVENT_BOUND_X - 1 || x == (int)(EVENT_BOUND_X / 2) - 1) continue;
		switch (x) {
		case 1:
			for (int j = 0; j < EVENT_BOUND_Y; ++j) {
				if (bound_event_arr[j][x]) {
					if (world.event_list[i].next_nodes.length == 0) world.event_list[i].next_nodes = List_Initialize(bound_event_arr[j][x]);
					else List_Insert_End(&world.event_list[i].next_nodes, bound_event_arr[j][x]);
					++event_linkage[bound_event_arr[j][x] - 1];
				}
			}
			break;
		case (int)(EVENT_BOUND_X / 2):
			for (int j = 0; j < EVENT_BOUND_Y; ++j) {
				if (bound_event_arr[j][x]) {
					if (world.event_list[i].next_nodes.length == 0) world.event_list[i].next_nodes = List_Initialize(bound_event_arr[j][x]);
					else List_Insert_End(&world.event_list[i].next_nodes, bound_event_arr[j][x]);
					++event_linkage[bound_event_arr[j][x] - 1];
				}
				if (bound_event_arr[j][x - 2]) {
					if (world.event_list[bound_event_arr[j][x - 2] - 1].next_nodes.length == 0) world.event_list[bound_event_arr[j][x - 2] - 1].next_nodes = List_Initialize(i + 1);
					++event_linkage[i];
				}
			}
		case EVENT_BOUND_X:
			for (int j = 0; j < EVENT_BOUND_Y; ++j) {
				if (bound_event_arr[j][x - 2]) {
					if (world.event_list[bound_event_arr[j][x - 2] - 1].next_nodes.length == 0) world.event_list[bound_event_arr[j][x - 2] - 1].next_nodes = List_Initialize(i + 1);
					++event_linkage[i];
				}
			}
			break;
		default:
			adjancent_bound = World_FindNextBoundNodes(bound_event_arr, y - 1, x, 0);
			// Find the next node with the same y bound but next 
			if (CP_Random_GetBool() && adjancent_bound) {
				world.event_list[i].next_nodes = List_Initialize(adjancent_bound);
				++event_linkage[adjancent_bound - 1];
			}
			// If true, find the nearest node in the next bound below it's y-bound
			// If this is still 0, iterate till non-zero
			adjancent_bound = World_FindNextBoundNodes(bound_event_arr, y - 1, x, 1);
			if (CP_Random_GetBool() && adjancent_bound) {
				if (world.event_list[i].next_nodes.length == 0) world.event_list[i].next_nodes = List_Initialize(adjancent_bound);
				else List_Insert_End(&world.event_list[i].next_nodes, adjancent_bound);
				++event_linkage[adjancent_bound - 1];
			}

			// If true, find the nearest node in the next bound above it's y-bound
			// If this is still 0, iterate till non-zero
			adjancent_bound = World_FindNextBoundNodes(bound_event_arr, y - 1, x, 2);
			if (CP_Random_GetBool() && adjancent_bound) {
				if (world.event_list[i].next_nodes.length == 0) world.event_list[i].next_nodes = List_Initialize(adjancent_bound);
				else List_Insert_End(&world.event_list[i].next_nodes, adjancent_bound);
				++event_linkage[adjancent_bound - 1];
			}
			break;
		}
		if (x == EVENT_BOUND_X || x == (int)(EVENT_BOUND_X / 2) || x == 1) continue;
		if (world.event_list[i].next_nodes.length == 0) {
			if (adjancent_bound = World_FindNextBoundNodes(bound_event_arr, y - 1, x, 0)) {
				world.event_list[i].next_nodes = List_Initialize(adjancent_bound);
				++event_linkage[adjancent_bound - 1];
			}
			else if (adjancent_bound = World_FindNextBoundNodes(bound_event_arr, y - 1, x, 1)) {
				if (world.event_list[i].next_nodes.length == 0) world.event_list[i].next_nodes = List_Initialize(adjancent_bound);
				else List_Insert_End(&world.event_list[i].next_nodes, adjancent_bound);
				++event_linkage[adjancent_bound - 1];
			}
			else if (adjancent_bound = World_FindNextBoundNodes(bound_event_arr, y - 1, x, 2)) {
				if (world.event_list[i].next_nodes.length == 0) world.event_list[i].next_nodes = List_Initialize(adjancent_bound);
				else List_Insert_End(&world.event_list[i].next_nodes, adjancent_bound);
				++event_linkage[adjancent_bound - 1];
			}
		}
	}
	world.is_generated = 1;
	return world;
}

void Generate_World(int world_number)
{
	// Random seed
	srand((unsigned int)time(NULL));
	EventNode event;
	event.next_nodes.length = 0;
	EventTypeMap type_map[NON_SPECIAL_TYPE_END - 1];
	int type_index = 0;
	// Used for recognising characters from the file
	char end = 0;
	// To get values for the event node relationships
	int node = 0;
	// Open the preset file
	FILE* map_file;
	if (fopen_s(&map_file, map_addr, "r") != 0) {
		printf("Failed to open map file\n");
		return;
	};
	// Event Type Map File
	FILE* type_file;
	if (fopen_s(&type_file, event_type_addr, "r") != 0) {
		printf("Failed to open events type file\n");
		return;
	};
	// Create the file for world to be generated
	FILE* generated_file;
	if (fopen_s(&generated_file, world_addr, "w") != 0) {
		printf("Failed to open world map file\n");
		return;
	};

	/* Update the event type map with the one in the file */
	for (int i = 0; i < NON_SPECIAL_TYPE_END - 1; ++i) {
		fscanf_s(type_file, "%d,%d", &type_map[i].type, &type_map[i].number);
		printf_s("Type: %d,Number: %d\n", type_map[i].type, type_map[i].number);
	}

	/* Example of one event in preset :
	   ID: %d, Type: %d, [%d,%d], {%d,...} */
	   /* Example of one event in generated world :
		  ID: %d, Type: %d, [%d,%d], {%d,...} */
	if (map_file) {
		for (int i = 1; i <= EVENT_NUMBER; ++i) {
			fscanf_s(map_file, " ID: %d, Type: %d, [%f,%f], {", &event.id, &event.type, &event.bound.x, &event.bound.y);
			// If the type is not set(aka START or 0), set to one of the non-special types
			if (event.type == START) {
				// From START + 1 to NON_SPECIAL_TYPE_END - 1
				event.type = World_GetRandom_EventType(type_map);
			}
			if (fprintf_s(generated_file, "ID: %d, Type: %d, [%d,%d], {", event.id, event.type, (int)event.bound.x, (int)event.bound.y) < 0) {
				printf("Error writing to generated file.\n");
				break;
			}
			//fprintf_s(generated_file, "ID: %d, Type: %d, [%d,%d], {", event.id, event.type, (int)event.location.x, (int)event.location.y);
			printf_s("ID: %d, Type: %d, [%d,%d], {", event.id, event.type, (int)event.bound.x, (int)event.bound.y);
			// Set and find all the node connections ID
			while (1) {
				fscanf_s(map_file, " %d%c", &node, &end, 3);
				fprintf_s(generated_file, "%d%c", node, end);
				printf_s("%d%c", node, end);
				if (end != ',') break;
			}
			fprintf_s(generated_file, "\n");
			fflush(generated_file);
			printf("\n");
		}
	}
	// Close the file streams to prevent memory leak
	fclose(map_file);
	fclose(generated_file);
}

World Read_World(int world_number)
{
	World world;
	world.id = world_number;
	char end = 0;
	int node = 0;
	// Create the file for world to be generated
	FILE* generated_file;
	if (fopen_s(&generated_file, world_addr, "r") != 0) {
		printf("Failed to open world map file\n");
		return world;
	};

	// Read and transfer all the information to world struct
	if (generated_file) {
		for (int i = 0; i < EVENT_NUMBER; ++i) {
			world.event_list[i].next_nodes.length = 0;
			fscanf_s(generated_file, " ID: %d, Type: %d, [%f,%f], {", &world.event_list[i].id,
				&world.event_list[i].type, &world.event_list[i].bound.x,
				&world.event_list[i].bound.y);
			// Set and find all the node connections ID
			while (1) {
				fscanf_s(generated_file, " %d%c", &node, &end, 3);
				if (world.event_list[i].next_nodes.length == 0) world.event_list[i].next_nodes = List_Initialize(node);
				else List_Insert_End(&world.event_list[i].next_nodes, node);
				printf_s("Length: %d\n", List_GetLength(world.event_list[i].next_nodes));
				if (end != ',') break;
			}
		}
	}
	printf_s("Succcesful Reading");
	fclose(generated_file);
	return world;
}

void World_Reset() {
	for (int i = 0; i < EVENT_NUMBER; ++i) {
		if (world.event_list[i].next_nodes.length) List_Free(&world.event_list[i].next_nodes);
	}
	player_node = 0;
	world.is_generated = 0;
}

CP_Color Event_Type_Colour(EventType type)
{
	CP_Color color = CP_Color_Create(255, 255, 255, 255);
	switch (type) {
	case BATTLE:
		color = CP_Color_Create(0, 0, 255, 255);
		break;
	case ITEM:
		color = CP_Color_Create(0, 255, 255, 255);
		break;
	case SHOP:
		color = CP_Color_Create(255, 0, 255, 255);
		break;
	case MIDBOSS_BATTLE:
		color = CP_Color_Create(255, 255, 0, 255);
		break;
	case BOSS_BATTLE:
		color = CP_Color_Create(255, 0, 0, 255);
		break;
	default:
		color = CP_Color_Create(105, 105, 105, 255);
	}
	return color;
}

void World_SwitchScene(EventType type) {
	switch (type) {
	case BATTLE:
		CP_Engine_SetNextGameState(Battle_System_Init, Battle_System_Update, Battle_System_Exit);
		break;
	case ITEM:
		CP_Engine_SetNextGameState(Battle_System_Init, Battle_System_Update, Battle_System_Exit);
		break;
	case SHOP:
		CP_Engine_SetNextGameState(Battle_System_Init, Battle_System_Update, Battle_System_Exit);
		break;
	case MIDBOSS_BATTLE:
		CP_Engine_SetNextGameState(Battle_System_Init, Battle_System_Update, Battle_System_Exit);
		break;
	case BOSS_BATTLE:
		World_Reset();
		++world_id;
		CP_Engine_SetNextGameState(Battle_System_Init, Battle_System_Update, Battle_System_Exit);
		break;
	default:
		CP_Engine_SetNextGameState(Battle_System_Init, Battle_System_Update, Battle_System_Exit);
	}
}

/* ============= HELPER FUNCTIONS ============= */

EventType World_GetRandom_EventType(EventTypeMap* type_map)
{
	EventType type = CP_Random_RangeInt(START + 1, NON_SPECIAL_TYPE_END - 1);
	while (type_map[type - 1].number == 0) {
		++type;
		if (type == NON_SPECIAL_TYPE_END) type = START + 1;
		if (type == type - 1) {
			printf("NOT ENOUGH NUMBER FOR TYPES!");
			break;
		}
	}
	type_map[type - 1].number--;
	return type;
}

int World_FindNextBoundNodes(int* event_matrix, int y, int next_x, int direction)
{
	int find_node = 1;
	int event = 0;
	switch (direction) {
	case 0:
		if (*(event_matrix + y * EVENT_BOUND_X + next_x) != 0) return *(event_matrix + y * EVENT_BOUND_X + next_x);
		else return 0;
		break;
	case 1:
		while (*(event_matrix + (y - find_node) * EVENT_BOUND_X + next_x) == 0) {
			if (y - find_node <= 0) break;
			++find_node;
		}
		if (*(event_matrix + (y - find_node) * EVENT_BOUND_X + next_x) && y - find_node >= 0) 
			return *(event_matrix + (y - find_node) * EVENT_BOUND_X + next_x);
		else return 0;
		break;
	case 2:
		while (*(event_matrix + (y + find_node) * EVENT_BOUND_X + next_x) == 0) {
			if (y + find_node >= EVENT_BOUND_X - 1) break;
			++find_node;
		}
		if (*(event_matrix + (y + find_node) * EVENT_BOUND_X + next_x) && y + find_node <= EVENT_BOUND_Y - 1)
			return *(event_matrix + (y + find_node) * EVENT_BOUND_X + next_x);
		else return 0;
		break;
	default:
		printf("NOT A DIRECTION!");
		return 0;
	}
	return 0;
}
