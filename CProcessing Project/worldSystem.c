#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "worldSystem.h"
#include "inventorySystem.h"
#include "itemSystem.h"
#include "battleSystem.h"
#include "worldHelper.h"

#define MIN_EXTRA_BOUND_EVENTS 0
#define MAX_EXTRA_BOUND_EVENTS 1

#define EVENT_BOUND_X 10
#define EVENT_BOUND_Y 5

#define OFFSET_X WINDOW_WIDTH/EVENT_BOUND_X
#define OFFSET_Y WINDOW_HEIGHT/EVENT_BOUND_Y

#define NODE_RECT_WIDTH (WINDOW_WIDTH / EVENT_NUMBER / 1.2f)
#define NODE_RECT_HEIGHT (WINDOW_HEIGHT / EVENT_NUMBER / 1.2f)

/* ============= WORLD VARIABLES ============= */
World world = { 0 };
int next_id = 0;
int world_id = 1;
int player_node = 0;
Item item_list[INVENTORY_SIZE] = { 0 };
int current_inventory_size = 0;
Player const base_player = {
	.health = 10,
	.mana = 2,
	.attack = 10,
	.defense = 10.0,
	.fire_crit = 1.2,
	.water_crit = 1.2,
	.grass_crit = 1.2
};

//Variables for Pause Menu
int fullscreen = 0;
int menu_open = 0;

//Variables for the player
Player player = { 0 };
Item current_inventory[] = { 0 };

/* ============= PRIVATE FUNCTIONS DECLARATIONS ============= */
/*
	Switches Scene from world based on the event type
*/
void World_SwitchScene(EventType type);

/* ============= GAME SCENE FUNCTIONS ============= */
void World_Init(void)
{
	//Test Player Data
	player.health = 10;
	player.mana = 2;
	player.attack = 10;
	player.defense = 10;
	player.fire_crit = 1.2;
	player.water_crit = 1.2;
	player.grass_crit = 1.2;

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
							PlayerStats_Calculate(current_inventory, player);
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

void World_Reset() {
	for (int i = 0; i < EVENT_NUMBER; ++i) {
		if (world.event_list[i].next_nodes.length) List_Free(&world.event_list[i].next_nodes);
	}
	player_node = 0;
	world.is_generated = 0;
	world_id = 0;
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
		CP_Engine_SetNextGameState(ItemEvent_Init, ItemEvent_Update, ItemEvent_Exit);
		break;
	case SHOP:
		CP_Engine_SetNextGameState(Battle_System_Init, Battle_System_Update, Battle_System_Exit);
		break;
	case MIDBOSS_BATTLE:
		CP_Engine_SetNextGameState(Battle_System_Init, Battle_System_Update, Battle_System_Exit);
		break;
	case BOSS_BATTLE:
		for (int i = 0; i < EVENT_NUMBER; ++i) {
			if (world.event_list[i].next_nodes.length) List_Free(&world.event_list[i].next_nodes);
		}
		player_node = 0;
		world.is_generated = 0;
		++world_id;
		CP_Engine_SetNextGameState(Battle_System_Init, Battle_System_Update, Battle_System_Exit);
		break;
	default:
		CP_Engine_SetNextGameState(Battle_System_Init, Battle_System_Update, Battle_System_Exit);
	}
}

void World_UpdateInventory(Item item) {
	if (current_inventory_size >= INVENTORY_SIZE) {
		printf("Inventory size too much, not adding.");
		return;
	}
	item_list[current_inventory_size] = item;
	++current_inventory_size;
}
