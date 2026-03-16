#include "communication/mqtt_client.h"

static WiFiClient wifi_client;
static PubSubClient mqttClient(wifi_client);

static void mqtt_callback(char *topic, byte *payload, unsigned int length)
{
    if (length == 0 || length >= 32)
    {
        log_error("Received MQTT message with invalid length");
        return;
    }

    char message[32];

    memcpy(message, payload, length);
    message[length] = '\0';

    log_debug("MQTT message received");

    String topicStr = String(topic);
    uint8_t val = (String(message) == "1") ? 1 : 0;

    mqtt_cmd_type_t cmd_type;

    // Led control
    if (topicStr == TOPIC_LED_CTL)
    {
        cmd_type = MQTT_CMD_LED;
    }

    // Fan control
    else if (topicStr == TOPIC_FAN_CTL)
    {
        cmd_type = MQTT_CMD_FAN;
    }

    // Door control
    else if (topicStr == TOPIC_DOOR_CTL)
    {
        cmd_type = MQTT_CMD_DOOR;
    }

    else
    {
        log_error("Received MQTT message with unknown topic");
        return;
    }

    mqtt_command_t *cmd = (mqtt_command_t *)malloc(sizeof(mqtt_command_t));
    if (!cmd)
    {
        log_error("Failed to allocate memory for MQTT command");
        return;
    }

    cmd->cmd_type = cmd_type;
    cmd->value = val;

    event_t ev;
    ev.type = EVENT_MQTT_COMMAND;
    ev.data = cmd;

    if (!event_queue_push(ev))
    {
        log_error("Failed to push MQTT command event to queue");
        free(cmd);
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

void mqtt_client_publish_temperature(float temperature)
{
    char buffer[16];

    sprintf(buffer, "%.2f", temperature);

    mqttClient.publish(TOPIC_TEMP, buffer);
}

void mqtt_client_publish_humidity(float humidity)
{
    char buffer[16];

    sprintf(buffer, "%.2f", humidity);

    mqttClient.publish(TOPIC_HUMIDITY, buffer);
}

void mqtt_client_publish_motion(bool motion)
{
    mqttClient.publish(TOPIC_MOTION, motion ? "1" : "0");
}