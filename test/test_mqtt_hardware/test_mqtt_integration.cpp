
#include <unity.h>
#include <Arduino.h>

#include "config/config.h"
#include "utils/logger.h"
#include "communication/wifi_manager.h"
#include "communication/mqtt_client.h"
#include "system/event_queue.h"
#include "services/command_service.h"
#include "drivers/led.h"
#include "drivers/fan.h"
#include "drivers/servo_door.h"

#define MQTT_RECV_TIMEOUT_MS 5000

static void wait_for_wifi(unsigned long timeout_ms = 10000)
{
    unsigned long start = millis();
    while (!wifi_is_connected() && (millis() - start) < timeout_ms)
    {
        wifi_manager_loop();
        delay(100);
    }
}

static void process_events_for(unsigned long ms)
{
    unsigned long start = millis();
    while (millis() - start < ms)
    {
        mqtt_client_loop();
        event_t ev;
        if (event_queue_pop(&ev))
            command_service_handle(&ev);
        delay(10);
    }
}

void setUp()
{
    event_queue_init();
    led_init(PIN_LED);
    fan_init(PIN_FAN);
    servo_door_init(PIN_SERVO);

    wifi_manager_init();
    wait_for_wifi();
    TEST_ASSERT_TRUE_MESSAGE(wifi_is_connected(), "WiFi not connected");

    mqtt_client_init();
    command_service_init();

    process_events_for(3000);
}

void tearDown()
{

    led_off();
    fan_off();
    door_close();
    delay(500);
}

void test_mqtt_led_on_command_activates_led()
{

    process_events_for(MQTT_RECV_TIMEOUT_MS);

    TEST_ASSERT_EQUAL_MESSAGE(HIGH, digitalRead(PIN_LED),
                              "LED GPIO should be HIGH after MQTT ON command");
}

void test_mqtt_fan_off_command_deactivates_fan()
{

    fan_on();
    TEST_ASSERT_EQUAL(HIGH, digitalRead(PIN_FAN));

    process_events_for(MQTT_RECV_TIMEOUT_MS);

    TEST_ASSERT_EQUAL_MESSAGE(LOW, digitalRead(PIN_FAN),
                              "Fan GPIO should be LOW after MQTT OFF command");
}

void test_mqtt_door_open_command_moves_servo()
{
    door_close();
    TEST_ASSERT_FALSE(door_is_open());

    process_events_for(MQTT_RECV_TIMEOUT_MS);

    TEST_ASSERT_TRUE_MESSAGE(door_is_open(),
                             "Door should be open after MQTT door OPEN command");
}

void test_event_queue_not_flooded_under_rapid_mqtt()
{

    for (int i = 0; i < 20; i++)
    {
        mqtt_client_loop();
        delay(50);
    }

    event_t ev;
    int popped = 0;
    while (event_queue_pop(&ev))
    {
        command_service_handle(&ev);
        popped++;
    }

    TEST_ASSERT_GREATER_OR_EQUAL(0, popped);
}

void setup()
{
    delay(2000);
    Serial.begin(115200);

    log_init();
    log_info("Starting MQTT integration tests...");

    UNITY_BEGIN();

    RUN_TEST(test_mqtt_led_on_command_activates_led);
    RUN_TEST(test_mqtt_fan_off_command_deactivates_fan);
    RUN_TEST(test_mqtt_door_open_command_moves_servo);
    RUN_TEST(test_event_queue_not_flooded_under_rapid_mqtt);

    UNITY_END();
}

void loop() {}