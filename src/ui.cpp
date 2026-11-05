#include "ui.h"
#include <cstdio>

ClusterUI::ClusterUI() : speed_label(nullptr), meter_arc(nullptr) {}

ClusterUI::~ClusterUI() {}

void ClusterUI::init() {
    // Obtener la pantalla activa
    lv_obj_t *scr = lv_screen_active();
    lv_obj_set_style_bg_color(scr, lv_color_hex(0x10141A), LV_PART_MAIN);

    // Crear un indicador circular (Arc)
    meter_arc = lv_arc_create(scr);
    lv_obj_set_size(meter_arc, 220, 220);
    lv_arc_set_rotation(meter_arc, 135);
    lv_arc_set_bg_angles(meter_arc, 0, 270);
    lv_arc_set_range(meter_arc, 0, 220);
    lv_arc_set_value(meter_arc, 0);
    lv_obj_center(meter_arc);
    lv_obj_remove_style(meter_arc, NULL, LV_PART_KNOB); // Quita el selector táctil
    lv_obj_clear_flag(meter_arc, LV_OBJ_FLAG_CLICKABLE);

    // Etiqueta numérica de velocidad
    speed_label = lv_label_create(scr);
    lv_label_set_text(speed_label, "0");
    lv_obj_set_style_text_font(speed_label, &lv_font_montserrat_48, LV_PART_MAIN);
    lv_obj_set_style_text_color(speed_label, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
    lv_obj_align(speed_label, LV_ALIGN_CENTER, 0, -10);

    // Etiqueta de unidades (km/h)
    lv_obj_t *unit_label = lv_label_create(scr);
    lv_label_set_text(unit_label, "km/h");
    lv_obj_set_style_text_font(unit_label, &lv_font_montserrat_16, LV_PART_MAIN);
    lv_obj_set_style_text_color(unit_label, lv_color_hex(0x888888), LV_PART_MAIN);
    lv_obj_align(unit_label, LV_ALIGN_CENTER, 0, 30);
}

void ClusterUI::updateSpeed(int speed_kmh) {
    if (meter_arc && speed_label) {
        lv_arc_set_value(meter_arc, speed_kmh);
        
        char buf[16];
        snprintf(buf, sizeof(buf), "%d", speed_kmh);
        lv_label_set_text(speed_label, buf);
    }
}