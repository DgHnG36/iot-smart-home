#pragma once

#include <stdint.h>

inline const char *WIFI_SSID = "";
inline const char *WIFI_PASSWORD = "";

inline const char *MQTT_BROKER = "";
inline const int MQTT_PORT = 1883;
inline const char *MQTT_USERNAME = "";
inline const char *MQTT_KEY = "";

inline const char *TOPIC_TEMP = "";
inline const char *TOPIC_HUMIDITY = "";
inline const char *TOPIC_MOTION = "";
inline const char *TOPIC_LED_CTL = "";
inline const char *TOPIC_FAN_CTL = "";
inline const char *TOPIC_DOOR_CTL = "";

inline const uint8_t PIN_DHT20_SDA = 0;
inline const uint8_t PIN_DHT20_SCL = 0;
inline const uint8_t PIN_PIR = 0;
inline const uint8_t PIN_LED = 0;
inline const uint8_t PIN_FAN = 0;
inline const uint8_t PIN_SERVO = 0;
inline const uint8_t PIN_LIGHT_SENSOR = 0;

inline const uint32_t SENSOR_UPDATE_INTERVAL = 5000;
inline const uint32_t MOTION_UPDATE_INTERVAL = 10000;
inline const uint32_t LIGHT_SENSOR_UPDATE_INTERVAL = 7000;
