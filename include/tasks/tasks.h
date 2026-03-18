#ifndef TASKS_H
#define TASKS_H

#include "system/timer_manager.h"
#include "system/event_queue.h"

#include "drivers/pir.h"
#include "drivers/light_sensor.h"

#include "config/config.h"

void tasks_init();

#endif // TASKS_H