#ifndef BB_H
#define BB_H

#include <cstddef>
#include <optional>

#include "hit.h"
#include "interval.h"
#include "ray.h"

struct bb {
    interval d[dim];
    bool nonempty() const;
    interval& operator[](std::size_t i);
    interval operator[](std::size_t i) const;
    std::optional<hit> intersect(ray r, interval t) const;
};

bb closure(const bb& a, const bb& b);
bb intersection(const bb& a, const bb& b);

const bb r3 = {reals, reals, reals};
const bb empty_box = {empty_interval, empty_interval, empty_interval};

#endif
