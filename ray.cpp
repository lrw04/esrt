#include "ray.h"

point ray::operator()(real t) const { return o + t * d; }
