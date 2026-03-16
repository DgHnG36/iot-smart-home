
#include <unity.h>
#include <Arduino.h>

#include "config/config.h"
#include "utils/logger.h"
#include "drivers/pir.h"
#include "drivers/led.h"
#include "drivers/servo_door.h"
#include "system/event_queue.h"
#include "services/motion_service.h"
#include "communication/mqtt_client.h"
#include "communication/wifi_manager.h"

#define WAIT_FOR_MOTION_MS 15000
#define TIMEOUT_MARGIN_MS 1000

static bool wait_for_motion(unsigned long timeout_ms)
{
    unsigned long start = millis();
    while (millis() - start < timeout_ms)
    {
        if (pir_detected())
            return true;
        delay(50);
    }
    return false;
}

void setUp()
{
    pir_init(PIN_PIR);
    led_init(PIN_LED);
    servo_door_init(PIN_SERVO);

    event_queue_init();
    motion_service_init();

    led_off();
    door_close();
    delay(300);
}

void tearDown()
{
    led_off();
    door_close();
    delay(300);
}

void test_pir_triggers_led_and_door()
{
    log_info(">>> Di chuyển trước cảm biến PIR trong 15 giây...");

    bool detected = wait_for_motion(WAIT_FOR_MOTION_MS);
    if (!detected)
    {
        TEST_IGNORE_MESSAGE("PIR not triggered within timeout — tester action required");
        return;
    }

    event_t ev = {EVENT_MOTION_DETECTED, nullptr};
    event_queue_push(ev);

    event_t out;
    if (event_queue_pop(&out))
        motion_service_handle(&out);

    TEST_ASSERT_EQUAL_MESSAGE(HIGH, digitalRead(PIN_LED),
                              "LED should be HIGH after PIR detection");
    TEST_ASSERT_TRUE_MESSAGE(door_is_open(),
                             "Door should be open after PIR detection");
}

void test_motion_timeout_closes_door_and_turns_off_led()
{

    event_t ev = {EVENT_MOTION_DETECTED, nullptr};
    motion_service_handle(&ev);

    TEST_ASSERT_TRUE(door_is_open());
    TEST_ASSERT_EQUAL(HIGH, digitalRead(PIN_LED));

    log_info(">>> Chờ motion timeout 10s...");
    unsigned long start = millis();
    while (millis() - start < 10000 + TIMEOUT_MARGIN_MS)
    {
        motion_service_tick();
        delay(100);
    }

    TEST_ASSERT_EQUAL_MESSAGE(LOW, digitalRead(PIN_LED),
                              "LED should be LOW after motion timeout");
    TEST_ASSERT_FALSE_MESSAGE(door_is_open(),
                              "Door should be closed after motion timeout");
}

void test_pir_pin_reads_low_in_idle_environment()
{

    log_info(">>> Đứng yên 3 giây...");
    delay(3000);

    int consecutive_low = 0;
    for (int i = 0; i < 10; i++)
    {
        if (!pir_detected())
            consecutive_low++;
        delay(100);
    }

    TEST_ASSERT_GREATER_OR_EQUAL_MESSAGE(8, consecutive_low,
                                         "PIR should read LOW in idle environment (no movement)");
}

void setup()
{
    delay(2000);
    Serial.begin(115200);
    log_init();
    log_info("Starting motion integration tests...");
    log_info("Follow the prompts for each test.");

    UNITY_BEGIN();

    RUN_TEST(test_pir_pin_reads_low_in_idle_environment);
    RUN_TEST(test_pir_triggers_led_and_door);
    RUN_TEST(test_motion_timeout_closes_door_and_turns_off_led);

    UNITY_END();
}

void loop() {}