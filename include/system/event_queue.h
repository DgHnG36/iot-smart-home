#ifndef EVENT_QUEUE_H
#define EVENT_QUEUE_H

#define _EVENT_QUEUE_SIZE 16

typedef enum
{
    EVENT_NONE = 0,
    EVENT_SENSOR_UPDATE,
    EVENT_MOTION_DETECTED,

    EVENT_MQTT_CONNECTED,
    EVENT_MQTT_COMMAND
} event_type_t;

typedef struct
{
    event_type_t type;
    void *data;
} event_t;

void event_queue_init();

bool event_queue_push(event_t event);
bool event_queue_pop(event_t *event);

#endif
