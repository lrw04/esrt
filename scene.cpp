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
    std::sort(a.begin(), a.end(), [axis](std::shared_ptr<object> a, std::shared_ptr<object> b) {
        return a->bound()[axis].l < b->bound()[axis].l;
    });
    auto middle = uniform_int(0, a.size() - 1);
    std::vector<std::shared_ptr<object>> l, r;
    for (std::size_t i = 0; i < middle; i++) l.push_back(a[i]);
    for (std::size_t i = middle; i < a.size(); i++) r.push_back(a[i]);
    lc = std::make_shared<bvh>(l, (axis + 1) % dim);
    rc = std::make_shared<bvh>(r, (axis + 2) % dim);
    box = closure(lc->bound(), rc->bound());
}

std::optional<hit> bvh::intersect(const ray& r, const interval& t) const {
    if (box.intersect(r, t))
        return lc->intersect(r, t) ^ rc->intersect(r, t);
    return std::nullopt;
}

bb bvh::bound() const { return box; }

std::optional<hit> empty::intersect(const ray& r, const interval& t) const {
    return std::nullopt;
}

bb empty::bound() const { return empty_box; }

triangle::triangle(point a, point b, point c, std::shared_ptr<material> m) {
    v[0] = a;
    v[1] = b;
    v[2] = c;
    mat = m;
}

std::optional<hit> triangle::intersect(const ray& r, const interval& t) const {
    auto a = v[0][0] - v[1][0], d = v[0][0] - v[2][0], g = r.d[0];
    auto b = v[0][1] - v[1][1], e = v[0][1] - v[2][1], h = r.d[1];
    auto c = v[0][2] - v[1][2], f = v[0][2] - v[2][2], i = r.d[2];
    auto j = v[0][0] - r.o[0], k = v[0][1] - r.o[1], l = v[0][2] - r.o[2];

    auto ei_hf = e * i - h * f, gf_di = g * f - d * i, dh_eg = d * h - e * g;
    auto ak_jb = a * k - j * b, jc_al = j * c - a * l, bl_kc = b * l - k * c;
    auto m = a * ei_hf + b * gf_di + c * dh_eg;
    if (abs(m) < eps) return std::nullopt;

    auto beta = (j * ei_hf + k * gf_di + l * dh_eg) / m;
    auto gamma = (i * ak_jb + h * jc_al + g * bl_kc) / m;
    auto t_hit = -(f * ak_jb + e * jc_al + d * bl_kc) / m;

    if (!element_of(t_hit, t)) return std::nullopt;
    if (beta > 0 && gamma > 0 && beta + gamma < 1) {
        hit h;
        h.mat = mat;
        h.n = (v[0] - v[1]).cross(v[1] - v[2]).normalized();
        if (h.n.dot(r.d) > 0) h.n *= -1;
        h.t = t_hit;
        h.p = r(t_hit);
        h.u = beta;
        h.v = gamma;
        return h;
    }
    return std::nullopt;
}

bb triangle::bound() const {
    bb box = r3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < dim; j++) {
            box[j].l = std::min(box[j].l, v[i][j]);
            box[j].r = std::max(box[j].r, v[i][j]);
        }
    }
    return box;
}

sphere::sphere(point o_, real r_, std::shared_ptr<material> m) {
    o = o_;
    rd = r_;
    mat = m;
}

std::optional<hit> sphere::intersect(const ray& r, const interval& t) const {
    auto dif = r.o - o;
    auto a = r.d.l2(), b = 2 * r.d.dot(dif), c = dif.l2() - rd * rd;
    auto delta = b * b - 4 * a * c;
    if (delta <= 0) return std::nullopt;
    real t_hit = INFINITY;
    auto mid = -b / (2 * a);
    auto d = sqrt(delta) / (2 * a);
    for (int sign = -1; sign <= 1; sign += 2) {
        auto t_cur = mid + sign * d;
        if (element_of(t_cur, t)) t_hit = std::min(t_hit, t_cur);
    }
    if (t_hit == INFINITY) return std::nullopt;
    hit h;
    h.mat = mat;
    h.n = (r(t_hit) - o).normalized();
    h.p = r(t_hit);
    h.t = t_hit;
    h.u = (atan2((h.p - o)[2], (h.p - o)[0]) + pi) / (2 * pi);
    h.v = (asin((h.p - o)[1]) + pi / 2) / pi;
    return h;
}

bb sphere::bound() const { return bb(o - v3(rd, rd, rd), o + v3(rd, rd, rd)); }
