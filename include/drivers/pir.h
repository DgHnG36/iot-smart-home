#ifndef PIR_DRIVER_H
#define PIR_DRIVER_H

#include <stdint.h>
#include <Arduino.h>

void pir_init(uint8_t pin);
bool pir_detected();

#endif // PIR_DRIVER_H