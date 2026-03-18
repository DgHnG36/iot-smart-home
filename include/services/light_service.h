#ifndef LIGHT_SERVICE_H
#define LIGHT_SERVICE_H

#include <stdlib.h>
#include <cstdio>

#include "system/event_queue.h"
#include "drivers/light_sensor.h"
#include "drivers/led.h"
#include "utils/logger.h"

void light_service_init();
void light_service_handle(event_t *event);

#endif // LIGHT_SERVICE_H