#ifndef _VIEWS_HPP
#define _VIEWS_HPP

#include <cstdint>

#define ICON_NUM 5
#define ICON_SIZE 8

typedef uint16_t IconBox[ICON_SIZE]; // 16 width pixes and 8 in height
typedef uint8_t ContentArea[0x300]; // 96x64 area


struct View {
	IconBox btn_0, btn_1, btn_2;
	ContentArea content;
};

extern IconBox icons[ICON_NUM];

enum View_Codes
{
	SAME_VIEW,
	BACK_VIEW,
	NEW_VIEW
};

View_Codes main_view(View&);
View_Codes menu_view(View&);
View_Codes bt_disc_view(View&);
View_Codes time_adj_view(View&);


#endif // _VIEWS_HPP
