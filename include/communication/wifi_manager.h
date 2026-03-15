#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <WiFi.h>

#include "config/config.h"
#include "utils/logger.h"

typedef enum
{
    WIFI_STATE_DISCONNECTED = 0,
    WIFI_STATE_CONNECTING,
    WIFI_STATE_CONNECTED
} wifi_state_t;

void wifi_manager_init();
void wifi_manager_loop();

bool wifi_is_connected();

#endif // WIFI_MANAGER_H