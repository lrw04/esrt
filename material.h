#ifndef MATERIAL_H
#define MATERIAL_H

#include <optional>

#include "hit.h"
#include "ray.h"
#include "vec.h"

struct scatter {
    ray out;
    color attenuation;
};

struct material {
    virtual color emitted(real u, real v, point p) const { return {}; }
    virtual std::optional<scatter> scattered(const ray& r,
                                             const hit& h) const = 0;
};

// TODO: everything

#endif
