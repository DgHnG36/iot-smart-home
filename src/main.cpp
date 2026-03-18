#include <Arduino.h>

#include "utils/logger.h"
#include "config/config.h"

#include "system/timer_manager.h"
#include "system/event_queue.h"

#include "drivers/dht20.h"

#include "tasks/tasks.h"

#include "services/climate_service.h"
#include "services/motion_service.h"
#include "services/command_service.h"
#include "services/light_service.h"

#include "communication/wifi_manager.h"
#include "communication/mqtt_client.h"

static void dispatch_event(event_t *event)
{
  climate_service_handle(event);
  motion_service_handle(event);
  command_service_handle(event);
  light_service_handle(event);
}

void setup()
{
  log_init();

  event_queue_init();
  time_manager_init();

  DHT20_init();
  wifi_manager_init();
  mqtt_client_init();

  climate_service_init();
  motion_service_init();
  command_service_init();
  light_service_init();

  tasks_init();
}

void loop()
{
  wifi_manager_loop();
  mqtt_client_loop();
  time_manager_update();
  motion_service_tick();

  event_t event;

  if (event_queue_pop(&event))
  {
    dispatch_event(&event);
  }
}