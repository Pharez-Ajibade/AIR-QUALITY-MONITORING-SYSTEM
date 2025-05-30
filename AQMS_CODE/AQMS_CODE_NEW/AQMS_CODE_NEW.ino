#define BLYNK_TEMPLATE_ID "TMPL2MZqL0OA5"
#define BLYNK_TEMPLATE_NAME "WQMS"
#define BLYNK_AUTH_TOKEN "9z572aAv0qi54USm_bQbhryUK8WFS7h1"
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#include <Adafruit_ADS1X15.h>
Adafruit_ADS1115 ads;

int samplingTime = 280; int deltaTime = 40; int sleepTime = 9680; int ledPin = 25;

float volts0, volts1, volts2, volts3;
float voMeasured = 0;
float dustDensity = 0;
int speaker_pin = 26;
float trigger_value ;
//---------------------------------
#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

//---------------------------------

// 'New Project', 128x64px
const unsigned char Front_LOGO [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0xe0, 0x3f, 0x00, 0x00, 0x80, 0xff, 0x00, 0x00, 0x80, 0x03, 0x00, 0x07, 0x00, 0x00, 0xfc, 0x07, 
	0xe0, 0x3f, 0x00, 0x00, 0x80, 0xff, 0x00, 0x00, 0x80, 0x03, 0x00, 0x07, 0x00, 0x00, 0xfc, 0x07, 
	0xf0, 0x3f, 0x00, 0x00, 0x80, 0xff, 0x00, 0x00, 0x80, 0x03, 0x00, 0x07, 0x00, 0x00, 0xfc, 0x07, 
	0x1c, 0xe0, 0x00, 0x00, 0x70, 0x00, 0x07, 0x00, 0x80, 0x03, 0x00, 0x07, 0x00, 0x80, 0x03, 0x3c, 
	0x1c, 0xe0, 0x00, 0x00, 0x70, 0x00, 0x07, 0x00, 0x80, 0x03, 0x00, 0x07, 0x00, 0x80, 0x03, 0x3c, 
	0x1c, 0xe0, 0x00, 0x00, 0x70, 0x00, 0x07, 0x00, 0x80, 0x03, 0x00, 0x07, 0x00, 0x80, 0x03, 0x38, 
	0x1c, 0xe0, 0x00, 0x00, 0x70, 0x00, 0x07, 0x00, 0x80, 0x1f, 0xe0, 0x07, 0x00, 0x80, 0x03, 0x00, 
	0x1c, 0xe0, 0x00, 0x00, 0x70, 0x00, 0x07, 0x00, 0x80, 0x1f, 0xe0, 0x07, 0x00, 0x80, 0x03, 0x00, 
	0x1c, 0xe0, 0x00, 0x00, 0x70, 0x00, 0x07, 0x00, 0x80, 0x7f, 0xf8, 0x07, 0x00, 0x80, 0xff, 0x03, 
	0x1c, 0xe0, 0x00, 0x00, 0x70, 0x00, 0x07, 0x00, 0x80, 0xf3, 0x1c, 0x07, 0x00, 0x00, 0xfc, 0x07, 
	0x1c, 0xe0, 0x00, 0x00, 0x70, 0x00, 0x07, 0x00, 0x80, 0xf3, 0x1c, 0x07, 0x00, 0x00, 0xfc, 0x07, 
	0xfc, 0xff, 0x00, 0x00, 0x70, 0x1c, 0x07, 0x00, 0x80, 0xe3, 0x1f, 0x07, 0x00, 0x00, 0xfc, 0x1f, 
	0xfc, 0xff, 0x00, 0x00, 0x70, 0x1c, 0x07, 0x00, 0x80, 0x83, 0x07, 0x07, 0x00, 0x00, 0x00, 0x3c, 
	0xfc, 0xff, 0x00, 0x00, 0x70, 0x1c, 0x07, 0x00, 0x80, 0x83, 0x07, 0x07, 0x00, 0x00, 0x00, 0x3c, 
	0x1c, 0xe0, 0x00, 0x00, 0x70, 0xe0, 0x00, 0x00, 0x80, 0x03, 0x00, 0x07, 0x00, 0x80, 0x03, 0x3c, 
	0x1c, 0xe0, 0x00, 0x00, 0x70, 0xe0, 0x00, 0x00, 0x80, 0x03, 0x00, 0x07, 0x00, 0x80, 0x03, 0x3c, 
	0x1c, 0xe0, 0x00, 0x00, 0x70, 0xe0, 0x00, 0x00, 0x80, 0x03, 0x00, 0x07, 0x00, 0x80, 0x03, 0x3c, 
	0x1c, 0xe0, 0x00, 0x0e, 0x80, 0x1f, 0x07, 0x38, 0x80, 0x03, 0x00, 0x07, 0x70, 0x00, 0xfc, 0x07, 
	0x1c, 0xe0, 0x00, 0x0e, 0x80, 0x1f, 0x07, 0x38, 0x80, 0x03, 0x00, 0x07, 0x70, 0x00, 0xfc, 0x07, 
	0x1c, 0xe0, 0x00, 0x0e, 0x80, 0x1f, 0x07, 0x38, 0x80, 0x03, 0x00, 0x07, 0x70, 0x00, 0xfc, 0x07, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};




// 'base', 128x64px
const unsigned char MENU [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x05, 0x80, 0x20, 0x0e, 0x07, 0x38, 0x3e, 0x11, 0x87, 0xe3, 0x01, 0x00, 0x00, 0x00, 0x00, 
	0x80, 0x04, 0x80, 0x20, 0x91, 0x08, 0x44, 0x02, 0x91, 0x48, 0x24, 0x02, 0x00, 0x00, 0x00, 0x00, 
	0x40, 0x04, 0x80, 0x31, 0x11, 0x08, 0x04, 0x02, 0x93, 0x40, 0x24, 0x02, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x04, 0x80, 0x2a, 0x11, 0x04, 0x38, 0x0e, 0x15, 0x47, 0x24, 0x02, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x04, 0x80, 0x24, 0x15, 0x02, 0x40, 0x02, 0x19, 0x48, 0xe4, 0x01, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x04, 0x80, 0x20, 0x09, 0x01, 0x44, 0x02, 0x91, 0x48, 0x24, 0x01, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x04, 0x80, 0x20, 0x96, 0x0f, 0x38, 0x3e, 0x11, 0x87, 0x23, 0x02, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0xf0, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x80, 0x70, 0x80, 0x20, 0x8e, 0x0f, 0x38, 0x3e, 0x11, 0x87, 0xe3, 0x01, 0x00, 0x00, 0x00, 0x00, 
	0x40, 0x40, 0x80, 0x20, 0x11, 0x08, 0x44, 0x02, 0x91, 0x48, 0x24, 0x02, 0x00, 0x00, 0x00, 0x00, 
	0x40, 0x60, 0x80, 0x31, 0x11, 0x04, 0x04, 0x02, 0x93, 0x40, 0x24, 0x02, 0x00, 0x00, 0x00, 0x00, 
	0x80, 0x30, 0x80, 0x2a, 0x11, 0x02, 0x38, 0x0e, 0x15, 0x47, 0x24, 0x02, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x18, 0x80, 0x24, 0x15, 0x01, 0x40, 0x02, 0x19, 0x48, 0xe4, 0x01, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x0c, 0x80, 0x20, 0x89, 0x00, 0x44, 0x02, 0x91, 0x48, 0x24, 0x01, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x06, 0x80, 0x20, 0x96, 0x00, 0x38, 0x3e, 0x11, 0x87, 0x23, 0x02, 0x00, 0x00, 0x00, 0x00, 
	0x80, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x80, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0xf0, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0xc0, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x20, 0x80, 0x20, 0x0e, 0x84, 0xe3, 0x03, 0x8e, 0x4f, 0xc4, 0xe1, 0x78, 0x00, 0x00, 0x00, 
	0x00, 0x20, 0x80, 0x20, 0x11, 0x46, 0x24, 0x00, 0x91, 0x40, 0x24, 0x12, 0x89, 0x00, 0x00, 0x00, 
	0x00, 0x20, 0x80, 0x31, 0x11, 0x05, 0xe4, 0x01, 0x81, 0xc0, 0x24, 0x10, 0x89, 0x00, 0x00, 0x00, 
	0xc0, 0x3f, 0x80, 0x2a, 0x11, 0x04, 0x03, 0x02, 0x8e, 0x43, 0xc5, 0x11, 0x89, 0x00, 0x00, 0x00, 
	0x00, 0x20, 0x80, 0x24, 0x15, 0x04, 0x04, 0x02, 0x90, 0x40, 0x06, 0x12, 0x79, 0x00, 0x00, 0x00, 
	0x00, 0x20, 0x80, 0x20, 0x09, 0x44, 0x24, 0x02, 0x91, 0x40, 0x24, 0x12, 0x49, 0x00, 0x00, 0x00, 
	0x00, 0x20, 0x80, 0x20, 0x16, 0x84, 0xc3, 0x01, 0x8e, 0x4f, 0xc4, 0xe1, 0x88, 0x00, 0x00, 0x00, 
	0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0xc0, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x34, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x2a, 0x00, 0x8f, 0x88, 0xe3, 0x03, 0x8e, 0x4f, 0xc4, 0xe1, 0x78, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x25, 0x00, 0x91, 0x48, 0x84, 0x00, 0x91, 0x40, 0x24, 0x12, 0x89, 0x00, 0x00, 0x00, 0x00, 
	0x80, 0x20, 0x00, 0x91, 0x48, 0x80, 0x00, 0x81, 0xc0, 0x24, 0x10, 0x89, 0x00, 0x00, 0x00, 0x00, 
	0x40, 0x20, 0x00, 0x91, 0x88, 0x83, 0x00, 0x8e, 0x43, 0xc5, 0x11, 0x89, 0x00, 0x00, 0x00, 0x00, 
	0xc0, 0x3f, 0x00, 0x91, 0x08, 0x84, 0x00, 0x90, 0x40, 0x06, 0x12, 0x79, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x20, 0x00, 0x91, 0x48, 0x84, 0x00, 0x91, 0x40, 0x24, 0x12, 0x49, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x20, 0x00, 0x0f, 0x87, 0x83, 0x00, 0x8e, 0x4f, 0xc4, 0xe1, 0x88, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};



// 'SCROOL', 128x15px
const unsigned char SCROLL [] PROGMEM = {
	0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 
	0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 
	0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 
	0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 
	0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 
	0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 
	0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 
	0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 
	0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 
	0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 
	0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 
	0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 
	0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 
	0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};



//----------------------------------
char ssid[] = "AQMS";
char pass[] = "AQMS2025";
BlynkTimer timer; // Creating a timer object
//----------------------------------
int Button_1 = 16;
int Button_2 = 4;
int Button_3 = 13;
int Button_4 = 15;
int scroll_y_position ;

void setup()
{
  pinMode(ledPin,OUTPUT);
  pinMode(speaker_pin,OUTPUT);
  pinMode(Button_1, INPUT_PULLUP);
  pinMode(Button_2, INPUT_PULLUP);
  pinMode(Button_3, INPUT_PULLUP);
  pinMode(Button_4, INPUT_PULLUP);

  u8g2.begin();

  u8g2.firstPage();
   do {
   u8g2.drawXBM( 0, 0, 128, 64, Front_LOGO ); //DRAW Bitmap logo
   } while ( u8g2.nextPage() );

   delay(2000);

  bool menu_state = false;
  scroll_y_position = 1;
  bool press_state = false ;
// MENU-------------------------------------

    u8g2.firstPage();
   do {
   u8g2.setDrawColor(1); 
   u8g2.setBitmapMode(1); //optional to ENABLE TRANSPARENCY USE 1 ELSE USE 0
   u8g2.drawXBM( 0, 0, 128, 64, MENU); //DRAW MENU
  } while ( u8g2.nextPage() );

  while (menu_state == false){

  if (digitalRead (Button_1) == LOW){
  scroll_y_position = 1;
  press_state = true;
      u8g2.firstPage();
   do {
   u8g2.setDrawColor(1); 
   u8g2.setBitmapMode(1); //optional to ENABLE TRANSPARENCY USE 1 ELSE USE 0
   u8g2.drawXBM( 0, 0, 128, 64, MENU); //DRAW MENU
   u8g2.drawXBM( 0, scroll_y_position, 128, 15, SCROLL); //DRAW Bitmap logo
  } while ( u8g2.nextPage() );
 }

  if (digitalRead (Button_2) == LOW){
  scroll_y_position = 17;
  press_state = true;
      u8g2.firstPage();
   do {
   u8g2.setDrawColor(1); 
   u8g2.setBitmapMode(1); //optional to ENABLE TRANSPARENCY USE 1 ELSE USE 0
   u8g2.drawXBM( 0, 0, 128, 64, MENU); //DRAW MENU
   u8g2.drawXBM( 0, scroll_y_position, 128, 15, SCROLL); //DRAW Bitmap logo
  } while ( u8g2.nextPage() );
 }

  if (digitalRead (Button_3) == LOW){
  scroll_y_position = 32;
  press_state = true;
      u8g2.firstPage();
   do {
   u8g2.setDrawColor(1); 
   u8g2.setBitmapMode(1); //optional to ENABLE TRANSPARENCY USE 1 ELSE USE 0
   u8g2.drawXBM( 0, 0, 128, 64, MENU); //DRAW MENU
   u8g2.drawXBM( 0, scroll_y_position, 128, 15, SCROLL); //DRAW Bitmap logo
  } while ( u8g2.nextPage() );
 }
  if (digitalRead (Button_4) == LOW){
  scroll_y_position = 49;
  press_state = true;
      u8g2.firstPage();
   do {
   u8g2.setDrawColor(1); 
   u8g2.setBitmapMode(1); //optional to ENABLE TRANSPARENCY USE 1 ELSE USE 0
   u8g2.drawXBM( 0, 0, 128, 64, MENU); //DRAW MENU
   u8g2.drawXBM( 0, scroll_y_position, 128, 15, SCROLL); //DRAW Bitmap logo
  } while ( u8g2.nextPage() );
  delay(1000);
 } 
   
 
 while( press_state == true){

  if (digitalRead (Button_1) == LOW){
       press_state = false;
  }

  if (digitalRead (Button_2) == LOW){
       press_state = false;
  }

  if (digitalRead (Button_3) == LOW){
       press_state = false;
  }

   if (digitalRead (Button_4) == LOW){
   press_state = false;
   menu_state = true;

   u8g2.clearBuffer();					// clear the internal memory
   u8g2.setFont(u8g2_font_ncenB08_tr);	// choose a suitable font
   u8g2.drawStr(0,10, "SENSOR SELECTED");	// write something to the internal memory );
   u8g2.sendBuffer();// transfer internal memory to the display
   delay(2000);

   }

 }

}

   u8g2.clearBuffer();					// clear the internal memory
   u8g2.setFont(u8g2_font_ncenB08_tr);	// choose a suitable font
   u8g2.drawStr(0,10, " ATTEMPTING Wi-Fi ");	// write something to the internal memory );
   u8g2.drawStr(0,30, "    CONNECTION   ");	// write something to the internal memory );
   u8g2.sendBuffer();// transfer internal memory to the display
   delay(1000);

if (!ads.begin())
  {
    Serial.println("Failed to initialize ADS.");
    while (1);
  }

  Serial.begin(115200);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  timer.setInterval(1000L, myTimerEvent); //Staring a timer


   u8g2.clearBuffer();					// clear the internal memory
   u8g2.setFont(u8g2_font_ncenB08_tr);	// choose a suitable font
   u8g2.drawStr(0,10, " ATTEMPTING Wi-Fi ");	// write something to the internal memory );
   u8g2.drawStr(0,30, "    CONNECTION   ");	// write something to the internal memory );
   u8g2.drawStr(0,50, " STATUS: SUCESSFUL");	// write something to the internal memory );
   u8g2.sendBuffer();// transfer internal memory to the display
   delay(1000);


  Serial.println("Warming up the MQ2 sensor");

   u8g2.clearBuffer();					// clear the internal memory
   u8g2.setFont(u8g2_font_ncenB08_tr);	// choose a suitable font
   u8g2.drawStr(0,10, "WARMING SENSORS");	// write something to the internal memory );
   u8g2.drawStr(0,30, "WAIT FOR 20 sec.");	// write something to the internal memory );
   u8g2.sendBuffer();// transfer internal memory to the display
   delay(20000);  // wait for the MQ2 to warm up
}


void myTimerEvent() // This loop defines what happens when timer is triggered
{
Blynk.virtualWrite(V0, volts0);
Blynk.virtualWrite(V1, volts1);
Blynk.virtualWrite(V2, volts2);
Blynk.virtualWrite(V3, dustDensity);

}

BLYNK_WRITE(V4)
{   
 trigger_value = param.asFloat(); // Get value as integer

}


void loop()
{

int16_t adc0, adc1, adc2, adc3;
 
  adc0 = ads.readADC_SingleEnded(0);
  adc1 = ads.readADC_SingleEnded(1);
  adc2 = ads.readADC_SingleEnded(2);
 
  volts0 = ads.computeVolts(adc0);
  volts1 = ads.computeVolts(adc1);
  volts2 = ads.computeVolts(adc2);

  Serial.println("-----------------------------------------------------------");
  Serial.print("AIN0 Mq2  : "); Serial.print(adc0); Serial.print("  "); Serial.print(volts0); Serial.println("V");
  Serial.print("AIN1 Mq7  : "); Serial.print(adc1); Serial.print("  "); Serial.print(volts1); Serial.println("V");
  Serial.print("AIN2 Mq135: "); Serial.print(adc2); Serial.print("  "); Serial.print(volts2); Serial.println("V");
  
  
  digitalWrite(ledPin,LOW); // power on the LED
  delayMicroseconds(samplingTime);
  
  adc3 = ads.readADC_SingleEnded(3);

  delayMicroseconds(deltaTime);
  digitalWrite(ledPin,HIGH); // turn the LED off
  delayMicroseconds(sleepTime);

  volts3 = ads.computeVolts(adc3);
  Serial.print("AIN3 Dust : "); Serial.print(adc3); Serial.print("  "); Serial.print(volts3); Serial.println("V");

  voMeasured =  volts3;

  if ( volts3 >= 0.6 ) {
      dustDensity = 0.17 * volts3 - 0.1;
  } else {
      dustDensity = 0;
  }

  Serial.print(" Dust Density: ");

  if( volts3 > 3.5 ) {
     Serial.print(">");  // unit: mg/m3
  }

  Serial.print(dustDensity);
  Serial.println(" mg/m3");

  delay(250);

Serial.print("TRIGGER VALUE: "); Serial.println(trigger_value);

switch( scroll_y_position ){
//------------------------------------- MQ2 SELECTOR
   case 1 :
    if ( volts0 > trigger_value ){
     digitalWrite(speaker_pin, HIGH);
     Serial.println ("SPEAKER TRIGGER HIGH"); 
    }
    else{
     digitalWrite(speaker_pin, LOW);
     Serial.println ("SPEAKER TRIGGER LOW"); 
    }
    break;
//-------------------------------------- MQ7 SELECTOR
   case 17:
    if ( volts1 > trigger_value ){
     digitalWrite(speaker_pin, HIGH);
     Serial.println ("SPEAKER TRIGGER HIGH"); 
    }
    else{
     digitalWrite(speaker_pin, LOW);
     Serial.println ("SPEAKER TRIGGER LOW"); 
    }
    break;
//------------------------------------- MQ135 SEELECTOR
   case 32:
    if ( volts2 > trigger_value ){
     digitalWrite(speaker_pin, HIGH);
     Serial.println ("SPEAKER TRIGGER HIGH"); 
    }
    else{
     digitalWrite(speaker_pin, LOW);
     Serial.println ("SPEAKER TRIGGER LOW"); 
    }
    break;
//-------------------------------------
   case 49:
    if ( dustDensity > trigger_value ){
     digitalWrite(speaker_pin, HIGH);
     Serial.println ("SPEAKER TRIGGER HIGH"); 

    }
    else{
     digitalWrite(speaker_pin, LOW);
     Serial.println ("SPEAKER TRIGGER LOW"); 
    }
    break;
   
}

     u8g2.clearBuffer();					// clear the internal memory
     u8g2.setFont(u8g2_font_ncenB08_tr);	// choose a suitable font
     u8g2.setCursor(0,10); u8g2.print("MQ2   Value:"); u8g2.setCursor(80,10);  u8g2.print(volts0);       u8g2.setCursor(110,10);  u8g2.print("v");
     u8g2.setCursor(0,25); u8g2.print("MQ7   Value:"); u8g2.setCursor(80,25);  u8g2.print(volts1);       u8g2.setCursor(110,25);  u8g2.print("v");
     u8g2.setCursor(0,40); u8g2.print("MQ135 Value:"); u8g2.setCursor(80,40);  u8g2.print(volts2);       u8g2.setCursor(110,40);  u8g2.print("v");
     u8g2.setCursor(0,55); u8g2.print("DUST  Value:"); u8g2.setCursor(80,55);  u8g2.print(dustDensity); // doesnt fit u8g2.setCursor(110,55);  u8g2.print("mg/m3");
     u8g2.sendBuffer();// transfer internal memory to the display
     delay(100);

  Blynk.run();
  timer.run(); // runs the timer in the loop

}