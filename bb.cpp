#include "bb.h"

#include <algorithm>

bool bb::nonempty() const {
    for (int i = 0; i < dim; i++) {
        if (!d[i].nonempty()) return false;
    }
    return true;
}

interval& bb::operator[](std::size_t i) { return d[i]; }
interval bb::operator[](std::size_t i) const { return d[i]; }

std::optional<hit> bb::intersect(ray r, interval t) const {
    interval t_in = {eps, INFINITY};
    for (int i = 0; i < dim; i++) {
        // r.o[i] + x * r.d[i] = d[i].l
        interval cur = {(d[i].l - r.o[i]) / r.d[i], (d[i].r - r.o[i]) / r.d[i]};
        if (!cur.nonempty()) std::swap(cur.l, cur.r);
        t_in = intersection(t_in, cur);
    }
    if (t_in.nonempty()) return {{r(t_in.l), v3(), t_in.l, 0, 0}};
    return std::nullopt;
}

bb closure(const bb& a, const bb& b) {
    bb out;
    for (int i = 0; i < dim; i++) out[i] = closure(a[i], b[i]);
    return out;
}

bb intersection(const bb& a, const bb& b) {
    bb out;
    for (int i = 0; i < dim; i++) out[i] = intersection(a[i], b[i]);
    return out;
}
