#include <cstdio>
#include <vector>
#include "esp_system.h"

extern "C" void app_main();

void app_main()
{
	printf("app_main starting...\n");
	esp_chip_info_t chip_info;
	esp_chip_info(&chip_info);
}
