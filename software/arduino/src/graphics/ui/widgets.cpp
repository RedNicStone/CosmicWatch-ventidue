//
// Created by RedNicStone for ProtonAnticheat-server on 9/4/22.
//

#include "widgets.h"

using namespace UI;

UIPixelType Button::renderFunction(const vec2 &pos) {
    if (!visible)
        return {0.0f, 0.0f, 0.0f, 1.0f};

    vec4 color;
}
