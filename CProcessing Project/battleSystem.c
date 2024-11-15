#include <stdio.h>
#include "worldSystem.h"
#include "battleSystem.h"
#include "magicSystemUtil.h"
#include "enemyStructs.h"
#include "TEST_playerUtil.h"

//Variables to generate enemies
int random_enemy_count = 0;
CP_Image enemy_image;

// Define images for each enemy type
CP_Image e_wizard_image;
CP_Image e_plant_image;
CP_Image e_vulture_image;

// an array of Enemy structures called enemies with a size of ENEMY_COUNT
Enemy enemies[ENEMY_COUNT];
int check_if_enemy_died = 0;

//Player object to calculate the damage to be done. Damage taken from a temp file
int initialize_player = 1;
Player player;

/* Circuits--------------------------------------------------------------------------------------------------------------*/
//Image of the circuit pieces
CP_Image circuit_image_corner, circuit_image_straight;

//List of all the circuit pieces the player can use
CircuitPiece circuit_list[CIRCUIT_UI_LIST_SIZE];

//Circuit Piece Selected
CircuitPiece circuit_selected_list[GRID_DIMENSIONS][GRID_DIMENSIONS] = { 0 };
CircuitPiece circuit_piece_selected = { 0 };
CP_Vector index_used[GRID_DIMENSIONS * GRID_DIMENSIONS] = { 0 };
int selected_circuit_piece = 0;

//mouse vector that will be updated when mouse down is detected
CP_Vector mouse_position = { 0 };

//Straight Circuit Pieces System
int total_s_pieces;

//Elemental Circuit System Variables
/*
0 : Grass
1 : Water
2 : Fire
*/
CP_Image elemental_circuit_images[4];

//bool to check if the elemental pipes have been shuffled for the current turn
int load_elements = 1;
/*-------------------------------------------------------------------------------------------------------------------------*/

//Grids that will be used to display the enemy
CP_Vector grid_squares[GRID_DIMENSIONS][GRID_DIMENSIONS];

//Button Variables
Button button_submit;


void Battle_System_Init()
{
	
	//Setting Modes for display
	CP_Settings_ImageMode(CP_POSITION_CENTER);
	CP_Settings_RectMode(CP_POSITION_CENTER);

	//Loading the image for the Magic Circuit's L Piece
	circuit_image_corner = CP_Image_Load(CIRCUIT_L_ASSET_ADDR);
	circuit_image_straight = CP_Image_Load(CIRCUIT_S_ASSET_ADDR);

	//Loading images for the elemental circuits
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
	float circuit_ui_corner_buffer_top = (float)(grid_size + GRID_CELL_SIZE_OFFSET * 4);
	float circuit_ui_corner_buffer_left = (float)(WINDOW_WIDTH - (GRID_CELL_SIZE * NUM_OF_L_PIECE + BUFFER * (NUM_OF_L_PIECE - 1))) / 2.f;

	//This loop will initialize the corner pieces to be displayed on the UI for selection
	for (int i = 0, j = i + 1; i < NUM_OF_L_PIECE; ++i, j = j < 3 ? j + 1 : 0) {
		circuit_list[i] = New_Circuit_Piece(
			CP_Vector_Set(circuit_ui_corner_buffer_left + GRID_CELL_SIZE_OFFSET + GRID_CELL_SIZE * i + BUFFER * i, circuit_ui_corner_buffer_top),
			circuit_image_corner,
			i, j, i, GRID_CELL_SIZE, L_Type);
	}

	float circuit_ui_straight_buffer_top = ((float)WINDOW_HEIGHT - (GRID_CELL_SIZE * NUM_OF_S_PIECE + BUFFER)) / 2.f;
	float circuit_ui_straight_buffer_left = circuit_ui_corner_buffer_left / 2.f;
	//This loop will initialize the straight pieces to be displayed on the UI for selection
	for (int i = 0, j = i + 2; i < NUM_OF_S_PIECE; ++i,++j) {
		circuit_list[NUM_OF_L_PIECE + i] = New_Circuit_Piece(
			CP_Vector_Set(circuit_ui_straight_buffer_left, circuit_ui_straight_buffer_top + (float)GRID_CELL_SIZE / 2.f + GRID_CELL_SIZE * i + BUFFER * i),
			circuit_image_straight,
			i, j, i, GRID_CELL_SIZE, S_Type);
	}

	total_s_pieces = 2;

	//Initialize the button for submit
	button_submit.width = 128 * 2;
	button_submit.height = 64;

	button_submit.position = CP_Vector_Set((float)(WINDOW_WIDTH - grid_size) * 0.75f + grid_size, (float)WINDOW_HEIGHT - (float)(WINDOW_HEIGHT - grid_size) / 2.f + button_submit.height / 2.f);
	/*------------------------------------------------------------------------------------------------ */

	//Initialize the grids for testing
	Grid_Initialize(grid_squares);

	// Randomly generate the number of enemies to be spawned
	random_enemy_count = CP_Random_RangeInt(1, 3);
	printf("Number of enemies to be generated: %d\n", random_enemy_count);

	// Randomly generate unique enemy positions
	Enemy_Initialize_Array(enemies, grid_squares, random_enemy_count,1);

	if (initialize_player) {
		PlayerStats_ReadFile(&player);
		initialize_player = 0;
	}
}

void Battle_System_Update()
{

	//DEBUG: Go Back to Map System
	if (CP_Input_KeyDown(KEY_ESCAPE)) {
		CP_Engine_SetNextGameState(World_Init, World_Update, World_Exit);
	}

	//Check if the enemies died
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

		if (!random_enemy_count) CP_Engine_SetNextGameState(World_Init, World_Update, World_Exit);

		check_if_enemy_died = 0;
	}
	//Load Player Stats
	if (initialize_player) {
		PlayerStats_ReadFile(&player);
		initialize_player = 0;
	}

	//Load Elemental Circuits
	if (load_elements) {
		Set_Elemental_Circuits(circuit_list, elemental_circuit_images);
		load_elements = 0;
	}

	/* --------------- This Section will be to check for the functions that can run when mouse is interacted -------------*/
	//Check where the mouse clicked and what piece was selected
	if (CP_Input_MouseDown(MOUSE_BUTTON_1)) {
		mouse_position = CP_Vector_Set(CP_Input_GetMouseX(), CP_Input_GetMouseY());

		//Function to check which circuit piece is selected
		if (!selected_circuit_piece)
			selected_circuit_piece = Circuit_Piece_Selected(&circuit_piece_selected, circuit_list, mouse_position, &total_s_pieces);

	}
	//Check when the mouse is released if the location for release is allowed for the piece
	else if (CP_Input_MouseReleased(MOUSE_BUTTON_1)) {
		if (selected_circuit_piece) {
			if (Grid_Circuit_Drop(circuit_selected_list, grid_squares, circuit_piece_selected, index_used, mouse_position)) {
				total_s_pieces -= circuit_piece_selected.type == S_Type ? 1 : 0;
			}
			selected_circuit_piece = 0;
		}
	}
	/* --------------------------------------------------------------------------------------------------------------------*/

	// Set the background with white
	CP_Graphics_ClearBackground(BACKGROUND_COLOR);

	// Set Grid color to black
	CP_Settings_Fill(COLOR_BLACK);

	//Draw grid
	Grid_Display(grid_squares);

	// Draw each enemy based on its type
	for (int i = 0; i < random_enemy_count; i++) {
		
		switch (enemies[i].enemy_type) {
		case E_Wizard:
			enemy_image = e_wizard_image;
			break;
		case E_Plant:
			enemy_image = e_plant_image;
			break;
		case E_Vulture:
			enemy_image = e_vulture_image;
			break;
		default:
			continue;
		}
		CP_Image_Draw(enemy_image, enemies[i].position.x, enemies[i].position.y, GRID_CELL_SIZE, GRID_CELL_SIZE, 255);
	}

	//Draw Circuit UI
	Draw_UI_CircuitPiece(circuit_list, circuit_image_corner, CIRCUIT_UI_LIST_SIZE);

	//Draw Selected Circuit Pieces
	Draw_SelectedCircuitPieces(circuit_selected_list);

	//Display Selected Circuit Piece while the player is dragging the piece
	if (selected_circuit_piece) {
		CP_Image_DrawAdvanced(
			circuit_piece_selected.image, mouse_position.x, mouse_position.y,
			(float)circuit_piece_selected.circuit_size, (float)circuit_piece_selected.circuit_size, 255, (float)circuit_piece_selected.rot * ANGLE_OF_ROTATION);
	}

	//Display button for submiting magic system
	if (Draw_Button("Submit", button_submit.position.x, button_submit.position.y, button_submit.width * WINDOW_RATIO, button_submit.height * WINDOW_RATIO)) {
		if (Is_Closed_Circuit(index_used, circuit_selected_list)) {
			Check_Enemy_Hit(enemies,index_used,circuit_selected_list,player);
			check_if_enemy_died = 1;

			//Delete all circuits chosen and reload elements
			load_elements = 1;
			memset(circuit_selected_list, 0, sizeof(circuit_selected_list));
			memset(index_used, 0, sizeof(index_used));
			Enemy_Initialize_Array(enemies, grid_squares, random_enemy_count, 0);
			printf("Closed Circuit\n");
		}
		else {
			printf("Opened Circuit\n");
		}
	}
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

	//Change back to true to make sure the pipe elements are shuffled upon re-entering battle-system
	load_elements = 1;
	initialize_player = 1;
}

