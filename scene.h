#ifndef SCENE_H
#define SCENE_H

#include <optional>

#include "bb.h"
#include "hit.h"
#include "interval.h"
#include "ray.h"
#include "vec.h"

struct object {
    virtual std::optional<hit> intersect(ray r, interval t) const = 0;
    virtual bb bound() const = 0;
};

struct bvh : public object {
    virtual std::optional<hit> intersect(ray r, interval t) const override;
    virtual bb bound() const override;
};

#endif
