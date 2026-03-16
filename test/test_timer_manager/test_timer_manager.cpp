#include <unity.h>
#include "Arduino.h"
#include "system/timer_manager.h"

static int callback_count = 0;
static void dummy_cb() { callback_count++; }

void setUp()
{
    callback_count = 0;
    mock_set_millis(0);
    time_manager_init();
}
void tearDown() {}

void test_fires_after_interval()
{
    time_manager_add(1000, dummy_cb);
    mock_set_millis(999);
    time_manager_update();
    TEST_ASSERT_EQUAL(0, callback_count);
    mock_set_millis(1000);
    time_manager_update();
    TEST_ASSERT_EQUAL(1, callback_count);
}

void test_fires_repeatedly()
{
    time_manager_add(500, dummy_cb);
    mock_set_millis(500);
    time_manager_update();
    mock_set_millis(1000);
    time_manager_update();
    mock_set_millis(1500);
    time_manager_update();
    TEST_ASSERT_EQUAL(3, callback_count);
}

void test_remove_stops_callback()
{
    int id = time_manager_add(100, dummy_cb);
    mock_set_millis(100);
    time_manager_update();
    TEST_ASSERT_EQUAL(1, callback_count);
    time_manager_remove(id);
    mock_set_millis(200);
    time_manager_update();
    TEST_ASSERT_EQUAL(1, callback_count);
}

void test_max_timers()
{
    for (int i = 0; i < _MAX_TIMERS; i++)
        TEST_ASSERT_NOT_EQUAL(-1, time_manager_add(100, dummy_cb));
    TEST_ASSERT_EQUAL(-1, time_manager_add(100, dummy_cb));
}

void test_slot_reuse_after_remove()
{
    int id = time_manager_add(100, dummy_cb);
    time_manager_remove(id);
    TEST_ASSERT_NOT_EQUAL(-1, time_manager_add(100, dummy_cb));
}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_fires_after_interval);
    RUN_TEST(test_fires_repeatedly);
    RUN_TEST(test_remove_stops_callback);
    RUN_TEST(test_max_timers);
    RUN_TEST(test_slot_reuse_after_remove);
    return UNITY_END();
}