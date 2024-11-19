#include "itemSystem.h"
#include "shopSystem.h"
#include "worldSystem.h"
#include "generalUtils.h"
#include <stdlib.h>
#include <stdio.h>

#define SHOP_ITEMS 5

Item shop_items[SHOP_ITEMS] = { 0 };
char price_str[5];
int half_num_items = 0;
int generated = 0;
CP_Image star_effect;
float star_rot = 0;
CP_Font exo2;
float shop_font_size = 0.0f;

CP_Color Shop_EnoughCurrencyColor(int player_currency, int price);

void Shop_Init(void)
{
	if (!generated) generated = Item_Generate_List();
	star_effect = CP_Image_Load("Assets/Item_Art/Star Effects.png");
	Item_RandomItemGenerator(shop_items, SHOP_ITEMS);
	exo2 = CP_Font_Load("Assets/Exo2-Regular.ttf");
	CP_Font_Set(exo2);
	shop_font_size = (float)(WINDOW_HEIGHT / 24); // text size
	half_num_items = (SHOP_ITEMS % 2 == 0) ? SHOP_ITEMS / 2 : SHOP_ITEMS / 2;
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
}

void Shop_Update(void)
{
	CP_Graphics_ClearBackground(BACKGROUND_COLOR);
	// Create Boxes
	for (int i = 0; i < SHOP_ITEMS; ++i) {
		CP_Image_Draw(shop_items[i].image, 
			WINDOW_WIDTH_HALF + ((i - half_num_items) * WINDOW_WIDTH_HALF * 0.35f), 
			WINDOW_HEIGHT_HALF,
			WINDOW_WIDTH * 0.15f, WINDOW_HEIGHT * 0.3f, 255);
		CP_Image_Draw(World_GetCurrencyImage(), WINDOW_WIDTH_HALF + ((i - half_num_items) * WINDOW_WIDTH_HALF * 0.35f) - WINDOW_WIDTH * 0.025f,
			WINDOW_HEIGHT_HALF + WINDOW_HEIGHT * 0.3f, WINDOW_WIDTH * 0.05f, WINDOW_HEIGHT * 0.1f, 255);
		sprintf_s(price_str, (unsigned int)sizeof price_str, "%d", shop_items[i].price);
		CP_Settings_TextSize(shop_font_size * 1.5f);
		CP_Settings_Fill(Shop_EnoughCurrencyColor(World_GetCurrency(), shop_items[i].price));
		CP_Font_DrawText(price_str, WINDOW_WIDTH_HALF + ((i - half_num_items) * WINDOW_WIDTH_HALF * 0.35f) + WINDOW_WIDTH * 0.025f,
			WINDOW_HEIGHT_HALF + WINDOW_HEIGHT * 0.3f);
		if (CP_Input_MouseClicked() && shop_items[i].price <= World_GetCurrency() && IsAreaClicked(WINDOW_WIDTH_HALF + ((i - half_num_items) * WINDOW_WIDTH_HALF * 0.35f), WINDOW_HEIGHT_HALF,
			WINDOW_WIDTH * 0.15f, WINDOW_HEIGHT * 0.3f, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
			World_UpdateInventory(shop_items[i]);
			World_UpdateCurrency(-shop_items[i].price);
			CP_Engine_SetNextGameState(World_Init, World_Update, World_Exit);
		}

	}

	if (Draw_Textbox("SKIP >>", shop_font_size, WINDOW_WIDTH - WINDOW_WIDTH / 12.0f, WINDOW_HEIGHT - WINDOW_HEIGHT / 24.0f, WINDOW_WIDTH * 0.2f, WINDOW_HEIGHT * 0.1f,
		CP_Color_Create(200, 200, 200, 255), CP_Color_Create(0, 0, 0, 255), CP_POSITION_CENTER)) {
		if (CP_Input_MouseClicked()) {
			CP_Engine_SetNextGameState(World_Init, World_Update, World_Exit);
		}
	}

	// For hovering
	for (int i = 0; i < SHOP_ITEMS; ++i) {
		if (IsAreaClicked(WINDOW_WIDTH_HALF + ((i - half_num_items) * WINDOW_WIDTH_HALF * 0.35f), WINDOW_HEIGHT_HALF,
			WINDOW_WIDTH * 0.15f, WINDOW_HEIGHT * 0.3f, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
			Draw_Textbox(shop_items[i].name, shop_font_size, CP_Input_GetMouseX(), CP_Input_GetMouseY(), 
				WINDOW_WIDTH * 0.2f, WINDOW_HEIGHT * 0.1f,
				CP_Color_Create(200, 200, 200, 255), CP_Color_Create(0, 0, 0, 255), CP_POSITION_CORNER);

			Draw_Textbox(shop_items[i].description, shop_font_size / 2, CP_Input_GetMouseX(), CP_Input_GetMouseY() + WINDOW_HEIGHT * 0.1f,
				WINDOW_WIDTH * 0.2f, WINDOW_HEIGHT * 0.1f,
				CP_Color_Create(200, 200, 200, 255), CP_Color_Create(0, 0, 0, 255), CP_POSITION_CORNER);

			CP_Image_DrawAdvanced(star_effect, WINDOW_WIDTH_HALF + ((i - half_num_items) * WINDOW_WIDTH_HALF * 0.35f),
				WINDOW_HEIGHT_HALF,
				WINDOW_WIDTH * 0.2f, WINDOW_HEIGHT * 0.3f, 255, star_rot * DELTA_TIME);
			star_rot -= 5.0f;

		}
	}
	World_PlayerUI();
}

void Shop_Exit(void)
{
	CP_Image_Free(&star_effect);
}

CP_Color Shop_EnoughCurrencyColor(int player_currency, int price) {
	if (player_currency < price) return CP_Color_Create(128, 0, 0, 255);
	return CP_Color_Create(255, 255, 255, 255);
}