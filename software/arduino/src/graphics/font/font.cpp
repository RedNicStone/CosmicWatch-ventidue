//
// Created by RedNicStone on 9/5/22.
//

#include <cmath>
#include <cstring>
#include <cassert>

#define STBTT_ifloor(x)   ((int) floor(x))
#define STBTT_iceil(x)    ((int) ceil(x))
#define STBTT_sqrt(x)      sqrt(x)
#define STBTT_pow(x,y)     pow(x,y)
#define STBTT_fmod(x,y)    fmod(x,y)
#define STBTT_cos(x)       cos(x)
#define STBTT_acos(x)      acos(x)
#define STBTT_fabs(x)      fabs(x)
#define STBTT_malloc(x,u)  ((void)(u),malloc(x))
#define STBTT_free(x,u)    ((void)(u),free(x))
#define STBTT_assert(x)    assert(x)
#define STBTT_strlen(x)    strlen(x)
#define STBTT_memcpy       memcpy
#define STBTT_memset       memset

#define STB_TRUETYPE_IMPLEMENTATION
#include "font.h"


void FontRenderer::bakeFont(wchar_t glyphBegin, wchar_t glyphEnd, float size) {
    int w, h;

    for (wchar_t glyph = glyphBegin; glyph < glyphEnd; ++glyph) {
        auto* bitmap = stbtt_GetGlyphBitmap(&fontObject, scale, scale, glyph, &w, &h, nullptr, nullptr);

        bakeData.insert(std::make_pair(glyph, GlyphBitmap{ bitmap, w, h }));
    }
}

void FontRenderer::drawToBuffer(PixelBuffer<uint8_t> *destination, wchar_t glyph, int x, int y) {
    if (!bakeData.contains(glyph))
        return;
    auto& bitmap = bakeData[glyph];
    int i, j, p, q;
    auto image_max = destination->getSize();

    for (i = x, p = 0; p < bitmap.sizeX; i++, p++)
        for (j = y, q = 0; q < bitmap.sizeY; j++, q++)
        {
            if ( i < 0              || j < 0              ||
                i >= image_max.x() || j >= image_max.y() )
                continue;

            auto pixel = bitmap.data[q * bitmap.sizeX + p];
            if (pixel == 0)
                continue;

            destination->setPixel({ (uint32_t) i, image_max.y() - (uint32_t) j - 1 }, pixel);
        }
}

FontRenderer::FontRenderer(const void *fontBlob, size_t blobSize, float fontSize) {
    assert(stbtt_InitFont(&fontObject, (uint8_t*) fontBlob, 0));

    scale = stbtt_ScaleForPixelHeight(&fontObject, fontSize);
    bakeFont(0x0020, 0x00FF, scale);
}

void FontRenderer::renderTextToBuffer(const std::string& text, PixelBuffer<uint8_t> *destination) {
    int ascent, decent, lineGap, advance, lsb, x0, y0, x1, y1;
    stbtt_GetFontVMetrics(&fontObject, &ascent, &decent, &lineGap);

    if (text.length() >= 1)
        stbtt_GetCodepointHMetrics(&fontObject, (int) text[0], &advance, &lsb);
    auto posX = (float) lsb * scale;
    auto posY = (float) ascent * scale;

    int idx = 0;
    while (text[idx]) {
        if (text[idx] == '\n' && text[idx + 1]) {
            stbtt_GetCodepointHMetrics(&fontObject, (int) text[0], &advance, &lsb);

            posX = (float) lsb * scale;
            posY += (float)(ascent - decent + lineGap) * scale;

            ++idx;
            continue;
        }

        auto glyph = stbtt_FindGlyphIndex(&fontObject, (int) text[idx]);
        stbtt_GetGlyphHMetrics(&fontObject, glyph, &advance, &lsb);
        stbtt_GetGlyphBitmapBox(&fontObject, glyph, scale, scale, &x0, &y0, &x1, &y1);

        drawToBuffer(destination, glyph, (int) ((float) lsb * scale + posX) + x0, (int) posY + y0);
        posX += (float) advance * scale;
        if (text[idx + 1])
            posX += scale * (float) stbtt_GetGlyphKernAdvance(&fontObject, glyph, (int) text[idx+1]);

        ++idx;
    }
}

Point2D FontRenderer::estimateTextSize(const std::string &text) {
    int ascent, decent, lineGap, advance, lsb;
    stbtt_GetFontVMetrics(&fontObject, &ascent, &decent, &lineGap);

    if (text.length() >= 1)
        stbtt_GetCodepointHMetrics(&fontObject, (int) text[0], nullptr, &lsb);
    auto posX = (float) lsb * scale;
    auto posY = (float) ascent * scale;

    int idx = 0;
    while (text[idx]) {
        if (text[idx] == '\n') {
            if (text[idx + 1])
                stbtt_GetCodepointHMetrics(&fontObject, (int) text[idx + 1], nullptr, &lsb);

            posX = (float) lsb * scale;
            posY += (float)(ascent - decent + lineGap) * scale;

            ++idx;
            continue;
        }

        auto glyph = stbtt_FindGlyphIndex(&fontObject, (int) text[idx]);
        stbtt_GetGlyphHMetrics(&fontObject, glyph, &advance, &lsb);

        posX += (float) advance * scale;
        if (text[idx + 1])
            posX += scale * (float) stbtt_GetGlyphKernAdvance(&fontObject, glyph, (int) text[idx+1]);

        ++idx;
    }
}

FontRenderer::~FontRenderer() {
    for (auto& pair : bakeData)
        delete[] pair.second.data;
}

void TextObject::redraw() {
    if (!text.empty() && imageBuffer.getSize() != Point2D(0u, 0u) && font != nullptr)
        font->renderTextToBuffer(text, &imageBuffer);
}

TextObject::TextObject(FontRenderer* font, Point2D size, std::string  text)
           : imageBuffer(size), font(font), text(std::move(text)) {
    redraw();
}

void TextObject::updateText(const std::string &newText) {
    if (text == newText)
        return;
    text = newText;
    redraw();
}

void TextObject::updateSize(Point2D newSize) {
    if (imageBuffer.getSize() == newSize)
        return;
    imageBuffer(newSize);
    redraw();
}

void TextObject::updateFont(FontRenderer *newFont) {
    if (font == newFont)
        return;
    font = newFont;
    redraw();
}

