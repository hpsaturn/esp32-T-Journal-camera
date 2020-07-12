# TTGO T-Journal camera

PlatformIO implementation for test a ESP32 TTGO T-Journal camera hardware module.

# Preparation

Change the variables on `secrets.load` file first, like this:

```Javascript
cp secrets.load.sample secrets.load                   # after clone copy a new secrets.load
chmod 755 secrets.load                                # edit and put here your wifi credentials
export PLATFORMIO_BUILD_FLAGS=`bash ./secrets.load`   # load secrets before building
```

Then connect your device to USB and compiling and uploading the firmware with:

```shell
pio run --target upload
```

In the display you should have the camera IP, you can access to it via any browser.
