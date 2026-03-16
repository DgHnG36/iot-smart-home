#pragma once

#include "mock_drivers.h"

inline void led_init(uint8_t) {}
inline void led_on() { mock_led_state = true; }
inline void led_off() { mock_led_state = false; }
inline void led_toggle() { mock_led_state = !mock_led_state; }
