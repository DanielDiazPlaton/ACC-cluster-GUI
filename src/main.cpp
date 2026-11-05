#include "lvgl/lvgl.h"
#if defined(USE_SDL)
#include "lvgl/src/drivers/sdl/lv_sdl_window.h"
#endif
#include "ui/cluster_view.h"
#include "cluster_data.h"
#include <unistd.h>

#define SCREEN_RES_X 1024
#define SCREEN_RES_Y 400

int main() {
    lv_init();

#if defined(USE_SDL)
    lv_display_t* disp = lv_sdl_window_create(SCREEN_RES_X, SCREEN_RES_Y);
    lv_sdl_window_set_title(disp, "Instrument Cluster & ACC Dashboard");
#else
    lv_display_t* disp = lv_linux_fbdev_create();
    lv_linux_fbdev_set_file(disp, "/dev/fb0");
#endif

    ClusterView cluster;
    cluster.init();

    ClusterState state;
    state.acc_state = ACCState::STANDBY;

    int tick = 0;
    while (1) {
        tick++;

        // Simulación periódica de dinámica vehicular y cambio de estado del ACC
        state.speed_kmh = 60.0f + 20.0f * (tick % 50) / 50.0f;
        state.engine_rpm = 1500.0f + (state.speed_kmh * 25.0f);

        if (tick % 200 < 100) {
            state.acc_state = ACCState::ACTIVE;
        } else {
            state.acc_state = ACCState::STANDBY;
        }

        cluster.update(state);

        uint32_t delay = lv_timer_handler();
        usleep(delay * 1000);
    }

    return 0;
}