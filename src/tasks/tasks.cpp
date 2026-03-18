#include "tasks/tasks.h"

static void sensor_task()
{
    event_t ev;

    ev.type = EVENT_SENSOR_UPDATE;
    ev.data = NULL;

    event_queue_push(ev);
}

static void motion_task()
{

    if (pir_detected())
    {
        event_t ev;

        ev.type = EVENT_MOTION_DETECTED;
        ev.data = NULL;

        event_queue_push(ev);
    }
}

static void light_sensor_task()
{
    event_t ev;
    ev.type = EVENT_LIGHT_SENSOR_UPDATE;
    ev.data = NULL;
    event_queue_push(ev);
}

void tasks_init()
{

    pir_init(PIN_PIR);

    time_manager_add(SENSOR_UPDATE_INTERVAL, sensor_task);
    time_manager_add(MOTION_UPDATE_INTERVAL, motion_task);
    time_manager_add(LIGHT_SENSOR_UPDATE_INTERVAL, light_sensor_task);
}