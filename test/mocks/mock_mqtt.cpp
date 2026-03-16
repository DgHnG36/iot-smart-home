#include "mock_mqtt.h"

void mock_mqtt_reset()
{
    mock_publish_temp_count = 0;
    mock_publish_temp_last = 0.0f;
    mock_publish_hum_count = 0;
    mock_publish_hum_last = 0.0f;
    mock_publish_motion_count = 0;
    mock_publish_motion_last = false;
}
