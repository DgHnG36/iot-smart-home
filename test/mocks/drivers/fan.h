#pragma once

#include "mock_drivers.h"

inline void fan_init(uint8_t) {}
inline void fan_on() { mock_fan_state = true; }
inline void fan_off() { mock_fan_state = false; }
inline bool fan_state() { return mock_fan_state; }
