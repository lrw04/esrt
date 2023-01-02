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

bool bb::intersect(ray r, interval t) const {
    if (!nonempty()) return false;
    for (int i = 0; i < dim; i++) {
        // r.o[i] + x * r.d[i] = d[i].l
        if (abs(r.d[i]) < eps) {
            if (abs(d[i].l - r.o[i]) < eps) continue;
            return false;
        }
        interval cur = {(d[i].l - r.o[i]) / r.d[i], (d[i].r - r.o[i]) / r.d[i]};
        if (!cur.nonempty()) std::swap(cur.l, cur.r);
        t = intersection(t, cur);
    }
    if (t.nonempty()) return true;
    return false;
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

bool element_of(const v3& v, const bb& b) {
    for (int i = 0; i < dim; i++) {
        if (!element_of(v[i], b[i])) return false;
    }
    return true;
}
