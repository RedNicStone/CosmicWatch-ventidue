//
// Created by RedNicStone for ProtonAnticheat-server on 9/7/22.
//

#include "../../data/fonts/verdana/Verdana.ttf.h"
#include "../../src/graphics/font/font.h"
#include "../../src/graphics/ui/widgets.h"
#include "../../src/file_writer.h"


int main() {
    FontRenderer font(Verdana_ttf, sizeof(Verdana_ttf), 14);
    UI::StyleSheet style{};
    style.font = &font;
    UI::Button button("test", &style);

    FileWriter::writeImageToFile("demo.bmp", button.getDrawFunction(), 128, 128);
    system("feh demo.bmp --zoom 1000 --force-aliasing");
}
