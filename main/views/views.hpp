#ifndef _VIEWS_HPP
#define _VIEWS_HPP

typedef unsigned IconBox[0x80]; // 16 width pixes and 8 in height
typedef unsigned ContentArea[0x1800]; // 96x64 area

struct View {
	IconBox btn_0, btn_1, btn2;
	ContentArea content;
};

void main_view();
void menu_view();
void bt_disc_view();
void time_adj_view();


#endif // _VIEWS_HPP
