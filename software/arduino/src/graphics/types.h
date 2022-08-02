//
// Created by RedNicStone for graphics on 01/08/22.
//

#ifndef GRAPHICS_TYPES_H
#define GRAPHICS_TYPES_H

#include "vector.h"

inline constexpr char operator "" _c( unsigned long long arg ) noexcept
{
    return static_cast< char >( arg );
}

inline constexpr unsigned char operator "" _uc( unsigned long long arg ) noexcept
{
    return static_cast< unsigned char >( arg );
}

typedef uvec2 Point2D;

struct Region2D {
    uvec2 begin;
    uvec2 end;
};

template<typename T>
class PixelBuffer {
  protected:
    Point2D size;

    T* data;

  public:
    explicit PixelBuffer(Point2D size);

    Point2D getSize() { return size; }

    virtual T getPixel(Point2D pos);
    virtual bool setPixel(T value, Point2D pos);

    virtual bool nativeTranspose(PixelBuffer<T>& buffer, Region2D region, Point2D destination);
    virtual bool fill(T value, Region2D region);

    T* getDataHandle() { return data; }
};

template<typename T>
class UnsafePixelBuffer : public PixelBuffer<T> {
  public:
    virtual T getPixel(Point2D pos);
    virtual bool setPixel(T value, Point2D pos);

    virtual bool nativeTranspose(PixelBuffer<T>& buffer, Region2D region, Point2D destination);
    virtual bool fill(T value, Region2D region);
};

template<typename T>
T UnsafePixelBuffer<T>::getPixel(Point2D pos) {
    return PixelBuffer<T>::data[pos.y() * PixelBuffer<T>::size.x() + pos.x()];
}

template<typename T>
bool UnsafePixelBuffer<T>::setPixel(T value, Point2D pos) {
    PixelBuffer<T>::data[pos.y() * PixelBuffer<T>::size.x() + pos.x()] = value;
    return true;
}

template<typename T>
bool UnsafePixelBuffer<T>::nativeTranspose(PixelBuffer<T> &buffer, Region2D region, Point2D destination) {
    for (unsigned int x = 0; x < region.end.x() - region.begin.x(); ++x) {
        for (unsigned int y = 0; y < region.end.y() - region.begin.y(); ++y) {
            auto pos = Point2D(x, y);
            T value = getPixel(region.begin + pos);
            buffer.setPixel(value, destination + pos);
        }
    }
    return true;
}

template<typename T>
bool UnsafePixelBuffer<T>::fill(T value, Region2D region) {
    for (unsigned int x = region.begin.x(); x < region.end.x(); ++x) {
        for (unsigned int y = region.begin.y(); y < region.end.y(); ++y) {
            setPixel(value, Point2D(x, y));
        }
    }

    return true;
}

template<typename TFrom, typename TTo>
class PixelTranspositionEngine {
  public:
    static TTo transpose(TFrom value) {
        return TTo(value);
    }
};

template<typename TFrom, typename TTo, class PixelEngine>
requires std::is_base_of_v<PixelTranspositionEngine<TFrom, TTo>, PixelEngine>
class BufferTranspositionEngine {
  private:
    static bool transpositionCheck(const PixelBuffer<TTo>& bufferOut, const PixelBuffer<TFrom>& bufferIn,
                                   const Region2D& region, const Point2D& destination) {
        return region.begin.x() > bufferIn.size.x() || region.begin.y() > bufferIn.size.y() ||
               region.begin.x() > region.end.x() || region.begin.x() > region.end.x() ||
               destination.x() - region.begin.x() + region.end.x() > bufferOut.size.x() ||
               destination.y() - region.begin.y() + region.end.y() > bufferOut.size.y();
    }

  public:
    static bool transpose(PixelBuffer<TTo>& bufferOut, const PixelBuffer<TFrom>& bufferIn,
                          Region2D region, Point2D destination) {
        if (transpositionCheck(bufferOut, bufferIn, region, destination))
            return false;

        for (unsigned int x = 0; x < region.end.x() - region.begin.x(); ++x) {
            for (unsigned int y = 0; y < region.end.y() - region.begin.y(); ++y) {
                auto pos = Point2D(x, y);
                TFrom value = bufferIn.getPixel(region.begin + pos);
                bufferOut.setPixel(PixelEngine::transpose(value), destination + pos);
            }
        }
        return true;
    }
};

typedef u_int8_t R8;
typedef ucvec2 RG8;
typedef ucvec3 RGB8;
typedef ucvec4 RGBA8;

typedef u_int16_t R16;
typedef usvec2 RG16;
typedef usvec3 RGB16;
typedef usvec4 RGBA16;

typedef u_int32_t R32;
typedef uivec2 RG32;
typedef uivec3 RGB32;
typedef uivec4 RGBA32;

template<typename T>
PixelBuffer<T>::PixelBuffer(Point2D size) {
    data = new T[size.x() * size.y()];
    PixelBuffer<T>::size = size;
}

template<typename T>
T PixelBuffer<T>::getPixel(Point2D pos) {
    if (pos.x() > size.x() || pos.y() > size.y())
        return T();

    return data[pos.y() * size.x() + pos.x()];
}

template<typename T>
bool PixelBuffer<T>::setPixel(T value, Point2D pos) {
    if (pos.x() > size.x() || pos.y() > size.y())
        return false;

    data[pos.y() * size.x() + pos.x()] = value;
    return true;
}

template<typename T>
bool PixelBuffer<T>::nativeTranspose(PixelBuffer<T> &buffer, Region2D region, Point2D destination) {
    if (region.begin.x() > size.x() || region.begin.y() > size.y() ||
        region.begin.x() > region.end.x() || region.begin.x() > region.end.x() ||
        destination.x() - region.begin.x() + region.end.x() > buffer.size.x() ||
        destination.y() - region.begin.y() + region.end.y() > buffer.size.y())
        return false;

    for (unsigned int x = 0; x < region.end.x() - region.begin.x(); ++x) {
        for (unsigned int y = 0; y < region.end.y() - region.begin.y(); ++y) {
            auto pos = Point2D(x, y);
            T value = getPixel(region.begin + pos);
            buffer.setPixel(value, destination + pos);
        }
    }
    return true;
}

template<typename T>
bool PixelBuffer<T>::fill(T value, Region2D region) {
    if (region.end.x() > size.x() || region.end.y() > size.y() ||
        region.begin.x() > region.end.x() || region.begin.x() > region.end.x() ||
        0 > region.begin.x() || 0 > region.begin.x())
        return false;

    for (unsigned int x = region.begin.x(); x < region.end.x(); ++x) {
        for (unsigned int y = region.begin.y(); y < region.end.y(); ++y) {
            setPixel(value, Point2D(x, y));
        }
    }

    return true;
}

#endif //GRAPHICS_TYPES_H
