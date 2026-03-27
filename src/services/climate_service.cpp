#include "services/climate_service.h"

static climate_state_t current_state = CLIMATE_STATE_NORMAL;

static const float TEMP_HIGH_THRESHOLD = 30.0;
static const float TEMP_LOW_THRESHOLD = 25.0;

void climate_service_init()
{
    current_state = CLIMATE_STATE_NORMAL;
    fan_init(PIN_FAN);
    led_init(PIN_LED);
    log_info("Climate service initialized");
}

void climate_service_handle(event_t *event)
{
    if (event->type != EVENT_SENSOR_UPDATE)
    {
        return;
    }

    DHT20Data data = DHT20_read();

    float temperature = data.temperature;
    float humidity = data.humidity;
    char msg[64];
    snprintf(msg, sizeof(msg), "Climate reading: Temp=%.2f°C, Humid=%.2f%%", temperature, humidity);
    log_debug(msg);

    led_blue_on();

    mqtt_client_publish_temperature(temperature);
    mqtt_client_publish_humidity(humidity);

    switch (current_state)
    {
    case CLIMATE_STATE_NORMAL:
        if (temperature > TEMP_HIGH_THRESHOLD)
        {
            fan_on();
            led_red_on();
            log_warn("Temperature high, switching to HOT state");
            current_state = CLIMATE_STATE_HOT;
        }
        break;
    case CLIMATE_STATE_HOT:
        if (temperature < TEMP_LOW_THRESHOLD)
        {
            fan_off();
            led_green_on();
            current_state = CLIMATE_STATE_NORMAL;
            log_info("Temperature back to normal, switching to NORMAL state");
        }
        break;
    default:
        current_state = CLIMATE_STATE_NORMAL;
        break;
    }
}

/* fix added humidity later */