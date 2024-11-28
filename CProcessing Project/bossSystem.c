/*
File: bossSystem.c
Author: Jason Teo Jun Hao (jasonjunhao.teo)
Description:
This file contains the definition runtime functions for the Boss System that will display everything related to the boss fight
 - void Boss_System_Init
 - void Boss_System_Update
 - void Boss_System_Exit
*/

//Header files for the bossSystem
#include <stdio.h>
#include "worldSystem.h"
#include "bossSystem.h"
#include "bossUtils.h"
#include "bossStruct.h"
#include "generalUtils.h"
#include "magicSystemUtil.h"
#include "TEST_playerUtil.h"
#include "battleSystemUI.h"
#include "battleSystem.h"
#include "battleLost.h"
#include "battleWon.h"

// Variables for Battle System UI
BattleUI boss_battle_ui[UI_COUNT];
CP_Image boss_background;
CP_Image boss_weakness_ui[3];

// An array of Enemy structures called enemies with a size of ENEMY_COUNT
Boss boss;
int check_if_boss_died = 0;
int enrage = 0;
BossPart original_bp[GRID_DIMENSIONS * GRID_DIMENSIONS];
int gate_core_initialize = 1;

// Player_boss object to calculate the damage to be done. Damage taken from a temp file
int initialize_player_b = 1;
Player player_boss;
float player_original_health;

/*--------------------------------------------------- Setting Variables for Circuits -----------------------------------------------------*/
//Image of the circuit pieces
CP_Image circuit_image_corner, circuit_image_straight;

//List of all the circuit pieces the player_boss can use
CircuitPiece circuit_list[CIRCUIT_UI_LIST_SIZE];

//Circuit Piece Selected
CircuitPiece circuit_selected_list_b[GRID_DIMENSIONS][GRID_DIMENSIONS] = { 0 };
CircuitPiece circuit_piece_selected_b = { 0 };
CP_Vector index_used_b[GRID_DIMENSIONS * GRID_DIMENSIONS] = { 0 };
int selected_circuit_piece_b = 0;

//mouse vector that will be updated when mouse down is detected
CP_Vector mouse_position_b = { 0 };

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
int load_elements_b = 1;
/*----------------------------------------------- END Setting Variables for Circuits -----------------------------------------------------*/

//Grids that will be used to display the enemy
CP_Vector grid_squares[GRID_DIMENSIONS][GRID_DIMENSIONS];

//Button Variables
Button button_submit;

void Boss_System_Init()
{
	enrage = 0;

	//Setting Modes for display
	CP_Settings_ImageMode(CP_POSITION_CENTER);
	CP_Settings_RectMode(CP_POSITION_CENTER);

	// Initialize UI
	UI_Initialize(boss_battle_ui);
	boss_background = CP_Image_Load("Assets/Door_Way.png");

	boss_weakness_ui[0] = CP_Image_Load(GRASS_UI);
	boss_weakness_ui[1] = CP_Image_Load(WATER_UI);
	boss_weakness_ui[2] = CP_Image_Load(FIRE_UI);

	//Loading the image for the Magic Circuit's L Piece
	circuit_image_corner = CP_Image_Load(CIRCUIT_L_ASSET_ADDR);
	circuit_image_straight = CP_Image_Load(CIRCUIT_S_ASSET_ADDR);

	//Loading images for the elemental circuits
	elemental_circuit_images[0] = CP_Image_Load(CIRCUIT_LG_ASSET_ADDR);
	elemental_circuit_images[1] = CP_Image_Load(CIRCUIT_LW_ASSET_ADDR);
	elemental_circuit_images[2] = CP_Image_Load(CIRCUIT_LF_ASSET_ADDR);
	elemental_circuit_images[3] = circuit_image_corner;

	/*------------Calculating the buffer for the display location of the UI for the circuits---------- */
	float grid_size = GRID_DIMENSIONS * GRID_CELL_SIZE;
	float circuit_piece_x = CIRCUIT_UI_X;
	float circuit_piece_y = CIRCUIT_UI_Y;

	for (int i = 0, j = i + 1; i < NUM_OF_L_PIECE; ++i, j = j < 3 ? j + 1 : 0) {
		circuit_list[i] = New_Circuit_Piece(
			CP_Vector_Set(circuit_piece_x - GRID_CELL_SIZE * i, circuit_piece_y),
			circuit_image_corner,
			i, j, i, GRID_CELL_SIZE, L_Type);
	}

	// This loop will initialize the straight pieces to be displayed on the UI for selection
	for (int i = 0, j = i + 2; i < NUM_OF_S_PIECE; ++i, ++j) {
		circuit_list[NUM_OF_L_PIECE + i] = New_Circuit_Piece(
			CP_Vector_Set(circuit_piece_x + GRID_CELL_SIZE * j, circuit_piece_y),
			circuit_image_straight,
			i, j, i, GRID_CELL_SIZE, S_Type);
	}

	//Initialize the button for submit
	button_submit.width = 128 * 2;
	button_submit.height = 64;

	button_submit.position = CP_Vector_Set((float)(WINDOW_WIDTH - grid_size) * 0.75f + grid_size, (float)WINDOW_HEIGHT - (float)(WINDOW_HEIGHT - grid_size) / 2.f + button_submit.height / 2.f);
	/*------------------------------------------------------------------------------------------------ */

	//Initialize the grids for testing
	Grid_Initialize(grid_squares);

	// Load Boss
	Boss_Initialize(&boss, World_GetBoss(), grid_squares);
	gate_core_initialize = 1;

	for (int i = 0; i < boss.num_of_bp; ++i) {
		original_bp[i] = boss.parts[i];
	}

	if (initialize_player_b) {
		PlayerStats_ReadFile(&player_boss);
		initialize_player_b = 0;
		player_original_health = player_boss.health;
		total_s_pieces = player_boss.s_mana;
	}
}

void Boss_System_Update()
{
	//Load player_boss Stats
	if (initialize_player_b) {
		PlayerStats_ReadFile(&player_boss);
		initialize_player_b = 0;
		total_s_pieces = player_boss.s_mana;
	}


	mouse_position_b = CP_Vector_Set(CP_Input_GetMouseX(), CP_Input_GetMouseY());

	//DEBUG: Go Back to Map System
	if (CP_Input_KeyDown(KEY_ESCAPE)) {
		CP_Engine_SetNextGameState(World_Init, World_Update, World_Exit);
	}


	//Load Elemental Circuits
	if (load_elements_b) {
		Set_Elemental_Circuits(circuit_list, elemental_circuit_images);
		load_elements_b = 0;
	}

	// Check if player's health is lesser than or equal to 0 or when player did not manage to clear enrage round that is set within the file
	if (enrage >= boss.enrage_time || player_boss.health <= 0) {
		initialize_player_b = 1;
		// Go to battleLost screen when player die
		CP_Engine_SetNextGameState(BattleLost_Initialize, BattleLost_Update, BattleLost_Exit);
	}

	//Check if the enemies died
	if (check_if_boss_died) {
		BossPart alive_enemies[GRID_DIMENSIONS * GRID_DIMENSIONS] = { 0 };
		int count_dead = 0;
		int index_to_remove[GRID_DIMENSIONS * GRID_DIMENSIONS] = { 0 };

		for (int i = 0, j = i; i < boss.num_of_bp; ++i) {
			if (boss.parts[i].healthbar < 0) {
				count_dead++;
				index_to_remove[j++] = i + 1;
			}
		}
		if (count_dead != 0) {
			for (int i = 1, j = 0; i <= boss.num_of_bp; ++i) {
				if (!Exist_In_Array(&i, index_to_remove, A_INT, 3)) {
					alive_enemies[j++] = boss.parts[i - 1];
				}
			}
			memset(boss.parts, 0, sizeof(boss.parts));
			boss.num_of_bp -= count_dead;
			for (int i = 0; i < boss.num_of_bp; ++i) {
				boss.parts[i] = alive_enemies[i];
			}
		}


		check_if_boss_died = 0;
		switch (boss.boss_id)
		{
		case 1:
			Gatekeeper_Mechanics(&player_boss, boss, &enrage);
			Boss_Randomise_Position(boss.parts, grid_squares, boss.num_of_bp);
			break;
		case 2:
			Gatekeeper_Mechanics(&player_boss, boss, &enrage);
			Boss_Randomise_Position(boss.parts, grid_squares, boss.num_of_bp);

			int check_core = 0;

			for (int i = 0; i < boss.num_of_bp; ++i) {
				if (boss.parts[i].id == 0) {
					check_core = 1;
					break;
				}
			}
			if (!check_core) {
				boss.num_of_bp = 0;
			}

			break;
		default:
			break;
		}

		// Check if it is the main boss as main boss ID is 2
		// Also check if number of boss body part is equal to zero
		if ((boss.boss_id % 2 == 0) && (boss.num_of_bp == 0)) {
			CP_Engine_SetNextGameState(BattleWon_Initialize, BattleWon_Update, BattleWon_Exit);
		}

		else if (!boss.num_of_bp) {
			World_UpdateCurrency(250);
			CP_Engine_SetNextGameState(World_Init, World_Update, World_Exit);
		}
	}

	/* --------------- This Section will be to check for the functions that can run when mouse is interacted -------------*/
	//Check where the mouse clicked and what piece was selected
	if (CP_Input_MouseDown(MOUSE_BUTTON_1)) {

		//Function to check which circuit piece is selected
		if (!selected_circuit_piece_b)
			selected_circuit_piece_b = Circuit_Piece_Selected(&circuit_piece_selected_b, circuit_list, mouse_position_b, &total_s_pieces);

	}
	//Check when the mouse is released if the location for release is allowed for the piece
	else if (CP_Input_MouseReleased(MOUSE_BUTTON_1)) {
		if (selected_circuit_piece_b) {
			if (Grid_Circuit_Drop(circuit_selected_list_b, grid_squares, circuit_piece_selected_b, index_used_b, mouse_position_b)) {
				total_s_pieces -= circuit_piece_selected_b.type == S_Type ? 1 : 0;
			}
			selected_circuit_piece_b = 0;
		}
	}
	/* --------------------------------------------------------------------------------------------------------------------*/

	// Set the background with white
	CP_Graphics_ClearBackground(BACKGROUND_COLOR);

	//Set the background image
	CP_Image_Draw(boss_background, (float)CP_System_GetWindowWidth() / 2.f, (float)CP_System_GetWindowHeight() / 2.f, (float)CP_System_GetWindowWidth(), (float)CP_System_GetWindowHeight(), DEFAULT_ALPHA);

	// Set background dim
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, (int)(DEFAULT_ALPHA / 1.5f)));
	CP_Graphics_DrawRect((float)CP_System_GetWindowWidth() / 2.f, (float)CP_System_GetWindowHeight() / 2.f, (float)CP_System_GetWindowWidth(), (float)CP_System_GetWindowHeight());

	// Set Grid color to black
	CP_Settings_Fill(COLOR_BLACK);

	// Draw grid
	Grid_Display(grid_squares);

	// Draw UI
	Display_UI(boss_battle_ui, player_boss, player_original_health,total_s_pieces);
	Display_Boss_Hover(boss, boss_weakness_ui, original_bp, mouse_position_b, boss_battle_ui[3], boss.num_of_bp);
	//Display_Enemy_Hover(enemies, original_enemy_arr, mouse_position, battle_ui[4]);

	// Draw each enemy based on its type
	for (int i = 0; i < boss.num_of_bp; i++) {
		CP_Image_Draw(boss.parts[i].image,
			boss.parts[i].pos.x,
			boss.parts[i].pos.y,
			GRID_CELL_SIZE, GRID_CELL_SIZE, 255);
	}


	//Draw Circuit UI
	Draw_UI_CircuitPiece(circuit_list, circuit_image_corner, CIRCUIT_UI_LIST_SIZE, total_s_pieces);

	//Draw Selected Circuit Pieces
	Draw_SelectedCircuitPieces(circuit_selected_list_b);

	//Display Selected Circuit Piece while the player_boss is dragging the piece
	if (selected_circuit_piece_b) {
		CP_Image_DrawAdvanced(
			circuit_piece_selected_b.image, mouse_position_b.x, mouse_position_b.y,
			(float)circuit_piece_selected_b.circuit_size, (float)circuit_piece_selected_b.circuit_size, 255, (float)circuit_piece_selected_b.rot * ANGLE_OF_ROTATION);
	}

	//Display button for submiting magic system
	if ((IsAreaClicked(boss_battle_ui[1].pos.x, boss_battle_ui[1].pos.y, boss_battle_ui[1].width, boss_battle_ui[1].height, CP_Input_GetMouseX(), CP_Input_GetMouseY()) && CP_Input_MouseClicked())) {
		if (Is_Closed_Circuit(index_used_b, circuit_selected_list_b)) {
			if (boss.boss_id == 2 && gate_core_initialize) {
				gate_core_initialize = 0;
			}
			else Check_Boss_Hit(boss.parts, index_used_b, circuit_selected_list_b, player_boss, boss.num_of_bp);
		}

		//Delete all circuits chosen and reload elements
		load_elements_b = 1;
		memset(circuit_selected_list_b, 0, sizeof(circuit_selected_list_b));
		memset(index_used_b, 0, sizeof(index_used_b));
		total_s_pieces = player_boss.s_mana;
		check_if_boss_died = 1;
	}
}

void Boss_System_Exit()
{
	//Reset the arrays when exiting the battle system
	memset(circuit_selected_list_b, 0, sizeof(circuit_selected_list_b));
	memset(index_used_b, 0, sizeof(index_used_b));

	//Free the images that were loaded
	CP_Image_Free(&circuit_image_corner);
	CP_Image_Free(&circuit_image_straight);

	//Change back to true to make sure the pipe elements are shuffled upon re-entering battle-system
	load_elements_b = 1;
	initialize_player_b = 1;
	enrage = 0;
}