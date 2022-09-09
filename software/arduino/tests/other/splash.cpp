//
// Created by RedNicStone on 9/7/22.
//

#include "../../data/fonts/verdana/Verdana.ttf.h"
#include "../../data/splash/demo.raw.h"
#include "../../src/graphics/font/font.h"
#include "../../src/file_writer.h"


int main() {
    auto font = FontRenderer(Verdana_ttf, sizeof(Verdana_ttf), 14);

    auto buffer = UnsafePixelBuffer<RGB8>({ 128u, 128u }, (RGB8*) demo_raw);

    FileWriter::writeImageToFile("demo.bmp", buffer, 128, 128);
    system("feh demo.bmp --zoom 1000 --force-aliasing");
}

