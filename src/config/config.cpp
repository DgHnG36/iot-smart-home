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

const char *TOPIC_TEMP = "/feeds/bbc-temp";
const char *TOPIC_HUMIDITY = "/feeds/bbc-humidity";
const char *TOPIC_MOTION = "/feeds/bbc-motion";

const char *TOPIC_LED_CTL = "/feeds/bbc-led";
const char *TOPIC_FAN_CTL = "/feeds/bbc-fan";
const char *TOPIC_DOOR_CTL = "/feeds/bbc-door";

/* PIN CONFIG */

const uint8_t PIN_DHT20_SDA = 21;
const uint8_t PIN_DHT20_SCL = 22;

const uint8_t PIN_PIR = 4;
const uint8_t PIN_LED = 2;
const uint8_t PIN_FAN = 5;
const uint8_t PIN_SERVO = 18;

/* SCHEDULER CONFIG */

const uint32_t SENSOR_UPDATE_INTERVAL = 5000;
const uint32_t MOTION_UPDATE_INTERVAL = 200;