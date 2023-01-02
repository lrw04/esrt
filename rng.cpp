#include "rng.h"

#include <random>

real uniform_real(real l, real r) {
    static thread_local std::mt19937_64 rng(seed);
    return std::uniform_real_distribution<real>(l, r)(rng);
}

uint64_t uniform_int(uint64_t l, uint64_t r) {
    static thread_local std::mt19937_64 rng(seed);
    return std::uniform_int_distribution<uint64_t>(l, r)(rng);
}

int64_t uniform_int(int64_t l, int64_t r) {
    static thread_local std::mt19937_64 rng(seed);
    return std::uniform_int_distribution<int64_t>(l, r)(rng);
}

bool event_with_probability(real p) { return uniform_real() < p; }

v3 uniform_unit_sphere() {
    real theta = uniform_real(0, 2 * pi), phi = acos(uniform_real(-1, 1));
    return {cos(theta) * sin(phi), cos(phi), sin(theta) * sin(phi)};
}

v3 uniform_in_unit_sphere() {
    return uniform_unit_sphere() * pow(uniform_real(), 1.0 / 3.0);
}
