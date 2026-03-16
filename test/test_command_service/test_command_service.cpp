#include <unity.h>
#include "Arduino.h"
#include "mock_drivers.h"
#include "services/command_service.h"

void setUp()
{
    mock_drivers_reset();
    command_service_init();
}
void tearDown() {}

static event_t make_ev(mqtt_cmd_type_t type, uint8_t val)
{
    mqtt_command_t *cmd = (mqtt_command_t *)malloc(sizeof(mqtt_command_t));
    cmd->cmd_type = type;
    cmd->value = val;
    return {EVENT_MQTT_COMMAND, cmd};
}

void test_led_on()
{
    event_t e = make_ev(MQTT_CMD_LED, 1);
    command_service_handle(&e);
    TEST_ASSERT_TRUE(mock_led_state);
}
void test_led_off()
{
    mock_led_state = true;
    event_t e = make_ev(MQTT_CMD_LED, 0);
    command_service_handle(&e);
    TEST_ASSERT_FALSE(mock_led_state);
}
void test_fan_on()
{
    event_t e = make_ev(MQTT_CMD_FAN, 1);
    command_service_handle(&e);
    TEST_ASSERT_TRUE(mock_fan_state);
}
void test_fan_off()
{
    mock_fan_state = true;
    event_t e = make_ev(MQTT_CMD_FAN, 0);
    command_service_handle(&e);
    TEST_ASSERT_FALSE(mock_fan_state);
}
void test_door_open()
{
    event_t e = make_ev(MQTT_CMD_DOOR, 1);
    command_service_handle(&e);
    TEST_ASSERT_TRUE(mock_door_state);
}
void test_door_close()
{
    mock_door_state = true;
    event_t e = make_ev(MQTT_CMD_DOOR, 0);
    command_service_handle(&e);
    TEST_ASSERT_FALSE(mock_door_state);
}

void test_ignores_other_event()
{
    event_t e = {EVENT_SENSOR_UPDATE, nullptr};
    command_service_handle(&e);
    TEST_ASSERT_FALSE(mock_led_state);
    TEST_ASSERT_FALSE(mock_fan_state);
    TEST_ASSERT_FALSE(mock_door_state);
}

void test_null_data_no_crash()
{
    event_t e = {EVENT_MQTT_COMMAND, nullptr};
    command_service_handle(&e);
    TEST_PASS();
}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_led_on);
    RUN_TEST(test_led_off);
    RUN_TEST(test_fan_on);
    RUN_TEST(test_fan_off);
    RUN_TEST(test_door_open);
    RUN_TEST(test_door_close);
    RUN_TEST(test_ignores_other_event);
    RUN_TEST(test_null_data_no_crash);
    return UNITY_END();
}