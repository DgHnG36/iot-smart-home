#include "communication/mqtt_client.h"

static WiFiClient wifi_client;
static PubSubClient mqttClient(wifi_client);

static void mqtt_callback(char *topic, byte *payload, unsigned int length)
{
    char message[32];

    memcpy(message, payload, length);
    message[length] = '\0';

    log_debug("MQTT message received");

    String topicStr = String(topic);
    String messageStr = String(message);

    // Led control
    if (topicStr == TOPIC_LED_CTL)
    {
        if (messageStr == "1")
        {
            led_on();
            log_debug("Turning LED on");
        }
        else if (messageStr == "0")
        {
            led_off();
            log_debug("Turning LED off");
        }
    }

    // Fan control
    if (topicStr == TOPIC_FAN_CTL)
    {
        if (messageStr == "1")
        {
            fan_on();
            log_debug("Turning fan on");
        }
        else if (messageStr == "0")
        {
            fan_off();
            log_debug("Turning fan off");
        }
    }

    // Door control
    if (topicStr == TOPIC_DOOR_CTL)
    {
        if (messageStr == "1")
        {
            door_open();
            log_info("Open door");
        }
        else if (messageStr == "0")
        {
            door_close();
            log_info("Close door");
        }
    }
}

static void mqtt_connect()
{
    if (!wifi_is_connected())
    {
        log_debug("WiFi not connected, cannot connect to MQTT broker");
        return;
    }

    if (mqttClient.connected())
    {
        return;
    }

    log_info("Connecting to MQTT broker...");

    if (mqttClient.connect("iot-smart-home", MQTT_USERNAME, MQTT_KEY))
    {
        log_info("Connected to MQTT broker");
        mqttClient.subscribe(TOPIC_LED_CTL);
        mqttClient.subscribe(TOPIC_FAN_CTL);
        mqttClient.subscribe(TOPIC_DOOR_CTL);
    }
    else
    {
        log_error("MQTT connection failed");
    }
}

void mqtt_client_init()
{
    mqttClient.setServer(MQTT_BROKER, MQTT_PORT);
    mqttClient.setCallback(mqtt_callback);
}

void mqtt_client_loop()
{
    mqtt_connect();
    mqttClient.loop();
}

void mqtt_publish_temperature(float temperature)
{
    char buffer[16];

    sprintf(buffer, "%.2f", temperature);

    mqttClient.publish(TOPIC_TEMP, buffer);
}

void mqtt_publish_humidity(float humidity)
{
    char buffer[16];

    sprintf(buffer, "%.2f", humidity);

    mqttClient.publish(TOPIC_HUMIDITY, buffer);
}

void mqtt_publish_motion(bool motion)
{
    if (motion)
        mqttClient.publish(TOPIC_MOTION, "1");
    else
        mqttClient.publish(TOPIC_MOTION, "0");
}