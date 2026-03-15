#include "drivers/led.h"

static uint8_t ledPin;

void led_init(uint8_t pin)
{
    ledPin = pin;
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, LOW);
}

void led_on()
{
    digitalWrite(ledPin, HIGH);
}

void led_off()
{
    digitalWrite(ledPin, LOW);
}

void led_toggle()
{
    digitalWrite(ledPin, !digitalRead(ledPin));
}