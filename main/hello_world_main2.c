/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "driver/gpio.h"
#include "driver/i2c.h"

#define DELAY(_cycles) for(size_t i = 0; i < _cycles; ++i)

void app_main_alt()
{
	printf("app_main starting...\n");
    /* Print chip information */
    esp_chip_info_t chip_info;
    esp_chip_info(&chip_info);
    printf("This is ESP32 chip with %d CPU cores, WiFi%s%s, ",
            chip_info.cores,
            (chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "",
            (chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "");

    printf("silicon revision %d, ", chip_info.revision);

    printf("%dMB %s flash\n", spi_flash_get_chip_size() / (1024 * 1024),
            (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");

	// GPIO setup
	gpio_config_t gpioConf;
	gpioConf.pin_bit_mask = GPIO_SEL_0;
	gpioConf.mode = GPIO_MODE_OUTPUT;
	gpioConf.pull_up_en = GPIO_PULLUP_DISABLE;
	gpioConf.pull_down_en = GPIO_PULLDOWN_DISABLE;
	gpioConf.intr_type = GPIO_INTR_DISABLE;

	if(gpio_config(&gpioConf) != ESP_OK) {
		printf("ERROR: GPIO config failed to pass!\n");
	} else {
		printf("Success: GPIO config passed!\n");
	}

	// I2C setup

	i2c_config_t i2cConf;
	i2cConf.mode = I2C_MODE_MASTER;
	i2cConf.sda_io_num = GPIO_NUM_34;
	i2cConf.sda_pullup_en = GPIO_PULLUP_ENABLE;
	i2cConf.scl_io_num = GPIO_NUM_35;
	i2cConf.scl_pullup_en = GPIO_PULLUP_ENABLE;
	i2cConf.master.clk_speed = 100;

	if(i2c_param_config(I2C_NUM_0, &i2cConf) != ESP_OK) {
		printf("ERROR: I2C config failed to pass!\n");
	} else {
		printf("Success: GPIO config passed!\n");
	}

	//i2c_driver_install(I2C_NUM_0, I2C_CMD_WRITE, 


	// Main program loop
	for(;;)
	{
		gpio_set_level(GPIO_NUM_0, 0);
		DELAY(10000000);
		gpio_set_level(GPIO_NUM_0, 1);
		DELAY(10000000);
	}


    for (int i = 10; i >= 0; i--) {
        printf("Restarting in %d seconds...\n", i);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    printf("Restarting now.\n");
    fflush(stdout);
    esp_restart();
}
