#include <stdio.h>
#include "worldSystem.h"
#include "battleSystem.h"
#include "magicSystemUtil.h"
#include "enemyStructs.h"

int random_enemy_count = 0;
CP_Image enemy_image;


// Define images for each enemy type
CP_Image e_wizard_image;
CP_Image e_plant_image;
CP_Image e_vulture_image;

// an array of Enemy structures called enemies with a size of ENEMY_COUNT
Enemy enemies[ENEMY_COUNT];



/* Circuits--------------------------------------------------------------------------------------------------------------*/
//Image of the circuit pieces
CP_Image circuit_image_l;

//List of all the circuit pieces the player can use
CircuitPiece circuit_list_l[CIRCUIT_UI_LIST_SIZE];
CircuitPiece circuit_pieces_s[2];

//Circuit Piece Selected
CircuitPiece circuit_selected_list[GRID_DIMENSIONS][GRID_DIMENSIONS] = { 0 };
CircuitPiece circuit_piece_selected = { 0 };
int selected_circuit_piece = 0;

//mouse vector that will be updated when mouse down is detected
CP_Vector mouse_position = { 0 };

/*-------------------------------------------------------------------------------------------------------------------------*/

//Grids that will be used to display the enemy
CP_Vector grid_squares[GRID_DIMENSIONS][GRID_DIMENSIONS];

void Battle_System_Init()
{
	
	//Setting Modes for display
	CP_Settings_ImageMode(CP_POSITION_CENTER);
	CP_Settings_RectMode(CP_POSITION_CENTER);

	//Loading the image for the Magic Circuit's L Piece
	circuit_image_l = CP_Image_Load(CIRCUIT_L_ASSET_ADDR);


	// Load each enemy image
	e_wizard_image = CP_Image_Load(E_WIZARD_ASSET_ADDR);
	e_plant_image = CP_Image_Load(E_PLANT_ASSET_ADDR);
	e_vulture_image = CP_Image_Load(E_VULTURE_ASSET_ADDR);


	/*------------Calculating the buffer for the display location of the UI for the circuits---------- */
	float circuit_ui_buffer_top = (float)(GRID_DIMENSIONS * CIRCUIT_PIECE_SIZE + CIRCUIT_CENTER_OFFSET * 4);
	float circuit_ui_buffer_left = (float)(WINDOW_WIDTH - (CIRCUIT_PIECE_SIZE * CIRCUIT_UI_LIST_SIZE + BUFFER * (CIRCUIT_UI_LIST_SIZE - 1))) / 2.f;

	//This loop will initialize the ciruits to be displayed on the UI for selection
	for (int i = 0, j = i + 1; i < 4; ++i, j = j < 3 ? j + 1 : 0) {
		circuit_list_l[i] = New_Circuit_Piece(
			CP_Vector_Set(circuit_ui_buffer_left + (float)CIRCUIT_PIECE_SIZE / 2.f + CIRCUIT_PIECE_SIZE * i + BUFFER * i, circuit_ui_buffer_top)
			, i, j, i);
		circuit_list_l[i].circuitSize = CIRCUIT_PIECE_SIZE;
	}
	/*------------------------------------------------------------------------------------------------ */

	//Initialize the grids for testing
	Grid_Initialize(grid_squares);

	// Randomly generate the number of enemies to be spawned
	random_enemy_count = CP_Random_RangeInt(1, 3);
	printf("Number of enemies to be generated: %d\n", random_enemy_count);

	Enemy_Initialize_Array(enemies, grid_squares, random_enemy_count);

	// Randomly generate unique enemy positions
	void Enemy_Initialize_Array(enemies, grid_squares, random_enemy_count);

}

void Battle_System_Update()
{
	//DEBUG: Go Back to Map System
	if (CP_Input_KeyDown(KEY_ESCAPE)) {
		CP_Engine_SetNextGameState(World_Init, World_Update, World_Exit);
	}

	/* --------------- This Section will be to check for the functions that can run when mouse is interacted -------------*/
	if (CP_Input_MouseDown(MOUSE_BUTTON_1)) {
		mouse_position = CP_Vector_Set(CP_Input_GetMouseX(), CP_Input_GetMouseY());

		//Function to check which circuit piece is selected
		if (!selected_circuit_piece)
			selected_circuit_piece = Circuit_PieceSelected(&circuit_piece_selected, circuit_list_l,mouse_position);

	}
	else if (CP_Input_MouseReleased(MOUSE_BUTTON_1)) {
		if (selected_circuit_piece) {
			Grid_Cricuit_Drop(circuit_piece_selected, circuit_selected_list, grid_squares,mouse_position);
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
		CP_Image_Draw(enemy_image, enemies[i].position.x, enemies[i].position.y, 128, 128, 255);
	}

	//Draw Circuit UI
	Draw_L_CircuitPiece(circuit_list_l,circuit_image_l, CIRCUIT_UI_LIST_SIZE);

	//Draw Selected Circuit Pieces
	Draw_SelectedCircuitPieces(circuit_selected_list,circuit_image_l);

	if (selected_circuit_piece) {
		CP_Image_DrawAdvanced(
			circuit_image_l, mouse_position.x, mouse_position.y,
			(float)circuit_piece_selected.circuitSize, (float)circuit_piece_selected.circuitSize, 255, (float)circuit_piece_selected.rot * ANGLE_OF_ROTATION);
	}
}

void Battle_System_Exit()
{
	memset(circuit_selected_list, 0, sizeof(circuit_selected_list));
	CP_Image_Free(circuit_image_l);
	CP_Image_Free(e_wizard_image);
	CP_Image_Free(e_plant_image);
	CP_Image_Free(e_vulture_image);
}

