#pragma once

#include "mock_drivers.h"

inline void light_sensor_init(uint8_t) {}
inline int light_sensor_read_raw() { return mock_light_raw; }
inline float light_sensor_read_lux() { return (float)mock_light_raw; }
inline bool is_light_sensor_dark() { return mock_light_raw < 500; }
