//
// Created by nic on 03/08/22.
//

#include <iostream>

#include "../../src/graphics/algorithms/sdf_generators.h"

int main() {
    std::cout << SDFCircle(5).getDistance(SDFPoint(2.0f, 2.0f));
}
