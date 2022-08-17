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

using namespace SDF;

unsigned int height = 128;
unsigned int width = 128;

float t = 0.5;

OLED_1inch5_128 oled;

void calcSDF(float t_) {
    // Create SDF
    auto sdf = MVisualization(
      TTranslate(
        CInterpolate(
          GSegment(vec2(-35.0f), vec2(35.0f), 10.0f),
          TRotate(
             GSegment(vec2(-35.0f), vec2(35.0f), 10.0f), 
           90), 
        t_),
      vec2(64))
    );

    auto sdfPixel = SPack565(MRGB8(sdf));

    oled.bake(sdfPixel);
}

void setup() {
  oled = OLED_1inch5_128(6);
}

void loop() {
  double timeDrawing = 0;
  double timeTransferring = 0;
  
  
  for (int i = 0; i < 30; i++) {
    // Generate a new Image
    unsigned long startTime = millis();
    
    calcSDF(0.5 + sin(t) * 0.5);
    unsigned long drawTime = millis();
    
    oled.transfer();
    unsigned long transferTime = millis();
    
    t += 0.2;

    timeDrawing += drawTime - startTime;
    timeTransferring += transferTime - drawTime;
  }
  
  double transferedData = OLED_1in5_RGB_HEIGHT * OLED_1in5_RGB_WIDTH * 2 * 30 / 1000;
  double transferRate = transferedData / timeTransferring * 1000;
  double drawTime = timeDrawing / 30;
  double transferTime = timeTransferring / 30;
  
  Serial.println("Drawing took is: " + String(drawTime) + "ms");
  Serial.println("Transfer rate is: " + String(transferRate) + "kB/s, Transferring took is: " + String(transferTime) + "ms");
}
