// #include <Arduino.h>
// #include <WiFi.h>
// #include <PubSubClient.h>
// #include <Wire.h>
// #include <DHT20.h>

// // CONFIGURATION
// #define WIFI_SSID "708H6-KH&KTMT"
// #define WIFI_PASSWORD "svkhktmt"

// #define MQTT_SERVER "io.adafruit.com"
// #define AIO_PORT 1883
// #define AIO_USERNAME "Nhom17"
// #define AIO_KEY "YOUR_AIO_KEY"

// #define LED_FEEDS "Nhom17/feeds/bbc-led"
// #define TEMP_FEEDS "Nhom17/feeds/bbc-temp"

// WiFiClient espClient;
// PubSubClient client(espClient);

// DHT20 dht20;
// volatile bool ledState = false;

// void connectWiFi()
// {
//   Serial.println("Connecting to WiFi...");
//   WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
//   uint8_t attempt = 20;
//   while (WiFi.status() != WL_CONNECTED)
//   {
//     delay(1000);
//     Serial.print(".");
//     attempt--;
//     if (attempt <= 0)
//     {
//       Serial.println("Failed to connect to WiFi, try to connect...");
//       WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
//     }
//   }
//   Serial.println("\nConnected to WiFi");
// }

// void mqttCallBack(char *topic, byte *payload, unsigned int length)
// {
//   String message = "";

//   for (int i = 0; i < length; i++)
//   {
//     message += (char)payload[i];
//   }

//   Serial.printf("Message arrived on topic: %s\n", message);

//   if (message == "1")
//   {
//     ledState = true;
//   }
//   else if (message == "0")
//   {
//     ledState = false;
//   }
// }

// void connectMQTT()
// {
//   client.setServer(MQTT_SERVER, AIO_PORT);
//   client.setCallback(mqttCallBack);

//   while (!client.connected())
//   {
//     Serial.println("Connecting to MQTT...");

//     if (client.connect("ESP32-DHT20", AIO_USERNAME, AIO_KEY))
//     {
//       Serial.println("Connected to MQTT");

//       client.subscribe(LED_FEEDS);
//     }
//     else
//     {
//       Serial.print("Failed to connect to MQTT, state: ");
//       Serial.print(client.state());
//       Serial.println(", retrying in 5 seconds...");
//       delay(5000);
//     }
//   }
// }

// void TaskLED(void *pvParameters)
// {
//   pinMode(GPIO_NUM_48, OUTPUT);
//   while (true)
//   {
//     digitalWrite(GPIO_NUM_48, ledState ? HIGH : LOW);
//     vTaskDelay(200 / portTICK_PERIOD_MS);
//   }
// }

// void TaskDHT20(void *pvParameters)
// {
//   while (true)
//   {
//     dht20.read();
//     delay(50);

//     float temp = dht20.getTemperature();
//     float hum = dht20.getHumidity();

//     Serial.print("Temperature: ");
//     Serial.print(temp);
//     Serial.print(" °C, Humidity: ");
//     Serial.print(hum);
//     Serial.println(" %");

//     char tempStr[8];
//     dtostrf(temp, 1, 2, tempStr);

//     if (client.publish("Nhom17/feeds/bbc-temp", tempStr))
//     {
//       Serial.println("Temperature published successfully");
//     }
//     else
//     {
//       Serial.println("Failed to publish temperature");
//     }
//     vTaskDelay(5000 / portTICK_PERIOD_MS);
//   }
// }

// void setup()
// {
//   Serial.begin(115200);
//   delay(2000); // Wait for Serial to initialize

//   // Initialize DHT20 sensor
//   Wire.begin(GPIO_NUM_11, GPIO_NUM_12); // SDA, SCL pins for I2C communication with DHT20
//   if (!dht20.begin())
//   {
//     Serial.println("DHT20 not found");
//   }

//   // Wifi and MQTT setup
//   connectWiFi();
//   connectMQTT();

//   // Create tasks for LED control and DHT20 reading
//   xTaskCreate(TaskDHT20, "TaskDHT20", 4096, NULL, 1, NULL);
//   xTaskCreate(TaskLED, "TaskLED", 4096, NULL, 1, NULL);
// }

// void loop()
// {

//   if (!client.connected())
//   {
//     connectMQTT();
//   }
//   client.loop();
// }

#include <Arduino.h>

#include "utils/logger.h"
#include "config/config.h"

#include "system/timer_manager.h"
#include "system/event_queue.h"

#include "tasks/tasks.h"

#include "services/climate_service.h"
#include "services/motion_service.h"
#include "services/command_service.h"

#include "communication/wifi_manager.h"
#include "communication/mqtt_client.h"

static void dispatch_event(event_t *event)
{
  climate_service_handle(event);
  motion_service_handle(event);
  command_service_handle(event);
}

void setup()
{
  log_init();

  event_queue_init();
  time_manager_init();

  wifi_manager_init();
  mqtt_client_init();

  climate_service_init();
  motion_service_init();
  command_service_init();

  tasks_init();
}

void loop()
{
  wifi_manager_loop();
  mqtt_client_loop();
  time_manager_update();
  motion_service_tick();

  event_t event;

  if (event_queue_pop(&event))
  {
    dispatch_event(&event);
  }
}