# ESP32 Gate

Simple ESP32 project to control two GPIO outputs via a small HTTP web interface and keep a timestamped action log.

## Overview
- Controls two outputs: GPIO4 and GPIO5 (toggle on/off).
- Reads an input `GPIO18` (RC or button) to flip both outputs with debounce.
- Runs a basic `WebServer` providing routes to toggle pins and poll status.
- Keeps recent action logs in memory and displays them on the web page.

## Pinout / Wiring
- `GPIO4` — output ("First" relay/actuator)
- `GPIO5` — output ("Second" relay/actuator)
- `GPIO18` — input (RC/button) — active HIGH to trigger flip
- `LED_BUILTIN` — activity LED (driven by WiFi status)

Adjust wiring to match your hardware. The code uses the Arduino `GPIO_NUM_x` constants.

## Configuration
- Wi‑Fi credentials are moved to `include/secrets.h` which is gitignored. Edit that file with:

```cpp
#define WIFI_SSID "your_real_ssid"
#define WIFI_PASSWORD "your_real_password"
```

If `include/secrets.h` is missing, the project falls back to placeholder credentials so native tests and CI still build.

## Build & Upload (PlatformIO)
From the project root:

- Build:
```bash
pio run
```

- Upload to the board (auto-detects port when possible):
```bash
pio run -e nodemcu-32s --target upload
```

- Upload to a specific port:
```bash
pio run -e nodemcu-32s --target upload --upload-port /dev/cu.SLAB_USBtoUART
```

- Monitor serial output (921600 baud):
```bash
pio device monitor -e nodemcu-32s -b 921600
# or
pio device monitor -p /dev/cu.SLAB_USBtoUART -b 921600
```

### Finding the serial port on macOS
```bash
ls /dev/cu.*
ls /dev/tty.*
system_profiler SPUSBDataType
```
Look for names like `/dev/cu.SLAB_USBtoUART`, `/dev/cu.wchusbserial*`, or `/dev/cu.usbserial-*`.

If the device does not appear:
- Try a different USB cable or port.
- Check for CH340/CP210x drivers (some boards require drivers on macOS).
- Reboot your Mac if the port used to be visible but no longer is.

## Unit Tests (native)
The project includes Unity tests for logging helpers. Run them locally without hardware:

```bash
pio test -e native -v
```

To run tests on the ESP32 (will build and upload test firmware):
```bash
pio test -e nodemcu-32s -v
```

## Continuous Integration
A GitHub Actions workflow (`.github/workflows/ci.yml`) runs the native tests on push and pull requests to `main`.

## Notes and Recommendations
- `custom_logging` keeps a bounded in-memory log (default last 50 entries). If you want persistence across reboots, consider adding LittleFS or SPIFFS and updating `logEntries()` to write to flash.
- Credentials are intentionally not committed — keep `include/secrets.h` private.
- The web interface is intentionally minimal and unauthenticated; if you expose this to an untrusted network, add authentication.

## Next steps you may want
- Persist logs to LittleFS and add tests for persistence.
- Add authentication to the web UI.
- Add a health endpoint or OTA update support.

