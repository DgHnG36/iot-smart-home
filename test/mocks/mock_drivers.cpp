#include "mock_drivers.h"

void mock_drivers_reset()
{
    mock_led_state = false;
    mock_fan_state = false;
    mock_door_state = false;
    mock_temperature = 25.0f;
    mock_humidity = 60.0f;
    mock_pir_detected = false;
}