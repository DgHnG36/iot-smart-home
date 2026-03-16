#ifndef COMMAND_SERVICE_H
#define COMMAND_SERVICE_H

#include <cstdlib>

#include "system/event_queue.h"
#include "drivers/led.h"
#include "drivers/fan.h"
#include "drivers/servo_door.h"
#include "utils/logger.h"

void command_service_init();
void command_service_handle(event_t *event);

#endif // COMMAND_SERVICE_H