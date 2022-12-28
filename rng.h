#ifndef RNG_H
#define RNG_H

#include <cinttypes>

#include "vec.h"

real uniform_real(real l = 0, real r = 1);
uint64_t uniform_int(uint64_t l = 0, uint64_t r = 1);
int64_t uniform_int(int64_t l = 0, int64_t r = 1);
bool event_with_probability(real p);

const int64_t seed = 0;

#endif
