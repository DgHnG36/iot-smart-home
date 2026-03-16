#pragma once

#include <stdint.h>
#include <stdbool.h>

inline bool mock_led_state = false;
inline bool mock_fan_state = false;
inline bool mock_door_state = false;

inline float mock_temperature = 25.0f;
inline float mock_humidity = 60.0f;
inline bool mock_pir_detected = false;

void mock_drivers_reset();
