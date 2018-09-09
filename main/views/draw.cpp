#include "../ssd1306-driver/include/ssd1306.hpp"
#include <cstdint>
#include "views.hpp"
#include "draw.hpp"



enum Btn 
{
	BTN_0,
	BTN_1,
	BTN_2
};

static void drawBtn(OLED& screen, const IconBox& icon, Btn btn_num)
{
	switch(btn_num) {
	case BTN_0:
		for(int i = 0; i < ICON_SIZE; ++i) {
			uint32_t byte_mask = 0x8000;
			for(int j = 0; j < 16; ++j) {
				if(byte_mask & icon[i]) {
					screen.draw_pixel(j, i, WHITE);
				}
			}
		}
		break;
	case BTN_1: break;
	case BTN_2: break;
	}
}

void drawView(OLED& screen, const View& view)
{
	screen.clear();
	drawBtn(screen, view.btn_0, Btn::BTN_0);
}

