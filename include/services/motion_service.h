#ifndef MOTION_SERVICE_H
#define MOTION_SERVICE_H

#include "system/event_queue.h"
#include "communication/mqtt_client.h"
#include "utils/logger.h"

typedef enum
{
    MOTION_STATE_IDLE = 0,
    MOTION_STATE_ACTIVE
} motion_state_t;

void motion_service_init();
void motion_service_handle(event_t *event);

#endif // MOTION_SERVICE_H