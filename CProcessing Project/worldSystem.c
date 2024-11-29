/*
* @author	William Wibisana Dumnanauw (williamwibisana.d)
* @brief	The file contains the world scene and the global variables realted to world and player
* @file		worldSystem.c
* All content © 2024 DigiPen Institute of Technology Singapore, all rights reserved.
*/

// Standard library
#include <stdlib.h> // memset(), strcpy()
#include <stdio.h>  // remove()
#include <time.h>

// Project files
#include "worldSystem.h"
#include "inventorySystem.h"
#include "itemSystem.h"
#include "battleSystem.h"
#include "bossSystem.h"
#include "worldHelper.h"
#include "shopSystem.h"
#include "cprocessing.h"
#include "TEST_playerUtil.h"

// Offset for each bound
#define OFFSET_X WINDOW_WIDTH/EVENT_BOUND_X
#define OFFSET_Y WINDOW_HEIGHT/EVENT_BOUND_Y

// Re-adjusted scale to fit legend at top right corner
#define NODE_SCALE 1.5
#define NODE_RECT_WIDTH (WINDOW_WIDTH / EVENT_NUMBER / 1.6f) * NODE_SCALE
#define NODE_RECT_HEIGHT (WINDOW_HEIGHT / EVENT_NUMBER / 0.9f) * NODE_SCALE

// Number of events types of nodes
#define NODE_TYPES_NUMBER (NON_SPECIAL_TYPE_END - 1) + (SPECIAL_END - SPECIAL_START - 1)

// Hover over text length for each node
#define TYPE_NAME_STR_LEN 150

/* ============= WORLD VARIABLES ============= */
// General Variables
World world = { 0 };
WorldMaster master = {
	.currency = 150,
	.current_world = 1,
	.current_event = 0
};
int next_id = 0;
int boss_id = 0;
CP_Image world_bg;
char type_str[TYPE_NAME_STR_LEN] = {0};

// Inventory Related Variables
Item item_list[INVENTORY_SIZE] = { 0 };
int current_inventory_size = 0;

// Currency Variables
char currency_str[5] = { 0 };
CP_Image currency_sprite;

// Node Variables
CP_Image base_node_sprite;
CP_Image selected_node_sprite;

// Node Animation Variables
//float maximum_change = 1.15f;
//float minimum_change = 0.85f;
//float change_rate = 0.01f;
//float size_scale = 1.0f;

// Player Variables
Player player = {
	.health = 1000,
	.s_mana = 2,
	.attack = 10,
	.defense = 1.0,
	.fire_crit = 1.2,
	.water_crit = 1.2,
	.grass_crit = 1.2
};

// Flags
int load_world_flag = 0;

//Variables for Pause Menu
int fullscreen = 0;
int menu_open = 0;

/* ============= PRIVATE FUNCTIONS DECLARATIONS ============= */

/*
* Switches Scene from world based on the event type
*/
void World_SwitchScene(EventType type);
/*
* Changes base node color whether selected or not
*/
CP_Image World_SelectBaseNode(int event_id);
/* @author: Kelly
* Decides the color of line based on adjancency
*/
CP_Color World_LineColor(int event);
/*! @author: Kelly
* When you hover over, decides the name of the event in the textbox
*/
void World_EventTypeName(char* str, size_t size, EventType type);

/* ============= GAME SCENE FUNCTIONS ============= */
void World_Init(void)
{
	// If World load flag is activated
	if (load_world_flag) {
		if (!World_Load(&world, &master, item_list, &current_inventory_size)) {
			world = World_Generate_Dynamic(master.current_world);
		}
		currency_sprite = CP_Image_Load("Assets/Crystal.png");
		base_node_sprite = CP_Image_Load("Assets/Node.png");
		selected_node_sprite = CP_Image_Load("Assets/Selected Node.png");
		load_world_flag = 0;
	}

	// If world is not generated
	if (!world.is_generated) { 
		world = World_Generate_Dynamic(master.current_world); 
		currency_sprite = CP_Image_Load("Assets/Crystal.png");
		base_node_sprite = CP_Image_Load("Assets/Node.png");
		selected_node_sprite = CP_Image_Load("Assets/Selected Node.png");
	}
	// Save world everytime the player comes back to world scene
	World_Save(world, master, item_list, current_inventory_size);

	world_bg = CP_Image_Load("Assets/world bg.png");
	CP_Settings_RectMode(CP_POSITION_CENTER);
}

void World_Update(void)
{
	// Handle pause menu
	Handle_Pause_Menu(&menu_open);

	// Handle fullscreen toggle
	Handle_Fullscreen(&fullscreen);

	// Handle Inventory Screen
	Handle_Inventory();

	// Handle background
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_RectMode(CP_POSITION_CENTER);
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 128));
	CP_Graphics_DrawRect(WINDOW_WIDTH_HALF, WINDOW_HEIGHT_HALF, (float)WINDOW_WIDTH, (float)WINDOW_HEIGHT);
	CP_Image_Draw(world_bg, WINDOW_WIDTH_HALF, WINDOW_HEIGHT_HALF, (float)WINDOW_WIDTH, (float)WINDOW_HEIGHT, 128);
	CP_Settings_Stroke(CP_Color_Create(255, 255, 255, 255));

	if (!menu_open) {
		// Render Nodes
		for (int i = 0; i < EVENT_NUMBER; ++i) {
			world.event_list[i].location.x = world.event_list[i].bound.x * (((WINDOW_WIDTH - OFFSET_X) - ((EVENT_BOUND_X - 1))) / EVENT_BOUND_X);
			world.event_list[i].location.y = world.event_list[i].bound.y * (((WINDOW_HEIGHT - OFFSET_Y) - ((EVENT_BOUND_Y - 1))) / EVENT_BOUND_Y);
			CP_Image_Draw(World_SelectBaseNode(i), world.event_list[i].location.x, world.event_list[i].location.y,
				NODE_RECT_WIDTH, NODE_RECT_HEIGHT, 255);
			CP_Image_Draw(world.event_list[i].event_sprite, world.event_list[i].location.x, world.event_list[i].location.y,
				NODE_RECT_WIDTH, NODE_RECT_HEIGHT, 255);
			for (int j = 0; j < world.event_list[i].next_nodes.length; ++j) {
				next_id = List_GetAtIndex(world.event_list[i].next_nodes, j);
				if (next_id <= 0) break;
				CP_Settings_StrokeWeight(WINDOW_WIDTH / 360.0f);

				// Color the line
				// Data type is CP_Color
				CP_Settings_Stroke(World_LineColor(i));

				CP_Graphics_DrawLine(world.event_list[i].location.x + NODE_RECT_WIDTH / 2,
					world.event_list[i].location.y,
					world.event_list[next_id - 1].location.x - NODE_RECT_WIDTH / 2,
					world.event_list[next_id - 1].location.y);
			}
		}

		// Update Player
		for (int i = 0; i < EVENT_NUMBER; ++i) {
			if (IsAreaClicked(world.event_list[i].location.x, world.event_list[i].location.y,
				NODE_RECT_WIDTH, NODE_RECT_HEIGHT, CP_Input_GetMouseX(), CP_Input_GetMouseY()))
			{
				// If mouse if clicked
				if (CP_Input_MouseClicked()) {
					for (int j = 0; j < world.event_list[master.current_event].next_nodes.length; ++j) {
						if (List_GetAtIndex(world.event_list[master.current_event].next_nodes, j) == i + 1) {
							master.current_event = i;
							// Go to battle system
							PlayerStats_Calculate(item_list, player);
							World_SwitchScene(world.event_list[i].type);
						}
					}
				}
				// If mouse is just hovered
				World_EventTypeName(type_str, TYPE_NAME_STR_LEN, world.event_list[i].type);
				Draw_TextBoxAdvanced(type_str, 20.0f * WINDOW_RATIO, CP_Input_GetMouseX(), CP_Input_GetMouseY(),
					WINDOW_WIDTH * 0.10f, WINDOW_HEIGHT * 0.15f, 2.5f/7.f, CP_Color_Create(255, 255, 255, 255), CP_Color_Create(0, 0, 0, 255), CP_POSITION_CORNER);
				
			}
		}
		// Update Player
		if (CP_Input_KeyTriggered(KEY_TAB)) {
				PlayerStats_Calculate(item_list, player);	
		}
		
		// Draw UI
		World_PlayerUI();
	}
}

void World_Exit(void)
{
	CP_Image_Free(&world_bg);
}

void World_Reset() {
	for (int i = 0; i < EVENT_NUMBER; ++i) {
		if (world.event_list[i].next_nodes.length) List_Free(&world.event_list[i].next_nodes);
		CP_Image_Free(&world.event_list[i].event_sprite);
	}
	memset(item_list, 0, sizeof item_list);
	current_inventory_size = 0;
	master.current_event = 0;
	world.is_generated = 0;
	CP_Image_Free(&currency_sprite);
	CP_Image_Free(&base_node_sprite);
	CP_Image_Free(&selected_node_sprite);
	master.current_world = 0;
}

CP_Image World_SelectBaseNode(int event) {
	return (event == master.current_event) ? selected_node_sprite : base_node_sprite;
}

CP_Color World_LineColor(int event) {
	if (event == master.current_event) {
		return CP_Color_Create(0, 0, 255, 255);
	}
	else {
		return CP_Color_Create(255, 255, 255, 255);
	}
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
		CP_Engine_SetNextGameState(Shop_Init, Shop_Update, Shop_Exit);
		break;
	case MIDBOSS_BATTLE:
		++boss_id;
		CP_Engine_SetNextGameState(Boss_System_Init, Boss_System_Update, Boss_System_Exit);
		break;
	case BOSS_BATTLE:
		// Reset everything and increment current world ID
		for (int i = 0; i < EVENT_NUMBER; ++i) {
			if (world.event_list[i].next_nodes.length) List_Free(&world.event_list[i].next_nodes);
			CP_Image_Free(&world.event_list[i].event_sprite);
		}
		master.current_event = 0;
		world.is_generated = 0;
		CP_Image_Free(&currency_sprite);
		CP_Image_Free(&base_node_sprite);
		CP_Image_Free(&selected_node_sprite);
		++master.current_world;
		boss_id = 2;
		CP_Engine_SetNextGameState(Boss_System_Init, Boss_System_Update, Boss_System_Exit);
		break;
	default:
		CP_Engine_SetNextGameState(Battle_System_Init, Battle_System_Update, Battle_System_Exit);
	}
}

void World_EventTypeName(char* str, size_t size, EventType type) {
	switch (type) {
	case BATTLE:
		strcpy_s(str, size, "You notice shadows in the woods. Investigate?");
		break;
	case ITEM:
		strcpy_s(str, size, "You found a treasure chest! Hooray!");
		break;
	case SHOP:
		strcpy_s(str, size, "You stumble upon a mystical shop! Choose wisely...Below 150 jewels will not be entertained!");
		break;
	case MIDBOSS_BATTLE:
		strcpy_s(str, size, "You hear growling and heavy footsteps approaching. Will you face it?");
		break;
	case BOSS_BATTLE:
		strcpy_s(str, size, "Danger lies ahead...");
		break;
	default:
		strcpy_s(str, size, "Adventure lies ahead!");
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

void World_UpdateCurrency(int amt) {
	master.currency += amt;
}

int World_GetCurrency() {
	return master.currency;
}

int World_GetBoss() {
	return boss_id;
}

CP_Image World_GetCurrencyImage()
{
	return currency_sprite;
}

void World_SetLoadFlag()
{
	load_world_flag = 1;
}

void World_PlayerUI()
{
	// Items
	float name_size = WINDOW_HEIGHT / 24.0f;
	CP_Settings_TextSize(name_size);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	float imgSize = 128;
	// Draw the items inside the player's inventory
	for (int i = 0; i < current_inventory_size; ++i) {
		CP_Image_Draw(item_list[i].image, (WINDOW_WIDTH / 64.0f) + (i * (WINDOW_WIDTH / 32.0f)), WINDOW_HEIGHT / 36.0f, WINDOW_HEIGHT / 24.0f, WINDOW_HEIGHT / 24.0f, 255);
	}
	// Draw the textbox describing item when hovering over
	for(int i = 0; i < current_inventory_size; ++i) {
		if (IsAreaClicked((WINDOW_WIDTH / 64.0f) + (i * (WINDOW_WIDTH / 32.0f)),
			WINDOW_HEIGHT / 48.0f, WINDOW_HEIGHT / 24.0f, WINDOW_HEIGHT / 24.0f, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
			Draw_Textbox(item_list[i].name, name_size, CP_Input_GetMouseX(), CP_Input_GetMouseY(),
				WINDOW_WIDTH * 0.2f, WINDOW_HEIGHT * 0.1f,
				CP_Color_Create(200, 200, 200, 255), CP_Color_Create(0, 0, 0, 255), CP_POSITION_CORNER);
			Draw_Textbox(item_list[i].description, name_size / 2, CP_Input_GetMouseX(), CP_Input_GetMouseY() + WINDOW_HEIGHT * 0.1f,
				WINDOW_WIDTH * 0.2f, WINDOW_HEIGHT * 0.1f,
				CP_Color_Create(200, 200, 200, 255), CP_Color_Create(0, 0, 0, 255), CP_POSITION_CORNER);
		}
	}
	CP_Settings_TextSize(name_size);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));

	// master.currency
	CP_Image_Draw(currency_sprite, WINDOW_WIDTH - WINDOW_WIDTH / 36.0f - WINDOW_HEIGHT / 18.0f, WINDOW_HEIGHT / 36.0f,
		WINDOW_HEIGHT / 24.0f, WINDOW_HEIGHT / 24.0f, 255);
	sprintf_s(currency_str, (unsigned int)sizeof currency_str, "%d", master.currency);
	CP_Font_DrawText(currency_str, WINDOW_WIDTH - WINDOW_WIDTH / 36.0f , WINDOW_HEIGHT / 36.0f);
}

// To reset 
// boss id when player die/ player wins the game
// currency back to base 150
void ResetGame() {
	boss_id = 0;
	master.currency = 150;
	remove("Assets/world.txt");
	World_Reset();
}
