#include "drivers/led.h"

static Adafruit_NeoPixel _strip(LED_NUM_PIXELS, 0, NEO_GRB + NEO_KHZ800);

void led_init(uint8_t pin)
{
    new (&_strip) Adafruit_NeoPixel(LED_NUM_PIXELS, pin, NEO_GRB + NEO_KHZ800);
    _strip.begin();
    _strip.setBrightness(80);
    led_off();
}

void led_set(uint8_t r, uint8_t g, uint8_t b)
{
    _strip.fill(_strip.Color(r, g, b));
    _strip.show();
}

void led_set_index(uint8_t index, uint8_t r, uint8_t g, uint8_t b)
{
    if (index >= LED_NUM_PIXELS)
        return;
    _strip.setPixelColor(index, _strip.Color(r, g, b));
    _strip.show();
}

void led_set_brightness(uint8_t brightness)
{
    _strip.setBrightness(brightness);
    _strip.show();
}

void led_red_on()
{
    led_set(255, 0, 0);
}
void led_green_on()
{
    led_set(0, 255, 0);
}
void led_blue_on()
{
    led_set(0, 0, 255);
}

void led_yellow_on()
{
    led_set(255, 255, 0);
}
void led_cyan_on()
{
    led_set(0, 255, 255);
}
void led_purple_on()
{
    led_set(128, 0, 128);
}

void led_orange_on()
{
    led_set(255, 165, 0);
}

void led_off()
{
    led_set(0, 0, 0);
}
