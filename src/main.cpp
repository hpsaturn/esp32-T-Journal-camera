#include <Arduino.h>
#include <EspNowJoystick.hpp>
#include "OV2640.h"

#define ENABLE_OLED //if want use oled ,turn on thi macro

#ifdef ENABLE_OLED
#include "SSD1306.h"
#define OLED_ADDRESS 0x3c
#define I2C_SDA 14
#define I2C_SCL 13
SSD1306Wire display(OLED_ADDRESS, I2C_SDA, I2C_SCL, GEOMETRY_128_32);
#endif

EspNowJoystick joystick;
JoystickMessage jm;
bool receiverConnected;

OV2640 cam;
uint32_t frames = 0; 

// callback to telemetries values (not mandatory)
class MyTelemetryCallbacks : public EspNowTelemetryCallbacks{
    void onTelemetryMsg(TelemetryMessage tm){
        Serial.println("Telemetry msg received");
        receiverConnected = tm.e1;
    };
    void onError(const char *msg){
    };
};

void setup()
{
  Serial.begin(115200);
  delay(2000);

  camera_config_t camera_config;
  camera_config.ledc_channel = LEDC_CHANNEL_0;
  camera_config.ledc_timer = LEDC_TIMER_0;
  camera_config.pin_d0 = 17;
  camera_config.pin_d1 = 35;
  camera_config.pin_d2 = 34;
  camera_config.pin_d3 = 5;
  camera_config.pin_d4 = 39;
  camera_config.pin_d5 = 18;
  camera_config.pin_d6 = 36;
  camera_config.pin_d7 = 19;
  camera_config.pin_xclk = 27;
  camera_config.pin_pclk = 21;
  camera_config.pin_vsync = 22;
  camera_config.pin_href = 26;
  camera_config.pin_sscb_sda = 25;
  camera_config.pin_sscb_scl = 23;
  camera_config.pin_reset = 15;
  camera_config.xclk_freq_hz = 20000000;
  camera_config.pixel_format = CAMERA_PF_JPEG;
  camera_config.frame_size = CAMERA_FS_SVGA;

  cam.init(camera_config);

  joystick.setTelemetryCallbacks(new MyTelemetryCallbacks());
  jm = joystick.newJoystickMsg();
  joystick.init();

#ifdef ENABLE_OLED
  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.drawString(128 / 2, 32 / 2, "ESPNOW READY");
  display.display();
#endif
}


void displayFrameRate(){
  static uint32_t framets = 0;
  if (millis() - framets > 1000){
    framets = millis();
    display.clear();
    display.setFont(ArialMT_Plain_10);
    display.setTextAlignment(TEXT_ALIGN_CENTER);
    display.drawString(128 / 2, 32 / 2, String(frames) + " fps");
    display.display();
    frames = 0;
  }
}

void loop() {
    frames++;
    cam.run();
    // client.write((char *)cam.getfb(), cam.getSize());
    cam.getfb();
    jm.ax = cam.getSize();
    joystick.sendJoystickMsg(jm);
    displayFrameRate();
}
