//
// Created by RedNicStone for ProtonAnticheat-server on 9/4/22.
//

#ifndef GRAPHICS_STYLE_H
#define GRAPHICS_STYLE_H

#include <string>

#include "../types.h"


const vec3 HEXtoRGB(uint32_t hexValue) {
    vec3 rgbColor;
    rgbColor.r() = ((hexValue >> 16) & 0xFF) / 255.0;
    rgbColor.g() = ((hexValue >> 8) & 0xFF) / 255.0;
    rgbColor.b() = ((hexValue) & 0xFF) / 255.0;
}

const vec4 HEXtoRGBA(uint32_t hexValue) {
    vec4 rgbColor;
    rgbColor.r() = ((hexValue >> 24) & 0xFF) / 255.0;
    rgbColor.g() = ((hexValue >> 16) & 0xFF) / 255.0;
    rgbColor.b() = ((hexValue >> 8) & 0xFF) / 255.0;
    rgbColor.a() = ((hexValue) & 0xFF) / 255.0;
}

const vec3 HEXtoRGB(std::string hexValue) {
    vec3 rgbColor;
    sscanf(hexValue.c_str() + 1, "%02f%02f%02f", &rgbColor.r(), &rgbColor.g(), &rgbColor.b());
}

const vec4 HEXtoRGBA(std::string hexValue) {
    vec4 rgbColor;
    sscanf(hexValue.c_str() + 1, "%02f%02f%02f%02f", &rgbColor.r(), &rgbColor.g(), &rgbColor.b(), &rgbColor.a());
}

class StyleSheet {
    vec4 background         = HEXtoRGBA(0xffffffFF);
    vec4 deactivated        = HEXtoRGBA(0xe0e0e0FF);
    vec4 text               = HEXtoRGBA(0x000000FF);
    vec4 highlighted        = HEXtoRGBA(0x8edaffFF);
    vec4 active             = HEXtoRGBA(0x60cbffFF);
    vec4 element            = HEXtoRGBA(0x2cbaffFF);
    vec4 border             = HEXtoRGBA(0x4f4f4fFF);
};

#endif //GRAPHICS_STYLE_H
