#pragma once

#include "mock_mqtt.h"

inline void mqtt_client_init() {}
inline void mqtt_client_loop() {}

inline void mqtt_client_publish_temperature(float v)
{
    mock_publish_temp_count++;
    mock_publish_temp_last = v;
}

inline void mqtt_client_publish_humidity(float v)
{
    mock_publish_hum_count++;
    mock_publish_hum_last = v;
}

inline void mqtt_client_publish_motion(bool v)
{
    mock_publish_motion_count++;
    mock_publish_motion_last = v;
}
