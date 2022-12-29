#include "bb.h"

#include <algorithm>

bb::bb(interval a, interval b, interval c) {
    d[0] = a;
    d[1] = b;
    d[2] = c;
}

bb::bb(point a, point b) {
    for (int i = 0; i < dim; i++) d[i] = {a[i], b[i]};
}

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
    t_in = intersection(t_in, t);
    for (int i = 0; i < dim; i++) {
        // r.o[i] + x * r.d[i] = d[i].l
        if (abs(r.d[i]) < eps) {
            if (abs(d[i].l - r.o[i]) < eps) continue;
            return std::nullopt;
        }
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

bool element_of(v3 v, const bb& b) {
    for (int i = 0; i < dim; i++) {
        if (!element_of(v[i], b[i])) return false;
    }
    return true;
}
