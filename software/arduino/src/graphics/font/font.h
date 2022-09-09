//
// Created by RedNicStone on 9/5/22.
//

#pragma once

#ifndef GRAPHICS_FONT_H
#define GRAPHICS_FONT_H

#ifndef __unix__
#include "../../lib/stb/stb_truetype.h"
#else
#include <stb_truetype.h>
#endif
#include <map>
#include <vector>
#include <string>

#include "../vector.h"
#include "../types.h"


class FontRenderer {
  private:
    struct GlyphBitmap {
        uint8_t *data;
        int sizeX;
        int sizeY;
    };

    float scale{};
    stbtt_fontinfo fontObject{};

    std::map<wchar_t, GlyphBitmap> bakeData{};

    void bakeFont(wchar_t glyphBegin, wchar_t glyphEnd, float scale);
    void drawToBuffer(PixelBuffer<uint8_t> *destination, wchar_t glyph, int x, int y);

  public:
    FontRenderer(const void *fontBlob, size_t blobSize, float fontSize);

    void renderTextToBuffer(const std::string& text, PixelBuffer<uint8_t>* destination);
    Point2D estimateTextSize(const std::string& text);

    ~FontRenderer();
};

class TextObject {
  private:
    FontRenderer* font;
    PixelBuffer<uint8_t> imageBuffer;
    std::string text;

    void redraw();

  public:
    TextObject(FontRenderer* font, Point2D size, std::string  text = "");

    void updateText(const std::string& newText = "");
    void updateSize(Point2D newSize);
    void updateFont(FontRenderer* newFont);

    std::string getCurrentText() { return text; }
    Point2D getCurrentSize() { return imageBuffer.getSize(); }
    FontRenderer* getCurrentFont() { return font; }

    PixelBuffer<uint8_t>& getBuffer() { return imageBuffer; }
};

#endif //GRAPHICS_FONT_H
