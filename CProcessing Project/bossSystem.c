#include <stdio.h>
#include "worldSystem.h"
#include "bossSystem.h"
#include "bossUtils.h"
#include "bossStruct.h"
#include "generalUtils.h"
#include "magicSystemUtil.h"
#include "TEST_playerUtil.h"

// an array of Enemy structures called enemies with a size of ENEMY_COUNT
Boss boss;
int check_if_boss_died = 0;

//Player object to calculate the damage to be done. Damage taken from a temp file
int initialize_player_b = 1;
Player player;

/* Circuits--------------------------------------------------------------------------------------------------------------*/
//Image of the circuit pieces
CP_Image circuit_image_corner, circuit_image_straight;

//List of all the circuit pieces the player can use
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
/*-------------------------------------------------------------------------------------------------------------------------*/

//Grids that will be used to display the enemy
CP_Vector grid_squares[GRID_DIMENSIONS][GRID_DIMENSIONS];

//Button Variables
Button button_submit;


void Boss_System_Init()
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
	for (int i = 0, j = i + 2; i < NUM_OF_S_PIECE; ++i, ++j) {
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

	// Load Boss
	Boss_Initialize(&boss, 1, grid_squares);


	if (initialize_player_b) {
		PlayerStats_ReadFile(&player);
		initialize_player_b = 0;
	}
}

void Boss_System_Update()
{

	//DEBUG: Go Back to Map System
	if (CP_Input_KeyDown(KEY_ESCAPE)) {
		CP_Engine_SetNextGameState(World_Init, World_Update, World_Exit);
	}

	//Load Player Stats
	if (initialize_player_b) {
		PlayerStats_ReadFile(&player);
		initialize_player_b = 0;
	}

	//Load Elemental Circuits
	if (load_elements_b) {
		Set_Elemental_Circuits(circuit_list, elemental_circuit_images);
		load_elements_b = 0;
	}

	//Check if the enemies died
	if (check_if_boss_died) {
		BossPart alive_enemies[GRID_DIMENSIONS*GRID_DIMENSIONS] = { 0 };
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

		if (!boss.num_of_bp) CP_Engine_SetNextGameState(World_Init, World_Update, World_Exit);

		check_if_boss_died = 0;
	}

	/* --------------- This Section will be to check for the functions that can run when mouse is interacted -------------*/
	//Check where the mouse clicked and what piece was selected
	if (CP_Input_MouseDown(MOUSE_BUTTON_1)) {
		mouse_position_b = CP_Vector_Set(CP_Input_GetMouseX(), CP_Input_GetMouseY());

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

	// Set Grid color to black
	CP_Settings_Fill(COLOR_BLACK);

	//Draw grid
	Grid_Display(grid_squares);

	// Draw each enemy based on its type
	for (int i = 0; i < boss.num_of_bp; i++) {
		CP_Image_Draw(boss.parts[i].image, 
			boss.parts[i].pos.x,
			boss.parts[i].pos.y,
			GRID_CELL_SIZE, GRID_CELL_SIZE, 255);
	}


	//Draw Circuit UI
	Draw_UI_CircuitPiece(circuit_list, circuit_image_corner, CIRCUIT_UI_LIST_SIZE);

	//Draw Selected Circuit Pieces
	Draw_SelectedCircuitPieces(circuit_selected_list_b);

	//Display Selected Circuit Piece while the player is dragging the piece
	if (selected_circuit_piece_b) {
		CP_Image_DrawAdvanced(
			circuit_piece_selected_b.image, mouse_position_b.x, mouse_position_b.y,
			(float)circuit_piece_selected_b.circuit_size, (float)circuit_piece_selected_b.circuit_size, 255, (float)circuit_piece_selected_b.rot * ANGLE_OF_ROTATION);
	}

	//Display button for submiting magic system
	if (Draw_Button("Submit", button_submit.position.x, button_submit.position.y, button_submit.width * WINDOW_RATIO, button_submit.height * WINDOW_RATIO)) {
		if (Is_Closed_Circuit(index_used_b, circuit_selected_list_b)) {
			check_if_boss_died = 1;
			Check_Boss_Hit(boss.parts, index_used_b, circuit_selected_list_b, player);

			//Delete all circuits chosen and reload elements
			load_elements_b = 1;
			memset(circuit_selected_list_b, 0, sizeof(circuit_selected_list_b));
			memset(index_used_b, 0, sizeof(index_used_b));
			printf("Closed Circuit\n");
		}
		else {
			printf("Opened Circuit\n");
		}
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
}

