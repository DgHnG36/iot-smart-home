#pragma once

#include "mock_drivers.h"

inline void servo_door_init(uint8_t) {}
inline void door_open() { mock_door_state = true; }
inline void door_close() { mock_door_state = false; }
inline bool door_is_open() { return mock_door_state; }
