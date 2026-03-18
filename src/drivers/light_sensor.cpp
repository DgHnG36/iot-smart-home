#include "drivers/light_sensor.h"

static uint8_t pinLight;
static const int DARK_THRESHOLD = 1000;

void light_sensor_init(uint8_t pin)
{
    pinLight = pin;
    pinMode(pinLight, INPUT);
}

int light_sensor_read_raw()
{
    return analogRead(pinLight);
}

float light_sensor_read_lux()
{
    int raw = light_sensor_read_raw();
    return (1.0f - raw / 4095.0f) * 100.0f;
}
