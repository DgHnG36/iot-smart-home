#ifndef LED_DRIVER_H
#define LED_DRIVER_H

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define LED_NUM_PIXELS 4

void led_init(uint8_t pin);

void led_set(uint8_t r, uint8_t g, uint8_t b);
void led_set_index(uint8_t index, uint8_t r, uint8_t g, uint8_t b);

void led_set_brightness(uint8_t brightness); // Used for light sensor

void led_red_on();
void led_green_on();
void led_blue_on();

void led_yellow_on();
void led_cyan_on();
void led_purple_on();
void led_orange_on();

void led_off();

#endif // LED_DRIVER_H