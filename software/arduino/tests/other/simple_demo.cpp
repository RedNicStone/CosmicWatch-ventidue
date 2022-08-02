//
// Created by nic on 06/07/22.
//

#include <iostream>

#include "../../src/file_writer.h"
#include "../../src/graphics/types.h"


int main() {
    unsigned int height = 128;
    unsigned int width = 128;

    PixelBuffer<RGB8> image(Point2D(height, width));
    image.fill(RGB8(100_uc, 100_uc, 100_uc), { Point2D(0_uc, 0_uc), Point2D(50_uc, 50_uc) });

    FileWriter::writeImageToFile("demo.bmp", (const unsigned char *)(image.getDataHandle()), width, height);

    system("feh demo.bmp --zoom 1000 --force-aliasing");
}

