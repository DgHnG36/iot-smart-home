#ifndef TIMER_MANAGER_H
#define TIMER_MANAGER_H

#include <Arduino.h>

#define _MAX_TIMERS 10

extern volatile SoftTimer timers[_MAX_TIMERS];

typedef void (*timer_callback)();
typedef struct
{
    unsigned long interval;
    unsigned long lastRun;
    timer_callback callback;
    bool enabled;
} SoftTimer;

void time_manager_init();

bool time_manager_is_expired(int timerID);

void time_manager_update();
int time_manager_add(unsigned long interval, timer_callback cb);
void time_manager_remove(int timerID);
void time_manager_update();

#endif // TIMER_MANAGER_H