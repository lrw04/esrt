#ifndef HIT_H
#define HIT_H

#include <memory>
#include <optional>

#include "vec.h"

struct material;

struct hit {
    point p;
    v3 n;
    real t, u, v;
    std::shared_ptr<material> mat;
};

std::optional<hit> operator^(const std::optional<hit>& a,
                             const std::optional<hit>& b);

#endif
