#ifndef LED_DRIVER_H
#define LED_DRIVER_H

#include <Arduino.h>

void led_init(uint8_t pin);

void led_on();
void led_off();

void led_toggle();

#endif