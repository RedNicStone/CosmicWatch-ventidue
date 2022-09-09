//
// Created by nic on 02/08/22.
//

#pragma once

#ifndef GRAPHICS_SDF_PRIMITIVES_H
#define GRAPHICS_SDF_PRIMITIVES_H

#include <functional>
#include <utility>

#include "../vector.h"


namespace SDF {

  typedef float SDFDistance;

  class PType { };

  template <typename FT>
  concept DistanceSignature = std::is_base_of_v<PType, FT> && requires(FT f, vec2 p)
  {
      { f(p) } -> std::convertible_to<SDFDistance>;
  };

}

#endif //GRAPHICS_SDF_PRIMITIVES_H
