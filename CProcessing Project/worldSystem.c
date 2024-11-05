#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "worldSystem.h"
#include "linkedlist.h"
#include "generalUtils.h"
#include "inventorySystem.h"
#include "battleSystem.h"

#define EVENT_BOUND_X 10
#define EVENT_BOUND_Y 5

#define OFFSET_X WINDOW_WIDTH/EVENT_BOUND_X
#define OFFSET_Y WINDOW_HEIGHT/EVENT_BOUND_Y

#define NODE_RECT_WIDTH (WINDOW_WIDTH / EVENT_NUMBER / 1.2f)
#define NODE_RECT_HEIGHT (WINDOW_HEIGHT / EVENT_NUMBER / 1.2f)

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

void World_Init(void)
{
	LinkedList list = List_Initialize(5);
	List_Traverse(list);
	List_Insert_End(&list, 6);
	List_Insert_Start(&list, 3);
	List_Traverse(list);
	List_Pop(&list);
	List_Traverse(list);

	world = Read_World(world_id);
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
				if (next_id == 0) break;
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
							CP_Engine_SetNextGameState(Battle_System_Init, Battle_System_Update, Battle_System_Exit);
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
				event.type = rand() % ((NON_SPECIAL_TYPE_END - 2) - START + 1) + START + 1;
				// If the event type is already completely used up, iterate until you find one that is not
				// Cycle back if needed
				type_index = event.type - 1;
				while (type_map[event.type - 1].number == 0) {
					++event.type;
					if (event.type == NON_SPECIAL_TYPE_END) event.type = START + 1;
					if (event.type == event.type - 1) {
						printf("NOT ENOUGH NUMBER FOR TYPES!");
						break;
					}
				}
				type_map[event.type - 1].number--;
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
		return;
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
		color = CP_Color_Create(255, 255, 255, 255);
	}
	return color;
}

