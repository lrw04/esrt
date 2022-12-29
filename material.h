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

struct texture {
    virtual color value(real u, real v, point p) const = 0;
};

struct material {
    virtual color emitted(real u, real v, point p) const { return {}; }
    virtual std::optional<scatter> scattered(const ray& r,
                                             const hit& h) const = 0;
};

struct solid_color : public texture {
    color c;
    solid_color(const color& c) : c(c) {}
    virtual color value(real u, real v, point p) const;
};

struct lambertian : public material {
    std::shared_ptr<texture> albedo;
    lambertian(std::shared_ptr<texture> albedo) : albedo(albedo) {}
    virtual color emitted(real u, real v, point p) const { return {}; }
    virtual std::optional<scatter> scattered(const ray& r,
                                             const hit& h) const = 0;
};

// TODO: everything else

#endif
