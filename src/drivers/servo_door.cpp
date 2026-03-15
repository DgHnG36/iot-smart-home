#include "drivers/servo_door.h"

static Servo doorServo;
static bool doorState = false;

static int openAngle = 90;
static int closeAngle = 0;

void servo_door_init(uint8_t pin)
{
    doorServo.attach(pin);
    doorServo.write(closeAngle);
    doorState = false;
}

void door_open()
{
    doorServo.write(openAngle);
    doorState = true;
}

void door_close()
{
    doorServo.write(closeAngle);
    doorState = false;
}

bool door_is_open()
{
    return doorState;
}