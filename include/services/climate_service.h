#ifndef CLIMATE_SERVICE_H
#define CLIMATE_SERVICE_H

#include <cstdio>

#include "config/config.h"
#include "system/event_queue.h"
#include "drivers/dht20.h"
#include "drivers/fan.h"
#include "drivers/led.h"
#include "communication/mqtt_client.h"
#include "utils/logger.h"

typedef enum
{
    CLIMATE_STATE_NORMAL,
    CLIMATE_STATE_HOT

} climate_state_t;

void climate_service_init();

void climate_service_handle(event_t *event);

#endif // CLIMATE_SERVICE_H