#include "services/motion_service.h"
#include <Arduino.h>

static motion_state_t current_motion_state = MOTION_STATE_IDLE;
static unsigned long last_motion_time = 0;

void motion_service_init()
{
    current_motion_state = MOTION_STATE_IDLE;
    last_motion_time = 0;
    log_info("Motion service initialized");
}

void motion_service_handle(event_t *event)
{
    if (event->type != EVENT_MOTION_DETECTED)
    {
        return;
    }

    unsigned long current_time = millis();

    switch (current_motion_state)
    {
    case MOTION_STATE_IDLE:
        log_info("Motion detected");

        led_off();
        led_cyan_on();
        door_open();
        mqtt_client_publish_motion(door_is_open());

        last_motion_time = current_time;
        current_motion_state = MOTION_STATE_ACTIVE;
        break;
    case MOTION_STATE_ACTIVE:
        last_motion_time = current_time;
        break;

    default:
        break;
    }
}

void motion_service_tick()
{
    if (current_motion_state != MOTION_STATE_ACTIVE)
    {
        return;
    }

    if (millis() - last_motion_time >= MOTION_ACTIVE_TIMEOUT_MS)
    {
        log_info("Motion timeout, returning to IDLE");

        led_off();
        door_close();

        mqtt_client_publish_motion(door_is_open());
        current_motion_state = MOTION_STATE_IDLE;
    }
}