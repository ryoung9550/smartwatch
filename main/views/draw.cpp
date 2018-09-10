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
	size_t x_adj = 0, y_adj = 0;

	switch(btn_num) {
	case BTN_0:
		x_adj = 0;
		y_adj = 0;
		break;
	case BTN_1:
		x_adj = 0;
		y_adj = 56;
		break;
	case BTN_2: 
		x_adj = 112;
		y_adj = 56;
		break;
	}

	for(int i = 0; i < ICON_SIZE; ++i) {
		uint16_t byte_mask = 0x8000;
		for(int j = 0; j < 16; ++j) {
			if(byte_mask & icon[i]) {
				screen.draw_pixel(j + x_adj, i + y_adj, WHITE);
			}
			byte_mask = byte_mask >> 1;
		}
	}
}

void drawView(OLED& screen, const View& view)
{
	screen.clear();
	drawBtn(screen, view.btn_0, Btn::BTN_0);
	drawBtn(screen, view.btn_1, Btn::BTN_1);
	drawBtn(screen, view.btn_2, Btn::BTN_2);
	screen.refresh(true);
}

