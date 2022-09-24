# ESP32 T-Journal Camera

PlatformIO implementation for test a ESP32 TTGO T-Journal camera hardware module.

## WiFi credentials

Via environment variables. Please first export your credentials:

```bash
export PIO_WIFI_PASSWORD='your_password'
export PIO_WIFI_SSID='your_wifi_network'
```

## Build and upload

Then connect your device to USB and compiling and uploading the firmware with:

```shell
pio run --target upload
```

In the display you should have the camera IP, you can access to it via any browser.
