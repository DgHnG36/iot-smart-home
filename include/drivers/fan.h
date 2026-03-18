#ifndef FAN_DRIVER_H
#define FAN_DRIVER_H

#include <Arduino.h>

void fan_init(uint8_t pin);

void fan_on();
void fan_off();

bool fan_state();

#endif // FAN_DRIVER_H