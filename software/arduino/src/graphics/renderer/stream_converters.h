//
// Created by nic on 11/08/22.
//

#ifndef GRAPHICS_STREAM_CONVERTERS_H
#define GRAPHICS_STREAM_CONVERTERS_H

#include "sdf_mix.h"
#include "../types.h"


class SType {};

template<class FT, typename PixelType>
concept StreamSignature = std::is_base_of_v<SType, FT> && requires(FT f, Point2D p)
{
    { f(p) } -> std::convertible_to<PixelType>;
};

template<typename PixelType, SDF::MixSignature<PixelType> FT>
class SRasterizer : public SType, FT {
  public:
    explicit SRasterizer(FT& ft) : FT(std::move(ft)) { };
    explicit SRasterizer(FT&& ft) : FT(std::move(ft)) { };

    inline PixelType operator() (Point2D pos) {
        return FT::operator() (vec2(pos));
    }
};

template<SDF::MixSignature<RGB8> FT>
class SPack565 : public SType, FT {
  public:
    explicit SPack565(FT& ft) : FT(std::move(ft)) { };
    explicit SPack565(FT&& ft) : FT(std::move(ft)) { };

    inline RGB565 operator() (Point2D pos) {
        auto color = FT::operator() (vec2(pos));
        bool x = color.y() > 128;
        //return (color.x() & 0xF8) << 8 | (color.y() & 0xFC) << 3 | color.z() >> 3;                   // big endian
        return color.x() & 0xF8 | color.y() >> 5 | (color.y() & 0xFC) << 11 | (color.z() & 0xF8) << 5; // little endian
    }
};

#endif //GRAPHICS_STREAM_CONVERTERS_H
