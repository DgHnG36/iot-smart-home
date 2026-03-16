#pragma once

#include "mock_drivers.h"

struct DHT20Data
{
    float temperature;
    float humidity;
};

inline void DHT20_init() {}
inline DHT20Data DHT20_read() { return {mock_temperature, mock_humidity}; }
