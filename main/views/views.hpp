#ifndef _VIEWS_HPP
#define _VIEWS_HPP

#include <cstdint>

typedef uint16_t IconBox[8]; // 16 width pixes and 8 in height
typedef uint8_t ContentArea[0x300]; // 96x64 area

struct View {
	IconBox btn_0, btn_1, btn2;
	ContentArea content;
};

extern IconBox icons[5];

void main_view();
void menu_view();
void bt_disc_view();
void time_adj_view();


#endif // _VIEWS_HPP
