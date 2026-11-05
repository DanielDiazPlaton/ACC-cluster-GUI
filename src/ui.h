#ifndef UI_H
#define UI_H

#include "lvgl/lvgl.h"

class ClusterUI {
public:
    ClusterUI();
    ~ClusterUI();

    // Inicializa pantallas, estilos y widgets
    void init();

    // Método de ejemplo para actualizar datos desde lógica externa (ej. CAN)
    void updateSpeed(int speed_kmh);

private:
    lv_obj_t *speed_label;
    lv_obj_t *meter_arc;
};

#endif // UI_H