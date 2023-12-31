#include "check.h"
#include "display.h"

DisplayDevice _Nonnull* tt_display_device_alloc(DisplayDriver _Nonnull* driver) {
    DisplayDevice _Nonnull* display = malloc(sizeof(DisplayDevice));
    memset(display, 0, sizeof(DisplayDevice));
    furi_check(driver->create_display_device(display), "failed to create display");
    furi_check(display->io_handle != NULL);
    furi_check(display->display_handle != NULL);
    furi_check(display->horizontal_resolution != 0);
    furi_check(display->vertical_resolution != 0);
    furi_check(display->draw_buffer_height > 0);
    furi_check(display->bits_per_pixel > 0);
    return display;
}
