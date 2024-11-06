#pragma once
#define INVENTORY_SIZE 10
#define array_count(a) sizeof(a)/sizeof(a[INVENTORY_SIZE])
#define COLOR_RED CP_Color_Create(255, 125, 125, 255)
#define COLOR_BLACK CP_Color_Create(0, 0, 0, 255)
#define COLOR_GREY CP_Color_Create(100, 100, 100, 255)

void Inventory_Init(void);

void Inventory_Update(void);

void Inventory_Exit(void);



typedef struct Sword {
	int attack;
} Sword;

typedef struct Shield {
	int defense;
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

Inventory Add_Sword_To_Inventory(Inventory, int, int);

Inventory Add_Shield_To_Inventory(Inventory, int, int);

Inventory Empty_Inventory_Slot(Inventory, int);

void Print_Inventory(Inventory);