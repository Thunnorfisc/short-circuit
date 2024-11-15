#pragma once

#define NAME_LENGTH 50 + 1 // Plus 1 for null terminator
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
} Item;

void ItemEvent_Init(void);
void ItemEvent_Update(void);
void ItemEvent_Exit(void);
void ItemEvent_ItemGenerator(void);

void Item_Generate_List(void);