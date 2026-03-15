#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#include <stdint.h>

/* WIFI CONFIGURATION */

extern const char *WIFI_SSID;
extern const char *WIFI_PASSWORD;

/* MQTT CONFIGURATION */

extern const char *MQTT_BROKER;
extern const int MQTT_PORT;

extern const char *MQTT_USERNAME;
extern const char *MQTT_KEY;

/* MQTT TOPICS */

extern const char *TOPIC_TEMP;
extern const char *TOPIC_HUMIDITY;
extern const char *TOPIC_MOTION;

extern const char *TOPIC_LED_CTL;
extern const char *TOPIC_FAN_CTL;
extern const char *TOPIC_DOOR_CTL;

/* PIN CONFIG */

extern const uint8_t PIN_DHT20_SDA;
extern const uint8_t PIN_DHT20_SCL;

extern const uint8_t PIN_PIR;
extern const uint8_t PIN_LED;
extern const uint8_t PIN_FAN;
extern const uint8_t PIN_SERVO;

/* SCHEDULER CONFIG */

extern const uint32_t SENSOR_UPDATE_INTERVAL;
extern const uint32_t MOTION_UPDATE_INTERVAL;

#endif