deps_config := \
	/home/ryoung/esp/esp-idf/components/app_trace/Kconfig \
	/home/ryoung/esp/esp-idf/components/aws_iot/Kconfig \
	/home/ryoung/esp/esp-idf/components/bt/Kconfig \
	/home/ryoung/esp/esp-idf/components/driver/Kconfig \
	/home/ryoung/esp/esp-idf/components/esp32/Kconfig \
	/home/ryoung/esp/esp-idf/components/esp_adc_cal/Kconfig \
	/home/ryoung/esp/esp-idf/components/esp_http_client/Kconfig \
	/home/ryoung/esp/esp-idf/components/ethernet/Kconfig \
	/home/ryoung/esp/esp-idf/components/fatfs/Kconfig \
	/home/ryoung/esp/esp-idf/components/freertos/Kconfig \
	/home/ryoung/esp/esp-idf/components/heap/Kconfig \
	/home/ryoung/esp/esp-idf/components/http_server/Kconfig \
	/home/ryoung/esp/esp-idf/components/libsodium/Kconfig \
	/home/ryoung/esp/esp-idf/components/log/Kconfig \
	/home/ryoung/esp/esp-idf/components/lwip/Kconfig \
	/home/ryoung/esp/esp-idf/components/mbedtls/Kconfig \
	/home/ryoung/esp/esp-idf/components/mdns/Kconfig \
	/home/ryoung/esp/esp-idf/components/openssl/Kconfig \
	/home/ryoung/esp/esp-idf/components/pthread/Kconfig \
	/home/ryoung/esp/esp-idf/components/spi_flash/Kconfig \
	/home/ryoung/esp/esp-idf/components/spiffs/Kconfig \
	/home/ryoung/esp/esp-idf/components/tcpip_adapter/Kconfig \
	/home/ryoung/esp/esp-idf/components/vfs/Kconfig \
	/home/ryoung/esp/esp-idf/components/wear_levelling/Kconfig \
	/home/ryoung/esp/esp-idf/Kconfig.compiler \
	/home/ryoung/esp/esp-idf/components/bootloader/Kconfig.projbuild \
	/home/ryoung/esp/esp-idf/components/esptool_py/Kconfig.projbuild \
	/home/ryoung/esp/esp-idf/components/partition_table/Kconfig.projbuild \
	/home/ryoung/esp/esp-idf/Kconfig

include/config/auto.conf: \
	$(deps_config)


$(deps_config): ;
