#ifndef _VIEWS_HPP
#define _VIEWS_HPP

#include <cstdint>
#include "../input.hpp"

#define ICON_NUM 5 // Number of icons avaiable
#define ICON_SIZE 8 // Number of uint16s needed for the icon

typedef uint16_t IconBox[ICON_SIZE]; // 16 width pixes and 8 in height
typedef uint8_t ContentArea[0x300]; // 96x64 area


struct View {
	IconBox btn_0, btn_1, btn_2;
	ContentArea content;
};

extern IconBox icons[ICON_NUM];

enum View_Code
{
	SAME_VIEW,
	BACK_VIEW,
	NEW_VIEW
};

struct View_Ret
{
	View_Code retCode;
	View_Ret (*next_view)(View&, const Input);
};

View_Ret main_view(View&, const Input);
View_Ret menu_view(View&, const Input);
View_Ret bt_disc_view(View&, const Input);
View_Ret time_adj_view(View&, const Input);


#endif // _VIEWS_HPP
