#include <unity.h>
#include "Arduino.h"
#include "mock_drivers.h"
#include "mock_mqtt.h"

#include "services/climate_service.h"

static event_t sensor_ev = {EVENT_SENSOR_UPDATE, nullptr};

void setUp()
{
    mock_drivers_reset();
    mock_mqtt_reset();
    climate_service_init();
}
void tearDown() {}

static void trigger(float t, float h)
{
    mock_temperature = t;
    mock_humidity = h;
    climate_service_handle(&sensor_ev);
}

void test_publishes_sensor_data()
{
    trigger(24.0f, 55.0f);
    TEST_ASSERT_EQUAL(1, mock_publish_temp_count);
    TEST_ASSERT_EQUAL(1, mock_publish_hum_count);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 24.0f, mock_publish_temp_last);
}

void test_fan_on_above_threshold()
{
    trigger(31.0f, 50.0f);
    TEST_ASSERT_TRUE(mock_fan_state);
}
void test_fan_off_below_threshold()
{
    trigger(28.0f, 50.0f);
    TEST_ASSERT_FALSE(mock_fan_state);
}

void test_fan_off_when_temp_normalizes()
{
    trigger(31.0f, 50.0f);
    TEST_ASSERT_TRUE(mock_fan_state);
    trigger(24.0f, 50.0f);
    TEST_ASSERT_FALSE(mock_fan_state);
}

void test_hysteresis_keeps_fan_on()
{
    trigger(31.0f, 50.0f);
    TEST_ASSERT_TRUE(mock_fan_state);
    trigger(27.0f, 50.0f);
    TEST_ASSERT_TRUE(mock_fan_state);
}

void test_ignores_other_events()
{
    event_t other = {EVENT_MOTION_DETECTED, nullptr};
    climate_service_handle(&other);
    TEST_ASSERT_EQUAL(0, mock_publish_temp_count);
    TEST_ASSERT_FALSE(mock_fan_state);
}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_publishes_sensor_data);
    RUN_TEST(test_fan_on_above_threshold);
    RUN_TEST(test_fan_off_below_threshold);
    RUN_TEST(test_fan_off_when_temp_normalizes);
    RUN_TEST(test_hysteresis_keeps_fan_on);
    RUN_TEST(test_ignores_other_events);
    return UNITY_END();
}