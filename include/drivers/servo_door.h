#ifndef SERVO_DOOR_DRIVER_H
#define SERVO_DOOR_DRIVER_H

#include <ESP32Servo.h>

void servo_door_init(uint8_t pin);

void door_open();
void door_close();

bool door_is_open();

#endif // SERVO_DOOR_DRIVER_H