#pragma once

#include <stdbool.h>

inline int mock_publish_temp_count = 0;
inline float mock_publish_temp_last = 0.0f;

inline int mock_publish_hum_count = 0;
inline float mock_publish_hum_last = 0.0f;

inline int mock_publish_motion_count = 0;
inline bool mock_publish_motion_last = false;

void mock_mqtt_reset();