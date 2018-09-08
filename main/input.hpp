#ifndef _INPUT_HPP
#define _INPUT_HPP

enum Button_State
{
	BTN_HI,
	BTN_LO
};

struct Input
{
	Button_State btn_0, btn_1, btn_2;
}

#endif // _INPUT_HPP
