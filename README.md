# IoT YOLO-UNO Smart Home

![PlatformIO](https://img.shields.io/badge/PlatformIO-Embedded-orange?logo=platformio&logoColor=white)
![C++](https://img.shields.io/badge/C%2B%2B-23-blue?logo=c%2B%2B&logoColor=white)
![Framework](https://img.shields.io/badge/Framework-Arduino-00979D?logo=arduino&logoColor=white)
![Board](https://img.shields.io/badge/Board-ESP32--S3-green)
![Tests](https://img.shields.io/badge/Tests-Unity-informational)
![License](https://img.shields.io/badge/License-MIT-lightgrey)

An IoT smart home project built for the YOLO-UNO / ESP32-S3 board using the Arduino framework and PlatformIO. The system is organized into modules for Wi-Fi, MQTT, climate monitoring, motion detection, command handling, and event queue processing.

## Main Features

- Read temperature and humidity from the DHT20 sensor.
- Detect motion using a PIR sensor.
- Control the LED, fan, and servo door through MQTT commands.
- Publish sensor readings and motion status to an MQTT broker.
- Support both native unit tests and on-device hardware integration tests with Unity.

## PlatformIO Environments

- `yolo_uno`: builds and uploads the firmware for the real device.
- `native`: runs unit tests locally with mocks.
- `yolo_uno_test`: runs hardware integration tests on the real board.

## Requirements

- VS Code with PlatformIO IDE, or PlatformIO Core (`pio`).
- A YOLO-UNO / ESP32-S3 board.
- Sensors and actuators connected according to the configured pins.
- A working Wi-Fi network and MQTT broker for real-device execution.

## Configure Before Running on Real Hardware

Update the Wi-Fi and MQTT settings in `src/config/config.cpp`:

```cpp
const char *WIFI_SSID = "";       // Your Wi-Fi SSID
const char *WIFI_PASSWORD = "";   // Your Wi-Fi password

const char *MQTT_BROKER = "";     // Your MQTT broker host
const int MQTT_PORT = 1883;
const char *MQTT_USERNAME = "";   // Your MQTT username
const char *MQTT_KEY = "";        // Your MQTT password or API key
```

If needed, also adjust the MQTT topics and GPIO pin mapping in the same file to match your hardware setup.

## Run on Real Hardware

### 1. Build the Firmware

```bash
pio run -e yolo_uno
```

### 2. Upload to the Board

```bash
pio run -e yolo_uno -t upload
```

### 3. Open the Serial Monitor

```bash
pio device monitor -b 115200
```

If you are using PlatformIO IDE in VS Code, you can select the `yolo_uno` environment and use the Build, Upload, and Monitor actions from the UI.

## Run Tests

### Native Unit Tests

Use this mode to test logic that does not require physical hardware. These tests rely on the mocks under `test/mocks`.

```bash
pio test -e native
```

Run a single suite:

```bash
pio test -e native -f test_event_queue
pio test -e native -f test_climate_service
pio test -e native -f test_motion_service
```

### Hardware Integration Tests

Use this mode when the board is connected and you want to validate MQTT, sensor, and motion behavior on the actual device.

```bash
pio test -e yolo_uno_test
```

Run a single hardware suite:

```bash
pio test -e yolo_uno_test -f test_mqtt_hardware
pio test -e yolo_uno_test -f test_sensor_hardware
pio test -e yolo_uno_test -f test_motion_hardware
```

## Test Notes

- `native` is the fastest feedback loop for day-to-day development.
- `yolo_uno_test` validates integration with the board and attached peripherals.
- Some hardware tests require Wi-Fi, a reachable MQTT broker, and connected sensors before execution.

## Available Test Suites

```text
test/
|- test_event_queue/
|- test_timer_manager/
|- test_climate_service/
|- test_motion_service/
|- test_command_service/
|- test_mqtt_hardware/
|- test_sensor_hardware/
`- test_motion_hardware/
```

## Quick Commands

```bash
# Build firmware
pio run -e yolo_uno

# Upload firmware
pio run -e yolo_uno -t upload

# Native unit tests
pio test -e native

# Hardware integration tests
pio test -e yolo_uno_test
```
