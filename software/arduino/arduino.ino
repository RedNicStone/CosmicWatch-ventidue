//
// Created by nic on 07/08/22.
//

#undef abs
#undef PI

#include "src/graphics/types.h"
#include "src/graphics/algorithms/sdf_generators.h"
#include "src/graphics/algorithms/sdf_transformations.h"
#include "src/graphics/algorithms/sdf_combiantorics.h"
#include "src/graphics/renderer/sdf_mix.h"
#include "src/graphics/renderer/stream_converters.h"
#include "src/graphics/renderer/assets.h"
#include "src/graphics/driver/OLED_1_5INCH_128x128.h"
#include "src/graphics/font/font.h"

#include "data/fonts/verdana/Verdana.ttf.h"
#include "data/fonts/droid-sans/DroidSans.ttf.h"
#include "data/splash/demo.raw.h"

using namespace SDF;

unsigned int height = 128;
unsigned int width = 128;
int iter = 0;
bool iterFlag = false;

float t = 0.5;

OLED_1inch5_128 oled;
FontRenderer fontV[] = { FontRenderer(Verdana_ttf, sizeof(Verdana_ttf), 14), 
                         FontRenderer(Verdana_ttf, sizeof(Verdana_ttf), 13), 
                         FontRenderer(Verdana_ttf, sizeof(Verdana_ttf), 12), 
                         FontRenderer(Verdana_ttf, sizeof(Verdana_ttf), 11) };
FontRenderer fontD[] = { FontRenderer(DroidSans_ttf, sizeof(DroidSans_ttf), 14), 
                         FontRenderer(DroidSans_ttf, sizeof(DroidSans_ttf), 13), 
                         FontRenderer(DroidSans_ttf, sizeof(DroidSans_ttf), 12), 
                         FontRenderer(DroidSans_ttf, sizeof(DroidSans_ttf), 11) };

void calcSDF(int t_) {
    auto* fontArray = fontV;
    if (t_ > 3) {
        fontArray = fontD;
        t_ -= 4;
    }

    auto buffer = PixelBuffer<uint8_t>({ 128u, 128u });
    fontArray[t_].renderTextToBuffer("This is a\n"
                            "complex multiline\n"
                            "text to\n"
                            "demonstrate text\n"
                            "rendering\n"
                            "capability", &buffer);

    auto sdf = SDF::SGrayscale(buffer);
  
    // Create SDF 
    /*auto sdf = MVisualization(
      TTranslate(
        CInterpolate(
          GSegment(vec2(-35.0f), vec2(35.0f), 10.0f),
          TRotate(
             GSegment(vec2(-35.0f), vec2(35.0f), 10.0f), 
           90), 
        t_),
      vec2(64))
    );*/

    auto sdfPixel = SPack565(sdf);

    oled.bake(sdfPixel);
}

void setup() {
  oled = OLED_1inch5_128(6);
  auto splashBuffer = UnsafePixelBuffer<RGB8>({ 128u, 128u }, (RGB8*) demo_raw);
  auto sdfPixel = SPack565(splashBuffer);
  oled.bake(sdfPixel);
  oled.transfer();
  delay(5000);
}

void loop() {
  double timeDrawing = 0;
  double timeTransferring = 0;
  
  
  for (int i = 0; i < 30; i++) {
    // Generate a new Image
    unsigned long startTime = millis();
    
    calcSDF(iter);
    unsigned long drawTime = millis();
    
    oled.transfer();
    unsigned long transferTime = millis();

    timeDrawing += drawTime - startTime;
    timeTransferring += transferTime - drawTime;

    if (iter >= 7)
        iterFlag = true;
    else if (iter <= 0)
        iterFlag = false;
  
    if (iterFlag)
        iter--;
    else
        iter++;
  }
  
  double transferedData = OLED_1in5_RGB_HEIGHT * OLED_1in5_RGB_WIDTH * 2 * 30 / 1000;
  double transferRate = transferedData / timeTransferring * 1000;
  double drawTime = timeDrawing / 30;
  double transferTime = timeTransferring / 30;
  
  Serial.println("Drawing took is: " + String(drawTime) + "ms");
  Serial.println("Transfer rate is: " + String(transferRate) + "kB/s, Transferring took is: " + String(transferTime) + "ms");
}
