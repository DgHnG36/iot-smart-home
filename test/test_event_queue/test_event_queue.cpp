#include <unity.h>

#include "Arduino.h"
#include "system/event_queue.h"

void setUp() { event_queue_init(); }
void tearDown() {}

void test_push_pop_single_event()
{
    event_t in = {EVENT_SENSOR_UPDATE, nullptr};
    TEST_ASSERT_TRUE(event_queue_push(in));

    event_t out;
    TEST_ASSERT_TRUE(event_queue_pop(&out));
    TEST_ASSERT_EQUAL(EVENT_SENSOR_UPDATE, out.type);
}

void test_pop_empty_returns_false()
{
    event_t ev;
    TEST_ASSERT_FALSE(event_queue_pop(&ev));
}

void test_fifo_order()
{
    event_t a = {EVENT_SENSOR_UPDATE, nullptr};
    event_t b = {EVENT_MOTION_DETECTED, nullptr};
    event_t c = {EVENT_MQTT_COMMAND, nullptr};
    event_queue_push(a);
    event_queue_push(b);
    event_queue_push(c);

    event_t out;
    event_queue_pop(&out);
    TEST_ASSERT_EQUAL(EVENT_SENSOR_UPDATE, out.type);
    event_queue_pop(&out);
    TEST_ASSERT_EQUAL(EVENT_MOTION_DETECTED, out.type);
    event_queue_pop(&out);
    TEST_ASSERT_EQUAL(EVENT_MQTT_COMMAND, out.type);
}

void test_queue_full_returns_false()
{
    event_t ev = {EVENT_NONE, nullptr};
    for (int i = 0; i < _EVENT_QUEUE_SIZE; i++)
        TEST_ASSERT_TRUE(event_queue_push(ev));
    TEST_ASSERT_FALSE(event_queue_push(ev));
}

void test_push_after_pop_on_full_queue()
{
    event_t ev = {EVENT_NONE, nullptr};
    for (int i = 0; i < _EVENT_QUEUE_SIZE; i++)
        event_queue_push(ev);
    event_t out;
    event_queue_pop(&out);
    TEST_ASSERT_TRUE(event_queue_push(ev));
}

void test_data_pointer_preserved()
{
    int dummy = 42;
    event_t ev = {EVENT_MQTT_COMMAND, (void *)&dummy};
    event_queue_push(ev);
    event_t out;
    event_queue_pop(&out);
    TEST_ASSERT_EQUAL_PTR(&dummy, out.data);
    TEST_ASSERT_EQUAL(42, *(int *)out.data);
}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_push_pop_single_event);
    RUN_TEST(test_pop_empty_returns_false);
    RUN_TEST(test_fifo_order);
    RUN_TEST(test_queue_full_returns_false);
    RUN_TEST(test_push_after_pop_on_full_queue);
    RUN_TEST(test_data_pointer_preserved);
    return UNITY_END();
}