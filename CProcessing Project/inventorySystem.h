#pragma once
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
	Inventory_Slot slots[5];
} Inventory;

Inventory Add_Sword_To_Inventory(Inventory, int, int);

Inventory Add_Shield_To_Inventory(Inventory, int, int);

Inventory Empty_Inventory_Slot(Inventory, int);

void Print_Inventory(Inventory);