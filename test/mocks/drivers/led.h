#pragma once

#include "mock_drivers.h"

inline void led_init(uint8_t) {}
inline void led_set(uint8_t, uint8_t, uint8_t) { mock_led_state = true; }
inline void led_set_index(uint8_t, uint8_t, uint8_t, uint8_t) { mock_led_state = true; }
inline void led_set_brightness(uint8_t brightness) { mock_led_brightness = brightness; }

inline void led_on() { mock_led_state = true; }
inline void led_off() { mock_led_state = false; }
inline void led_toggle() { mock_led_state = !mock_led_state; }

inline void led_red_on() { mock_led_state = true; }
inline void led_green_on() { mock_led_state = true; }
inline void led_blue_on() { mock_led_state = true; }
inline void led_yellow_on() { mock_led_state = true; }
inline void led_cyan_on() { mock_led_state = true; }
inline void led_purple_on() { mock_led_state = true; }
inline void led_orange_on() { mock_led_state = true; }
