#ifndef MQTT_CLIENT_H
#define MQTT_CLIENT_H

#include <PubSubClient.h>

#include "communication/wifi_manager.h"
#include "system/event_queue.h"
#include "utils/logger.h"

void mqtt_client_init();
void mqtt_client_loop();

void mqtt_client_publish_temperature(float temperature);
void mqtt_client_publish_humidity(float humidity);
void mqtt_client_publish_motion(bool motion);

#endif // MQTT_CLIENT_H