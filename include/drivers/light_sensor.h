#ifndef LIGHT_SENSOR_H
#define LIGHT_SENSOR_H

#include <Arduino.h>

void light_sensor_init(uint8_t pin);
int light_sensor_read_raw();
float light_sensor_read_lux();
bool is_light_sensor_dark();

#endif