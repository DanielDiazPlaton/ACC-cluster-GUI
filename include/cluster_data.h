#pragma once
#include <cstdint>

enum class ACCState {
    OFF = 0,
    STANDBY,
    ACTIVE,
    BRAKING_ALERT
};

struct ClusterState {
    float speed_kmh{0.0f};          // Velocidad digital central
    float engine_rpm{0.0f};         // Tacómetro analógico externo (0 - 6 x1000)
    float coolant_temp{0.5f};       // 0.0 (C) a 1.0 (H)
    float fuel_level{0.8f};         // 0.0 (E) a 1.0 (F)
    uint32_t odo_km{487};           // Odómetro
    int distance_to_empty{295};     // Autonomía restante
    
    // Señales específicas de ACC
    ACCState acc_state{ACCState::STANDBY};
    float lead_car_distance_m{35.0f}; // Distancia al vehículo líder detectada
    bool lead_car_detected{true};     // Si el radar/LiDAR detecta auto adelante
};