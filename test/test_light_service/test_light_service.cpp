#include <unity.h>
#include "Arduino.h"
#include "mock_drivers.h"

#include "services/light_service.h"

static event_t light_ev = {EVENT_LIGHT_SENSOR_UPDATE, nullptr};

void setUp()
{
    mock_drivers_reset();
    light_service_init();
}
void tearDown() {}

void test_init_turns_led_on()
{
    TEST_ASSERT_TRUE(mock_led_state);
}

void test_ignores_other_events()
{
    mock_led_brightness = 123;
    event_t other = {EVENT_SENSOR_UPDATE, nullptr};
    light_service_handle(&other);
    TEST_ASSERT_EQUAL_UINT8(123, mock_led_brightness);
}

void test_dark_raw_maps_to_max_brightness()
{
    mock_light_raw = 300;
    light_service_handle(&light_ev);
    TEST_ASSERT_EQUAL_UINT8(255, mock_led_brightness);
}

void test_bright_raw_maps_to_min_brightness()
{
    mock_light_raw = 3000;
    light_service_handle(&light_ev);
    TEST_ASSERT_EQUAL_UINT8(20, mock_led_brightness);
}

void test_small_brightness_change_is_ignored()
{
    mock_light_raw = 1650;
    light_service_handle(&light_ev);
    TEST_ASSERT_EQUAL_UINT8(137, mock_led_brightness);

    mock_light_raw = 1600;
    light_service_handle(&light_ev);
    TEST_ASSERT_EQUAL_UINT8(137, mock_led_brightness);
}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_init_turns_led_on);
    RUN_TEST(test_ignores_other_events);
    RUN_TEST(test_dark_raw_maps_to_max_brightness);
    RUN_TEST(test_bright_raw_maps_to_min_brightness);
    RUN_TEST(test_small_brightness_change_is_ignored);
    return UNITY_END();
}
