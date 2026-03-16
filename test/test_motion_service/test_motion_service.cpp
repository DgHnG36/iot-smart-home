#include <unity.h>
#include "Arduino.h"
#include "mock_drivers.h"
#include "mock_mqtt.h"
#include "services/motion_service.h"

static event_t motion_ev = {EVENT_MOTION_DETECTED, nullptr};

void setUp()
{
    mock_drivers_reset();
    mock_mqtt_reset();
    mock_set_millis(0);
    motion_service_init();
}
void tearDown() {}

void test_activates_led_and_door()
{
    motion_service_handle(&motion_ev);
    TEST_ASSERT_TRUE(mock_led_state);
    TEST_ASSERT_TRUE(mock_door_state);
}

void test_publishes_motion_true()
{
    motion_service_handle(&motion_ev);
    TEST_ASSERT_EQUAL(1, mock_publish_motion_count);
    TEST_ASSERT_TRUE(mock_publish_motion_last);
}

void test_no_double_publish_on_repeat()
{
    motion_service_handle(&motion_ev);
    motion_service_handle(&motion_ev);
    motion_service_handle(&motion_ev);
    TEST_ASSERT_EQUAL(1, mock_publish_motion_count);
}

void test_timeout_resets_to_idle()
{
    motion_service_handle(&motion_ev);
    mock_set_millis(11000);
    motion_service_tick();
    TEST_ASSERT_FALSE(mock_led_state);
    TEST_ASSERT_FALSE(mock_door_state);
    TEST_ASSERT_FALSE(mock_publish_motion_last);
    TEST_ASSERT_EQUAL(2, mock_publish_motion_count);
}

void test_new_motion_resets_timeout()
{
    motion_service_handle(&motion_ev);
    mock_set_millis(8000);
    motion_service_handle(&motion_ev);
    mock_set_millis(16000);
    motion_service_tick();
    TEST_ASSERT_TRUE(mock_led_state);
    mock_set_millis(19000);
    motion_service_tick();
    TEST_ASSERT_FALSE(mock_led_state);
}

void test_tick_idle_does_nothing()
{
    mock_set_millis(99999);
    motion_service_tick();
    TEST_ASSERT_EQUAL(0, mock_publish_motion_count);
}

void test_reactivates_after_idle()
{
    motion_service_handle(&motion_ev);
    mock_set_millis(11000);
    motion_service_tick();
    TEST_ASSERT_FALSE(mock_led_state);
    mock_set_millis(12000);
    motion_service_handle(&motion_ev);
    TEST_ASSERT_TRUE(mock_led_state);
}

void test_ignores_other_events()
{
    event_t other = {EVENT_SENSOR_UPDATE, nullptr};
    motion_service_handle(&other);
    TEST_ASSERT_FALSE(mock_led_state);
}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_activates_led_and_door);
    RUN_TEST(test_publishes_motion_true);
    RUN_TEST(test_no_double_publish_on_repeat);
    RUN_TEST(test_timeout_resets_to_idle);
    RUN_TEST(test_new_motion_resets_timeout);
    RUN_TEST(test_tick_idle_does_nothing);
    RUN_TEST(test_reactivates_after_idle);
    RUN_TEST(test_ignores_other_events);
    return UNITY_END();
}