#include "ui/cluster_view.h"
#include <cstdio>

void ClusterView::init(lv_obj_t* parent) {
    lv_obj_t* scr = parent ? parent : lv_screen_active();
    lv_obj_set_style_bg_color(scr, lv_color_hex(0x020718), LV_PART_MAIN);

    create_header(scr);
    create_central_gauge(scr);
    create_left_panel(scr);
    create_right_panel(scr);
    create_bottom_status(scr);
}

void ClusterView::create_header(lv_obj_t* parent) {
    // Brújula: usando '>' ASCII en lugar de '▲' para evitar glifos rotos
    lv_obj_t* comp = lv_label_create(parent);
    lv_label_set_text(comp, "> SW");
    lv_obj_set_style_text_color(comp, lv_color_hex(0xBDD1F8), 0);
    lv_obj_align(comp, LV_ALIGN_TOP_LEFT, 35, 18);

    // Reloj central
    lv_obj_t* time_lbl = lv_label_create(parent);
    lv_label_set_text(time_lbl, "08:42 PM");
    lv_obj_set_style_text_font(time_lbl, &lv_font_montserrat_16, 0);
    lv_obj_set_style_text_color(time_lbl, lv_color_hex(0xFFFFFF), 0);
    lv_obj_align(time_lbl, LV_ALIGN_TOP_MID, 40, 18);

    // Temperatura exterior
    lv_obj_t* temp_lbl = lv_label_create(parent);
    lv_label_set_text(temp_lbl, "27 °C");
    lv_obj_set_style_text_color(temp_lbl, lv_color_hex(0xBDD1F8), 0);
    lv_obj_align(temp_lbl, LV_ALIGN_TOP_RIGHT, -35, 18);
}

void ClusterView::create_central_gauge(lv_obj_t* parent) {
    // 1. Arco inferior amarillo/dorado decorativo (base del gauge)
    lv_obj_t* yellow_arc = lv_arc_create(parent);
    lv_obj_set_size(yellow_arc, 300, 300);
    lv_arc_set_rotation(yellow_arc, 135);
    lv_arc_set_bg_angles(yellow_arc, 0, 70);
    lv_arc_set_range(yellow_arc, 0, 100);
    lv_arc_set_value(yellow_arc, 100);
    lv_obj_align(yellow_arc, LV_ALIGN_CENTER, 40, -10);
    lv_obj_remove_style(yellow_arc, NULL, LV_PART_KNOB);
    lv_obj_clear_flag(yellow_arc, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_style_arc_color(yellow_arc, lv_color_hex(0xF6C324), LV_PART_INDICATOR);
    lv_obj_set_style_arc_width(yellow_arc, 12, LV_PART_INDICATOR);
    lv_obj_set_style_arc_width(yellow_arc, 0, LV_PART_MAIN);

    // 2. Tacómetro principal (RPM)
    rpm_arc = lv_arc_create(parent);
    lv_obj_set_size(rpm_arc, 300, 300);
    lv_arc_set_rotation(rpm_arc, 135);
    lv_arc_set_bg_angles(rpm_arc, 0, 270);
    lv_arc_set_range(rpm_arc, 0, 6000);
    lv_arc_set_value(rpm_arc, 0);
    lv_obj_align(rpm_arc, LV_ALIGN_CENTER, 40, -10);

    lv_obj_remove_style(rpm_arc, NULL, LV_PART_KNOB);
    lv_obj_clear_flag(rpm_arc, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_style_arc_color(rpm_arc, lv_color_hex(0x0C2B68), LV_PART_MAIN);
    lv_obj_set_style_arc_width(rpm_arc, 12, LV_PART_MAIN);
    lv_obj_set_style_arc_color(rpm_arc, lv_color_hex(0x00A6FF), LV_PART_INDICATOR);
    lv_obj_set_style_arc_width(rpm_arc, 12, LV_PART_INDICATOR);

    // Texto: rpm x1000
    lv_obj_t* rpm_lbl = lv_label_create(parent);
    lv_label_set_text(rpm_lbl, "rpm x1000");
    lv_obj_set_style_text_font(rpm_lbl, &lv_font_montserrat_12, 0);
    lv_obj_set_style_text_color(rpm_lbl, lv_color_hex(0x6A84B5), 0);
    lv_obj_align(rpm_lbl, LV_ALIGN_CENTER, 40, -85);

    // Velocidad digital central
    speed_label = lv_label_create(parent);
    lv_label_set_text(speed_label, "0");
    lv_obj_set_style_text_font(speed_label, &lv_font_montserrat_48, 0);
    lv_obj_set_style_text_color(speed_label, lv_color_hex(0xFFFFFF), 0);
    lv_obj_align(speed_label, LV_ALIGN_CENTER, 40, -15);

    // Unidad km/h
    lv_obj_t* unit = lv_label_create(parent);
    lv_label_set_text(unit, "km/h");
    lv_obj_set_style_text_font(unit, &lv_font_montserrat_14, 0);
    lv_obj_set_style_text_color(unit, lv_color_hex(0x8DA4D0), 0);
    lv_obj_align(unit, LV_ALIGN_CENTER, 40, 25);
}

void ClusterView::create_left_panel(lv_obj_t* parent) {
    // Barra de Temperatura
    temp_bar = lv_bar_create(parent);
    lv_obj_set_size(temp_bar, 6, 130);
    lv_obj_align(temp_bar, LV_ALIGN_LEFT_MID, 50, 0);
    lv_bar_set_range(temp_bar, 0, 100);
    lv_bar_set_value(temp_bar, 45, LV_ANIM_OFF);
    lv_obj_set_style_bg_color(temp_bar, lv_color_hex(0x081D45), LV_PART_MAIN);
    lv_obj_set_style_bg_color(temp_bar, lv_color_hex(0x00A6FF), LV_PART_INDICATOR);

    // Letras H y C con color visible
    lv_obj_t* lbl_h = lv_label_create(parent);
    lv_label_set_text(lbl_h, "H");
    lv_obj_set_style_text_color(lbl_h, lv_color_hex(0xBDD1F8), 0);
    lv_obj_align(lbl_h, LV_ALIGN_LEFT_MID, 45, -75);

    lv_obj_t* lbl_c = lv_label_create(parent);
    lv_label_set_text(lbl_c, "C");
    lv_obj_set_style_text_color(lbl_c, lv_color_hex(0xBDD1F8), 0);
    lv_obj_align(lbl_c, LV_ALIGN_LEFT_MID, 45, 75);

    // Anillos concéntricos de eficiencia (Verde exterior, Amarillo medio, Azul interior)
    static const struct { int size; uint32_t color; int rot; int angle; } rings[] = {
        {100, 0x44D62C, 120, 240}, // Verde
        {80,  0xF6C324, 135, 220}, // Amarillo
        {60,  0x00A6FF, 150, 200}  // Azul
    };

    for (const auto& r : rings) {
        lv_obj_t* arc = lv_arc_create(parent);
        lv_obj_set_size(arc, r.size, r.size);
        lv_arc_set_rotation(arc, r.rot);
        lv_arc_set_bg_angles(arc, 0, r.angle);
        lv_arc_set_range(arc, 0, 100);
        lv_arc_set_value(arc, 100);
        lv_obj_align(arc, LV_ALIGN_LEFT_MID, 130, 15);
        lv_obj_remove_style(arc, NULL, LV_PART_KNOB);
        lv_obj_clear_flag(arc, LV_OBJ_FLAG_CLICKABLE);
        lv_obj_set_style_arc_color(arc, lv_color_hex(r.color), LV_PART_INDICATOR);
        lv_obj_set_style_arc_width(arc, 5, LV_PART_INDICATOR);
        lv_obj_set_style_arc_width(arc, 0, LV_PART_MAIN);
    }

    // Puntaje central dentro de los anillos
    lv_obj_t* score_lbl = lv_label_create(parent);
    lv_label_set_text(score_lbl, "9");
    lv_obj_set_style_text_font(score_lbl, &lv_font_montserrat_16, 0);
    lv_obj_set_style_text_color(score_lbl, lv_color_hex(0xFFFFFF), 0);
    lv_obj_align(score_lbl, LV_ALIGN_LEFT_MID, 175, 15);

    // Texto de encabezado Drive Next
    lv_obj_t* trip_title = lv_label_create(parent);
    lv_label_set_text(trip_title, "Drive Next\n. . . . . .\nCurrent Trip");
    lv_obj_set_style_text_font(trip_title, &lv_font_montserrat_14, 0);
    lv_obj_set_style_text_color(trip_title, lv_color_hex(0xFFFFFF), 0);
    lv_obj_align(trip_title, LV_ALIGN_LEFT_MID, 160, -60);

    // Lista de métricas (sustituyendo viñetas Unicode rotas por '-')
    lv_obj_t* trip_stats = lv_label_create(parent);
    lv_label_set_text(trip_stats, "- Efficiency   9\n- Driving      9\n- Safety       7");
    lv_obj_set_style_text_font(trip_stats, &lv_font_montserrat_12, 0);
    lv_obj_set_style_text_color(trip_stats, lv_color_hex(0xBDD1F8), 0);
    lv_obj_align(trip_stats, LV_ALIGN_LEFT_MID, 250, 15);
}

void ClusterView::create_right_panel(lv_obj_t* parent) {
    // Barra de Combustible
    fuel_bar = lv_bar_create(parent);
    lv_obj_set_size(fuel_bar, 6, 130);
    lv_obj_align(fuel_bar, LV_ALIGN_RIGHT_MID, -50, 0);
    lv_bar_set_range(fuel_bar, 0, 100);
    lv_bar_set_value(fuel_bar, 75, LV_ANIM_OFF);
    lv_obj_set_style_bg_color(fuel_bar, lv_color_hex(0x081D45), LV_PART_MAIN);
    lv_obj_set_style_bg_color(fuel_bar, lv_color_hex(0x00A6FF), LV_PART_INDICATOR);

    // Letras F y E visibles
    lv_obj_t* lbl_f = lv_label_create(parent);
    lv_label_set_text(lbl_f, "F");
    lv_obj_set_style_text_color(lbl_f, lv_color_hex(0xBDD1F8), 0);
    lv_obj_align(lbl_f, LV_ALIGN_RIGHT_MID, -45, -75);

    lv_obj_t* lbl_e = lv_label_create(parent);
    lv_label_set_text(lbl_e, "E");
    lv_obj_set_style_text_color(lbl_e, lv_color_hex(0xBDD1F8), 0);
    lv_obj_align(lbl_e, LV_ALIGN_RIGHT_MID, -45, 75);

    // Distance to empty
    lv_obj_t* dte_title = lv_label_create(parent);
    lv_label_set_text(dte_title, "Distance To Empty");
    lv_obj_set_style_text_color(dte_title, lv_color_hex(0xFFFFFF), 0);
    lv_obj_align(dte_title, LV_ALIGN_RIGHT_MID, -120, -30);

    dte_label = lv_label_create(parent);
    lv_label_set_text(dte_label, "[Car] ---- 295 km");
    lv_obj_set_style_text_font(dte_label, &lv_font_montserrat_14, 0);
    lv_obj_set_style_text_color(dte_label, lv_color_hex(0xBDD1F8), 0);
    lv_obj_align(dte_label, LV_ALIGN_RIGHT_MID, -100, 10);
}

void ClusterView::create_bottom_status(lv_obj_t* parent) {
    // Testigo ACC (Adaptive Cruise Control)
    acc_label = lv_label_create(parent);
    lv_label_set_text(acc_label, "ACC");
    lv_obj_set_style_text_font(acc_label, &lv_font_montserrat_16, 0);
    lv_obj_set_style_text_color(acc_label, lv_color_hex(0x00FF44), 0);
    lv_obj_align(acc_label, LV_ALIGN_BOTTOM_LEFT, 240, -30);

    // Modo CITY
    lv_obj_t* mode = lv_label_create(parent);
    lv_label_set_text(mode, "CITY");
    lv_obj_set_style_text_color(mode, lv_color_hex(0xFFFFFF), 0);
    lv_obj_align(mode, LV_ALIGN_BOTTOM_LEFT, 310, -30);

    // Testigo Freno (!)
    lv_obj_t* brake = lv_label_create(parent);
    lv_label_set_text(brake, "(!)");
    lv_obj_set_style_text_color(brake, lv_color_hex(0xFF2222), 0);
    lv_obj_align(brake, LV_ALIGN_BOTTOM_MID, 70, -30);

    // Odómetro
    odo_label = lv_label_create(parent);
    lv_label_set_text(odo_label, "ODO   487 km");
    lv_obj_set_style_text_color(odo_label, lv_color_hex(0xBDD1F8), 0);
    lv_obj_align(odo_label, LV_ALIGN_BOTTOM_RIGHT, -180, -30);
}

void ClusterView::update(const ClusterState& data) {
    char buf[16];
    snprintf(buf, sizeof(buf), "%d", static_cast<int>(data.speed_kmh));
    lv_label_set_text(speed_label, buf);

    lv_arc_set_value(rpm_arc, static_cast<int32_t>(data.engine_rpm));

    switch (data.acc_state) {
        case ACCState::OFF:
            lv_obj_add_flag(acc_label, LV_OBJ_FLAG_HIDDEN);
            break;
        case ACCState::STANDBY:
            lv_obj_clear_flag(acc_label, LV_OBJ_FLAG_HIDDEN);
            lv_obj_set_style_text_color(acc_label, lv_color_hex(0xFFA500), 0);
            break;
        case ACCState::ACTIVE:
            lv_obj_clear_flag(acc_label, LV_OBJ_FLAG_HIDDEN);
            lv_obj_set_style_text_color(acc_label, lv_color_hex(0x00FF44), 0);
            break;
        case ACCState::BRAKING_ALERT:
            lv_obj_clear_flag(acc_label, LV_OBJ_FLAG_HIDDEN);
            lv_obj_set_style_text_color(acc_label, lv_color_hex(0xFF0000), 0);
            break;
    }

    snprintf(buf, sizeof(buf), "ODO   %u km", data.odo_km);
    lv_label_set_text(odo_label, buf);

    snprintf(buf, sizeof(buf), "[Car] ---- %d km", data.distance_to_empty);
    lv_label_set_text(dte_label, buf);
}