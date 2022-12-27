#include "scene.h"

std::optional<hit> bvh::intersect(ray r, interval t) const {
    return std::optional<hit>();
}

bb bvh::bound() const {
    // TODO
    return bb();
}
