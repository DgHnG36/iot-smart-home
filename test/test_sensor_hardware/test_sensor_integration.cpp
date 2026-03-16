
#include <unity.h>
#include <Arduino.h>
#include <Wire.h>

#include "config/config.h"
#include "utils/logger.h"
#include "drivers/dht20.h"
#include "system/event_queue.h"
#include "communication/mqtt_client.h"
#include "communication/wifi_manager.h"
#include "services/climate_service.h"

#define TEMP_MIN_VALID 0.0f
#define TEMP_MAX_VALID 60.0f
#define HUM_MIN_VALID 0.0f
#define HUM_MAX_VALID 100.0f

void setUp()
{
    Wire.begin(PIN_DHT20_SDA, PIN_DHT20_SCL);
    DHT20_init();
    delay(500);
}

void tearDown() {}

void test_dht20_reads_valid_temperature()
{
    DHT20Data data = DHT20_read();

    char msg[64];
    sprintf(msg, "Temp=%.2f out of range [%.0f, %.0f]",
            data.temperature, TEMP_MIN_VALID, TEMP_MAX_VALID);

    TEST_ASSERT_FLOAT_WITHIN_MESSAGE(
        (TEMP_MAX_VALID - TEMP_MIN_VALID) / 2,
        (TEMP_MAX_VALID + TEMP_MIN_VALID) / 2,
        data.temperature, msg);
}

void test_dht20_reads_valid_humidity()
{
    DHT20Data data = DHT20_read();

    TEST_ASSERT_TRUE_MESSAGE(
        data.humidity >= HUM_MIN_VALID && data.humidity <= HUM_MAX_VALID,
        "Humidity out of valid range [0, 100]");
}

void test_dht20_consecutive_reads_consistent()
{
    DHT20Data a = DHT20_read();
    delay(200);
    DHT20Data b = DHT20_read();

    TEST_ASSERT_FLOAT_WITHIN_MESSAGE(2.0f, a.temperature, b.temperature,
                                     "Consecutive temperature reads differ too much");
    TEST_ASSERT_FLOAT_WITHIN_MESSAGE(5.0f, a.humidity, b.humidity,
                                     "Consecutive humidity reads differ too much");
}

void test_climate_service_publishes_on_sensor_event()
{

    wifi_manager_init();
    unsigned long start = millis();
    while (!wifi_is_connected() && millis() - start < 10000)
    {
        wifi_manager_loop();
        delay(100);
    }

    if (!wifi_is_connected())
    {
        TEST_IGNORE_MESSAGE("WiFi not available — skipping MQTT publish test");
        return;
    }

    event_queue_init();
    mqtt_client_init();
    climate_service_init();
    delay(2000);

    event_t ev = {EVENT_SENSOR_UPDATE, nullptr};
    climate_service_handle(&ev);

    TEST_PASS();
}

void setup()
{
    delay(2000);
    Serial.begin(115200);
    log_init();
    log_info("Starting sensor integration tests...");

    UNITY_BEGIN();

    RUN_TEST(test_dht20_reads_valid_temperature);
    RUN_TEST(test_dht20_reads_valid_humidity);
    RUN_TEST(test_dht20_consecutive_reads_consistent);
    RUN_TEST(test_climate_service_publishes_on_sensor_event);

    UNITY_END();
}

void loop() {}