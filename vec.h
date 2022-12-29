#ifndef VEC_H
#define VEC_H

#include <cstddef>

using real = float;
const int dim = 3;

struct v3 {
    real d[dim];
    v3(real val = 0);
    v3(real x, real y, real z);
    real& x();
    real& y();
    real& z();
    real& operator[](std::size_t i);
    real x() const;
    real y() const;
    real z() const;
    real operator[](std::size_t i) const;
    v3 operator+(const v3& rhs) const;
    v3 operator-() const;
    v3 operator-(const v3& rhs) const;
    v3 operator*(real rhs) const;
    v3 operator/(real rhs) const;
    real dot(const v3& rhs) const;
    v3 cross(const v3& rhs) const;
    v3& operator+=(const v3& rhs);
    v3& operator-=(const v3& rhs);
    v3& operator*=(real rhs);
    v3& operator/=(real rhs);
    real l2() const;
    real len() const;
    v3 normalized() const;
    v3 make_length(real l) const;
    v3 operator*(const v3& rhs) const;
};

v3 operator*(real lhs, const v3& rhs);

using color = v3;
using point = v3;

const real eps = 1e-5f;
const real pi = acos(-1);

#endif
