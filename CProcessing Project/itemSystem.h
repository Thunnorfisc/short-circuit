#pragma once
#include "cprocessing.h"

#define NAME_LENGTH 50 + 1 // Plus 1 for null terminator
#define DESC_LENGTH 100 + 1

typedef enum AffectType {
	HEALTH,
	MANA,
	ATTACK,
	DEFENSE,
	FIRE,
	WATER,
	GRASS
} AffectType;

typedef struct Item {
	int id;
	char name[NAME_LENGTH];
	AffectType type;
	double modifier;
	char description[DESC_LENGTH];
	int price;
	CP_Image image;
} Item;

void ItemEvent_Init(void);
void ItemEvent_Update(void);
void ItemEvent_Exit(void);

void Item_RandomItemGenerator(Item* random_items, int num_items);
int Item_ListCount();
int Item_Generate_List();

int Draw_Textbox(const char* text, float textSize, float x, float y,
	float w, float h, CP_Color box_color, CP_Color text_color, CP_POSITION_MODE mode);