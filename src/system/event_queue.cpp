#include "system/event_queue.h"

static event_t event_queue[_EVENT_QUEUE_SIZE];

static volatile int head = 0;
static volatile int tail = 0;
static volatile int count = 0;

void event_queue_init()
{
    head = 0;
    tail = 0;
    count = 0;
}

bool event_queue_push(event_t event)
{
    if (count >= _EVENT_QUEUE_SIZE)
    {
        return false;
    }

    event_queue[tail] = event;
    tail = (tail + 1) % _EVENT_QUEUE_SIZE;
    count++;

    return true;
}

bool event_queue_pop(event_t *event)
{
    if (count <= 0)
    {
        return false;
    }

    *event = event_queue[head];
    head = (head + 1) % _EVENT_QUEUE_SIZE;
    count--;

    return true;
}
