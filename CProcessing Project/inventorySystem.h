#pragma once

#define INVENTORY_SIZE 10
#define array_count(a) sizeof(a)/sizeof(a[INVENTORY_SIZE])
#define COLOR_RED CP_Color_Create(255, 125, 125, 255)
#define MOUSEX CP_Input_GetMouseX()
#define MOUSEY CP_Input_GetMouseY()
#define CLICKED CP_Input_MouseClicked()


void Inventory_Init(void);

void Inventory_Update(void);

void Inventory_Exit(void);

typedef struct Sword {
	int attack;
} Sword;

typedef struct Shield {
	int hp;
} Shield;




typedef enum Inventory_Type {
	InventoryTYPE_EMPTY,
	InventoryTYPE_SWORD,
	InventoryTYPE_SHIELD,

} Inventory_Type;

typedef struct Inventory_Slot {
	Inventory_Type type;
	union {
		Sword sword;
		Shield shield;
	};
} Inventory_Slot;

typedef struct Inventory {
	Inventory_Slot slots[INVENTORY_SIZE];
} Inventory;

void Print_Inventory(Inventory);

Inventory Add_Sword_To_Inventory(Inventory, int);

Inventory Add_Shield_To_Inventory(Inventory, int);

Inventory Empty_Inventory_Slot(Inventory, int);