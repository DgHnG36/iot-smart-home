#pragma once

#include <stdint.h>
#include <stdbool.h>

inline bool mock_led_state = false;
inline bool mock_fan_state = false;
inline bool mock_door_state = false;
inline uint8_t mock_led_brightness = 0;

inline float mock_temperature = 25.0f;
inline float mock_humidity = 60.0f;
inline bool mock_pir_detected = false;
inline int mock_light_raw = 3000;

void mock_drivers_reset();
