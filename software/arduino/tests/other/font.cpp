//
// Created by RedNicStone on 9/5/22.
//

#include "../../data/fonts/verdana/Verdana.ttf.h"
#include "../../src/graphics/font/font.h"
#include "../../src/file_writer.h"


int main() {
    auto font = FontRenderer(Verdana_ttf, sizeof(Verdana_ttf), 14);

    auto buffer = PixelBuffer<uint8_t>({ 128u, 128u });
    font.renderTextToBuffer("This is a\n"
                            "complex multiline\n"
                            "demo text to\n"
                            "demonstrate text\n"
                            "rendering\n"
                            "capability", &buffer);

    auto sdf = SDF::SGrayscale(buffer);

    FileWriter::writeImageToFile("demo.bmp", sdf, 128, 128);
    system("feh demo.bmp --zoom 1000 --force-aliasing");
}
