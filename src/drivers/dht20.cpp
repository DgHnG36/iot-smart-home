#include "drivers/dht20.h"

static DHT20 dht20;

void DHT20_init()
{
    Wire.begin();
    dht20.begin();
}

DHT20Data DHT20_read()
{
    DHT20Data data;
    data.temperature = dht20.getTemperature();
    data.humidity = dht20.getHumidity();
    return data;
}