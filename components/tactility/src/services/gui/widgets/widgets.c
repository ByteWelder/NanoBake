#include "widgets.h"

void lv_obj_set_style_bg_blacken(lv_obj_t* obj) {
    lv_obj_set_style_bg_color(obj, lv_color_black(), 0);
    lv_obj_set_style_border_color(obj, lv_color_black(), 0);
}

void lv_obj_set_style_bg_invisible(lv_obj_t* obj) {
    lv_obj_set_style_bg_opa(obj, 0, 0);
    lv_obj_set_style_border_opa(obj, 0, 0);
}

void lv_obj_set_style_no_padding(lv_obj_t* obj) {
    lv_obj_set_style_pad_all(obj, LV_STATE_DEFAULT, 0);
    lv_obj_set_style_pad_gap(obj, LV_STATE_DEFAULT, 0);
}
