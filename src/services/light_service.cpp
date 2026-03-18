#include "services/light_service.h"

static const int RAW_DARK = 300;
static const int RAW_BRIGHT = 3000;

static const uint8_t MAX_BRIGHTNESS = 255;
static const uint8_t MIN_BRIGHTNESS = 20;

static uint8_t last_brightness = 0;

static uint8_t map_clamp(int value, int in_min, int in_max,
                         uint8_t out_min, uint8_t out_max)
{
    if (value <= in_min)
        return out_max;
    if (value >= in_max)
        return out_min;

    long mapped = (long)(in_max - value) * (out_max - out_min) / (in_max - in_min) + out_min;
    return (uint8_t)mapped;
}

void light_service_init()
{
    last_brightness = 0;
    led_orange_on();
    log_info("Light service initialized");
}

void light_service_handle(event_t *event)
{
    if (event->type != EVENT_LIGHT_SENSOR_UPDATE)
        return;

    int raw = light_sensor_read_raw();
    uint8_t brightness = map_clamp(raw, RAW_DARK, RAW_BRIGHT,
                                   MIN_BRIGHTNESS, MAX_BRIGHTNESS);

    if (abs((int)brightness - (int)last_brightness) < 5)
        return;

    last_brightness = brightness;
    led_set_brightness(brightness);

    char msg[48];
    sprintf(msg, "Light raw=%d brightness=%d", raw, brightness);
    log_debug(msg);
}