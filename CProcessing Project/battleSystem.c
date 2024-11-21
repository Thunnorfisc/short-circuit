#include <stdio.h>
#include "worldSystem.h"
#include "battleSystem.h"
#include "magicSystemUtil.h"
#include "enemyStructs.h"
#include "TEST_playerUtil.h"
#include "battleSystemUI.h"
#include "tutorial.h"
#include "battleLost.h"
#include "itemSystem.h"


// Variables for Battle System UI
BattleUI battle_ui[UI_COUNT];
CP_Image background;
CP_Image weakness_ui[3];
CP_Image circuit_ui;

// Variables to generate enemies
int random_enemy_count = 0;
CP_Image enemy_image = { 0 };

// Store string to show element of each pipe to be shown when hovering over
const char* element_type[4] = {"This is a base circuit", "This is a grass element", "This is a water element", "This is a fire element"};

// Define images for each enemy type
CP_Image e_wizard_image;
CP_Image e_plant_image;
CP_Image e_vulture_image;

// an array of Enemy structures called enemies with a size of ENEMY_COUNT
Enemy enemies[ENEMY_COUNT];
Enemy original_enemy_arr[ENEMY_COUNT];
int check_if_enemy_died = 0;
int original_count_enemy = 0;

// player_battle object to calculate the damage to be done. Damage taken from a temp file
int initialize_player = 1;
Player player_battle;
float original_health;

/*----------------------------------- Circuits -----------------------------------*/
// Image of the circuit pieces
CP_Image circuit_image_corner, circuit_image_straight;

// List of all the circuit pieces the player_battle can use
CircuitPiece circuit_list[CIRCUIT_UI_LIST_SIZE];

// Circuit Piece Selected
CircuitPiece circuit_selected_list[GRID_DIMENSIONS][GRID_DIMENSIONS] = { 0 };
CircuitPiece circuit_piece_selected = { 0 };
CP_Vector index_used[GRID_DIMENSIONS * GRID_DIMENSIONS] = { 0 };
int selected_circuit_piece = 0;

// mouse vector that will be updated when mouse down is detected
CP_Vector mouse_position = { 0 };

// Straight Circuit Pieces System
int total_s_pieces;

// Elemental Circuit System Variables
/*
0 : Grass
1 : Water
2 : Fire
*/
CP_Image elemental_circuit_images[4];

// bool to check if the elemental pipes have been shuffled for the current turn
int load_elements = 1;
/*-------------------------------------------------------------------------------------------------------------------------*/

// Grids that will be used to display the enemy
CP_Vector grid_squares[GRID_DIMENSIONS][GRID_DIMENSIONS];

// Button Variables
Button button_submit;

// Various checks
int Piece_Placed = 0;
int Spell_Cast = 0;

void Battle_System_Init()
{	
	// Setting Modes for display
	CP_Settings_ImageMode(CP_POSITION_CENTER);
	CP_Settings_RectMode(CP_POSITION_CENTER);

	// Initialize UI
	UI_Initialize(battle_ui);
	background = CP_Image_Load("Assets/Door_Way.png");

	weakness_ui[0] = CP_Image_Load(GRASS_UI);
	weakness_ui[1] = CP_Image_Load(WATER_UI);
	weakness_ui[2] = CP_Image_Load(FIRE_UI);

	// Loading the image for the Magic Circuit's L Piece
	circuit_image_corner = CP_Image_Load(CIRCUIT_L_ASSET_ADDR);
	circuit_image_straight = CP_Image_Load(CIRCUIT_S_ASSET_ADDR);

	// Loading images for the elemental circuits
	elemental_circuit_images[0] = CP_Image_Load(CIRCUIT_LG_ASSET_ADDR);
	elemental_circuit_images[1] = CP_Image_Load(CIRCUIT_LW_ASSET_ADDR);
	elemental_circuit_images[2] = CP_Image_Load(CIRCUIT_LF_ASSET_ADDR);
	elemental_circuit_images[3] = circuit_image_corner;

	// Load each enemy image
	e_wizard_image = CP_Image_Load(E_WIZARD_ASSET_ADDR);
	e_plant_image = CP_Image_Load(E_PLANT_ASSET_ADDR);
	e_vulture_image = CP_Image_Load(E_VULTURE_ASSET_ADDR);
	/*------------Calculating the buffer for the display location of the UI for the circuits---------- */
	float grid_size = GRID_DIMENSIONS * GRID_CELL_SIZE;
	float circuit_piece_x = CIRCUIT_UI_X;
	float circuit_piece_y = CIRCUIT_UI_Y;

	// This loop will initialize the corner pieces to be displayed on the UI for selection
	for (int i = 0, j = i + 1; i < NUM_OF_L_PIECE; ++i, j = j < 3 ? j + 1 : 0) {
		circuit_list[i] = New_Circuit_Piece(
			CP_Vector_Set(circuit_piece_x - GRID_CELL_SIZE * i, circuit_piece_y),
			circuit_image_corner,
			i, j, i, GRID_CELL_SIZE, L_Type);
	}

	// This loop will initialize the straight pieces to be displayed on the UI for selection
	for (int i = 0, j = i + 2; i < NUM_OF_S_PIECE; ++i,++j) {
		circuit_list[NUM_OF_L_PIECE + i] = New_Circuit_Piece(
			CP_Vector_Set(circuit_piece_x + GRID_CELL_SIZE * j, circuit_piece_y),
			circuit_image_straight,
			i, j, i, GRID_CELL_SIZE, S_Type);
	}

	
	

	// Initialize the button for submit
	button_submit.width = 128 * 2;
	button_submit.height = 64;

	button_submit.position = CP_Vector_Set((float)(WINDOW_WIDTH - grid_size) * 0.75f + grid_size, (float)WINDOW_HEIGHT - (float)(WINDOW_HEIGHT - grid_size) / 2.f + button_submit.height / 2.f);
	/*------------------------------------------------------------------------------------------------ */

	// Initialize the grids for testing
	Grid_Initialize(grid_squares);

	// Randomly generate the number of enemies to be spawned
	random_enemy_count = CP_Random_RangeInt(1, ENEMY_COUNT);
	
	
	
	("Number of enemies to be generated: %d\n", random_enemy_count);

	// Randomly generate unique enemy positions
	Enemy_Initialize_Array(enemies, grid_squares, random_enemy_count, 1);
	original_count_enemy = random_enemy_count;

	for (int i = 0; i < ENEMY_COUNT; ++i) {
		original_enemy_arr[i] = enemies[i];
	}
	if (initialize_player) {
		PlayerStats_ReadFile(&player_battle);
		original_health = player_battle.health;
		initialize_player = 0;
	}

	total_s_pieces = player_battle.s_mana;

	// Initialize Tutorial
	Tutorial_SetState(TUTORIAL_BATTLE_START);
}

void Battle_System_Update()
{
	//Set Mouse position
	mouse_position = CP_Vector_Set(CP_Input_GetMouseX(), CP_Input_GetMouseY());
	float circuit_piece_x = CIRCUIT_UI_X;
	float circuit_piece_y = CIRCUIT_UI_Y;

	// To calculate the starting x,y position of the circuit background image
	float starting_position_circuit_background = circuit_piece_x - (GRID_CELL_SIZE * 3.5f);
	// Get x value difference
	float x_difference = CP_Input_GetMouseX() - starting_position_circuit_background;
	// Get y value difference
	float y_difference = circuit_piece_y  - CP_Input_GetMouseY();
	// To absolute negative y value difference and return positive value
	y_difference = (y_difference < 0) ? -y_difference : y_difference;
	
	// Check if mouse is hovering over the circuit background UIs
	if ((x_difference > 0.f && x_difference < GRID_CELL_SIZE * 7.f) && (y_difference < GRID_CELL_SIZE / 2.0F)) {
		// x_difference is from starting position of the circuit background image to the mouse's x y position divded by each grid size
		// To get the index
		int index = (int) (x_difference / GRID_CELL_SIZE);
		// How the index is stored in circuit_list is the opposite
		//index 0 of circuit_list == index 3 of current array
		if (index <= 3) {
			index = 3 - index;
			CircuitPiece CP = circuit_list[index];
			// To debug and ensure it is the correct string showing
			//printf("string %s\n", element_type[CP.element]);
			Draw_TextBoxAdvanced(element_type[CP.element], 20.0f * WINDOW_RATIO, CP_Input_GetMouseX(), CP_Input_GetMouseY(),
				WINDOW_WIDTH * 0.10f, WINDOW_HEIGHT * 0.15f, 2.5f / 7.f, CP_Color_Create(255, 255, 255, 255), CP_Color_Create(0, 0, 0, 255), CP_POSITION_CORNER);
			CP_Settings_RectMode(CP_POSITION_CENTER);
		}
		// circuit background image have a total of 6 indexes
		// circuit_list have a total of 5 indexes
		// Remaining of 2 indexes (5, 6)
		// Example: current index is 5
		// index - 1 = index 4 of circuit_list
		if (index > 4) {
			index = index - 1;
			CircuitPiece CP = circuit_list[index];
			// To debug and ensure it is the correct string showing
			//printf("string %s\n", element_type[CP.element]);
			
		}
	}

	// DEBUG: Go Back to Map System
	/*if (CP_Input_KeyDown(KEY_ESCAPE)) {
		CP_Engine_SetNextGameState(World_Init, World_Update, World_Exit);
	}*/
	// Load player_battle Stats
	if (initialize_player) {
		PlayerStats_ReadFile(&player_battle);
		initialize_player = 0;
		total_s_pieces = player_battle.s_mana;
	}

	if (player_battle.health <= 0) {
		initialize_player = 1;
		// Go to battleLost screen when player health is lesser than or equal to 0
		CP_Engine_SetNextGameState(BattleLost_Initialize, BattleLost_Update, BattleLost_Exit);
	}

	// Check if the enemies died
	if (check_if_enemy_died) {
		Enemy alive_enemies[ENEMY_COUNT] = { 0 };
		int count_dead = 0;
		int index_to_remove[ENEMY_COUNT] = { 0 };

		for (int i = 0, j = i; i < random_enemy_count; ++i) {
			if (enemies[i].healthbar < 0) {
				count_dead++;
				index_to_remove[j++] = i + 1;
			}
		}
		if (count_dead != 0) {
			for (int i = 1,j = 0; i <= random_enemy_count; ++i) {
				if (!Exist_In_Array(&i,index_to_remove,A_INT,3)) {
					alive_enemies[j++] = enemies[i-1];
				}
			}
			memset(enemies, 0, sizeof(enemies));
			random_enemy_count -= count_dead;
			for (int i = 0; i < random_enemy_count; ++i) {
				enemies[i] = alive_enemies[i];
			}
		}

		if (!random_enemy_count) {
			World_UpdateCurrency(original_count_enemy*50);
			CP_Engine_SetNextGameState(World_Init, World_Update, World_Exit);
		}

		// Enemy will damage the player_battle after checking if they are still alive
		Enemy_Damage_Player(enemies, &player_battle);

		check_if_enemy_died = 0;
	}

	// Load Elemental Circuits
	if (load_elements) {
		Set_Elemental_Circuits(circuit_list, elemental_circuit_images);
		load_elements = 0;
	}

	/* --------------- This Section will be to check for the functions that can run when mouse is interacted -------------*/
	// Check where the mouse clicked and what piece was selected
	if (CP_Input_MouseDown(MOUSE_BUTTON_1)) {

		//Function to check which circuit piece is selected
		if (!selected_circuit_piece) {
			selected_circuit_piece = Circuit_Piece_Selected(&circuit_piece_selected, circuit_list, mouse_position, &total_s_pieces);
		}
	}
	// Check when the mouse is released if the location for release is allowed for the piece
	else if (CP_Input_MouseReleased(MOUSE_BUTTON_1)) {
		if (selected_circuit_piece) {
			if (Grid_Circuit_Drop(circuit_selected_list, grid_squares, circuit_piece_selected, index_used, mouse_position)) {
				total_s_pieces -= circuit_piece_selected.type == S_Type ? 1 : 0;
				Piece_Placed = 1;
			}
			selected_circuit_piece = 0;
		}
	}

	
	/* ------------------------------------End of check for function when mouse is interacted ----------------------------*/

	/*  ------------------------------------------- DISPLAY ASSETS --------------------------------------------------------*/
	// Set the background with white
	CP_Graphics_ClearBackground(BACKGROUND_COLOR);

	//Set the background image
	CP_Image_Draw(background, (float)CP_System_GetWindowWidth()/2.f, (float)CP_System_GetWindowHeight()/2.f, (float)CP_System_GetWindowWidth(), (float)CP_System_GetWindowHeight(), DEFAULT_ALPHA);

	// Set background dim
	CP_Settings_Fill(CP_Color_Create(0,0,0,(int)(DEFAULT_ALPHA/1.5f)));
	CP_Graphics_DrawRect((float)CP_System_GetWindowWidth() / 2.f, (float)CP_System_GetWindowHeight() / 2.f, (float)CP_System_GetWindowWidth(), (float)CP_System_GetWindowHeight());
	
	// Set Grid color to black
	CP_Settings_Fill(COLOR_BLACK);

	// Draw UI
	Display_UI(battle_ui, player_battle, original_health, total_s_pieces);

	Display_Enemy_Hover(enemies, weakness_ui, original_enemy_arr, mouse_position, battle_ui[3]);

	// Draw grid
	Grid_Display(grid_squares);

	// Draw each enemy based on its type
	for (int i = 0; i < random_enemy_count; i++) {
		switch (enemies[i].enemy_type) {
		case E_Wizard:
			CP_Image_Draw(e_wizard_image, enemies[i].position.x, enemies[i].position.y, GRID_CELL_SIZE, GRID_CELL_SIZE, 255);
			break;
		case E_Plant:
			CP_Image_Draw(e_plant_image, enemies[i].position.x, enemies[i].position.y, GRID_CELL_SIZE, GRID_CELL_SIZE, 255);
			break;
		case E_Vulture:
			CP_Image_Draw(e_vulture_image, enemies[i].position.x, enemies[i].position.y, GRID_CELL_SIZE, GRID_CELL_SIZE, 255);
			break;
		default:
			continue;
		}
		
	}

	// Draw Circuit UI
	Draw_UI_CircuitPiece(circuit_list, circuit_image_corner, CIRCUIT_UI_LIST_SIZE, total_s_pieces);

	// Draw Selected Circuit Pieces
	Draw_SelectedCircuitPieces(circuit_selected_list);

	// Display Selected Circuit Piece while the player_battle is dragging the piece
	if (selected_circuit_piece) {
		CP_Image_DrawAdvanced(
			circuit_piece_selected.image, mouse_position.x, mouse_position.y,
			(float)circuit_piece_selected.circuit_size, (float)circuit_piece_selected.circuit_size, 255, (float)circuit_piece_selected.rot * ANGLE_OF_ROTATION);
	}

	// Display button for submiting magic system
	if ((IsAreaClicked(battle_ui[1].pos.x, battle_ui[1].pos.y, battle_ui[1].width, battle_ui[1].height, CP_Input_GetMouseX(), CP_Input_GetMouseY()) && CP_Input_MouseClicked())) {
		if (Is_Closed_Circuit(index_used, circuit_selected_list)) {
			Check_Enemy_Hit(enemies,index_used,circuit_selected_list,player_battle);
			Spell_Cast = 1;
		}
		// Delete all circuits chosen and reload elements
		memset(circuit_selected_list, 0, sizeof(circuit_selected_list));
		memset(index_used, 0, sizeof(index_used));
		load_elements = 1;
		total_s_pieces = player_battle.s_mana;
		// Randomisze enemy positions again
		Enemy_Initialize_Array(enemies, grid_squares, random_enemy_count, 0);
		check_if_enemy_died = 1;
	}
	Tutorial_Update();
	Tutorial_Draw();
	/*--------------------------------------------- END DISPLAY ASSETS --------------------------------------------------------*/
}

void Battle_System_Exit()
{
	//Reset the arrays when exiting the battle system
	memset(circuit_selected_list, 0, sizeof(circuit_selected_list));
	memset(index_used, 0, sizeof(index_used));

	//Free the images that were loaded
	CP_Image_Free(&circuit_image_corner);
	CP_Image_Free(&circuit_image_straight);
	CP_Image_Free(&e_wizard_image);
	CP_Image_Free(&e_plant_image);
	CP_Image_Free(&e_vulture_image);

	for (int i = 0; i < UI_COUNT; ++i) {
		CP_Image_Free(&battle_ui[i].img);
	}
	//Change back to true to make sure the pipe elements are shuffled upon re-entering battle-system
	load_elements = 1;
	initialize_player = 1;
}

void Reset_Initialize(int* boss_initialize) {
	initialize_player = 1;
	*boss_initialize = 1;
}