//
// Created by RedNicStone for ProtonAnticheat-server on 9/4/22.
//

#include "widgets.h"
#include "../algorithms/sdf_generators.h"
#include "../renderer/sdf_mix.h"
#include "../renderer/stream_converters.h"

using namespace UI;

Button::Button(const std::string &description, StyleSheet* style, bool activated) : active(activated), style(style),
                                                                                    text(style->font, {}, description) {
    auto textSize = style->font->estimateTextSize(description);
    text.updateSize(textSize);
    size = textSize + Point2D(4u, 4u);
}

UIPixelType Button::renderFunction(const Point2D &pos) {
    if (!visible)
        return {};

    auto shape = SDF::GRoundedSquare(vec2(size), {2.0f, 2.0f, 2.0f, 2.0f});
    auto color = SDF::MSimpleBinary<UIPixelType, decltype(shape)>(shape, UIPixelType(), style->element);
    auto background = SDF::SRasterizer<UIPixelType, decltype(color)>(color);
    if (AABB(pos, {{ 2u, 2u }, size - Point2D(2u, 2u)})) {
        auto textFunction = SDF::SSimpleMix(text.getBuffer(), style->text, style->element);
        auto renderFunction = SDF::SAlphaMix<float, decltype(textFunction), decltype(background)>
            (textFunction, background);
        return renderFunction(pos);
    }
    return background(pos);
}
