#include "services/command_service.h"

void command_service_init()
{
    led_init(PIN_LED);
    fan_init(PIN_FAN);
    servo_door_init(PIN_SERVO);
    log_info("Command service initialized");
}

void command_service_handle(event_t *event)
{
    if (event->type != EVENT_MQTT_COMMAND)
    {
        return;
    }

    mqtt_command_t *cmd = (mqtt_command_t *)event->data;
    if (!cmd)
    {
        log_error("Received null MQTT command");
        return;
    }

    switch (cmd->cmd_type)
    {
    case MQTT_CMD_LED:
        cmd->value ? led_purple_on() : led_off();
        log_debug(cmd->value ? "LED ON" : "LED OFF");
        break;

    case MQTT_CMD_FAN:
        cmd->value ? fan_on() : fan_off();
        log_debug(cmd->value ? "FAN ON" : "FAN OFF");
        break;

    case MQTT_CMD_DOOR:
        cmd->value ? door_open() : door_close();
        log_debug(cmd->value ? "DOOR OPEN" : "DOOR CLOSE");
        break;

    default:
        log_error("Received MQTT command with unknown type");
        break;
    }

    free(cmd);
}