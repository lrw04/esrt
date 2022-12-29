#ifndef SCENE_H
#define SCENE_H

#include <memory>
#include <optional>
#include <vector>

#include "bb.h"
#include "hit.h"
#include "interval.h"
#include "ray.h"
#include "vec.h"
#include "material.h"

struct object {
    virtual std::optional<hit> intersect(ray r, interval t) const = 0;
    virtual bb bound() const = 0;
};

struct empty : public object {
    virtual std::optional<hit> intersect(ray r, interval t) const override;
    virtual bb bound() const override;
};

struct bvh : public object {
    std::shared_ptr<object> lc, rc;
    bb box;
    bvh(const std::vector<std::shared_ptr<object>>& objects, int axis = 0);
    virtual std::optional<hit> intersect(ray r, interval t) const override;
    virtual bb bound() const override;
};

struct triangle : public object {
    point v[3];
    std::shared_ptr<material> mat;
    triangle(point a, point b, point c, std::shared_ptr<material> m);
    virtual std::optional<hit> intersect(ray r, interval t) const override;
    virtual bb bound() const override;
};

struct sphere : public object {
    point o;
    real rd;
    std::shared_ptr<material> mat;
    sphere(point o_, real r_, std::shared_ptr<material> m);
    virtual std::optional<hit> intersect(ray r, interval t) const override;
    virtual bb bound() const override;
};

#endif
