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
    virtual color value(real u, real v, point p) const override;
};

struct lambertian : public material {
    std::shared_ptr<texture> albedo;
    lambertian(std::shared_ptr<texture> albedo) : albedo(albedo) {}
    virtual std::optional<scatter> scattered(const ray& r,
                                             const hit& h) const override;
};

struct diffuse_light : public material {
    std::shared_ptr<texture> emission;
    diffuse_light(std::shared_ptr<texture> emission) : emission(emission) {}
    virtual color emitted(real u, real v, point p) const override;
    virtual std::optional<scatter> scattered(const ray& r,
                                             const hit& h) const override;
};

struct reflective : public material {
    std::shared_ptr<texture> albedo;
    real fuzz;
    reflective(std::shared_ptr<texture> alb, real fuz);
    virtual std::optional<scatter> scattered(const ray& r,
                                             const hit& h) const override;
};

// TODO: everything else

#endif
