//
// Created by nic on 11/08/22.
//

#pragma once

#ifndef GRAPHICS_STREAM_CONVERTERS_H
#define GRAPHICS_STREAM_CONVERTERS_H

#include <limits>

#include "sdf_mix.h"
#include "../types.h"


template<class FT, typename PixelType>
concept StreamSignature = requires(FT f, Point2D p)
{
    { f(p) } -> std::convertible_to<PixelType>;
};

namespace SDF {

  class SType {};

  template<typename PixelType, SDF::MixSignature<PixelType> FT>
  class SRasterizer : public SType, FT {
    public:
      explicit SRasterizer(FT& ft) : FT(std::move(ft)) { };
      explicit SRasterizer(FT&& ft) : FT(std::move(ft)) { };

      inline PixelType operator() (Point2D pos) {
          return FT::operator() (vec2(pos));
      }
  };

  template<StreamSignature<RGB8> FT>
  class SPack565 : public SType, FT {
    public:
      explicit SPack565(FT& ft) : FT(std::move(ft)) { };
      explicit SPack565(FT&& ft) : FT(std::move(ft)) { };

      inline RGB565 operator() (Point2D pos) {
          auto color = FT::operator() (pos);
          bool x = color.y() > 128;
          //return (color.x() & 0xF8) << 8 | (color.y() & 0xFC) << 3 | color.z() >> 3;                   // big endian
          return (color.x() & 0xF8)         | ( color.y() >> 5) |
                 ((color.y() & 0xFC) << 11) | ((color.z() & 0xF8) << 5); // little endian
      }
  };

  template<typename T, size_t N, StreamSignature<vec_abs<T, N>> FT>
  class STypeSize : public SType, FT {
    public:
      explicit STypeSize(FT& ft) : FT(std::move(ft)) { };
      explicit STypeSize(FT&& ft) : FT(std::move(ft)) { };

      inline vec_abs<float, N> operator() (Point2D pos) {
          vec_abs<float, N> ret;
          for (size_t i = 0; i < N; i++)
              ret[i] = (float)FT::operator() (pos) / (float)std::numeric_limits<T>::max();
      }
  };

  template<StreamSignature<uint8_t> FT>
  class SGrayscale : public SType, FT {
    public:
      explicit SGrayscale(FT& ft) : FT(std::move(ft)) { };
      explicit SGrayscale(FT&& ft) : FT(std::move(ft)) { };

      inline RGB8 operator() (Point2D pos) {
          auto color = FT::operator() (pos);
          return {color, color, color};
      }
  };

  template<typename PixelType, StreamSignature<uint8_t> FT>
  class SSimpleMix : public SType, FT {
    private:
      PixelType FColor;
      PixelType BColor;

    public:
      explicit SSimpleMix(FT& f, const PixelType& FColor, const PixelType& BColor) :
          FT(std::move(f)), FColor(FColor), BColor(BColor) {}
      explicit SSimpleMix(FT&& f, const PixelType& FColor, const PixelType& BColor) :
      FT(std::move(f)), FColor(FColor), BColor(BColor) {}

      inline PixelType operator() (Point2D pos) {
          float factor = (float) FT::operator() (pos) / (float) std::numeric_limits<uint8_t>::max();
          return (FColor * factor) + (BColor * (1.0f - factor));
      }
  };

  template<typename T, StreamSignature<vec_abs<T, 4>> FT1, StreamSignature<vec_abs<T, 4>> FT2>
  class SAlphaMix : public SType, FT1, FT2 {
    public:
      explicit SAlphaMix(FT1& f1, FT2& f2) :
          FT1(std::move(f1)), FT2(std::move(f2)) {}
      explicit SAlphaMix(FT1&& f1, FT2&& f2) :
          FT1(std::move(f1)), FT2(std::move(f2)) {}

      inline vec_abs<T, 4> operator() (Point2D pos) {
          float factor = (float) FT1::operator() (pos).a() / (float) std::numeric_limits<T>::max();
          return (FT1::operator() (pos) * factor) + (FT2::operator() (pos) * (1.0f - factor));
      }
  };

}

#endif //GRAPHICS_STREAM_CONVERTERS_H
