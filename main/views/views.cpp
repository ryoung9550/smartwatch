#include "../input.hpp"
#include "../time.hpp"
#include "draw.hpp"
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

const unsigned TIME_HEIGHT = (64 / 2) - (8 / 2);
const unsigned TIME_WIDTH = (128 / 2) - (42 / 2);
WatchTime watchTime({12, 0});

View_Ret main_view(View& view, const Input input)
{
	view.screen->select_font(0);
	memcpy(view.btn_0, icons[2], sizeof(IconBox));
	memcpy(view.btn_1, icons[0], sizeof(IconBox));
	memcpy(view.btn_2, icons[1], sizeof(IconBox));

	if(input.btn_0 == BTN_HI) {
		return {NEW_VIEW, menu_view};
	}

	view.screen->draw_string(TIME_WIDTH, TIME_HEIGHT, watchTime.getTime().c_str(), WHITE, BLACK);

	return {SAME_VIEW, nullptr};
}

struct Menu_Item
{
	const char* name;
	View_Code code;
	View_Ret(*view)(View&, const Input);
};

#define MENU_ITEM_NUM 3
#define MENU_HEIGHT_GAP 7
#define SCREEN_MARGIN 24

namespace TimeView {

const unsigned BEGINNING_REF = (128 / 2) - (7 * 6 / 2);
const unsigned CHAR_SPACING = 6;

unsigned short numIndex = 0; // The selected number in time

/*
 * 0 - Hours
 * 1 - Tens of Minutes
 * 2 - Ones of Minutes
 * 3 - AM = 0 --- PM = 1
 */
unsigned short timeDigits[4] {12, 0, 0, 0};

unsigned cursor_x = 0;

View_Ret time_view(View& view, const Input input)
{
	view.screen->select_font(0);
	memcpy(view.btn_0, icons[5], sizeof(IconBox));
	memcpy(view.btn_1, icons[6], sizeof(IconBox));
	memcpy(view.btn_2, icons[3], sizeof(IconBox));

	// Input Handling

	if(input.btn_0 == BTN_HI) {
		switch(numIndex) {
		case 0: 
			if(timeDigits[0] < 12) {
				++timeDigits[0];
			}
			break;
		case 1:
			if(timeDigits[1] < 5) {
				++timeDigits[1];
			}
			break;
		case 2:
			if(timeDigits[2] < 9) {
				++timeDigits[2];
			}
			break;
		case 3:
			if(timeDigits[3] == 0) {
				timeDigits[3] = 1;
			}
			break;
		}
	}

	if(input.btn_1 == BTN_HI) {
		switch(numIndex) {
		case 0:
			if(timeDigits[0] > 1) {
				--timeDigits[numIndex];
			}
			break;
		case 1:
		case 2:
		case 3:
			if(timeDigits[numIndex] > 0) {
				--timeDigits[numIndex];
			}
			break;
		}
	}

	if(input.btn_2 == BTN_HI) {
		++numIndex;
		if(numIndex > 3) {
			TimeRep retTime{0, 0};
			retTime.minutes = (timeDigits[1] * 10) + timeDigits[2];
			if(timeDigits[0] == 12) {
				timeDigits[0] = 0;
			}
			retTime.hours = timeDigits[0] + (timeDigits[3] * 12);
			watchTime.setTime(retTime);

			// Reset Values
			numIndex = 0;
			timeDigits[0] = 12;
			timeDigits[1] = 0;
			timeDigits[2] = 0;
			timeDigits[3] = 0;

			return {BACK_VIEW, nullptr};
		}
	}


	char firstDigit = (timeDigits[0] < 10) ? ' ' : '1';
	char secondDigit = '0' + timeDigits[0] % 10;
	char thirdDigit = '0' + timeDigits[1];
	char fourthDigit = '0' + timeDigits[2];
	char charTOD = timeDigits[3] == 0 ? 'A' : 'P';

	switch(numIndex) {
	case 0: cursor_x = 1; break;
	case 1: cursor_x = 3; break;
	case 2: cursor_x = 4; break;
	case 3: cursor_x = 5; break;
	}


	view.screen->draw_char(BEGINNING_REF + CHAR_SPACING * 0, TIME_HEIGHT, firstDigit, WHITE, BLACK);
	view.screen->draw_char(BEGINNING_REF + CHAR_SPACING * 1, TIME_HEIGHT, secondDigit, WHITE, BLACK);
	view.screen->draw_char(BEGINNING_REF + CHAR_SPACING * 2, TIME_HEIGHT, ':', WHITE, BLACK);
	view.screen->draw_char(BEGINNING_REF + CHAR_SPACING * 3, TIME_HEIGHT, thirdDigit, WHITE, BLACK);
	view.screen->draw_char(BEGINNING_REF + CHAR_SPACING * 4, TIME_HEIGHT, fourthDigit, WHITE, BLACK);
	view.screen->draw_char(BEGINNING_REF + CHAR_SPACING * 5, TIME_HEIGHT, charTOD, WHITE, BLACK);
	view.screen->draw_char(BEGINNING_REF + CHAR_SPACING * 6, TIME_HEIGHT, 'M', WHITE, BLACK);

	drawIcon(*view.screen, icons[5], BEGINNING_REF + CHAR_SPACING * cursor_x, TIME_HEIGHT + 10);

	return {SAME_VIEW, nullptr};
}

};

Menu_Item menu_items[MENU_ITEM_NUM] = {
	{"Connect BT device", NEW_VIEW, nullptr},
	{"Setup time", NEW_VIEW, TimeView::time_view},
	{"Exit", BACK_VIEW, nullptr}
};

unsigned cursor_pos = 0;

View_Ret menu_view(View& view, const Input input)
{
	view.screen->select_font(1);
	memcpy(view.btn_0, icons[5], sizeof(IconBox));
	memcpy(view.btn_1, icons[6], sizeof(IconBox));
	memcpy(view.btn_2, icons[3], sizeof(IconBox));

	if(input.btn_0 == BTN_HI && cursor_pos > 0) {
		--cursor_pos;
	}
	else if(input.btn_1 == BTN_HI && cursor_pos < MENU_ITEM_NUM - 1) {
		++cursor_pos;
	}
	else if(input.btn_2 == BTN_HI) {
		if(cursor_pos == (MENU_ITEM_NUM - 1)) {
			cursor_pos = 0;
			return {BACK_VIEW, nullptr};
		} else {
			return {NEW_VIEW, menu_items[cursor_pos].view};
		}
	}

	for(int i = 0; i < MENU_ITEM_NUM; ++i) {
		view.screen->draw_string(SCREEN_MARGIN, (i * (8 + MENU_HEIGHT_GAP)), menu_items[i].name, WHITE, BLACK);
	}
	drawIcon(*view.screen, icons[7], 14, (cursor_pos * (8 + MENU_HEIGHT_GAP) + 1));
	
	
	return {SAME_VIEW, nullptr};
}
