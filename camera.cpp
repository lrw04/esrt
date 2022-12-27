#include "camera.h"

#include <cmath>

camera::camera(point o_, v3 up_, v3 dir_, real aspect_ratio_, real fov_) {
    o = o_;
    up = up_;
    dir = dir_;
    aspect_ratio = aspect_ratio_;
    fov = fov_;

    const real f = 1, w = 2 * tan(fov / 2), h = w / aspect_ratio;

    difx = dir.cross(up).make_length(w);
    dify = dir.cross(difx).make_length(h);
    luc = dir.normalized() - difx / 2 - dify / 2;
}

ray camera::operator()(real y, real x) const {
    return {o, luc + y * dify + x * difx};
}
