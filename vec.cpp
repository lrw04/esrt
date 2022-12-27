#include "vec.h"

#include <cmath>

v3::v3(real val) {
    for (int i = 0; i < 3; i++) d[i] = val;
}

v3::v3(real x, real y, real z) {
    d[0] = x;
    d[1] = y;
    d[2] = z;
}

real& v3::x() { return d[0]; }
real& v3::y() { return d[1]; }
real& v3::z() { return d[2]; }
real& v3::operator[](std::size_t i) { return d[i]; }

real v3::x() const { return d[0]; }
real v3::y() const { return d[1]; }
real v3::z() const { return d[2]; }
real v3::operator[](std::size_t i) const { return d[i]; }

v3 v3::operator+(const v3& rhs) const {
    return {d[0] + rhs[0], d[1] + rhs[1], d[2] + rhs[2]};
}
v3 v3::operator-() const { return {-d[0], -d[1], -d[2]}; }
v3 v3::operator-(const v3& rhs) const { return (*this) + (-rhs); }
v3 v3::operator*(real rhs) const {
    return {rhs * d[0], rhs * d[1], rhs * d[2]};
}
v3 v3::operator/(real rhs) const {
    return {d[0] / rhs, d[1] / rhs, d[2] / rhs};
}
v3 operator*(real lhs, const v3& rhs) {
    return {lhs * rhs[0], lhs * rhs[1], lhs * rhs[2]};
}
real v3::dot(const v3& rhs) const {
    return d[0] * rhs[0] + d[1] * rhs[1] + d[2] * rhs[2];
}
v3 v3::cross(const v3& rhs) const {
    return {d[1] * rhs[2] - d[2] * rhs[1], d[2] * rhs[0] - d[0] * rhs[2],
            d[0] * rhs[1] - d[1] * rhs[2]};
}

v3& v3::operator+=(const v3& rhs) { return *this = (*this) + rhs; }
v3& v3::operator-=(const v3& rhs) { return *this = (*this) - rhs; }
v3& v3::operator*=(real rhs) { return *this = (*this) * rhs; }
v3& v3::operator/=(real rhs) { return *this = (*this) / rhs; }

real v3::l2() const { return this->dot(*this); }
real v3::len() const { return sqrt(this->l2()); }

v3 v3::normalized() const { return (*this) / this->len(); }
v3 v3::make_length(real l) const { return this->normalized() * l; }
