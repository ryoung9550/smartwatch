#ifndef _DRAW_HPP
#define _DRAW_HPP

#include "../ssd1306-driver/include/ssd1306.hpp"
#include "views.hpp"

void drawView(OLED& screen, const View&);
void drawIcon(OLED& screen, const IconBox& icon, const unsigned& x_adj, const unsigned& y_adj);

#endif // _DRAW_HPP
