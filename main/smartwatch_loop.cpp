#include <cstdio>
#include <stack>
#include "input.hpp"
#include "esp_system.h"
#include "views/views.hpp"
#include "views/draw.hpp"

extern "C" void app_main();

void app_main()
{
	printf("app_main starting...\n");
	esp_chip_info_t chip_info;
	esp_chip_info(&chip_info);

	Input input {BTN_LO, BTN_LO, BTN_LO};
	View view_screen;

	std::stack<View_Ret(*)(View&, const Input)> view_stack;
	// Push initial View
	view_stack.push(&main_view);
	
	while(!view_stack.empty()) {
		View_Ret retCode = view_stack.top()(view_screen, input);
		drawView(view_screen);
		switch(retCode.retCode) {
			case SAME_VIEW: break;
			case BACK_VIEW: view_stack.pop(); break;
			case NEW_VIEW: view_stack.push(retCode.next_view); break;
		}
	}
}