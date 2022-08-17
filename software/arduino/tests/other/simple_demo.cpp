//
// Created by nic on 07/08/22.
//

#include <iostream>
#include <chrono>

#include "../../src/file_writer.h"
#include "../../src/graphics/types.h"
#include "../../src/graphics/algorithms/sdf_generators.h"
#include "../../src/graphics/algorithms/sdf_transformations.h"
#include "../../src/graphics/algorithms/sdf_combiantorics.h"
#include "../../src/graphics/renderer/sdf_mix.h"
#include "../../src/graphics/renderer/assets.h"


using namespace SDF;

int main() {
    unsigned int height = 128;
    unsigned int width = 128;

    PixelBuffer<RGB8> image(Point2D(height, width));
    auto sdf = MVisualization(TTranslate(TScale(CInterpolate(
        GSegment(vec2(-35.0f), vec2(35.0f), 10.0f),
        TRotate(GSegment(vec2(-35.0f), vec2(35.0f), 10.0f), 90)
        , 0.9), 1), vec2(64)));

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()
    << "[us]" <<
    std::endl;

    FileWriter::writeImageToFile("demo.bmp", (const unsigned char *)(image.getDataHandle()), width, height);

    system("feh demo.bmp --zoom 1000 --force-aliasing");
}