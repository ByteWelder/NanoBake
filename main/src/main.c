#include <nanobake.h>

// Hardware
#include <board_2432s024_touch.h>
#include <board_2432s024_display.h>

// Apps
#include "hello_world/hello_world.h"

void app_main(void) {
    static nb_config_t config = {
        .display_driver = &board_2432s024_create_display_driver,
        .touch_driver = &board_2432s024_create_touch_driver,
        .apps = {
            &hello_world_app
        },
        .apps_count = 1
    };

    nanobake_start(&config);
}