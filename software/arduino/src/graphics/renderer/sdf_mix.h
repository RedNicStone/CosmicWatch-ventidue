//
// Created by nic on 05/08/22.
//

#ifndef GRAPHICS_SDF_MIX_H
#define GRAPHICS_SDF_MIX_H

#ifdef abs
#undef abs
#endif

#include "../types.h"
#include "../algorithms/sdf_primitives.h"


namespace SDF {

  class MType {};

  template<class FT, typename PixelType>
  concept MixSignature = std::is_base_of_v<MType, FT> && requires(FT f, vec2 p)
  {
      { f(p) } -> std::convertible_to<PixelType>;
  };

  template<typename PixelType, DistanceSignature FT>
  class MSimpleBinary : public MType, FT {
    private:
      PixelType FColor;
      PixelType BColor;

    public:
      inline PixelType operator()(const vec2& pos) const {
          return FT::operator() (pos) > 0 ? BColor : FColor;
      }

      explicit MSimpleBinary(FT& f, const PixelType& FColor, const PixelType& BColor) :
          FT(std::move(f)), FColor(FColor), BColor(BColor) {}
      explicit MSimpleBinary(FT&& f, const PixelType& FColor, const PixelType& BColor) :
          FT(std::move(f)), FColor(FColor), BColor(BColor) {}
  };

  template<DistanceSignature FT>
  class MVisualization : public MType, FT {
    private:

    public:
      vec3 operator()(const vec2& pos) const {
          float d = FT::operator() (pos) * 0.01;
          vec3 col = (d>0.0) ? vec3(0.9f,0.6f,0.3f) : vec3(0.65f,0.85f,1.0f);
          col *= 1.0f - std::exp(-6.0f * std::abs(d));
          col *= 0.8f + 0.2f * std::cos(150.0f * d);
          return mix(col, vec3(1.0f), 1.0f - smoothstep(0.0f, 0.01f, std::abs(d)));
      }

      explicit MVisualization(FT& f) : FT(std::move(f)) {}
      explicit MVisualization(FT&& f) : FT(std::move(f)) {}
  };

  template<MixSignature<vec3> FT>
  class MRGB8 : public MType, FT {
    private:

    public:
      inline RGB8 operator()(const vec2& pos) const {
          return RGB8(FT::operator() (pos) * 255);
      }

      explicit MRGB8(FT& f) : FT(std::move(f)) {}
      explicit MRGB8(FT&& f) : FT(std::move(f)) {}
  };

}

#endif //GRAPHICS_SDF_MIX_H
