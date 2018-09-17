#include <cstdio>
#include <stack>
#include "input.hpp"
#include "esp_system.h"
#include "views/views.hpp"
#include "views/draw.hpp"
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "ssd1306-driver/include/ssd1306.hpp"

extern "C" void app_main();

Input input {BTN_LO, BTN_LO, BTN_LO};

void IRAM_ATTR btn_0_isr(void* arg)
{
	input.btn_0 = BTN_HI;
}

void IRAM_ATTR btn_1_isr(void* arg)
{
	input.btn_1 = BTN_HI;
}

void IRAM_ATTR btn_2_isr(void* arg)
{
	input.btn_2 = BTN_HI;
}

void app_main()
{
	printf("app_main starting...\n");
	esp_chip_info_t chip_info;
	esp_chip_info(&chip_info);

	gpio_pad_select_gpio(GPIO_NUM_1);
	gpio_set_direction(GPIO_NUM_1, GPIO_MODE_INPUT);
	gpio_set_intr_type(GPIO_NUM_1, GPIO_INTR_NEGEDGE);
	gpio_install_isr_service(ESP_INTR_FLAG_LOWMED);
	gpio_isr_handler_add(GPIO_NUM_1, btn_1_isr, NULL);

	gpio_pad_select_gpio(GPIO_NUM_3);
	gpio_set_direction(GPIO_NUM_3, GPIO_MODE_INPUT);
	gpio_set_intr_type(GPIO_NUM_3, GPIO_INTR_NEGEDGE);
	gpio_install_isr_service(ESP_INTR_FLAG_LOWMED);
	gpio_isr_handler_add(GPIO_NUM_3, btn_0_isr, NULL);

	gpio_pad_select_gpio(GPIO_NUM_21);
	gpio_set_direction(GPIO_NUM_21, GPIO_MODE_INPUT);
	gpio_set_intr_type(GPIO_NUM_21, GPIO_INTR_NEGEDGE);
	gpio_install_isr_service(ESP_INTR_FLAG_LOWMED);
	gpio_isr_handler_add(GPIO_NUM_21, btn_2_isr, NULL);

	// Create Screen object
	OLED screen = OLED(GPIO_NUM_19, GPIO_NUM_22, SSD1306_128x64);
	screen.init();
	screen.select_font(0);

	View view_screen;
	view_screen.screen = &screen;

	std::stack<View_Ret(*)(View&, const Input)> view_stack;
	// Push initial View
	view_stack.push(&main_view);
	
	while(!view_stack.empty()) {
		screen.clear();
		View_Ret retCode = view_stack.top()(view_screen, input);
		input.btn_0 = BTN_LO;
		input.btn_1 = BTN_LO;
		input.btn_2 = BTN_LO;
		drawView(screen, view_screen);
		switch(retCode.retCode) {
			case SAME_VIEW: break;
			case BACK_VIEW: view_stack.pop(); break;
			case NEW_VIEW: view_stack.push(retCode.next_view); break;
		}
	}
	printf("Shutting down...\n");
}
