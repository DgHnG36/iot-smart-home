#ifndef MOTION_SERVICE_H
#define MOTION_SERVICE_H

#include "system/event_queue.h"
#include "communication/mqtt_client.h"
#include "drivers/led.h"
#include "drivers/servo_door.h"
#include "utils/logger.h"

#define MOTION_ACTIVE_TIMEOUT_MS 10000UL

typedef enum
{
    MOTION_STATE_IDLE = 0,
    MOTION_STATE_ACTIVE
} motion_state_t;

void motion_service_init();
void motion_service_handle(event_t *event);

void motion_service_tick();

#endif // MOTION_SERVICE_H