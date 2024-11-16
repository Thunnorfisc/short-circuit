#include <stdio.h>
#include <stdlib.h>
#include "worldSystem.h"
#include "itemSystem.h"
#include "generalUtils.h"
#include <string.h>

#define NO_OF_ITEMS 3

Item items[20] = { 0 };
int total_items = 0;
Item random_items[NO_OF_ITEMS] = { 0 };
int list_generated = 0;
CP_Font exo2;
char const* item_addr = "Assets/Item_List.txt";
int Item_ListCount();

void ItemEvent_Init(void)
{
	if (!list_generated) {
		Item_Generate_List();
		total_items = Item_ListCount();
	}
	ItemEvent_ItemGenerator();
	exo2 = CP_Font_Load("Assets/Exo2-Regular.ttf");
	CP_Font_Set(exo2);
	float textSize = 30.0f; // text size
	CP_Settings_TextSize(textSize); //text size
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
	CP_Settings_RectMode(CP_POSITION_CENTER);
}

void ItemEvent_Update(void)
{
	CP_Graphics_ClearBackground(BACKGROUND_COLOR);;
	for (int i = 0; i < NO_OF_ITEMS; ++i) {
		if (Draw_Textbox(random_items[i].name, 30.0f, (WINDOW_WIDTH_HALF * (0.5f + i * 0.5f)),
			WINDOW_HEIGHT_HALF, WINDOW_WIDTH * 0.2f, WINDOW_HEIGHT * 0.3f,
			CP_Color_Create(200, 200, 200, 255), CP_Color_Create(0, 0, 0, 255))) {
			CP_Engine_SetNextGameState(World_Init, World_Update, World_Exit);
		}
	}
}

void ItemEvent_Exit(void)
{
	
}

void ItemEvent_ItemGenerator(void)
{
	int id = 0;
	for (int i = 0; i < NO_OF_ITEMS; ++i) {
		id = rand() % total_items + 1;
		random_items[i] = items[id - 1];
		printf("ID: %d\n", random_items[i].id);
		strcpy_s(random_items[i].name, _countof(random_items[i].name), items[id - 1].name);
	}
}

void Item_Generate_List(void)
{
	Item item = { 0 };
	FILE* item_file;
	if (fopen_s(&item_file, item_addr, "r") != 0) {
		printf("Failed to open item file\n");
		return;
	};
	int i = 0;
	
	while (fscanf_s(item_file, "%d, %[^,], %d, %lf\n", &item.id,
		item.name, (unsigned int)sizeof(item.name), &item.type, &item.modifier) == 4) {
		printf("Items: %d,%s,%d,%lf\n", item.id, item.name, item.type, item.modifier);
		items[i] = item;
		++i;
	}
	list_generated = 1;
}

int Item_ListCount() {
	int count = 0;
	for (int i = 0; items[i].id != 0; ++i) ++count;
	return count;
}

int Draw_Textbox(const char* text, float textSize, float x, float y, 
	float w, float h, CP_Color box_color, CP_Color text_color) {
	CP_Settings_Fill(box_color);
	CP_Graphics_DrawRect(x, y, w, h);
	CP_Settings_TextSize(textSize);
	CP_Settings_Fill(text_color);
	CP_Font_DrawTextBox(text, x - (w / 2), y, w);
	if (CP_Input_MouseClicked() && IsAreaClicked(x, y, w, h, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
		return 1;
	}
	return 0;
}