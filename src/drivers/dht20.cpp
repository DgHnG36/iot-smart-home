#include "drivers/dht20.h"
#include "config/config.h"

static DHT20 dht20;

void DHT20_init()
{
    Wire.begin(PIN_DHT20_SDA, PIN_DHT20_SCL);
    dht20.begin();
}

DHT20Data DHT20_read()
{
    DHT20Data data;
    dht20.read();
    delay(50);
    data.temperature = dht20.getTemperature();
    data.humidity = dht20.getHumidity();
    return data;
}