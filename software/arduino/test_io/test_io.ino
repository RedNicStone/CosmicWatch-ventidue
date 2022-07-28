#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BME280.h>
#include <Arduino.h>
#include <RotaryEncoder.h>
#include <NMEAGPS.h>
#include <Streamers.h>
#include <DS3231.h>

#include "src/lib/oled/OLED_Driver.h"
#include "src/lib/oled/GUI_Paint.h"
#include "src/lib/oled/DEV_Config.h"
#include "src/lib/oled/Debug.h"
#include "src/lib/oled/ImageData.h"

#define SEALEVELPRESSURE_HPA (1013.25)

#define ROATRY_IN1 28
#define ROATRY_IN2 29
#define ROATRY_BTN 30

#define SMBL_ROATRY_CLENGTH 9
#define SMBL_ROATRY_CUTIN   1

#define GPS_BAUD  9600
#define GPS_PORT  Serial1

static Adafruit_BME280 bme;
static RotaryEncoder encoder(ROATRY_IN1, ROATRY_IN2, RotaryEncoder::LatchMode::TWO03);

static unsigned long periodStartMillis;
static unsigned long currentMillis;

static bool showGps = false;
static bool previousButtonState = false;

static NMEAGPS  gps;
static gps_fix  fix;

static RTClib rtc;

void interruptCheckRotary() {
  encoder.tick();
}

void setup() {
  Serial.begin(9600);
  
  System_Init();
  
  Serial.print(F("OLED_Init()...\r\n"));
  OLED_1in5_rgb_Init();
  Driver_Delay_ms(500);
  OLED_1in5_rgb_Clear();  
  
  UBYTE *BlackImage;
  Serial.print("Paint_NewImage\r\n");
  Paint_NewImage(BlackImage, OLED_1in5_RGB_WIDTH, OLED_1in5_RGB_HEIGHT, 180, BLACK);  
  Paint_SetScale(65);

  bme.begin(0x76);

  pinMode(ROATRY_BTN, INPUT_PULLUP);
  periodStartMillis = millis();
  attachInterrupt(digitalPinToInterrupt(ROATRY_IN1), interruptCheckRotary, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ROATRY_IN2), interruptCheckRotary, CHANGE);
  
  GPS_PORT.begin(GPS_BAUD);
}

void loop() {
  //encoder.tick();
  while (gps.available(GPS_PORT)) {
    fix = gps.read();
    Serial.print( fix.latitude(), 6 );
    Serial.print( ',' );
    Serial.println( fix.longitude(), 6 );
  }

  currentMillis = millis();
  if (currentMillis - periodStartMillis >= 300) {
    drawFrame();
    periodStartMillis = currentMillis;
  }
}

void drawFrame() {
  char buffer[40];
  if (showGps) {
    Paint_DrawString_EN(0, 0, "Position:", &Font12, BLACK, RED);
    Paint_DrawString_EN(10, 12, (String(fix.latitude() ) + "LAT" ).c_str(), &Font12, BLACK, RED);
    Paint_DrawString_EN(10, 24, (String(fix.longitude()) + "LONG").c_str(), &Font12, BLACK, RED);
  
    Paint_DrawString_EN(0, 42, "Altitude:", &Font12, BLACK, GREEN);
    Paint_DrawString_EN(10, 54, (String(fix.altitude()) + " m").c_str(), &Font12, BLACK, GREEN);

    DateTime now = rtc.now();
    Paint_DrawString_EN(0, 72, "RTC Time:", &Font12, BLACK, YELLOW);
    sprintf("Date: %d/%-d")
    Paint_DrawString_EN(10, 84, (String(now.year()) + "/" + String(now.month()) + "/" + String(now.day())).c_str(), &Font12, BLACK, YELLOW);
    Paint_DrawString_EN(10, 96, (String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second())).c_str(), &Font12, BLACK, YELLOW);
  } else {
    Paint_DrawString_EN(0, 0, "Temperature:", &Font12, BLACK, RED);
    Paint_DrawString_EN(10, 12, (String(bme.readTemperature()) + " *C").c_str(), &Font12, BLACK, RED);
  
    Paint_DrawString_EN(0, 30, "Humidity:", &Font12, BLACK, BLUE);
    Paint_DrawString_EN(10, 42, (String(bme.readHumidity()) + " %").c_str(), &Font12, BLACK, BLUE);
  
    Paint_DrawString_EN(0, 60, "Pressure:", &Font12, BLACK, YELLOW);
    Paint_DrawString_EN(10, 72, (String(bme.readPressure() / 100.0F) + " hPa").c_str(), &Font12, BLACK, YELLOW);
  
    Paint_DrawString_EN(0, 90, "Altitude:", &Font12, BLACK, GREEN);
    Paint_DrawString_EN(10, 102, (String(bme.readAltitude(SEALEVELPRESSURE_HPA)) + " m").c_str(), &Font12, BLACK, GREEN);
  }
    
  Paint_DrawRectangle(90, 30, 120, 60, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);

  bool pressed = digitalRead(ROATRY_BTN) == LOW;
  if (pressed && !previousButtonState) {
    showGps =! showGps;
    OLED_1in5_rgb_Clear();
  }
  previousButtonState = pressed;
  
  Paint_DrawRectangle(90, 30, 120, 60, WHITE, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
  Paint_DrawCircle(105, 45, 10, WHITE, DOT_PIXEL_1X1, pressed ? DRAW_FILL_FULL : DRAW_FILL_EMPTY);

  float pos = encoder.getPosition() / 20.0F * PI;
  float deltaX1 = sin(pos - SMBL_ROATRY_CUTIN) * SMBL_ROATRY_CLENGTH;
  float deltaY1 = cos(pos - SMBL_ROATRY_CUTIN) * SMBL_ROATRY_CLENGTH;
  float deltaX2 = sin(pos + SMBL_ROATRY_CUTIN) * SMBL_ROATRY_CLENGTH;
  float deltaY2 = cos(pos + SMBL_ROATRY_CUTIN) * SMBL_ROATRY_CLENGTH;
  Paint_DrawLine(105 + deltaX1, 45 - deltaY1, 105 + deltaX2, 45 - deltaY2, pressed ? BLACK : WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
}
