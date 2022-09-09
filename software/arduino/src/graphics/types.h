//
// Created by RedNicStone for graphics on 01/08/22.
//

#pragma once

#ifndef GRAPHICS_TYPES_H
#define GRAPHICS_TYPES_H

#include <cstdint>

#include "vector.h"


inline constexpr char operator "" _c( unsigned long long arg ) noexcept {
    return static_cast< char >( arg );
}

inline constexpr unsigned char operator "" _uc( unsigned long long arg ) noexcept {
    return static_cast< unsigned char >( arg );
}

typedef uvec2 Point2D;

struct Region2D {
    Point2D begin;
    Point2D end;
};

template<typename T>
class PixelBuffer {
  protected:
    Point2D size;

    T* data;
    bool isDataOwned = true;

    explicit PixelBuffer(Point2D size, T* data) : size(size), data(data) {};

  public:
    explicit PixelBuffer(Point2D size);
    PixelBuffer(PixelBuffer<T>& buffer) : data(buffer.data), size(buffer.size), isDataOwned(false) { };
    PixelBuffer(PixelBuffer<T>&& buffer)  noexcept : data(buffer.data), size(buffer.size), isDataOwned(false) { };

    [[nodiscard]] inline Point2D getSize() const { return size; }

    inline T operator() (Point2D pos) { return getPixel(pos); }

    inline virtual T getPixel(Point2D pos) const;
    inline virtual bool setPixel(Point2D pos, T value);

    virtual bool nativeTranspose(PixelBuffer<T>* buffer, Region2D region, Point2D destination);
    virtual bool fill(T value, Region2D region);

    inline T* getDataHandle() { return data; }
    inline const T* getDataHandle() const { return data; }

    virtual ~PixelBuffer() { if (isDataOwned) delete[] data; }
};

template<typename T>
class UnsafePixelBuffer : public PixelBuffer<T> {
  public:
    explicit UnsafePixelBuffer(Point2D size) : PixelBuffer<T>(size) { };
    UnsafePixelBuffer(Point2D size, T* data) : PixelBuffer<T>(size, data) { PixelBuffer<T>::isDataOwned = false; }

    inline virtual T getPixel(Point2D pos) const;
    inline virtual bool setPixel(Point2D pos, T value);

    virtual bool nativeTranspose(PixelBuffer<T>* buffer, Region2D region, Point2D destination);
    virtual bool fill(T value, Region2D region);
};

template<typename TFrom, typename TTo>
class SimplePixelTranspositionEngine {
  public:
    inline TTo operator() (TFrom value) {
        return TTo(value);
    }
};

template <typename FT, typename TFrom, typename TTo>
concept PixelEngineSignature = requires(FT f, TFrom v)
{
    { f(v) } -> std::convertible_to<TTo>;
};

template<typename TFrom, typename TTo, PixelEngineSignature<TFrom, TTo> PixelEngine>
class BufferTranspositionEngine : PixelEngine {
  private:
    inline static bool transpositionCheck(const PixelBuffer<TTo>& bufferOut, const PixelBuffer<TFrom>& bufferIn,
                                   const Region2D& region, const Point2D& destination) {
        return region.begin.x() > bufferIn.getSize().x() || region.begin.y() > bufferIn.getSize().y() ||
               region.begin.x() > region.end.x() || region.begin.x() > region.end.x() ||
               destination.x() - region.begin.x() + region.end.x() > bufferOut.getSize().x() ||
               destination.y() - region.begin.y() + region.end.y() > bufferOut.getSize().y();
    }

  public:
    static bool transpose(PixelBuffer<TTo>& bufferOut, const PixelBuffer<TFrom>& bufferIn,
                          Region2D region, Point2D destination) {
        if (transpositionCheck(bufferOut, bufferIn, region, destination))
            return false;

        for (unsigned int x = 0; x < region.end.x() - region.begin.x(); ++x) {
            for (unsigned int y = 0; y < region.end.y() - region.begin.y(); ++y) {
                auto pos = Point2D(x, y);
                auto pos2 = pos + region.begin;
                //Serial.println(F("Transposing Pixel ") + String(region.begin.x() + x) + ", " + String(region.begin.y
                //    () + y));
                TFrom value = bufferIn.getPixel(pos2);
                bufferOut.setPixel(destination + pos, PixelEngine::transpose(value));
            }
        }
        return true;
    }

    explicit BufferTranspositionEngine(PixelEngine& engine) : PixelEngine(std::move(engine)) {};
    explicit BufferTranspositionEngine(PixelEngine&& engine) : PixelEngine(std::move(engine)) {};
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

typedef uint16_t RGB565;

template<typename T>
PixelBuffer<T>::PixelBuffer(Point2D size) {
    data = new T[size.x() * size.y()]();
    //Serial.println(F("Size: ") + String(size.x()) + String(size.y()));
    PixelBuffer<T>::size = size;
}

template<typename T>
T PixelBuffer<T>::getPixel(Point2D pos) const {
    //Serial.println(F("With value "));
    if (pos.x() > size.x() || pos.y() > size.y())
        return T();

    return data[pos.y() * size.x() + pos.x()];
}

template<typename T>
bool PixelBuffer<T>::setPixel(Point2D pos, T value) {
    if (pos.x() > size.x() || pos.y() > size.y())
        return false;

    data[pos.y() * size.x() + pos.x()] = value;
    return true;
}

template<typename T>
bool PixelBuffer<T>::nativeTranspose(PixelBuffer<T> *buffer, Region2D region, Point2D destination) {
    if (region.begin.x() > size.x() || region.begin.y() > size.y() ||
        region.begin.x() > region.end.x() || region.begin.x() > region.end.x() ||
        destination.x() - region.begin.x() + region.end.x() > buffer->size.x() ||
        destination.y() - region.begin.y() + region.end.y() > buffer->size.y())
        return false;

    for (unsigned int x = 0; x < region.end.x() - region.begin.x(); ++x) {
        for (unsigned int y = 0; y < region.end.y() - region.begin.y(); ++y) {
            auto pos = Point2D(x, y);
            T value = getPixel(region.begin + pos);
            buffer->setPixel(destination + pos, value);
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
            setPixel(Point2D(x, y), value);
        }
    }

    return true;
}

template<typename T>
T UnsafePixelBuffer<T>::getPixel(Point2D pos) const {
    return PixelBuffer<T>::data[pos.y() * PixelBuffer<T>::size.x() + pos.x()];
}

template<typename T>
bool UnsafePixelBuffer<T>::setPixel(Point2D pos, T value) {
    PixelBuffer<T>::data[pos.y() * PixelBuffer<T>::size.x() + pos.x()] = value;
    return true;
}

template<typename T>
bool UnsafePixelBuffer<T>::nativeTranspose(PixelBuffer<T> *buffer, Region2D region, Point2D destination) {
    for (unsigned int x = 0; x < region.end.x() - region.begin.x(); ++x) {
        for (unsigned int y = 0; y < region.end.y() - region.begin.y(); ++y) {
            auto pos = Point2D(x, y);
            T value = getPixel(region.begin + pos);
            buffer->setPixel(destination + pos, value);
        }
    }
    return true;
}

template<typename T>
bool UnsafePixelBuffer<T>::fill(T value, Region2D region) {
    for (unsigned int x = region.begin.x(); x < region.end.x(); ++x) {
        for (unsigned int y = region.begin.y(); y < region.end.y(); ++y) {
            setPixel(Point2D(x, y), value);
        }
    }

    return true;
}

#endif //GRAPHICS_TYPES_H
