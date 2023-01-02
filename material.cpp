#include "material.h"

#include "rng.h"

color solid_color::value(real u, real v, const point& p) const { return c; }

std::optional<scatter> lambertian::scattered(const ray& r, const hit& h) const {
    auto dir = h.n + uniform_unit_sphere();
    if (dir.len() < eps) dir = h.n;
    scatter sc;
    sc.attenuation = albedo->value(h.u, h.v, h.p);
    sc.out = ray(h.p, dir);
    return sc;
}

color diffuse_light::emitted(real u, real v, const point& p) const {
    return emission->value(u, v, p);
}

std::optional<scatter> diffuse_light::scattered(const ray& r,
                                                const hit& h) const {
    return std::nullopt;
}

reflective::reflective(std::shared_ptr<texture> alb, real fuz) {
    albedo = alb;
    fuzz = std::min(fuz, (real)1);
}

std::optional<scatter> reflective::scattered(const ray& r, const hit& h) const {
    scatter sc;
    sc.attenuation = albedo->value(h.u, h.v, h.p);
    sc.out = ray(h.p, r.d - 2 * (r.d.dot(h.n)) * h.n);
    return sc;
}
