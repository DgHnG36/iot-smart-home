#ifndef DHT20_DRIVER_H
#define DHT20_DRIVER_H

#include <Wire.h>
#include <DHT20.h>

struct DHT20Data
{
    float temperature;
    float humidity;
};

void DHT20_init();
DHT20Data DHT20_read();

#endif // DHT20_DRIVER_H