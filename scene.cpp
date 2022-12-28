#include "scene.h"

#include <algorithm>

#include "rng.h"

bvh::bvh(const std::vector<std::shared_ptr<object>>& objects, int axis) {
    if (objects.empty()) {
        lc = rc = std::make_shared<empty>();
        box = empty_box;
        return;
    }
    if (objects.size() == 1) {
        lc = std::make_shared<empty>();
        rc = objects[0];
        box = rc->bound();
        return;
    }
    if (objects.size() == 2) {
        lc = objects[0];
        rc = objects[1];
        box = closure(lc->bound(), rc->bound());
        return;
    }
    auto a = objects;
    auto pivot = uniform_int((size_t)0, a.size() - 1);
    real val = a[pivot]->bound()[axis].l;
    auto middle = std::partition(a.begin(), a.end(),
                                 [val, axis](std::shared_ptr<object> p) {
                                     return p->bound()[axis].l < val;
                                 });
    std::vector<std::shared_ptr<object>> l, r;
    for (auto it = a.begin(); it != middle; it++) l.push_back(*it);
    for (auto it = middle; it != a.end(); it++) r.push_back(*it);
    lc = std::make_shared<bvh>(l, (axis + 1) % dim);
    rc = std::make_shared<bvh>(r, (axis + 2) % dim);
    box = closure(lc->bound(), rc->bound());
}

std::optional<hit> bvh::intersect(ray r, interval t) const {
    if (box.intersect(r, t).has_value())
        return lc->intersect(r, t) ^ rc->intersect(r, t);
    return std::nullopt;
}

bb bvh::bound() const { return box; }

std::optional<hit> empty::intersect(ray r, interval t) const {
    return std::nullopt;
}

bb empty::bound() const { return empty_box; }
