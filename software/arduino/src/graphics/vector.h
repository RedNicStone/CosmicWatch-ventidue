//
// Created by RedNicStone for graphics on 01/08/22.
//

#pragma once

#ifndef GRAPHICS_VECTOR_H
#define GRAPHICS_VECTOR_H

#ifdef __unix__
#include <type_traits>
#else
#include <ArxTypeTraits.h>
#endif

#include <array>
#include <cstddef>
#include <cmath>
#include <algorithm>

#ifdef abs
#undef abs
#endif


template<typename T, typename ...Ts>
constexpr bool all_convertible_to() {
    return (std::is_convertible<T, Ts>::value && ...);
}

template<typename T, size_t N>
class vec_abs {
  public:
    // constants

    static constexpr unsigned short X = 0;  // index X
    static constexpr unsigned short Y = 1;  // index Y
    static constexpr unsigned short Z = 2;  // index Z
    static constexpr unsigned short W = 3;  // index W

    static constexpr unsigned short R = 0;  // index R (red)
    static constexpr unsigned short G = 1;  // index G (green)
    static constexpr unsigned short B = 2;  // index B (blue)
    static constexpr unsigned short A = 3;  // index A (alpha)


    // constructors

    vec_abs();  // construct empty

    explicit vec_abs(const std::array<T, N> &arr);  // construct from array

    // disabled due to issue with immediate values
    /*template<typename ...Ts> requires // only compile if:
    std::conjunction<std::is_convertible<Ts, T>...>::value &&  // all can be converted to T
    (sizeof...(Ts) == N)  // there are N arguments
    explicit vec_abs(const Ts&&... values);  // construct from multiple arguments*/

    template<typename ...Ts> requires (sizeof...(Ts) == N)  // there are N arguments
    explicit(N <= 1) vec_abs(const Ts... values);  // construct from multiple arguments

    template<class _ = void> requires // only compile if:
    (N > 1)  // there are N arguments
    explicit vec_abs(T value);  // construct from multiple arguments

    template<typename TOther> requires // only compile if:
    std::is_convertible<TOther, T>::value  // all can be converted to T
    explicit vec_abs(const vec_abs<TOther, N>& vector);  // construct from multiple arguments

    template<typename TOther>
    explicit vec_abs(const vec_abs<TOther, N>& vector);  // construct from multiple arguments


    // Getters

    inline T operator[](int index) const { return pData[index]; };
    inline T& operator[](int index) { return pData[index]; };


    template<class _ = void> requires (N >= 1)  // If there are enough elements
    inline T x() const { return pData[0]; };  // get X

    template<class _ = void> requires (N >= 2)  // If there are enough elements
    inline T y() const { return pData[1]; };  // get Y

    template<class _ = void> requires (N >= 3)  // If there are enough elements
    inline T z() const { return pData[2]; };  // get Z

    template<class _ = void> requires (N >= 4)  // If there are enough elements
    inline T w() const { return pData[3]; };  // get W

    template<class _ = void> requires (N >= 1)  // If there are enough elements
    inline T r() const { return pData[0]; };  // get R

    template<class _ = void> requires (N >= 2)  // If there are enough elements
    inline T g() const { return pData[1]; };  // get G

    template<class _ = void> requires (N >= 3)  // If there are enough elements
    inline T b() const { return pData[2]; };  // get B

    template<class _ = void> requires (N >= 4)  // If there are enough elements
    inline T a() const { return pData[3]; };  // get A

    template<class _ = void> requires (N >= 1)  // If there are enough elements
    inline T& x() { return pData[0]; };  // get X

    template<class _ = void> requires (N >= 2)  // If there are enough elements
    inline T& y() { return pData[1]; };  // get Y

    template<class _ = void> requires (N >= 3)  // If there are enough elements
    inline T& z() { return pData[2]; };  // get Z

    template<class _ = void> requires (N >= 4)  // If there are enough elements
    inline T& w() { return pData[3]; };  // get W

    template<class _ = void> requires (N >= 1)  // If there are enough elements
    inline T& r() { return pData[0]; };  // get R

    template<class _ = void> requires (N >= 2)  // If there are enough elements
    inline T& g() { return pData[1]; };  // get G

    template<class _ = void> requires (N >= 3)  // If there are enough elements
    inline T& b() { return pData[2]; };  // get B

    template<class _ = void> requires (N >= 4)  // If there are enough elements
    inline T& a() { return pData[3]; };  // get A

#ifdef __unix__
    template<typename ...D> requires // only compile if:
    std::conjunction<std::is_convertible<D, unsigned short>...>::value  // all can be converted to unsigned short
    auto swizzle(D... indices) const -> vec_abs<T, sizeof...(indices)>;
#endif

    template<class _ = void> requires std::is_arithmetic_v<T>
    inline explicit operator T();

    template<class _ = void> requires std::is_arithmetic_v<T>
    inline T getLength() const;


    //actual functions

    template<class _ = void> requires std::is_arithmetic_v<T>
    inline vec_abs operator+(const vec_abs<T, N>& vector) const;
    template<class _ = void> requires std::is_arithmetic_v<T>
    inline vec_abs operator-(const vec_abs<T, N>& vector) const;
    //template<class _ = void> requires std::is_arithmetic_v<T>
    //const vec_abs& operator*(const vec_abs<T, N>& vector);  // cross product
    template<class _ = void> requires std::is_arithmetic_v<T>
    inline vec_abs operator*(const T& fac) const;  // scalar product
    template<class _ = void> requires std::is_arithmetic_v<T>
    inline vec_abs operator/(const T& fac) const;  // scalar division

    template<class _ = void> requires std::is_arithmetic_v<T>
    inline const vec_abs& operator+=(const vec_abs& vector);
    template<class _ = void> requires std::is_arithmetic_v<T>
    inline const vec_abs& operator-=(const vec_abs& vector);
    //template<class _ = void> requires std::is_arithmetic_v<T>
    //const vec_abs& operator*=(const vec_abs& vector);
    template<class _ = void> requires std::is_arithmetic_v<T>
    inline const vec_abs& operator*=(const T& value);
    template<class _ = void> requires std::is_arithmetic_v<T>
    inline const vec_abs& operator/=(const T& value);

    template<class _ = void> requires std::is_arithmetic_v<T>
    inline vec_abs normalize() const;
    template<class _ = void> requires std::is_arithmetic_v<T>
    inline vec_abs absolute() const;
    //template<class _ = void> requires std::is_arithmetic_v<T>
    //const vec_abs& cross(const vec_abs& vec);
    template<class _ = void>
    inline bool operator==(const vec_abs& vector) const;
    template<class _ = void>
    inline bool operator!=(const vec_abs& vector) const;
    template<class _ = void>
    inline bool operator<(const vec_abs& vector) const;
    template<class _ = void>
    inline bool operator>(const vec_abs& vector) const;
    template<class _ = void>
    inline bool operator<=(const vec_abs& vector) const;
    template<class _ = void>
    inline bool operator>=(const vec_abs& vector) const;

    [[nodiscard]] inline void* data() { return pData.data(); };

  private:
    std::array<T, N> pData;
};

typedef vec_abs<float, 2> vec2;
typedef vec_abs<float, 3> vec3;
typedef vec_abs<float, 4> vec4;

typedef vec_abs<double, 2> dvec2;
typedef vec_abs<double, 3> dvec3;
typedef vec_abs<double, 4> dvec4;

typedef vec_abs<int8_t, 2> cvec2;
typedef vec_abs<int8_t, 3> cvec3;
typedef vec_abs<int8_t, 4> cvec4;

typedef vec_abs<u_int8_t, 2> ucvec2;
typedef vec_abs<u_int8_t, 3> ucvec3;
typedef vec_abs<u_int8_t, 4> ucvec4;

typedef vec_abs<int16_t, 2> svec2;
typedef vec_abs<int16_t, 3> svec3;
typedef vec_abs<int16_t, 4> svec4;

typedef vec_abs<u_int16_t, 2> usvec2;
typedef vec_abs<u_int16_t, 3> usvec3;
typedef vec_abs<u_int16_t, 4> usvec4;

typedef vec_abs<int32_t, 2> ivec2;
typedef vec_abs<int32_t, 3> ivec3;
typedef vec_abs<int32_t, 4> ivec4;

typedef vec_abs<u_int32_t, 2> uivec2;
typedef vec_abs<u_int32_t, 3> uivec3;
typedef vec_abs<u_int32_t, 4> uivec4;

typedef uivec2 uvec2;
typedef uivec3 uvec3;
typedef uivec4 uvec4;

typedef vec_abs<int64_t, 2> lvec2;
typedef vec_abs<int64_t, 3> lvec3;
typedef vec_abs<int64_t, 4> lvec4;

typedef vec_abs<u_int64_t, 2> ulvec2;
typedef vec_abs<u_int64_t, 3> ulvec3;
typedef vec_abs<u_int64_t, 4> ulvec4;

template<typename T, size_t N>
vec_abs<T, N>::vec_abs() {
    pData = std::array<T, N>();  // create a new array
}

template<typename T, size_t N>
vec_abs<T, N>::vec_abs(const std::array<T, N> &arr) {
    pData = std::array<T, N>(arr);  // copy the array
}

/*template<typename T, size_t N>
template<typename ...Ts> requires std::conjunction<std::is_convertible<Ts, T>...>::value && (sizeof...(Ts) == N)
vec_abs<T, N>::vec_abs(const Ts &&... values) {
    pData = std::array<T, N>{values...};  // create a new array with the given values
}*/

template<typename T, size_t N>
template<class _> requires (N > 1)
vec_abs<T, N>::vec_abs(const T value) {
    pData = std::array<T, N>();
    pData.fill(value);
}

template<typename T, size_t N>
template<typename... Ts> requires (sizeof...(Ts) == N)
vec_abs<T, N>::vec_abs(const Ts... values) {
    pData = std::array<T, N>{static_cast<T>(values)...};  // create a new array with the given values
}

template<typename T, size_t N>
template<typename TOther>
vec_abs<T, N>::vec_abs(const vec_abs<TOther, N> &vector) {
    pData = std::array<T, N>();
    for (size_t i = 0; i < N; i++) {
        pData[i] = (T) vector[i];
    }
}

#ifdef __unix__
template<typename T, size_t N>
template<typename ...D> requires std::conjunction<std::is_convertible<D, unsigned short>...>::value
auto vec_abs<T, N>::swizzle(D... indices) const -> vec_abs<T, sizeof...(indices)> {
    std::array<T, sizeof...(indices)> array;
    size_t i = 0;
    for (auto index : { indices... }) {
        array[i] = pData[index];
        i++;
    }
    return vec_abs<T, sizeof...(indices)>(array);
}
#endif

template<typename T, size_t N>
template<class _> requires std::is_arithmetic_v<T>
vec_abs<T, N>::operator T() {
    T length;
    for (size_t i = 0; i < N; i++) {
        length += pData[i] * pData[i];
    }
    length = std::sqrt(length);
    return length;
}


template<typename T, size_t N>
template<class _> requires std::is_arithmetic_v<T>
T vec_abs<T, N>::getLength() const {
    T length = 0;
    for (size_t i = 0; i < N; i++) {
        length += pData[i] * pData[i];
    }
    length = std::sqrt(length);
    return length;
}

template<typename T, size_t N>
template<class _> requires std::is_arithmetic_v<T>
vec_abs<T, N> vec_abs<T, N>::operator+(const vec_abs &vector) const {
    vec_abs<T, N> res;
    for (size_t i = 0; i < N; i++) {
        res[i] = pData[i] + vector[i];
    }
    return res;
}

template<typename T, size_t N>
template<class _> requires std::is_arithmetic_v<T>
vec_abs<T, N> vec_abs<T, N>::operator-(const vec_abs &vector) const {
    vec_abs<T, N> res;
    for (size_t i = 0; i < N; i++) {
        res[i] = pData[i] - vector[i];
    }
    return res;
}

/*template<typename T, size_t N>
template<class _> requires std::is_arithmetic_v<T>
const vec_abs &vec_abs<T, N>::operator*(const vec_abs &vector) {
    vec_abs<T, N> res;
    for (size_t i = 0; i < N; i++) {
        res[i] = pData[i] * vector[i];
    }
    return res;
}*/

template<typename T, size_t N>
template<class _> requires std::is_arithmetic_v<T>
vec_abs<T, N> vec_abs<T, N>::operator*(const T &fac) const {
    vec_abs<T, N> res;
    for (size_t i = 0; i < N; i++) {
        res[i] = pData[i] * fac;
    }
    return res;
}

template<typename T, size_t N>
template<class _> requires std::is_arithmetic_v<T>
vec_abs<T, N> vec_abs<T, N>::operator/(const T &fac) const {
    vec_abs<T, N> res;
    for (size_t i = 0; i < N; i++) {
        res[i] = pData[i] / fac;
    }
    return res;
}

template<typename T, size_t N>
template<class _> requires std::is_arithmetic_v<T>
const vec_abs<T, N> &vec_abs<T, N>::operator+=(const vec_abs &vector) {
    for (size_t i = 0; i < N; i++) {
        pData[i] = pData[i] + vector[i];
    }
    return *this;
}

template<typename T, size_t N>
template<class _> requires std::is_arithmetic_v<T>
const vec_abs<T, N> &vec_abs<T, N>::operator-=(const vec_abs &vector) {
    for (size_t i = 0; i < N; i++) {
        pData[i] = pData[i] - vector[i];
    }
    return *this;
}

template<typename T, size_t N>
template<class _> requires std::is_arithmetic_v<T>
const vec_abs<T, N> &vec_abs<T, N>::operator*=(const T &value) {
    for (size_t i = 0; i < N; i++) {
        pData[i] = pData[i] * value;
    }
    return *this;
}

template<typename T, size_t N>
template<class _> requires std::is_arithmetic_v<T>
const vec_abs<T, N> &vec_abs<T, N>::operator/=(const T &value) {
    for (size_t i = 0; i < N; i++) {
        pData[i] = pData[i] / value;
    }
    return *this;
}

template<typename T, size_t N>
template<class _> requires std::is_arithmetic_v<T>
vec_abs<T, N> vec_abs<T, N>::normalize() const {
    vec_abs<T, N> res;
    T length = getLength();
    for (size_t i = 0; i < N; i++) {
        res[i] = pData[i] / length;
    }
    return res;
}

template<typename T, size_t N>
template<class _> requires std::is_arithmetic_v<T>
vec_abs<T, N> vec_abs<T, N>::absolute() const {
    vec_abs<T, N> res;
    for (size_t i = 0; i < N; i++) {
        res[i] = std::abs(pData[i]);
    }
    return res;
}

template<typename T, size_t N>
template<class _>
bool vec_abs<T, N>::operator==(const vec_abs &vector) const {
    bool res = true;
    for (size_t i = 0; i < N; i++)
        res &= pData[i] == vector.pData[i];
    return res;
}

template<typename T, size_t N>
template<class _>
bool vec_abs<T, N>::operator!=(const vec_abs &vector) const {
    for (size_t i = 0; i < N; i++)
        if (pData[i] != vector.pData[i])
            return false;
    return true;
}

template<typename T, size_t N>
template<class _>
bool vec_abs<T, N>::operator<(const vec_abs &vector) const {
    for (size_t i = 0; i < N; i++)
        if (pData[i] >= vector.pData[i])
            return false;
    return true;
}

template<typename T, size_t N>
template<class _>
bool vec_abs<T, N>::operator>(const vec_abs &vector) const {
    for (size_t i = 0; i < N; i++)
        if (pData[i] <= vector.pData[i])
            return false;
    return true;
}

template<typename T, size_t N>
template<class _>
bool vec_abs<T, N>::operator<=(const vec_abs &vector) const {
    for (size_t i = 0; i < N; i++)
        if (pData[i] > vector.pData[i])
            return false;
    return true;
}

template<typename T, size_t N>
template<class _>
bool vec_abs<T, N>::operator>=(const vec_abs &vector) const {
    for (size_t i = 0; i < N; i++)
        if (pData[i] < vector.pData[i])
            return false;
    return true;
}

template<typename T, size_t N> requires std::is_arithmetic_v<T>
T dot(const vec_abs<T, N>& v1, const vec_abs<T, N>& v2) {
    T res = 0;
    for (size_t i = 0; i < N; i++) {
        res += v1[i] * v2[i];
    }
    return res;
}

template<typename T, size_t N> requires std::is_arithmetic_v<T>
vec_abs<T, N> max(const vec_abs<T, N>& v1, const vec_abs<T, N>& v2) {
    vec_abs<T, N> res;
    for (size_t i = 0; i < N; i++) {
        res[i] = std::max(v1[i], v2[i]);
    }
    return res;
}

template<typename T, size_t N> requires std::is_arithmetic_v<T>
vec_abs<T, N> min(const vec_abs<T, N>& v1, const vec_abs<T, N>& v2) {
    vec_abs<T, N> res;
    for (size_t i = 0; i < N; i++) {
        res[i] = std::min(v1[i], v2[i]);
    }
    return res;
}

template<typename T> requires std::is_arithmetic_v<T>
inline T max(T t1, T t2) {
    return std::max(t1, t2);
}

template<typename T> requires std::is_arithmetic_v<T>
inline T min(T t1, T t2) {
    return std::min(t1, t2);
}

template<typename T> requires std::is_arithmetic_v<T>
inline T clamp(T t1, T t2, T t3) {
    return std::clamp(t1, t2, t3);
}

template<typename T, size_t N> requires std::is_arithmetic_v<T>
inline T length (const vec_abs<T, N>& v) {
    return v.getLength();
}

template<typename T> requires std::is_arithmetic_v<T>
T smoothstep(T edge0, T edge1, T x) {
    // Scale, bias and saturate x to 0..1 range
    x = clamp((x - edge0) / (edge1 - edge0), 0.0f, 1.0f);
    // Evaluate polynomial
    return x * x * (3 - 2 * x);
}

template<typename T> requires std::is_arithmetic_v<T>
T mix(T edge0, T edge1, T x) {
    return edge0 * (1 - x) + edge1 * x;
}

template<typename T, size_t N> requires std::is_arithmetic_v<T>
vec_abs<T, N> mix(vec_abs<T, N> edge0, vec_abs<T, N> edge1, T x) {
    return edge0 * (1 - x) + edge1 * x;
}

/*template<typename T, size_t N>
template<class _>
const vec_abs &vec_abs<T, N>::cross(const vec_abs &vec) {
    return <#initializer#>;
}*/

#endif //GRAPHICS_VECTOR_H
