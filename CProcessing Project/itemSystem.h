/*
* @author	William Wibisana Dumnanauw (williamwibisana.d)
* @brief	The file contains the item system
* @file		itemSystem.h
* All content © 2024 DigiPen Institute of Technology Singapore, all rights reserved.
*/
#pragma once
#include "cprocessing.h"

// Maximum length of name and description
#define NAME_LENGTH 50 + 1 // Plus 1 for null terminator
#define DESC_LENGTH 100 + 1

// The enum is used to tell the item what stat it affects
typedef enum AffectType {
	HEALTH,
	MANA,
	ATTACK,
	DEFENSE,
	FIRE,
	WATER,
	GRASS
} AffectType;

// Item struct
// modifier can be additive or multiplicative
typedef struct Item {
	int id;
	char name[NAME_LENGTH];
	AffectType type;
	double modifier;
	char description[DESC_LENGTH];
	int price;
	CP_Image image;
} Item;

/* ======== SCENE FUNCTIONS ======== */
void ItemEvent_Init(void);
void ItemEvent_Update(void);
void ItemEvent_Exit(void);

/* ======== SYSTEM FUNCTIONS ======== */
// Randomizes the items into an array
void Item_RandomItemGenerator(Item* random_items, int num_items);
// Gives count of items in the list
int Item_ListCount();
// Generates the list of items from the item txt file
int Item_Generate_List();

/* ======== UTILS FUNCTIONS ======== */
// Used to draw a textbox which allows wrapping of text around the drawn box
int Draw_Textbox(const char* text, float textSize, float x, float y,
	float w, float h, CP_Color box_color, CP_Color text_color, CP_POSITION_MODE mode);