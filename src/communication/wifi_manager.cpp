#include "communication/wifi_manager.h"

static wifi_state_t wifi_state = WIFI_STATE_DISCONNECTED;

static unsigned long last_attempts = 0;
static const unsigned long RECONNECT_INTERVAL = 5000;

void wifi_manager_init()
{
    WiFi.mode(WIFI_STA);

    wifi_state = WIFI_STATE_CONNECTING;

    log_info("Wifi manager initialized");
}

static void wifi_connect()
{
    log_info("Connecting to WiFi...");

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    last_attempts = millis();

    wifi_state = WIFI_STATE_CONNECTING;
}

void wifi_manager_loop()
{
    switch (wifi_state)
    {
    case WIFI_STATE_DISCONNECTED:
        if (millis() - last_attempts > RECONNECT_INTERVAL)
        {
            wifi_connect();
        }
        break;
    case WIFI_STATE_CONNECTING:
        if (WiFi.status() == WL_CONNECTED)
        {
            log_info("WiFi connected");
            Serial.println(WiFi.localIP());

            wifi_state = WIFI_STATE_CONNECTED;
        }

        else if (millis() - last_attempts > RECONNECT_INTERVAL)
        {
            log_warn("WiFi reconnecting");
            wifi_connect();
        }

        break;
    case WIFI_STATE_CONNECTED:
        if (WiFi.status() != WL_CONNECTED)
        {
            log_warn("WiFi disconnected");
            wifi_state = WIFI_STATE_DISCONNECTED;
        }
        break;

    default:
        break;
    }
}

bool wifi_is_connected()
{
    return WiFi.status() == WL_CONNECTED;
}