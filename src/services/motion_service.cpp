#include "services/motion_service.h"

static motion_state_t current_motion_state = MOTION_STATE_IDLE;

void motion_service_init()
{
    current_motion_state = MOTION_STATE_IDLE;
    log_info("Motion service initialized");
}

void motion_service_handle(event_t *event)
{
    if (event->type != EVENT_MOTION_DETECTED)
    {
        return;
    }

    switch (current_motion_state)
    {
    case MOTION_STATE_IDLE:
        log_info("Motion detected");

        led_on();
        door_open();
        mqtt_client_publish_motion(door_is_open());

        current_motion_state = MOTION_STATE_ACTIVE;
        break;
    case MOTION_STATE_ACTIVE:
        break;

    default:
        break;
    }
}