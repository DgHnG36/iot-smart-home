#include "drivers/fan.h"

static uint8_t fanPin;
static bool fanState = false;

void fan_init(uint8_t pin)
{
    fanPin = pin;
    pinMode(fanPin, OUTPUT);
    digitalWrite(fanPin, LOW);
}

void fan_on()
{
    digitalWrite(fanPin, HIGH);
    fanState = true;
}

void fan_off()
{
    digitalWrite(fanPin, LOW);
    fanState = false;
}

bool fan_state()
{
    return fanState;
}