#include "interval.h"

#include <algorithm>

bool interval::nonempty() const { return l < r; }

interval closure(const interval& a, const interval& b) {
    if (a.nonempty() && b.nonempty())
        return {std::min(a.l, b.l), std::max(a.r, b.r)};
    if (a.nonempty()) return a;
    if (b.nonempty()) return b;
    return empty_interval;
}

interval intersection(const interval& a, const interval& b) {
    return {std::max(a.l, b.l), std::min(a.r, b.r)};
}

bool element_of(real x, const interval& s) { return s.l < x && x < s.r; }
