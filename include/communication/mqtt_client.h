#ifndef MQTT_CLIENT_H
#define MQTT_CLIENT_H

#include <PubSubClient.h>

#include "communication/wifi_manager.h"
#include "drivers/led.h"
#include "drivers/fan.h"
#include "drivers/servo_door.h"

void mqtt_client_init();
void mqtt_client_loop();

void mqtt_client_publish_temperature(float temperature);
void mqtt_client_publish_humidity(float humidity);
void mqtt_client_publish_motion(bool motion);

#endif // MQTT_CLIENT_H