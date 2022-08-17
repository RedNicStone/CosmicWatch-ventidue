//
// Created by nic on 07/08/22.
//

#include <iostream>

#include "../../src/file_writer.h"
#include "../../src/graphics/types.h"
#include "../../src/graphics/algorithms/sdf_generators.h"
#include "../../src/graphics/algorithms/sdf_transformations.h"
#include "../../src/graphics/algorithms/sdf_combiantorics.h"
#include "../../src/graphics/renderer/sdf_mix.h"
#include "../../src/graphics/renderer/assets.h"


using namespace SDF;

class CustomPixelTranspositionEngine : public PixelTranspositionEngine {
  public:
    inline static RGB8 transpose(vec3 value) {
        return RGB8(value * 255);
    }
};

int main() {
    unsigned int height = 128;
    unsigned int width = 128;

    PixelBuffer<RGB8> image(Point2D(height, width));
    auto sdf = MVisualization(TTranslate(TScale(CInterpolate(
        GSegment(vec2(-35.0f), vec2(35.0f), 10.0f),
        TRotate(GSegment(vec2(-35.0f), vec2(35.0f), 10.0f), 90)
        , 0.9), 1), vec2(64)));

    auto asset = SDFAsset<vec3, decltype(sdf)>(sdf, {height, width});
    asset.load();

    BufferTranspositionEngine<vec3, RGB8, CustomPixelTranspositionEngine>::transpose(image, asset.getBuffer(), { {
                                                                                                                     0u, 0u }, { height, width }}, {0u, 0u});

    asset.free();

    FileWriter::writeImageToFile("demo.bmp", (const unsigned char *)(image.getDataHandle()), width, height);

    system("feh demo.bmp --zoom 1000 --force-aliasing");
}