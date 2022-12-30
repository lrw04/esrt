#ifndef VEC_H
#define VEC_H

#include <cmath>
#include <cstddef>

using real = double;
const int dim = 3;

struct v3 {
    real d[dim];
    v3(real val = 0) {
        for (int i = 0; i < dim; i++) d[i] = val;
    }
    v3(real x, real y, real z) {
        d[0] = x;
        d[1] = y;
        d[2] = z;
    }
    real& x() { return d[0]; }
    real& y() { return d[1]; }
    real& z() { return d[2]; }
    real& operator[](std::size_t i) { return d[i]; }
    real x() const { return d[0]; }
    real y() const { return d[1]; }
    real z() const { return d[2]; }
    real operator[](std::size_t i) const { return d[i]; }
    v3 operator+(const v3& rhs) const {
        return {d[0] + rhs[0], d[1] + rhs[1], d[2] + rhs[2]};
    }
    v3 operator-() const { return {-d[0], -d[1], -d[2]}; }
    v3 operator-(const v3& rhs) const { return (*this) + (-rhs); }
    v3 operator*(real rhs) const {
        return {rhs * d[0], rhs * d[1], rhs * d[2]};
    }
    v3 operator/(real rhs) const {
        return {d[0] / rhs, d[1] / rhs, d[2] / rhs};
    }
    real dot(const v3& rhs) const {
        return d[0] * rhs[0] + d[1] * rhs[1] + d[2] * rhs[2];
    }
    v3 cross(const v3& rhs) const {
        return {d[1] * rhs[2] - d[2] * rhs[1], d[2] * rhs[0] - d[0] * rhs[2],
                d[0] * rhs[1] - d[1] * rhs[0]};
    }
    v3& operator+=(const v3& rhs) { return *this = (*this) + rhs; }
    v3& operator-=(const v3& rhs) { return *this = (*this) - rhs; }
    v3& operator*=(real rhs) { return *this = (*this) * rhs; }
    v3& operator/=(real rhs) { return *this = (*this) / rhs; }
    real l2() const { return this->dot(*this); }
    real len() const { return sqrt(this->l2()); }
    v3 normalized() const { return (*this) / this->len(); }
    v3 make_length(real l) const { return this->normalized() * l; }
    v3 operator*(const v3& rhs) const {
        return {d[0] * rhs[0], d[1] * rhs[1], d[2] * rhs[2]};
    }
};

v3 operator*(real lhs, const v3& rhs);

using color = v3;
using point = v3;

const real eps = 1e-5f;
const real pi = acosf(-1);

#endif
