#include "lvgl/lvgl.h"
#if defined(USE_SDL)
#include "lvgl/src/drivers/sdl/lv_sdl_window.h"
#endif
#include "ui.h"
#include <unistd.h>
#include <iostream>

#define DISPLAY_WIDTH  800
#define DISPLAY_HEIGHT 480

int main(int argc, char **argv) {
    // 1. Inicializar el core de LVGL
    lv_init();

#if defined(USE_SDL)
    // Inicializar backend SDL en host Ubuntu (LVGL v9 maneja SDL internamente)
    lv_display_t *disp = lv_sdl_window_create(DISPLAY_WIDTH, DISPLAY_HEIGHT);
    lv_sdl_window_set_title(disp, "Cluster Simulator - LVGL 9 (Ubuntu Host)");
    
    // Crear mouse simulado por SDL
    lv_indev_t *mouse = lv_sdl_mouse_create();
    lv_indev_set_display(mouse, disp);
#else
    // Backend embebido para Yocto (Linux Framebuffer o DRM)
    // Ejemplo usando Linux Framebuffer (/dev/fb0):
    lv_display_t *disp = lv_linux_fbdev_create();
    lv_linux_fbdev_set_file(disp, "/dev/fb0");
#endif

    // 2. Instanciar e inicializar la interfaz
    ClusterUI ui;
    ui.init();

    std::cout << "LVGL iniciado correctamente." << std::endl;

    // 3. Ciclo principal de eventos
    int speed_sim = 0;
    int step = 1;

    while (1) {
        // Simulación sencilla de variación de velocidad
        speed_sim += step;
        if (speed_sim >= 200 || speed_sim <= 0) {
            step = -step;
        }
        ui.updateSpeed(speed_sim);

        // Notificar el tiempo transcurrido a LVGL y procesar tareas
        uint32_t time_till_next = lv_timer_handler();
        
        // Pausa adecuada para no saturar la CPU (aprox 5ms - 10ms)
        usleep(time_till_next * 1000);
    }

    return 0;
}