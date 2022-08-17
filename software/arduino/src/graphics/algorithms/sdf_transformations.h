//
// Created by nic on 02/08/22.
//

#ifndef GRAPHICS_SDF_TRANSFORMATIONS_H
#define GRAPHICS_SDF_TRANSFORMATIONS_H

#include "sdf_primitives.h"


namespace SDF {

  template <DistanceSignature FT>
  class TTranslate : FT {
    private:
      vec2 offset;

    public:
      inline float operator()(const vec2& pos) const {
          return FT::operator() (pos - offset);
      }

      explicit TTranslate(FT& f, const vec2& offset) : FT(std::move(f)), offset(offset) {}
      explicit TTranslate(FT&& f, const vec2& offset) : FT(std::move(f)), offset(offset) {}
  };

  template <DistanceSignature FT>
  class TRotate : FT {
    private:
      float rotation;

    public:
      inline float operator()(const vec2& pos) const {
          const float PI = 3.14159;
          float angle = rotation / 360 * PI * 2 * -1;
          float sine = std::sin(angle), cosine = std::cos(angle);
          vec2 newPos = {cosine * pos.x() + sine * pos.y(),
                         cosine * pos.y() - sine * pos.x()};
          return FT::operator() (newPos);
      }

      explicit TRotate(FT& f, float rotation) : FT(std::move(f)), rotation(rotation) {}
      explicit TRotate(FT&& f, float rotation) : FT(std::move(f)), rotation(rotation) {}
  };

  template <DistanceSignature FT>
  class TScale : FT {
    private:
      float scale;

    public:
      inline float operator()(const vec2& pos) const {
          return FT::operator() (pos / scale) * scale;
      }

      explicit TScale(FT& f, float scale) : FT(std::move(f)), scale(scale) {}
      explicit TScale(FT&& f, float scale) : FT(std::move(f)), scale(scale) {}
  };

}

#endif //GRAPHICS_SDF_TRANSFORMATIONS_H
