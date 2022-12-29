#include "material.h"

#include "rng.h"

color solid_color::value(real u, real v, point p) const { return c; }

std::optional<scatter> lambertian::scattered(const ray& r, const hit& h) const {
    auto dir = h.n.normalized() + uniform_unit_sphere();
    if (dir.len() < eps) dir = h.n.normalized();
    scatter sc;
    sc.attenuation = albedo->value(h.u, h.v, h.p);
    sc.out = ray(h.p, dir);
    return sc;
}
