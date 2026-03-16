#include "system/timer_manager.h"

volatile SoftTimer timers[_MAX_TIMERS];

void time_manager_init()
{
    int i = 0;
    for (i = 0; i < _MAX_TIMERS; ++i)
    {
        timers[i].enabled = false;
    }
}

bool time_manager_is_expired(int timerID)
{
    return timers[timerID].enabled && (millis() - timers[timerID].lastRun >= timers[timerID].interval);
}

void time_manager_update()
{
    int i = 0;
    for (i = 0; i < _MAX_TIMERS; ++i)
    {
        if (time_manager_is_expired(i))
        {
            timers[i].lastRun = millis();

            if (timers[i].callback)
            {
                timers[i].callback();
            }
        }
    }
}

int time_manager_add(unsigned long interval, timer_callback cb)
{
    for (int i = 0; i < _MAX_TIMERS; ++i)
    {
        if (!timers[i].enabled)
        {
            timers[i].interval = interval;
            timers[i].lastRun = millis();
            timers[i].callback = cb;
            timers[i].enabled = true;
            return i;
        }
    }
    return -1;
}

void time_manager_remove(int timerID)
{
    if (timerID >= 0 && timerID < _MAX_TIMERS)
    {
        timers[timerID].enabled = false;
    }
}