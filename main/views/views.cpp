#include "../input.hpp"
#include "views.hpp"
#include <cstring>

IconBox icons[ICON_NUM] {
	// <<
	{0x1860, 0x38E0, 0x79E0, 0xFBE0,
	 0xFBE0, 0x79E0, 0x38E0, 0x1860},
	// >>
	{0x0618, 0x071C, 0x079E, 0x07DF,
	 0x07DF, 0x079E, 0x071C, 0x0618},
	// three bar icon
	{0xFF00, 0xFF00, 0x0000, 0xFF00,
	 0xFF00, 0x0000, 0xFF00, 0xFF00},
	// Check Mark
	{0x0001, 0x0001, 0x0003, 0x0006,
	 0x0086, 0x006C, 0x003C, 0x0018},
	// X
	{0x0081, 0x0042, 0x0024, 0x0018,
	 0x0018, 0x0024, 0x0042, 0x0081},
	// ^
	{0x3000, 0x7800, 0xfc00, 0x3000,
	 0x3000, 0x3000, 0x3000, 0x3000},
	// \/
	{0x3000, 0x3000, 0x3000, 0x3000,
	 0x3000, 0xfc00, 0x7800, 0x3000},
	// >
	{0xc000, 0xe000, 0xf000, 0xf800,
	 0xf800, 0xf000, 0xe000, 0xc000}
};

View_Ret main_view(View& view, const Input input)
{
	memcpy(view.btn_0, icons[2], sizeof(IconBox));
	memcpy(view.btn_1, icons[0], sizeof(IconBox));
	memcpy(view.btn_2, icons[1], sizeof(IconBox));



	return {SAME_VIEW, nullptr};
}

struct Menu_Item
{
	const char* name;
	View_Code code;
	View_Ret(*view)(View&, const Input);
};

#define MENU_ITEM_NUM 3
#define MENU_HEIGHT_GAP 6
#define SCREEN_MARGIN 16

Menu_Item menu_items[MENU_ITEM_NUM] = {
	{"Connect bluetooth device", NEW_VIEW, nullptr},
	{"Setup time", NEW_VIEW, nullptr},
	{"Exit", BACK_VIEW, nullptr}
};

unsigned cursor_pos = 0;

View_Ret menu_view(View& view, const Input input)
{
	memcpy(view.btn_0, icons[5], sizeof(IconBox));
	memcpy(view.btn_1, icons[6], sizeof(IconBox));
	memcpy(view.btn_2, icons[3], sizeof(IconBox));

	for(int i = 0; i < MENU_ITEM_NUM; ++i) {
		view.screen->draw_string(SCREEN_MARGIN, (i * (8 + SCREEN_MARGIN)), menu_items[i].name, BLACK, WHITE);
	}
	
	return {SAME_VIEW, nullptr};
}
