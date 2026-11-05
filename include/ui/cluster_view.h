#pragma once
#include "lvgl/lvgl.h"
#include "cluster_data.h"

class ClusterView {
public:
    void init(lv_obj_t* parent = nullptr);
    void update(const ClusterState& data);

private:
    void create_header(lv_obj_t* parent);
    void create_central_gauge(lv_obj_t* parent);
    void create_left_panel(lv_obj_t* parent);
    void create_right_panel(lv_obj_t* parent);
    void create_bottom_status(lv_obj_t* parent);

    // Widgets dinámicos
    lv_obj_t* speed_label{nullptr};
    lv_obj_t* rpm_arc{nullptr};
    lv_obj_t* acc_label{nullptr};
    lv_obj_t* temp_bar{nullptr};
    lv_obj_t* fuel_bar{nullptr};
    lv_obj_t* odo_label{nullptr};
    lv_obj_t* dte_label{nullptr};
};