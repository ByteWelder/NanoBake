idf_component_register(
    SRC_DIRS "src"
    "src/apps/system/system_info"
    "src/services/desktop"
    "src/services/loader"
    "src/services/gui"
    "src/services/gui/widgets"

    INCLUDE_DIRS "src"

    REQUIRES cmsis_core
        esp_lcd
        esp_lcd_touch
        esp_lvgl_port
        driver
        fatfs
        furi
        mlib
        nvs_flash
        spiffs
)

set(ASSETS_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/assets")
spiffs_create_partition_image(assets ${ASSETS_SRC_DIR} FLASH_IN_PROJECT)

set(CONFIG_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/config")
spiffs_create_partition_image(config ${CONFIG_SRC_DIR} FLASH_IN_PROJECT)
