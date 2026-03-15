#include "drivers/pir.h"

static uint8_t pirPin;

void pir_init(uint8_t pin)
{
    pirPin = pin;
    pinMode(pirPin, INPUT);
}

bool pir_detected()
{
    return digitalRead(pirPin) == HIGH;
}