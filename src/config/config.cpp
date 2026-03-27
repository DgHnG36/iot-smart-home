#include "config/config.h"

/* WIFI CONFIGURATION */

const char *WIFI_SSID = "";
const char *WIFI_PASSWORD = "";

/* MQTT CONFIGURATION */

const char *MQTT_BROKER = "io.adafruit.com";
const int MQTT_PORT = 1883;

const char *MQTT_USERNAME = "Nhom17";
const char *MQTT_KEY = "";

/* MQTT TOPICS */

const char *TOPIC_TEMP = "Nhom17/feeds/bbc-temp";
const char *TOPIC_HUMIDITY = "Nhom17/feeds/bbc-humidity";
const char *TOPIC_MOTION = "Nhom17/feeds/bbc-motion";

const char *TOPIC_LED_CTL = "Nhom17/feeds/bbc-led";
const char *TOPIC_FAN_CTL = "Nhom17/feeds/bbc-fan";
const char *TOPIC_DOOR_CTL = "Nhom17/feeds/bbc-door";

// const char *TOPIC_TEMP = "";
// const char *TOPIC_HUMIDITY = "";
// const char *TOPIC_MOTION = "";

// const char *TOPIC_LED_CTL = "";
// const char *TOPIC_FAN_CTL = "";
// const char *TOPIC_DOOR_CTL = "";

/* PIN CONFIG */

const uint8_t PIN_DHT20_SDA = GPIO_NUM_11;
const uint8_t PIN_DHT20_SCL = GPIO_NUM_12;

const uint8_t PIN_PIR = GPIO_NUM_6;
const uint8_t PIN_LED = GPIO_NUM_18;
const uint8_t PIN_FAN = GPIO_NUM_10;
const uint8_t PIN_SERVO = GPIO_NUM_5;
const uint8_t PIN_LIGHT_SENSOR = GPIO_NUM_9;

/* SCHEDULER CONFIG */

const uint32_t SENSOR_UPDATE_INTERVAL = 10000;
const uint32_t MOTION_UPDATE_INTERVAL = 12000;
const uint32_t LIGHT_SENSOR_UPDATE_INTERVAL = 7000;