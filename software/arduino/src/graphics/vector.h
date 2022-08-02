//
// Created by RedNicStone for graphics on 01/08/22.
//

#ifndef GRAPHICS_VECTOR_H
#define GRAPHICS_VECTOR_H

#include <array>
#include <cstddef>
#include <type_traits>
#include <cmath>

template<typename T, typename ...Ts>
constexpr bool all_convertible_to() {
    return (std::is_convertible_v<T, Ts> && ...);
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

    template<typename ...Ts> requires // only compile if:
    std::conjunction<std::is_convertible<Ts, T>...>::value &&  // all can be converted to T
        (sizeof...(Ts) == N)  // there are N arguments
    explicit vec_abs(const Ts... values);  // construct from multiple arguments

    template<typename ...Ts> requires // only compile if:
    std::conjunction<std::is_convertible<Ts, T>...>::value &&  // all can be converted to T
    (sizeof...(Ts) == N)  // there are N arguments
    explicit vec_abs(const vec_abs& vector, const Ts&&... values_post);  // construct from multiple arguments

    template<typename ...Ts> requires // only compile if:
    std::conjunction<std::is_convertible<Ts, T>...>::value &&  // all can be converted to T
    (sizeof...(Ts) == N)  // there are N arguments
    explicit vec_abs(const Ts&&... values_pre, const vec_abs& vector);  // construct from multiple arguments

    template<typename ...Ts> requires // only compile if:
    std::conjunction<std::is_convertible<Ts, T>...>::value &&  // all can be converted to T
    (sizeof...(Ts) == N)  // there are N arguments
    explicit vec_abs(const Ts&&... values_pre, const vec_abs& vector, const Ts&&... values_post);  // construct from multiple arguments


    // Getters

    T operator[](int index) const { return data[index]; };
    T& operator[](int index) { return data[index]; };


    template<class _ = void> requires (N >= 1)  // If there are enough elements
    const T& x() const { return data[0]; };  // get X

    template<class _ = void> requires (N >= 2)  // If there are enough elements
    const T& y() const { return data[1]; };  // get Y

    template<class _ = void> requires (N >= 3)  // If there are enough elements
    const T& z() const { return data[2]; };  // get Z

    template<class _ = void> requires (N >= 4)  // If there are enough elements
    const T& w() const { return data[3]; };  // get W

    template<class _ = void> requires (N >= 1)  // If there are enough elements
    const T& r() const { return data[0]; };  // get R

    template<class _ = void> requires (N >= 2)  // If there are enough elements
    const T& g() const { return data[1]; };  // get G

    template<class _ = void> requires (N >= 3)  // If there are enough elements
    const T& b() const { return data[2]; };  // get B

    template<class _ = void> requires (N >= 4)  // If there are enough elements
    const T& a() const { return data[3]; };  // get A

    template<typename ...D> requires // only compile if:
    std::conjunction<std::is_convertible<D, unsigned short>...>::value  // all can be converted to unsigned short
    const vec_abs<T, N>& swizzle(D... indices);

    template<class _ = void> requires std::is_arithmetic_v<T>
    explicit operator T();

    template<class _ = void> requires std::is_arithmetic_v<T>
    const T& getLength();


    //actual functions

    template<class _ = void> requires std::is_arithmetic_v<T>
    const vec_abs& operator+(const vec_abs<T, N>& vector);
    template<class _ = void> requires std::is_arithmetic_v<T>
    const vec_abs& operator-(const vec_abs<T, N>& vector);
    //template<class _ = void> requires std::is_arithmetic_v<T>
    //const vec_abs& operator*(const vec_abs<T, N>& vector);  // cross product
    template<class _ = void> requires std::is_arithmetic_v<T>
    const vec_abs& operator*(const T& fac);  // scalar product

    template<class _ = void> requires std::is_arithmetic_v<T>
    const vec_abs& operator+=(const vec_abs& vector);
    template<class _ = void> requires std::is_arithmetic_v<T>
    const vec_abs& operator-=(const vec_abs& vector);
    //template<class _ = void> requires std::is_arithmetic_v<T>
    //const vec_abs& operator*=(const vec_abs& vector);
    template<class _ = void> requires std::is_arithmetic_v<T>
    const vec_abs& operator*=(const T& vector);

    template<class _ = void> requires std::is_arithmetic_v<T>
    const vec_abs& normalize();
    template<class _ = void> requires std::is_arithmetic_v<T>
    const vec_abs& dot(const T& fac);
    //template<class _ = void> requires std::is_arithmetic_v<T>
    //const vec_abs& cross(const vec_abs& vec);

  private:
    std::array<T, N> data;
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
    data = std::array<T, N>();  // create a new array
}

template<typename T, size_t N>
vec_abs<T, N>::vec_abs(const std::array<T, N> &arr) {
    data = std::array<T, N>(arr);  // copy the array
}

/*template<typename T, size_t N>
template<typename ...Ts> requires std::conjunction<std::is_convertible<Ts, T>...>::value && (sizeof...(Ts) == N)
vec_abs<T, N>::vec_abs(const Ts &&... values) {
    data = std::array<T, N>{values...};  // create a new array with the given values
}*/

template<typename T, size_t N>
template<typename... Ts> requires std::conjunction<std::is_convertible<Ts, T>...>::value && (sizeof...(Ts) == N)
vec_abs<T, N>::vec_abs(const Ts... values) {
    data = std::array<T, N>{values...};  // create a new array with the given values
}

template<typename T, size_t N>
template<typename... Ts> requires std::conjunction<std::is_convertible<Ts, T>...>::value && (sizeof...(Ts) == N)
vec_abs<T, N>::vec_abs(const vec_abs &vector, const Ts &&... values_post) {

}

template<typename T, size_t N>
template<typename... Ts> requires std::conjunction<std::is_convertible<Ts, T>...>::value && (sizeof...(Ts) == N)
vec_abs<T, N>::vec_abs(const Ts &&... values_pre, const vec_abs &vector) {

}

template<typename T, size_t N>
template<typename... Ts> requires std::conjunction<std::is_convertible<Ts, T>...>::value && (sizeof...(Ts) == N)
vec_abs<T, N>::vec_abs(const Ts &&... values_pre, const vec_abs &vector, const Ts &&... values_post) {

}

template<typename T, size_t N>
template<typename ...D> requires std::conjunction<std::is_convertible<D, unsigned short>...>::value
const vec_abs<T, N>& vec_abs<T, N>::swizzle(D... indices) {
    std::array<T, sizeof...(indices)> array;
    size_t i = 0;
    for (auto index : { indices... }) {
        array[i] = data[index];
        i++;
    }
    return vec_abs<T, sizeof...(indices)>(array);
}

template<typename T, size_t N>
template<class _> requires std::is_arithmetic_v<T>
vec_abs<T, N>::operator T() {
    T length;
    for (size_t i = 0; i < N; i++) {
        length += data[i] * data[i];
    }
    length = std::sqrt(length);
    return length;
}


template<typename T, size_t N>
template<class _> requires std::is_arithmetic_v<T>
const T &vec_abs<T, N>::getLength() {
    T length;
    for (size_t i = 0; i < N; i++) {
        length += data[i] * data[i];
    }
    length = std::sqrt(length);
    return length;
}

template<typename T, size_t N>
template<class _> requires std::is_arithmetic_v<T>
const vec_abs<T, N> &vec_abs<T, N>::operator+(const vec_abs &vector) {
    vec_abs<T, N> res;
    for (size_t i = 0; i < N; i++) {
        res[i] = data[i] + vector[i];
    }
    return res;
}

template<typename T, size_t N>
template<class _> requires std::is_arithmetic_v<T>
const vec_abs<T, N> &vec_abs<T, N>::operator-(const vec_abs &vector) {
    vec_abs<T, N> res;
    for (size_t i = 0; i < N; i++) {
        res[i] = data[i] - vector[i];
    }
    return res;
}

/*template<typename T, size_t N>
template<class _> requires std::is_arithmetic_v<T>
const vec_abs &vec_abs<T, N>::operator*(const vec_abs &vector) {
    vec_abs<T, N> res;
    for (size_t i = 0; i < N; i++) {
        res[i] = data[i] * vector[i];
    }
    return res;
}*/

template<typename T, size_t N>
template<class _> requires std::is_arithmetic_v<T>
const vec_abs<T, N> &vec_abs<T, N>::operator*(const T &fac) {
    vec_abs<T, N> res;
    for (size_t i = 0; i < N; i++) {
        res[i] = data[i] * fac;
    }
    return res;
}

template<typename T, size_t N>
template<class _> requires std::is_arithmetic_v<T>
const vec_abs<T, N> &vec_abs<T, N>::operator+=(const vec_abs &vector) {
    for (size_t i = 0; i < N; i++) {
        data[i] = data[i] + vector[i];
    }
    return *this;
}

template<typename T, size_t N>
template<class _> requires std::is_arithmetic_v<T>
const vec_abs<T, N> &vec_abs<T, N>::operator-=(const vec_abs &vector) {
    for (size_t i = 0; i < N; i++) {
        data[i] = data[i] - vector[i];
    }
    return *this;
}

template<typename T, size_t N>
template<class _> requires std::is_arithmetic_v<T>
const vec_abs<T, N> &vec_abs<T, N>::operator*=(const T &vector) {
    for (size_t i = 0; i < N; i++) {
        data[i] = data[i] * vector[i];
    }
    return *this;
}

template<typename T, size_t N>
template<class _> requires std::is_arithmetic_v<T>
const vec_abs<T, N> &vec_abs<T, N>::normalize() {
    vec_abs<T, N> res;
    T length = this;
    for (size_t i = 0; i < N; i++) {
        res[i] = data[i] / length;
    }
    return res;
}

template<typename T, size_t N>
template<class _> requires std::is_arithmetic_v<T>
const vec_abs<T, N> &vec_abs<T, N>::dot(const T &fac) {
    vec_abs<T, N> res;
    for (size_t i = 0; i < N; i++) {
        res[i] = data[i] * fac;
    }
    return res;
}

/*template<typename T, size_t N>
template<class _>
const vec_abs &vec_abs<T, N>::cross(const vec_abs &vec) {
    return <#initializer#>;
}*/

#endif //GRAPHICS_VECTOR_H
